#include "async.h"
#include <assert.h>
#include <stdio.h>

static void test_async_create()
{
    // Basic test to ensure poll creation works
    async *asyn = async_init();
    assert(asyn != NULL);
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