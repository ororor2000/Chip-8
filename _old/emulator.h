#include "chip8.h"

void emulate_cycle();

void draw_square(float x, float y);
void idle();

int decode_key(uchar key);
void key_press(uchar key, int x, int y);
void key_release(uchar key, int x, int y);


void print_regs(Chip8 *chip8);
void print_stack(Chip8 *chip8);
void print_keyboard(Chip8 *chip8);