#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "chip8.h"
#include "chip8_handlers.h"

decode_handler handlers[] = {
    [0x00] = chip8_decode_msb_0,
    [0x10] = chip8_decode_msb_1,
    [0x20] = chip8_decode_msb_2,
    [0x30] = chip8_decode_msb_3,
    [0x40] = chip8_decode_msb_4,
    [0x50] = chip8_decode_msb_5,
    [0x60] = chip8_decode_msb_6,
    [0x70] = chip8_decode_msb_7,
    [0x80] = chip8_decode_msb_8,
    [0x90] = chip8_decode_msb_9,
    [0xA0] = chip8_decode_msb_A,
    [0xB0] = chip8_decode_msb_B,
    [0xC0] = chip8_decode_msb_C,
    [0xD0] = chip8_decode_msb_D,
    [0xE0] = chip8_decode_msb_E,
    [0xF0] = chip8_decode_msb_F,
};

static chip8_error_code_t chip8_load_rom(chip8_t *chip8, const char* rom_file) {
    FILE *fd = NULL;
    struct stat st;
    chip8_error_code_t err = CHIP8_OK;

    if (stat(rom_file, &st) != 0) {
        return CHIP8_ROM_ERR;
    }
    printf("rom size: %lld\n", st.st_size);
    if (st.st_size > CHIP8_MAX_ROM_SIZE) {
        return CHIP8_ROM_TOO_BIG_ERR;
    }

    fd = fopen(rom_file, "r");
    if (fd == NULL) {
        return CHIP8_ROM_ERR;
    }

    if (fread(&chip8->memory[CHIP8_ROM_START], 1, st.st_size, fd) != st.st_size) {
        err = CHIP8_ROM_READ_ERR;
    }

    fclose(fd);
    return CHIP8_OK;
}

chip8_error_code_t chip8_init(chip8_t *chip8, const char* rom_file) {
    chip8 = calloc(1, sizeof(chip8_t));
    if (chip8 == NULL) {
        return CHIP8_ALLOC_ERR;
    }

    chip8->program_counter = CHIP8_ROM_START;
    return chip8_load_rom(chip8, rom_file);
}

static chip8_error_code_t chip8_fetch_decode_execute(chip8_t *chip8) {
    chip8_error_code_t err;
    ushort_t command;
    uchar_t opcode;
    int jump = 0;

    /* get the first half of the instruction and left shift it by 8 */
    command = CHIP8_MEM(chip8, chip8->program_counter) << 8;
    /* append the second half of the command */
    command &= CHIP8_MEM(chip8, chip8->program_counter + 1);

    /* opcode is the MSB (0xF000) */
    opcode = command & CHIP8_NIBBLE_MASK(4);

    if (opcode < 0x00 || opcode > 0xF0 || !handlers[opcode]) {
        return CHIP8_OPCODE_ERR;
    }

    err = handlers[opcode](chip8, command, opcode);

    if (!jump) {
        chip8->program_counter += 2;
    }

    return err;
}

chip8_error_code_t chip8_cycle(chip8_t *chip8) {
    /* time delay equivalent to 1MHz */
    struct timespec req = {0, 1000};
    nanosleep(&req, NULL);

    return chip8_fetch_decode_execute(chip8);
}

void chip8_cleanup(chip8_t *chip8) {
    free(chip8);
    /* TODO: */
}
