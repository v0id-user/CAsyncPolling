/*
This header file defines functions that are compatible with asynchronous programming.
One of the key functions included is `async_sleep`, which allows for non-blocking sleep
operations. Unlike traditional sleep functions that halt the entire thread,
`async_sleep` enables other tasks to continue executing while waiting, thus
maintaining the responsiveness of the application.
 */
#ifndef ASYNCIO_H
#define ASYNCIO_H

#include "async.h"


async* async_sleep(async* self, int ms);
async* async_read(async* self, int fd);
async* async_write(async* self, int fd);



#endif