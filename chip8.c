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