// Cpu Registers
#define REG_SIZE 16

#define V0 0
#define V1 1
#define V2 2
#define V3 3
#define V4 4
#define V5 5
#define V6 6
#define V7 7
#define V8 8
#define V9 9
#define VA 10
#define VB 11
#define VC 12
#define VD 13
#define VE 14
#define VF 15

#define STACK_SIZE 16
#define KEYPAD_SIZE 16

// RAM
#define MEM_SIZE 4096
#define INT_START 0x000  // 0
#define INT_END 0x1FF // 511

#define FONT_START 0x000 // 0
#define FONT_END 0x050 // 80
#define FONT_SIZE (FONT_END - FONT_START)

#define ROM_START 0x200 // 512
#define ROM_END 0xFFF // 4095
#define ROM_SIZE (ROM_END - ROM_START)

// Display
#define DISPLAY_SIZE 64 * 32

#define SIZE(arr) sizeof(arr)/sizeof(arr[0])

typedef struct Chip8 {
    unsigned short I;
    unsigned short pc;
    unsigned short sp;
    unsigned short opcode;
    unsigned char delay_timer;
    unsigned char sound_timer;

    unsigned char V[REG_SIZE];
    unsigned char memory[MEM_SIZE];

    unsigned short key[KEYPAD_SIZE];
    unsigned short stack[STACK_SIZE];

    unsigned char display[DISPLAY_SIZE];

} Chip8;

const unsigned char fontset[FONT_SIZE] = {
	0xF0, 0x90, 0x90, 0x90, 0xF0,		// 0
	0x20, 0x60, 0x20, 0x20, 0x70,		// 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0,		// 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0,		// 3
	0x90, 0x90, 0xF0, 0x10, 0x10,		// 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0,		// 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0,		// 6
	0xF0, 0x10, 0x20, 0x40, 0x40,		// 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0,		// 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0,		// 9
	0xF0, 0x90, 0xF0, 0x90, 0x90,		// A
	0xE0, 0x90, 0xE0, 0x90, 0xE0,		// B
	0xF0, 0x80, 0x80, 0x80, 0xF0,		// C
	0xE0, 0x90, 0x90, 0x90, 0xE0,		// D
	0xF0, 0x80, 0xF0, 0x80, 0xF0,		// E
	0xF0, 0x80, 0xF0, 0x80, 0x80		// F
};