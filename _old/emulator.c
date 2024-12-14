#include "emulator.h"
#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LENGTH 640
#define HEIGHT 320

#define ROM "ibm_logo.ch8"

Chip8 chip;


int main(int argc, char** argv) {
    srand(time(NULL));
    
    if (init_chip8(&chip, ROM) != 0) {
        return 1;
    }

    glutInit(&argc, argv);

	// initialize display and window
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(DISPLAY_LENGTH, DISPLAY_HEIGHT);
	glutCreateWindow("Chip8 Emulator");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, DISPLAY_LENGTH, DISPLAY_HEIGHT, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	glClearColor(0.f, 0.f, 0.f, 1.f);

	// callback register
	glutKeyboardFunc(key_press);
	glutKeyboardUpFunc(key_release);
	
	glutDisplayFunc(emulate_cycle);
	glutIdleFunc(idle);


	glutMainLoop();

	return 0;
}

void emulate_cycle() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	cycle(&chip);

	if (chip.draw) {
		for (int i = 0; i < DISPLAY_LENGTH; i++) {
			for (int j = 0; j < DISPLAY_HEIGHT; j++) {
				if (!chip.display[i][j]) {
					continue;
				}

				draw_square((float)(i * 10), (float)(j * 10));
			}
		}

		chip.draw = FALSE;
	}

	glutSwapBuffers();

	print_regs(&chip);
	print_stack(&chip);
	print_keyboard(&chip);
}

void draw_square(float x, float y) {
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex2f(x, y);
	glVertex2f(x + 10, y);
	glVertex2f(x + 10, y + 10);
	glVertex2f(x, y + 10);
	glEnd();
}

void idle() {	
	glutPostRedisplay();
}

int decode_key(uchar key) {
    switch (key)
    {    
        case '1':
			return 0x0001;
			break;
		case '2':
			return 0x0002;
			break;
		case '3':
			return 0x0003;
			break;
		case '4':
			return 0x000C;
			break;
		case 'q':
			return 0x0004;
			break;
		case 'w':
			return 0x0005;
			break;
		case 'e':
			return 0x0006;
			break;
		case 'r':
			return 0x000D;
			break;
		case 'a':
			return 0x0007;
			break;
		case 's':
			return 0x0008;
			break;
		case 'd':
			return 0x0009;
			break;
		case 'f':
			return 0x000E;
			break;
		case 'z':
			return 0x000A;
			break;
		case 'x':
			return 0x0000;
			break;
		case 'c':
			return 0x000B;
			break;
		case 'v':
			return 0x000F;
			break;
		default:
            return -1;
			break;
    }
}

void key_press(uchar key, int x, int y) {
	// |1|2|3|C|		=>		|1|2|3|4|
	// |4|5|6|D|		=>		|Q|W|E|R|
	// |7|8|9|E|		=>		|A|S|D|F|
	// |A|0|B|F|		=>		|Z|X|C|V|    

    if (key == 27) {
        printf("esc");
        exit(0);
    }

    int input = 0;
    key = decode_key(key);

    if (key < 0) {
        return;
    }

    set_key(&chip, input, 1);
}

void key_release(uchar key, int x, int y) {

    int input;
    input = decode_key(key);

    set_key(&chip, input, 0);
}


// Debugging

void print_regs(Chip8 *chip8) {
    // print registers
    printf("Current OP: 0x%X\n", chip8->opcode);
    for (int i = 0; i < REG_SIZE; i++) {
        printf("V Reg %X: 0x%X\n",i , chip8->V[i]);
    }
    printf("Index Reg: 0x%X\n", chip8->I);
    printf("PC Reg: 0x%X\n", chip8->pc);
    printf("SP Reg: 0x%X\n", chip8->sp);
    printf("Delay Timer Reg: 0x%X\n", chip8->delay_timer);
    printf("Sound Timer Reg: 0x%X\n", chip8->sound_timer);
    printf("\n");
}


void print_stack(Chip8 *chip8) {
    // print stack
    for (int i = 0; i < STACK_SIZE; i++) {
        printf("Stack Element %i: 0x%X\n",i , chip8->stack[i]);
    }
}


void print_keyboard(Chip8 *chip8) {
    // print keyboard
    for (int i = 0; i < KEYPAD_SIZE; i++) {
        printf("Keyboard Key %X: %i\n",i , chip8->key[i]);
    }
}