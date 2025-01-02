#ifndef PPRINT_H
#define PPRINT_H

#include "utils.h"
#include <stdio.h>

#ifdef _DEBUG
#define DEBUG_PRINT(...)                                                                           \
    BLOCK(printf("[%s:%d] ", __FILE__, __LINE__); printf(__VA_ARGS__); printf("\n"))
#else
#define DEBUG_PRINT(...) BLOCK(0;)
#endif

#define DEBUG_ERROR(...) BLOCK(fprintf(stderr, "[ERROR] %s (%s)\n", __VA_ARGS__, strerror(errno));)

// Error handling
#define HANDLE_ERROR(msg) BLOCK(DEBUG_ERROR(msg); exit(1);)

#endif