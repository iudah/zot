#include <stdlib.h>

#include "../include/zot.h"

typedef uint64_t zsize;

void *zcalloc(const zsize n, const zsize size) { return calloc(n, size); }
void *zrealloc(void *ptr, const zsize size) { return realloc(ptr, size); }

void zfree(void *ptr) { return free(ptr); }

static void __attribute__((constructor(100))) on_load() {}