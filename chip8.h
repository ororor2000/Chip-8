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

// and/or bits macro
#define SIG_0 0x0000
#define SIG_1 0x1000
#define SIG_2 0x2000
#define SIG_3 0x3000
#define SIG_4 0x4000
#define SIG_5 0x5000
#define SIG_6 0x6000
#define SIG_7 0x7000
#define SIG_8 0x8000
#define SIG_9 0x9000
#define SIG_A 0xA000
#define SIG_B 0xB000
#define SIG_C 0xC000
#define SIG_D 0xD000
#define SIG_E 0xE000
#define SIG_F 0xF000

#define FIRST_BIT 0xF000
#define SECOND_BIT 0x0F00
#define THIRD_BIT 0x00F0
#define FOURTH_BIT 0x000F

#define TWO_RIGHTS_BITS 0x00FF
#define THREE_RIGHT_BITS 0x0FFF
#define FOUR_BITS 0xFFFF

#define BYTESCAN(N) (0x80 >> N) 

#define TRUE 1
#define FALSE 0

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

#define SIZE(arr) sizeof(arr)/sizeof(arr[0])

typedef unsigned short ushort;
typedef unsigned char uchar;
typedef int bool;

// Display
#define DISPLAY_HEIGHT 64
#define DISPLAY_LENGTH 32
#define DISPLAY_SIZE (DISPLAY_HEIGHT * DISPLAY_LENGTH * sizeof(uchar))


typedef struct Chip8 {
	bool draw;
	
    ushort I;
    ushort pc;
    ushort sp;
    ushort opcode;
    uchar delay_timer;
    uchar sound_timer;

    uchar V[REG_SIZE];
    uchar memory[MEM_SIZE];

    ushort key[KEYPAD_SIZE];
    ushort stack[STACK_SIZE];

    uchar display[DISPLAY_LENGTH][DISPLAY_HEIGHT];

} Chip8;

const uchar fontset[FONT_SIZE] = {
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