/*
 The scheduler is responsible for managing the event loop.
*/
#ifndef SCHEDULER_H
#define SCHEDULER_H

#define SCHEDULER_TICK_MS 25

#include <stdbool.h>

struct schedular
{

    bool is_running;
};

#endif