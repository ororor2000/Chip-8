#ifndef __CHIP8_HANDLERS_H__
#define __CHIP8_HANDLERS_H__

#include "include/chip8.h"

chip8_error_code_t chip8_decode_msb_0(chip8_t *chip8, ushort_t command, uchar_t opcode);
chip8_error_code_t chip8_decode_msb_1(chip8_t *chip8, ushort_t command, uchar_t opcode);
chip8_error_code_t chip8_decode_msb_2(chip8_t *chip8, ushort_t command, uchar_t opcode);
chip8_error_code_t chip8_decode_msb_3(chip8_t *chip8, ushort_t command, uchar_t opcode);
chip8_error_code_t chip8_decode_msb_4(chip8_t *chip8, ushort_t command, uchar_t opcode);
chip8_error_code_t chip8_decode_msb_5(chip8_t *chip8, ushort_t command, uchar_t opcode);
chip8_error_code_t chip8_decode_msb_6(chip8_t *chip8, ushort_t command, uchar_t opcode);
chip8_error_code_t chip8_decode_msb_7(chip8_t *chip8, ushort_t command, uchar_t opcode);
chip8_error_code_t chip8_decode_msb_8(chip8_t *chip8, ushort_t command, uchar_t opcode);
chip8_error_code_t chip8_decode_msb_9(chip8_t *chip8, ushort_t command, uchar_t opcode);
chip8_error_code_t chip8_decode_msb_A(chip8_t *chip8, ushort_t command, uchar_t opcode);
chip8_error_code_t chip8_decode_msb_B(chip8_t *chip8, ushort_t command, uchar_t opcode);
chip8_error_code_t chip8_decode_msb_C(chip8_t *chip8, ushort_t command, uchar_t opcode);
chip8_error_code_t chip8_decode_msb_D(chip8_t *chip8, ushort_t command, uchar_t opcode);
chip8_error_code_t chip8_decode_msb_E(chip8_t *chip8, ushort_t command, uchar_t opcode);
chip8_error_code_t chip8_decode_msb_F(chip8_t *chip8, ushort_t command, uchar_t opcode);

#endif /* __CHIP8_HANDLERS_H__ */