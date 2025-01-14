#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "chip8.h"

static void test_chip8_init(void **state) {
    // ... your test code using cmocka assertions ...
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_chip8_init),
        // ... add more test cases ...
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}