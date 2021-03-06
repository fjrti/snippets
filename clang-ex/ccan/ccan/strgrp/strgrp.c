/*
    Group similar strings
    Copyright (C) 2014  Andrew Jeffery <andrew@aj.id.au>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "ccan/darray/darray.h"
#include "ccan/stringmap/stringmap.h"
#include "ccan/tal/tal.h"
#include "ccan/tal/str/str.h"
#include "strgrp.h"
#include "config.h"

typedef darray(struct strgrp_grp *) darray_grp;
typedef darray(struct strgrp_item *) darray_item;

typedef stringmap(struct strgrp_grp *) stringmap_grp;

struct grp_score {
    struct strgrp_grp *grp;
    double score;
};

typedef darray(struct grp_score *) darray_score;

struct strgrp {
    double threshold;
    stringmap_grp known;
    unsigned int n_grps;
    darray_grp grps;
    struct grp_score *scores;
};

struct strgrp_iter {
    const struct strgrp *ctx;
    int i;
};

struct strgrp_grp {
    const char *key;
    size_t key_len;
    darray_item items;
    int32_t n_items;
};

struct strgrp_grp_iter {
    const struct strgrp_grp *grp;
    int i;
};

struct strgrp_item {
    const char *key;
    void *value;
};

#define ROWS 2

static inline int cmi(int i, int j) {
    return ROWS * j + i;
}

static inline int16_t
lcs(const char *const a, const char *const b) {
    const int lb = strlen(b);
    const int lbp1 = lb + 1;
    int16_t *const lookup = calloc(ROWS * lbp1, sizeof(int16_t));
    if (!lookup) {
        return -1;
    }
    int ia, ib;
    for (ia = (strlen(a) - 1); ia >= 0; ia--) {
        const char iav = a[ia];
        for (ib = lb - 1; ib >= 0; ib--) {
            const char ibv = b[ib];
            const int ial = (ia + 1) & 1; // ia last
            const int iac = ia & 1; // ia current
            const int ibl = ib + 1; // ib last
            // don't need separate "ib current" as it's just ib
            if (iav == ibv) {
                lookup[cmi(iac, ib)] = 1 + lookup[cmi(ial, ibl)];
            } else {
                const int16_t valb = lookup[cmi(ial, ib)];
                const int16_t vabl = lookup[cmi(iac, ibl)];
                lookup[cmi(iac, ib)] = (valb > vabl) ? valb : vabl;
            }
        }
    }
    int16_t result = lookup[0];
    free(lookup);
    return result;
}

#undef ROWS

static inline double
nlcs(const char *const a, const char *const b) {
    const double lcss = lcs(a, b);
    return 2 * lcss / (strlen(a) + strlen(b));
}

static bool
should_grp_score(const struct strgrp *const ctx,
        const struct strgrp_grp *const grp, const char *const str) {
    const size_t strl = strlen(str);
    const size_t keyl = grp->key_len;
    double sr =  strl / keyl;
    if (1 < sr) {
        sr = 1 / sr;
    }
    return ctx->threshold <= sr;
}

static inline double
grp_score(const struct strgrp_grp *const grp, const char *const str) {
    return nlcs(grp->key, str);
}

static struct strgrp_item *
new_item(tal_t *const tctx, const char *const str, void *const data) {
    struct strgrp_item *i = talz(tctx, struct strgrp_item);
    if (!i) {
        return NULL;
    }
    i->key = tal_strdup(i, str);
    i->value = data;
    return i;
}

static bool
add_item(struct strgrp_grp *const ctx, const char *const str,
        void *const data) {
    struct strgrp_item *i = new_item(ctx, str, data);
    if (!i) {
        return false;
    }
    darray_push(ctx->items, i);
    ctx->n_items++;
    return true;
}

static void
free_grp(struct strgrp_grp *grp) {
    darray_free(grp->items);
}

static struct strgrp_grp *
new_grp(tal_t *const tctx, const char *const str, void *const data) {
    struct strgrp_grp *b = talz(tctx, struct strgrp_grp);
    if (!b) {
        return NULL;
    }
    b->key = tal_strdup(b, str);
    b->key_len = strlen(str);
    b->n_items = 0;
    darray_init(b->items);
    tal_add_destructor(b, free_grp);
    if (!add_item(b, str, data)) {
        return tal_free(b);
    }
    return b;
}

static struct strgrp_grp *
add_grp(struct strgrp *const ctx, const char *const str,
        void *const data) {
    struct strgrp_grp *b = new_grp(ctx, str, data);
    if (!b) {
        return NULL;
    }
    darray_push(ctx->grps, b);
    ctx->n_grps++;
    if (ctx->scores) {
        if (!tal_resize(&ctx->scores, ctx->n_grps)) {
            return NULL;
        }
    } else {
        ctx->scores = tal_arr(ctx, struct grp_score, ctx->n_grps);
        if (!ctx->scores) {
            return NULL;
        }
    }
    return b;
}

struct strgrp *
strgrp_new(const double threshold) {
    struct strgrp *ctx = talz(NULL, struct strgrp);
    ctx->threshold = threshold;
    stringmap_init(ctx->known, NULL);
    darray_init(ctx->grps);
    return ctx;
}

static inline void
cache(struct strgrp *const ctx, struct strgrp_grp *const grp,
        const char *const str) {
    *(stringmap_enter(ctx->known, str)) = grp;
}

static struct strgrp_grp *
grp_for(struct strgrp *const ctx, const char *const str) {
    if (!ctx->n_grps) {
        return NULL;
    }
    {
        struct strgrp_grp **const grp = stringmap_lookup(ctx->known, str);
        if (grp) {
            return *grp;
        }
    }
    int i;
// Keep ccanlint happy in reduced feature mode
#if HAVE_OPENMP
    #pragma omp parallel for schedule(dynamic)
#endif
    for (i = 0; i < ctx->n_grps; i++) {
        ctx->scores[i].grp = darray_item(ctx->grps, i);
        const bool ss = should_grp_score(ctx, ctx->scores[i].grp, str);
        ctx->scores[i].score = ss ? grp_score(ctx->scores[i].grp, str) : 0;
    }
    struct grp_score *max = NULL;
    for (i = 0; i < ctx->n_grps; i++) {
        if (!max || ctx->scores[i].score > max->score) {
            max = &(ctx->scores[i]);
        }
    }
    return (max && max->score >= ctx->threshold) ? max->grp : NULL;
}

const struct strgrp_grp *
strgrp_grp_for(struct strgrp *const ctx, const char *const str) {
    return grp_for(ctx, str);
}

const struct strgrp_grp *
strgrp_add(struct strgrp *const ctx, const char *const str,
        void *const data) {
    bool inserted = false;
    struct strgrp_grp *pick = grp_for(ctx, str);
    if (pick) {
        inserted = add_item(pick, str, data);
    } else {
        pick = add_grp(ctx, str, data);
        inserted = (NULL != pick);
    }
    if (inserted) {
        assert(NULL != pick);
        cache(ctx, pick, str);
    }
    return pick;
}

struct strgrp_iter *
strgrp_iter_new(struct strgrp *const ctx) {
    struct strgrp_iter *iter = talz(ctx, struct strgrp_iter);
    if (!iter) {
        return NULL;
    }
    iter->ctx = ctx;
    iter->i = 0;
    return iter;
}

const struct strgrp_grp *
strgrp_iter_next(struct strgrp_iter *const iter) {
    return (iter->ctx->n_grps == iter->i) ?
        NULL : darray_item(iter->ctx->grps, iter->i++);
}

void
strgrp_iter_free(struct strgrp_iter *const iter) {
    tal_free(iter);
}

struct strgrp_grp_iter *
strgrp_grp_iter_new(const struct strgrp_grp *const grp) {
    struct strgrp_grp_iter *iter = talz(grp, struct strgrp_grp_iter);
    if (!iter) {
        return NULL;
    }
    iter->grp = grp;
    iter->i = 0;
    return iter;
}

const struct strgrp_item *
strgrp_grp_iter_next(struct strgrp_grp_iter *const iter) {
    return (iter->grp->n_items == iter->i) ?
        NULL : darray_item(iter->grp->items, iter->i++);
}

void
strgrp_grp_iter_free(struct strgrp_grp_iter *iter) {
    tal_free(iter);
}

const char *
strgrp_grp_key(const struct strgrp_grp *const grp) {
    return grp->key;
}

const char *
strgrp_item_key(const struct strgrp_item *const item) {
    return item->key;
}

void *
strgrp_item_value(const struct strgrp_item *const item) {
    return item->value;
}

void
strgrp_free(struct strgrp *const ctx) {
    darray_free(ctx->grps);
    stringmap_free(ctx->known);
    tal_free(ctx);
}

void
strgrp_free_cb(struct strgrp *const ctx, void (*cb)(void *data)) {
    struct strgrp_grp **grp;
    struct strgrp_item **item;
    darray_foreach(grp, ctx->grps) {
        darray_foreach(item, (*grp)->items) {
            cb((*item)->value);
        }
    }
    strgrp_free(ctx);
}

#include <stdio.h>

static void
print_item(const struct strgrp_item *item) {
    printf("\t%s\n", item->key);
}

static void
print_grp(const struct strgrp_grp *const grp) {
    struct strgrp_item **item;
    printf("%s:\n", grp->key);
    darray_foreach(item, grp->items) {
        print_item(*item);
    }
    printf("\n");
}

void
strgrp_print(const struct strgrp *const ctx) {
    struct strgrp_grp **grp;
    darray_foreach(grp, ctx->grps) {
        print_grp(*grp);
    }
}
