# CC=gcc
# CFLAGS=-std=c99	-c	-Wall	-lopengl32 -lglu32 -lglut32
# SOURCES=chip8.c	emulator.c
# OBJECTS=$(SOURCES:.c=.o)
# EXECUTABLE=emulator

clean:
	rm -rf *o emulator

all:
	gcc -c chip8.c
	gcc -c emulator.c
	gcc -o emulator chip8.o emulator.o -lopengl32 -lglu32 -lglut32

# all: $(SOURCES) $(EXECUTABLE)
	
# $(EXECUTABLE): $(OBJECTS)
# 	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

# .c.o:
# 	$(CC) $(CFLAGS) $< -o $@

