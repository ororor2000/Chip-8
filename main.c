#include <stdio.h>
#include <signal.h>
#include "emulator.h"

static emulator_t emulator = {0};

void handle_signal(int signal) {
    emulator.quit = 1;
}

int main(int argc, char **argv) {
    int err;
    char *rom;

    signal(SIGINT, handle_signal);

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <path to ROM>\n", argv[0]);
        return 1;
    } else {
        rom = argv[1];
    }

    if (err != EMULATOR_SUCCESS) {
        err = emulator_init(&emulator, rom);
        goto out;
    }

    emulator_cycle(&emulator);

out:
    emulator_cleanup(&emulator);
    return 0;
}