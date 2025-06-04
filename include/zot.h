#ifndef ZOT_H
#define ZOT_H

#ifndef __clang__
#define _Nonnull
#define _Nullable
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Type definition for object sizes.
 */
typedef uint64_t zsize;

/**
 * Allocates memory for an array of objects.
 * @param n Number of objects.
 * @param size Size of each object.
 * @return Pointer to the allocated memory.
 */
void *_Nullable zcalloc(const zsize n, const zsize size);

void *_Nullable zmalloc(zsize size);

void *_Nullable zrealloc(void *_Nonnull mptr, zsize size);

/**
 * Frees allocated memory.
 * @param ptr Pointer to the memory to be freed.
 */
bool zfree(void *_Nonnull ptr);

int zthread_create(pthread_t *_Nonnull thread_ptr,
                   pthread_attr_t const *_Nullable thread_attr,
                   void *_Nonnull (*_Nonnull start_routine)(void *_Nonnull),
                   void *_Nullable input);

#define LOG(fmt, ...) fprintf(stderr, "[LOG]: " fmt "\n", ##__VA_ARGS__)
#define LOG_ERROR(msg, ...)                                                    \
  fprintf(stderr, "[ERROR]: %s: " msg "\n", __FUNCTION__, ##__VA_ARGS__);      \
  abort();

#ifdef __cplusplus
}
#endif

#endif