#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "chip8_handlers.c"
#include "chip8.c"

static void test_chip8_decode_handlers_null_ptr(void** state) {
    int i;
    int err;

    for (i = 0; i < sizeof(handlers) / sizeof(handlers[0]); i++) {
        err = handlers[i](NULL, 0, 0);
        assert_int_equal(err, CHIP8_INVALID_PTR_ERR);
    }
}

static void test_chip8_decode_handler_msb_0_opcode_00E0(void **state) {
    int i;
    int j;
    chip8_t chip8;
    ushort_t command = 0x00E0;
    uchar_t opcode;

    chip8_decode_handler_msb_0(&chip8, command, opcode);

    for (i = 0; i < CHIP8_DISPLAY_HEIGHT; i++) {
        for (j = 0; j < CHIP8_DISPLAY_WIDTH; j++) {
            assert_true(chip8.display[i][j] == '\0');
        }
    }
}

static void test_chip8_decode_handler_msb_0_opcode_00EE_invalid_sp(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0x00EE;
    uchar_t opcode;

    chip8.stack_pointer = (sizeof(chip8.stack) / sizeof(uchar_t)) * 2;
    err = chip8_decode_handler_msb_0(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_INVALID_STACK_PTR_ERR);

    chip8.stack_pointer = -1;
    err = chip8_decode_handler_msb_0(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_INVALID_STACK_PTR_ERR);
}


int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_chip8_decode_handlers_null_ptr),
        cmocka_unit_test(test_chip8_decode_handler_msb_0_opcode_00E0),
        cmocka_unit_test(test_chip8_decode_handler_msb_0_opcode_00EE_invalid_sp),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}