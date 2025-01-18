#ifndef __CHIP8_HANDLERS_H__
#define __CHIP8_HANDLERS_H__

#include "chip8.h"

int chip8_decode_handler_msb_0(chip8_t *chip8, ushort_t command, uchar_t opcode);
int chip8_decode_handler_msb_1(chip8_t *chip8, ushort_t command, uchar_t opcode);
int chip8_decode_handler_msb_2(chip8_t *chip8, ushort_t command, uchar_t opcode);
int chip8_decode_handler_msb_3(chip8_t *chip8, ushort_t command, uchar_t opcode);
int chip8_decode_handler_msb_4(chip8_t *chip8, ushort_t command, uchar_t opcode);
int chip8_decode_handler_msb_5(chip8_t *chip8, ushort_t command, uchar_t opcode);
int chip8_decode_handler_msb_6(chip8_t *chip8, ushort_t command, uchar_t opcode);
int chip8_decode_handler_msb_7(chip8_t *chip8, ushort_t command, uchar_t opcode);
int chip8_decode_handler_msb_8(chip8_t *chip8, ushort_t command, uchar_t opcode);
int chip8_decode_handler_msb_9(chip8_t *chip8, ushort_t command, uchar_t opcode);
int chip8_decode_handler_msb_A(chip8_t *chip8, ushort_t command, uchar_t opcode);
int chip8_decode_handler_msb_B(chip8_t *chip8, ushort_t command, uchar_t opcode);
int chip8_decode_handler_msb_C(chip8_t *chip8, ushort_t command, uchar_t opcode);
int chip8_decode_handler_msb_D(chip8_t *chip8, ushort_t command, uchar_t opcode);
int chip8_decode_handler_msb_E(chip8_t *chip8, ushort_t command, uchar_t opcode);
int chip8_decode_handler_msb_F(chip8_t *chip8, ushort_t command, uchar_t opcode);

#endif /* __CHIP8_HANDLERS_H__ */