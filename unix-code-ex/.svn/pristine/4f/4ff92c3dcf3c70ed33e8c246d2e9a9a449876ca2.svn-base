#include <stdio.h>
#include <dlfcn.h>
#include "lib/test.h"

int (*fn)(void);


int main(int argc, const char *argv[])
{
    void *handle = dlopen("./libtest_d.so", RTLD_LAZY);
    const char *err = dlerror();
    if (err != NULL) {
        perror("open so error");
    }

    fn = dlsym(handle, "print_a");
    fn();

    fn = dlsym(handle, "print_b");
    fn();

    dlclose(handle);

    return 0;
}



