
sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)
LIBRARY := $(OBJ_DIR)/xxxx.a
OBJS_$(d) := \
	$(OBJ_DIR)/xxxx.o \
$(OBJS_$(d)) : CFLAGS_LOCAL := -I$(d) -02 -g -W -Wall
DEPS_$(d) :=  $(OBJS_$(d):.o=.d)
LIBS_LIST := $(LIBS_LIST) $(LIBRARY)
CLEAN_LIST  :=  $(CLEAN_LIST) $(OBJS_$(d)) $(DEPS_$(d)) $(LIBRARY)
-include $(DEP_$(d))
$(LIBRARY): $(OBJS_$(d))
	$(MAKELIB)
$(OBJ_DIR)/%.o: $(d)/%.c
	$(COMPILE)
d   :=  $(dirstack_$(sp))
sp  :=  $(basename $(sp))
