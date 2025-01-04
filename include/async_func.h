/*
 The func is responsible for structuring the function and its arguments.
 More like standarizing the functions structer so it's easier to manage.
*/
#ifndef FUNC_H
#define FUNC_H

#include "utils.h"
#include <stdbool.h>
#include <stdint.h>

typedef void (*async_function)(void *,void *, void *);

struct async_func
{
    CONTEXT_POINTER self;
    int32_t id;

    async_function f;
    void *arg;
};

typedef struct async_func async_func_t;

#endif