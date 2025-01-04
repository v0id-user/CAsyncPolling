#include "pprint.h"
#include "async.h"
#include <assert.h>
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// Cross-platform sleep function (milliseconds)
static void platform_sleep(unsigned int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);  // usleep takes microseconds
#endif
}

void test_function(async_ctx *ctx, async_state *state, char *arg){
    DEBUG_PRINT("STATE PTR: %p\n", (void *)state);
    for (int i = 0; i < 5; i++) {
        // Mimic a long running function
        DEBUG_PRINT("TEST FUNCTION: %p\n", arg);
        platform_sleep(35); // Sleep for 35ms to simulate a long running function (35ms is 35000000ns, yes this is long), the scheduler is 25ms
        // TODO: Check if calling on each loop introduces an overhead
        async_yield(ctx, state);
    }
}

// The expected output is 10 TEST FUNCTION: {address} run it 
// and press ctrl+f search for "TEST FUNCTION" if you see 10 
// of them, then the test passed. Not the most brilliant test, 
// but it's a start ;D
static void test_async_create()
{
    printf("Testing async creation...\n");
    
    // Basic test to ensure poll creation works
    async *asyn = async_init();
    if (asyn == NULL) {
        printf("FAIL: async_init returned NULL\n");
        return;
    }
    
    assert(asyn != NULL);
    assert(asyn->ctx != NULL);
    assert(asyn->ctx->state != NULL);
    assert(asyn->ctx->poll != NULL);
    assert(asyn->async_run != NULL);

    // Create async_func_t structure
    char *arg1 = "Hello, World1!";
    char *arg2 = "Hello, World2!";
    DEBUG_PRINT("ARG1: %p", arg1);
    DEBUG_PRINT("ARG2: %p", arg2);
    async_func_t async_test_function1 = {
        .self = NULL,  // Will be set by the async system
        .id = 0,       // Will be set by the async system
        .f = test_function,
        .arg = arg1
    };

    async_func_t async_test_function2 = {
        .self = NULL,  // Will be set by the async system
        .id = 0,       // Will be set by the async system
        .f = test_function,
        .arg = arg2
    };


    // Run same function twice to test if it can be run again

    // TODO: Unix support
    DEBUG_PRINT("Running async_run 1 %p", async_test_function1.f);
    DEBUG_PRINT("Running async_run async address 1 %p", asyn);
    DEBUG_PRINT("Running async_run function address 1 %p", asyn->async_run);
    asyn->async_run(asyn->ctx, &async_test_function1);

    DEBUG_PRINT("Running async_run 2 %p", async_test_function2.f);
    DEBUG_PRINT("Running async_run async address 2 %p", asyn);
    DEBUG_PRINT("Running async_run function address 2 %p", asyn->async_run);
    asyn->async_run(asyn->ctx, &async_test_function2);

    // Wait for the functions to finish
    asyn->await(asyn->ctx);

    // Cleanup
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