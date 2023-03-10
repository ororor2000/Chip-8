#include <stdio.h>
#include <stdlib.h>
#include "chip8.h"

void init_chip8(Chip8 *chip8, char *file_name) {
    chip8->pc = ROM_START;    
    chip8->opcode = 0;
    chip8->I = 0;
    chip8->sp = 0;   

    chip8->delay_timer = 0;
    chip8->sound_timer = 0;

    memset(chip8->V, 0, REG_SIZE);
    memset(chip8->key, 0, KEYPAD_SIZE);
    memset(chip8->memory, 0, MEM_SIZE);
    memset(chip8->stack, 0, STACK_SIZE);
    memset(chip8->display, 0, DISPLAY_SIZE);

    for (int i = FONT_START; i < FONT_END; i++) {
        chip8->memory[i] = fontset[i];
    }

    load_rom(chip8, file_name);
}

int load_rom(Chip8 *chip8, char* file_name) {
    FILE *fd;
    int file_size;

    fd = fopen(file_name, "rb");

    if (fd == NULL) {
        return 1;
    }
    
    fseek(fd, 0, SEEK_END);
    file_size = ftell(fd);
    rewind(fd);

    if (file_size > ROM_SIZE) {
        return 1;
    }

    char tmp_buffer[file_size];
    fread(tmp_buffer, sizeof(char), file_size, fd);

    for (int i = 0; i < file_size; i++)
    {
        chip8->memory[ROM_START + i] = tmp_buffer[i];
    }

    return 0;
}

int cycle(Chip8 *chip8) {
    if (chip8->delay_timer > 0) {
        --(chip8->delay_timer);
    }

    if (chip8->sound_timer > 0) {
        --(chip8->sound_timer);
    }

    ushort opcode = chip8->memory[chip8->pc] << 8 | chip8->memory[chip8->pc + 1];
    
    decode(chip8, opcode);
}

int decode(Chip8 *chip8, ushort opcode) {
    chip8->opcode = opcode;

    ushort left_bit = chip8->opcode & FIRST_BIT;
    ushort x = (opcode & SECOND_BIT) >> 8;
    ushort y = (opcode & THIRD_BIT) >> 4;

    bool jump = FALSE;

    switch (left_bit) {
        case SIG_0:
            decode_sig_0_codes(chip8, opcode);
            break;
        case SIG_1: // 1nnn
            chip8->pc = opcode & THREE_RIGHT_BITS; // JUMP: PC = nnn
            jump = TRUE;
            break;
        case SIG_6: // 6xkk
            chip8->V[x] = opcode & TWO_RIGHTS_BITS; // Vx = kk
            break;
        case SIG_7: // 7xkk    
            chip8->V[x] += opcode & TWO_RIGHTS_BITS; // Vx = kk
            break;
        case SIG_8:
            decode_sig_8_codes(chip8, x, y, opcode);
        case SIG_A: // Annn
            chip8->I = opcode & THREE_RIGHT_BITS; // I = nnn
            break;     
        case SIG_B: // Bnnn
            ushort nnn = opcode & THREE_RIGHT_BITS;
            chip8->pc = nnn + chip8->V[V0]; // Jump to nnn + V0
            jump = TRUE;
            break;
        case SIG_C: // Cxkk
            ushort random  = rand() % 255;
            ushort kk = opcode & TWO_RIGHTS_BITS;
            chip8->V[x] = random & kk;
            break;
        case SIG_E:
            decode_sig_E_codes(chip8, x, opcode);
            break;
        case SIG_D: // DXYN
            draw(chip8, opcode);
        default:
            return 2;
    }

    // if a the opcode doesnt inclue the a jump command
    // go to the next instruction
    if (!jump) { 
        chip8->pc += 2;
    }
}

void decode_sig_0_codes(Chip8 *chip8, ushort opcode) {
    if (opcode == 0x00E0) {
        memset(chip8->display, 0, DISPLAY_SIZE);
    } 
    // else if (opcode == 0x00EE) {
    //     //
        
    // } else { // 0x0nnn

    // }
}

void decode_sig_8_codes(Chip8 *chip8, ushort x, ushort y, ushort opcode) {
    ushort nibble = opcode & FOURTH_BIT;

    switch (nibble)
    {
        case 0: // Vx = Vy
            chip8->V[x] = chip8->V[y];
            break;
        case 1: // Vx = Vx OR Vy
            chip8->V[x] = chip8->V[x] | chip8->V[y];
            break;
        case 2: // Vx = Vx AND Vy
            chip8->V[x] = chip8->V[x] & chip8->V[y];
            break;
        case 3: // Vx = Vx XOR Vy
            chip8->V[x] = chip8->V[x] ^ chip8->V[y];
            break;
        case 4: // Vx = Vx + Vy, Vf=1 if > 255

            if (chip8->V[x] + chip8->V[y] > 255) {
                chip8->V[VF] = 1;
            } else {
                chip8->V[VF] = 0;
            }

            chip8->V[x] += chip8->V[y];
            break;
        case 5: // Vx = Vx - Vy, Vf=1 if Vx > Vy
            if (chip8->V[x] > chip8->V[y]) {
                chip8->V[VF] = 1;
            } else {
                chip8->V[VF] = 0;
            }

            chip8->V[x] -= chip8->V[y];
            break;
    }
}

void decode_sig_E_codes(Chip8 *chip8, ushort x, ushort opcode) {
}

void decode_sig_F_codes(Chip8 *chip8, ushort x, ushort opcode) {
}

void draw(Chip8 *chip8, unsigned short opcode) {
    unsigned short vx, vy, nibble;

    vx = opcode & SECOND_BIT;
    vy = opcode & THIRD_BIT;
    nibble = opcode & FOURTH_BIT;
}

// 00E0 (clear screen) - v
// 1NNN (jump) - v
// 6XNN (set register VX) - v
// 7XNN (add value to register VX) - v
// ANNN (set index register I) - v
// DXYN (display/draw)