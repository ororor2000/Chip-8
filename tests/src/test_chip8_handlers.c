#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "chip8_handlers.c"
#include "chip8.c"

#include <stdio.h>

void __wrap_srand(unsigned int seed) {
    printf("wrap srand");
};

time_t __wrap_time(time_t *tloc) {
    time_t t;
    printf("wrap time");
    return t;
}

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

    chip8.stack_pointer = -10;
    err = chip8_decode_handler_msb_0(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_INVALID_STACK_PTR_ERR);
}

static void test_chip8_decode_handler_msb_0_opcode_00EE_success(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0x00EE;
    uchar_t opcode;

    chip8.stack_pointer = 10;
    chip8.stack[chip8.stack_pointer] = 11;
    err = chip8_decode_handler_msb_0(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.program_counter, 11);
    assert_int_equal(chip8.stack_pointer, 9);
}

static void test_chip8_decode_handler_msb_1_opcode_1NNN_success(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0x1FFF;
    uchar_t opcode;

    err = chip8_decode_handler_msb_1(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.program_counter, 0x0FFF);
}

static void test_chip8_decode_handler_msb_2_opcode_2NNN_invalid_sp(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0x2FFF;
    uchar_t opcode;

    chip8.stack_pointer = (sizeof(chip8.stack) / sizeof(uchar_t)) * 2;
    err = chip8_decode_handler_msb_2(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_INVALID_STACK_PTR_ERR);

    chip8.stack_pointer = -10;
    err = chip8_decode_handler_msb_2(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_INVALID_STACK_PTR_ERR);
}

static void test_chip8_decode_handler_msb_2_opcode_2NNN_success(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0x2FFF;
    uchar_t opcode;

    chip8.program_counter = 1;
    chip8.stack_pointer = 4;
    err = chip8_decode_handler_msb_2(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.stack_pointer, 5);
    assert_int_equal(chip8.stack[chip8.stack_pointer], 1);
    assert_int_equal(chip8.program_counter, 0x0FFF);
}

static void test_chip8_decode_handler_msb_3_opcode_3XKK_success(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0x3ABB;
    uchar_t opcode;

    chip8.program_counter = 1;
    chip8.registers[0xA] = 0xAA;
    err = chip8_decode_handler_msb_3(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.program_counter, 1);

    chip8.program_counter = 1;
    chip8.registers[0xA] = 0xBB;
    err = chip8_decode_handler_msb_3(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.program_counter, 3);
}

static void test_chip8_decode_handler_msb_4_opcode_4XKK_success(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0x4ABB;
    uchar_t opcode;

    chip8.program_counter = 1;
    chip8.registers[0xA] = 0xBB;
    err = chip8_decode_handler_msb_4(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.program_counter, 1);

    chip8.program_counter = 1;
    chip8.registers[0xA] = 0xAA;
    err = chip8_decode_handler_msb_4(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.program_counter, 3);
}

static void test_chip8_decode_handler_msb_5_opcode_5XY0_success(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0x5AB0;
    uchar_t opcode;

    chip8.program_counter = 1;
    chip8.registers[0xA] = 0xB;
    chip8.registers[0xB] = 0xB;
    err = chip8_decode_handler_msb_5(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.program_counter, 1);

    chip8.program_counter = 1;
    chip8.registers[0xA] = 0xA;
    chip8.registers[0xB] = 0xB;
    err = chip8_decode_handler_msb_5(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.program_counter, 3);
}

static void test_chip8_decode_handler_msb_6_opcode_6XKK_success(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0x6ABB;
    uchar_t opcode;

    err = chip8_decode_handler_msb_6(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.registers[0xA], 0xBB);
}

static void test_chip8_decode_handler_msb_7_opcode_7XKK_success(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0x7ABB;
    uchar_t opcode;

    chip8.registers[0xA] = 0x00;
    err = chip8_decode_handler_msb_7(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.registers[0xA], 0xBB);
}

static void test_chip8_decode_handler_msb_8_opcode_8XY0_success(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0x8AB0;
    uchar_t opcode;

    chip8.registers[0xA] = 0xAA;
    chip8.registers[0xB] = 0xFF;
    err = chip8_decode_handler_msb_8(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.registers[0xA], 0xFF);
}

static void test_chip8_decode_handler_msb_8_opcode_8XY1_success(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0x8AB1;
    uchar_t opcode;

    chip8.registers[0xA] = 0xAA;
    chip8.registers[0xB] = 0xFF;
    err = chip8_decode_handler_msb_8(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.registers[0xA], 0xFF | 0xAA );
}

static void test_chip8_decode_handler_msb_8_opcode_8XY2_success(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0x8AB2;
    uchar_t opcode;

    chip8.registers[0xA] = 0xAA;
    chip8.registers[0xB] = 0xFF;
    err = chip8_decode_handler_msb_8(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.registers[0xA], 0xFF & 0xAA);
}

static void test_chip8_decode_handler_msb_8_opcode_8XY3_success(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0x8AB3;
    uchar_t opcode;

    chip8.registers[0xA] = 0xAA;
    chip8.registers[0xB] = 0xFF;
    err = chip8_decode_handler_msb_8(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.registers[0xA], 0xFF ^ 0xAA);
}

static void test_chip8_decode_handler_msb_8_opcode_8XY4_success(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0x8AB4;
    uchar_t opcode;

    chip8.registers[0xA] = 0x10;
    chip8.registers[0xB] = 0x20;

    err = chip8_decode_handler_msb_8(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.registers[0xA], 0x30);
    assert_int_equal(chip8.registers[0xF], 0);
}

static void test_chip8_decode_handler_msb_8_opcode_8XY4_carry(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0x8AB4;
    uchar_t opcode;

    chip8.registers[0xA] = 0xFF;
    chip8.registers[0xB] = 0x01;

    err = chip8_decode_handler_msb_8(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.registers[0xA], 0x00);
    assert_int_equal(chip8.registers[0xF], 1);
}

static void test_chip8_decode_handler_msb_8_opcode_8XY5_no_borrow(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0x8AB5;
    uchar_t opcode;

    chip8.registers[0xA] = 0x30;
    chip8.registers[0xB] = 0x20;

    err = chip8_decode_handler_msb_8(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.registers[0xA], 0x10);
    assert_int_equal(chip8.registers[0xF], 1);
}

static void test_chip8_decode_handler_msb_8_opcode_8XY5_borrow(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0x8AB5;
    uchar_t opcode;

    chip8.registers[0xA] = 0x10;
    chip8.registers[0xB] = 0x20;

    err = chip8_decode_handler_msb_8(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.registers[0xA], 0xF0);
    assert_int_equal(chip8.registers[0xF], 0);
}

static void test_chip8_decode_handler_msb_8_opcode_8XY6_shift_right_even(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0x8AB6;
    uchar_t opcode;

    chip8.registers[0xA] = 0x14;

    err = chip8_decode_handler_msb_8(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.registers[0xA], 0x0A);
    assert_int_equal(chip8.registers[0xF], 0);
}

static void test_chip8_decode_handler_msb_8_opcode_8XY6_shift_right_odd(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0x8AB6;
    uchar_t opcode;

    chip8.registers[0xA] = 0x15;

    err = chip8_decode_handler_msb_8(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.registers[0xA], 0x0A);
    assert_int_equal(chip8.registers[0xF], 1);
}

static void test_chip8_decode_handler_msb_8_opcode_8XY7_no_borrow(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0x8AB7;
    uchar_t opcode;

    chip8.registers[0xA] = 0x20;
    chip8.registers[0xB] = 0x30;

    err = chip8_decode_handler_msb_8(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.registers[0xA], 0x10);
    assert_int_equal(chip8.registers[0xF], 1);
}

static void test_chip8_decode_handler_msb_8_opcode_8XY7_borrow(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0x8AB7;
    uchar_t opcode;

    chip8.registers[0xA] = 0x30;
    chip8.registers[0xB] = 0x10;

    err = chip8_decode_handler_msb_8(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.registers[0xA], 0xE0);
    assert_int_equal(chip8.registers[0xF], 0);
}

static void test_chip8_decode_handler_msb_8_opcode_8XYE_shift(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0x8ABE;
    uchar_t opcode;

    chip8.registers[0xA] = 0x80;
    chip8.registers[0xB] = 0x00;

    err = chip8_decode_handler_msb_8(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.registers[0xA], 0x00);
    assert_int_equal(chip8.registers[0xF], 1);
}

static void test_chip8_decode_handler_msb_8_opcode_8XYE_no_carry(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0x8ABE;
    uchar_t opcode;

    chip8.registers[0xA] = 0x40;
    chip8.registers[0xB] = 0x00;

    err = chip8_decode_handler_msb_8(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.registers[0xA], 0x80);
    assert_int_equal(chip8.registers[0xF], 0);
}

static void test_chip8_decode_handler_msb_9_opcode_9XY0_success(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0x9AB0;
    uchar_t opcode;

    chip8.program_counter = 1;
    chip8.registers[0xA] = 0x10;
    chip8.registers[0xB] = 0x20;

    err = chip8_decode_handler_msb_9(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.program_counter, 3);

    chip8.program_counter = 1;
    chip8.registers[0xA] = 0x10;
    chip8.registers[0xB] = 0x10;

    err = chip8_decode_handler_msb_9(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.program_counter, 1);
}

static void test_chip8_decode_handler_msb_A_opcode_ANNN_success(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0xACCC;
    uchar_t opcode;


    chip8.i_register = 0xFF;

    err = chip8_decode_handler_msb_A(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.i_register, 0xCCC);
}

static void test_chip8_decode_handler_msb_B_opcode_BNNN_success(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0xBCCC;
    uchar_t opcode;


    chip8.registers[0x0] = 0x01;
    chip8.program_counter = 0;
    err = chip8_decode_handler_msb_B(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.program_counter, 0x01 + 0xCCC);
}

static void test_chip8_decode_handler_msb_C_opcode_CXKK_success(void **state) {
    int err;
    chip8_t chip8;
    ushort_t command = 0x6ABB;
    uchar_t opcode;

    err = chip8_decode_handler_msb_C(&chip8, command, opcode);

    assert_int_equal(err, CHIP8_OK);
    assert_int_equal(chip8.registers[0xA], 0xBB);
}


int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_chip8_decode_handlers_null_ptr),
        cmocka_unit_test(test_chip8_decode_handler_msb_0_opcode_00E0),
        cmocka_unit_test(test_chip8_decode_handler_msb_0_opcode_00EE_invalid_sp),
        cmocka_unit_test(test_chip8_decode_handler_msb_0_opcode_00EE_success),
        cmocka_unit_test(test_chip8_decode_handler_msb_1_opcode_1NNN_success),
        cmocka_unit_test(test_chip8_decode_handler_msb_2_opcode_2NNN_invalid_sp),
        cmocka_unit_test(test_chip8_decode_handler_msb_2_opcode_2NNN_success),
        cmocka_unit_test(test_chip8_decode_handler_msb_3_opcode_3XKK_success),
        cmocka_unit_test(test_chip8_decode_handler_msb_4_opcode_4XKK_success),
        cmocka_unit_test(test_chip8_decode_handler_msb_5_opcode_5XY0_success),
        cmocka_unit_test(test_chip8_decode_handler_msb_6_opcode_6XKK_success),
        cmocka_unit_test(test_chip8_decode_handler_msb_7_opcode_7XKK_success),
        cmocka_unit_test(test_chip8_decode_handler_msb_8_opcode_8XY0_success),
        cmocka_unit_test(test_chip8_decode_handler_msb_8_opcode_8XY1_success),
        cmocka_unit_test(test_chip8_decode_handler_msb_8_opcode_8XY2_success),
        cmocka_unit_test(test_chip8_decode_handler_msb_8_opcode_8XY3_success),
        cmocka_unit_test(test_chip8_decode_handler_msb_8_opcode_8XY4_success),
        cmocka_unit_test(test_chip8_decode_handler_msb_8_opcode_8XY4_carry),
        cmocka_unit_test(test_chip8_decode_handler_msb_8_opcode_8XY5_no_borrow),
        cmocka_unit_test(test_chip8_decode_handler_msb_8_opcode_8XY5_borrow),
        cmocka_unit_test(test_chip8_decode_handler_msb_8_opcode_8XY6_shift_right_even),
        cmocka_unit_test(test_chip8_decode_handler_msb_8_opcode_8XY6_shift_right_odd),
        cmocka_unit_test(test_chip8_decode_handler_msb_8_opcode_8XY7_no_borrow),
        cmocka_unit_test(test_chip8_decode_handler_msb_8_opcode_8XY7_borrow),
        cmocka_unit_test(test_chip8_decode_handler_msb_8_opcode_8XYE_shift),
        cmocka_unit_test(test_chip8_decode_handler_msb_8_opcode_8XYE_no_carry),
        cmocka_unit_test(test_chip8_decode_handler_msb_9_opcode_9XY0_success),
        cmocka_unit_test(test_chip8_decode_handler_msb_A_opcode_ANNN_success),
        cmocka_unit_test(test_chip8_decode_handler_msb_B_opcode_BNNN_success),
        cmocka_unit_test(test_chip8_decode_handler_msb_C_opcode_CXKK_success),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}