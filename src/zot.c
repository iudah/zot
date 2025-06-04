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

bool zfree(void *ptr) {
  // return free(ptr);
  return claim(ptr);
}

int zthread_create(pthread_t *_Nonnull thread_ptr,
                   pthread_attr_t const *_Nullable thread_attr,
                   void *_Nonnull (*_Nonnull start_routine)(void *_Nonnull),
                   void *_Nullable input) {
  return create_thread(thread_ptr, thread_attr, start_routine, input);
}

static void __attribute__((constructor(100))) on_load() {}