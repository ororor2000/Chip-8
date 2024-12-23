#ifndef __CHIP_8_H__
#define __CHIP_8_H__

#define CHIP8_MEMORY_SIZE        (4096)
#define CHIP8_REGISTERS_SIZE     (16)
#define CHIP8_KEYPAD_SIZE        (0xF)
#define CHIP8_STACK_SIZE         (16 * 2) /* 16 levels stack, each 2 byte*/

#define CHIP8_DISPLAY_WIDTH      (64)
#define CHIP8_DISPLAY_HEIGHT     (32)

#define CHIP8_ROM_START          (0x200)
#define CHIP8_ROM_END            (0xFF)
#define CHIP8_MAX_ROM_SIZE       (CHIP8_ROM_END - CHIP8_ROM_START)

#define CHIP8_MEM(chip8, index)  chip8->memory[index]

#define CHIP8_OPCODE_MASK       (0xF000)
#define CHIP8_LOWER_8_BITS_MASK (0xFF)

#define CHIP8_LSB_MASK(index)    (((1 << ((index) * 4)) - 1))
#define CHIP8_NIBBLE_MASK(index) ((0xF) << ((index - 1) * 4))

#define CHIP8_Vx(chip8, x)       chip8->registers[x]
#define CHIP8_V0(chip8)          CHIP8_Vx(chip8, 0)
#define CHIP8_VF(chip8)          CHIP8_Vx(chip8, 0xF0)

#define CHIP8_STACK_TOP(chip8)   chip8->stack[chip8->stack_pointer]
#define CHIP8_ASSERT_SP_VALID(chip8)  \
        if (chip8->stack_pointer < 0 || chip8->stack_pointer >= sizeof(chip8->stack) / sizeof(uchar_t)) { \
            return CHIP8_INVALID_STACK_PTR_ERR; \
        }

#define CHIP8_ASSERT_VALID_REGISTER(chip8, r) \
        if (r < 0 && r >= sizeof(chip8->registers) / sizeof(uchar_t)) { \
            return CHIP8_INVALID_REGISTER_ERR; \
        }

#define CHIP8_ASSERT_VALID_KEY(chip8, k) \
        if (k < 0 && k >= sizeof(chip8->keypad_state) / sizeof(uchar_t)) { \
            return CHIP8_INVALID_KEY_ERR; \
        }


typedef unsigned char uchar_t;
typedef unsigned short ushort_t;

typedef (*decode_handler)(chip8_t *chip8, ushort_t command, uchar_t opcode);

typedef enum {
    CHIP8_KEY_IDLE,
    CHIP8_KEY_PRESSED,
} chip8_key_state_t;

typedef enum {
    CHIP8_OK = 0,
    CHIP8_ALLOC_ERR,
    CHIP8_ROM_TOO_BIG_ERR,
    CHIP8_ROM_READ_ERR,
    CHIP8_DECODE_ERR,
    CHIP8_ROM_ERR,
    CHIP8_OPCODE_ERR,
    CHIP8_INVALID_STACK_PTR_ERR,
    CHIP8_INVALID_REGISTER_ERR,
    CHIP8_INVALID_KEY_ERR,
    CHIP8_ERR,
    CHIP8_MAX, /* must be last one */
} chip8_error_code_t;

typedef struct {
    ushort_t program_counter;
    ushort_t stack_pointer;
    ushort_t i_register;

    uchar_t delay_timer;
    uchar_t sound_timer;

    uchar_t stack[CHIP8_STACK_SIZE];
    uchar_t memory[CHIP8_MEMORY_SIZE];
    uchar_t registers[CHIP8_REGISTERS_SIZE];
    uchar_t keypad_state[CHIP8_KEYPAD_SIZE + 1];
    uchar_t display[CHIP8_DISPLAY_HEIGHT][CHIP8_DISPLAY_WIDTH];
} chip8_t;

chip8_error_code_t chip8_init(chip8_t *chip8, const char* rom_file);
chip8_error_code_t chip8_cycle(chip8_t *chip8);
void chip8_cleanup(chip8_t *chip8);

#endif /* __CHIP_8_H__ */