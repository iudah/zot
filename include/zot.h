#ifndef ZOT_H
#define ZOT_H

#include <stdint.h>

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
void *zcalloc(const zsize n, const zsize size);

void *zrealloc(void *mptr, zsize size);

/**
 * Frees allocated memory.
 * @param ptr Pointer to the memory to be freed.
 */
void zfree(void *ptr);

#define LOG(fmt, ...) fprintf(stderr, "[LOG]: " fmt "\n", ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif