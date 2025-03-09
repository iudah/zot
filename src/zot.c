#include <mem.h>
#include <stdlib.h>
#include <zot.h>

typedef uint64_t zsize;

void *zmalloc(const zsize size) {
  // return malloc(size);
  return allocate(size);
}
void *zcalloc(const zsize count, const zsize unit_size) {
  if (!count || !unit_size)
    return NULL;
  uint64_t size = count * unit_size;
  /* check mul overflow */
  if (unit_size != size / count)
    return NULL;
  void *ptr = zmalloc(size);
  if (!ptr)
    return NULL;
  memset(ptr, 0, size);
  return ptr;
}
void *zrealloc(void *ptr, const zsize size) {
  // return realloc(ptr, size);
  return reallocate(ptr, size);
}

void zfree(void *ptr) {
  // return free(ptr);
  return claim(ptr);
}

static void __attribute__((constructor(100))) on_load() {}