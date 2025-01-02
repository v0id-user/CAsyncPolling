#include "async.h"
#include <assert.h>
#include <stdio.h>

void test_function(,void *arg){
    printf("TEST FUNCTION: %s\n", (char *)arg);
}

static void test_async_create()
{
    // Basic test to ensure poll creation works
    async *asyn = async_init();
    assert(asyn != NULL);

    // todo: do a checksum make sure any function that want to run async
    //       accept the async as a self argument to yeild control back to 
    //       event loop
    asyn->async_run(asyn->ctx, test_function, "Hello, World!");
    async_free(asyn);

    printf("test_async_create: PASS\n");
}

int main(int argc, char **argv)
{
    printf("Running async tests...\n");

    test_async_create();

    printf("All tests passed!\n");
    return 0;
}