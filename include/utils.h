#ifndef UTILS_H
#define UTILS_H

#include "pprint.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#define sleep(seconds) Sleep((seconds) * 1000)
typedef void (*fiber_func)(void *);
#else
#include <errno.h>
#include <sys/ucontext.h>
#include <unistd.h>
#define WINAPI
#endif

#ifdef _WIN32
#define CONTEXT_POINTER LPVOID
#else
#define CONTEXT_POINTER ucontext_t *
#endif

#define BLOCK(x)                                                                                   \
    do                                                                                             \
    {                                                                                              \
        x;                                                                                         \
    } while (0)

#endif  // UTILS_H