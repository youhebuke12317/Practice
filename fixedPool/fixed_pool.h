#ifndef __FIXED_POOL_H__
#define __FIXED_POOL_H__

struct Pool;

// 创建一个内存池
struct Pool *create_pool(char *name, unsigned int size);

void *pool_alloc(struct Pool *pool);

int pool_free(struct Pool *pool, void *element);

void pool_destroy(struct Pool *pool);


#endif
