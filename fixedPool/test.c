/**************************************************
  >File Name: test.c
  >Author:silence
  >Create Time: 2018年02月06日 星期二 20时23分34秒
**************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "fixed_pool.h"

struct Buffer {
    char buf[1024];
};

static struct Pool *buffer_pool = NULL;


static void *pthread_func()
{
    struct Buffer *buffer = (struct Buffer *)pool_alloc(buffer_pool);
    if (buffer == NULL) {
        return NULL;
    }

    strcpy(buffer->buf, "qwertyuiop[]");

    printf("pthread buffer: %s\n", buffer->buf);
    
    return NULL;
}



int main()
{
    int i = 0;
    pthread_t pid[10];

    buffer_pool = create_pool("buffer", sizeof(struct Buffer)); 
    if (buffer_pool == NULL) {
        return -1;
    } 

    for (i = 0; i < 10; i++) {
        pthread_create(&pid[i], NULL, (void *)&pthread_func, NULL);
        usleep(100);
    }

    struct Buffer *buffer = (struct Buffer *)pool_alloc(buffer_pool);
    if (buffer == NULL) {
        return -1;
    }

    strcpy(buffer->buf, "qwertyuiop[]");

    printf("buffer: %s\n", buffer->buf);

    return 0;
}
