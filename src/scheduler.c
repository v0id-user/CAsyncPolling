#include "scheduler.h"
#include "pprint.h"
#include <time.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

static long long get_time_ms() {
#ifdef _WIN32
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    ULARGE_INTEGER uli;
    uli.LowPart = ft.dwLowDateTime;
    uli.HighPart = ft.dwHighDateTime;
    // Convert to milliseconds from 100ns intervals and adjust for Unix epoch
    return (uli.QuadPart / 10000) - 11644473600000LL;
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)tv.tv_sec * 1000LL + (long long)tv.tv_usec / 1000LL;
#endif
}

static bool did_time_pass(void *self) {
    long long current_ms = get_time_ms();
    long long tick_ms = ((schedular_t *)self)->tick;
    bool result = (current_ms - tick_ms) > SCHEDULER_TICK_MS;
    
    DEBUG_PRINT("Did time pass: %d", result);
    DEBUG_PRINT("Current tick: %lld ms", tick_ms);
    DEBUG_PRINT("Current time: %lld ms", current_ms); 
    DEBUG_PRINT("Time difference: %lld ms", current_ms - tick_ms);
    return result;
}

schedular_t *schedular_new() {
    schedular_t *schedular = (schedular_t *)malloc(sizeof(schedular_t));
    if (schedular == NULL) {
        HANDLE_ERROR("Failed to allocate memory for schedular");
        return NULL;
    }
    schedular->did_time_pass = did_time_pass;
    schedular->tick = get_time_ms();  // Initialize tick at creation
    return schedular;
}

schedular_t *schedule(schedular_t *self) {
    self->tick = get_time_ms();
    return self;
}

void schedular_free(schedular_t *schedular) {
    if (schedular != NULL) {
        free(schedular);
        schedular = NULL;
    }
}
