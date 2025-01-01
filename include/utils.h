#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
    #define sleep(seconds) Sleep((seconds) * 1000)
    typedef void (*fiber_func)(void*);
#else
    #include <unistd.h>
    #include <ucontext.h>
    #include <errno.h>
    #define WINAPI
#endif

#define FIBER_STACK_SIZE (64*1024)

#define CONTEXT_POINTER void*

// Error handling
#define HANDLE_ERROR(msg) do { \
    fprintf(stderr, "[ERROR] %s (%s)\n", msg, strerror(errno)); \
    exit(1); \
} while(0)

#endif // UTILS_H