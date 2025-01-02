/*
 The scheduler is responsible for managing the event loop.
*/
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdbool.h>
#include <time.h>
#include "poll.h"

#define SCHEDULER_TICK_MS 25

struct schedular
{
    time_t last_tick;
    poll_t *poll;
};

typedef struct schedular schedular_t;

schedular_t *schedular_new();
void schedule(schedular_t *schedular);
void schedular_free(schedular_t *schedular);

#endif