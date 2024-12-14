CC = gcc
CFLAGS=-I"C:\MinGW\glut" -Wall -Wextra
LDFLAGS=-L"C:\MinGW\glut" -lglut -lGL -lGLU -lm

TARGET = emulator

all: $(TARGET)

$(TARGET): $(TARGET).c
    $(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c chip8.c $(LDFLAGS)

clean:
    rm -f $(TARGET) *.o


gcc -I"C:\MinGW\glut" -Wall -Wextra -o emulator emulator.c chip8.c -L"C:\MinGW\glut" -lglut -lGL -lGLU -lm