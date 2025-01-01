/*
 The func is responsible for structuring the function and its arguments.
 More like standarizing the functions structer so it's easier to manage.
*/
#ifndef FUNC_H
#define FUNC_H

#include "utils.h"
#include <stdbool.h>
#include <stdint.h>

typedef void (*function)(void*);

struct func{
    CONTEXT_POINTER self;
    int32_t id;

    function f;
    void* arg;
    bool is_completed;
};

typedef struct func func_t;

#endif