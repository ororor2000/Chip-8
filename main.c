#include <stdio.h>
#include "SDL.h"
#include "chip8.h"

int main(int argc, char **argv) {
    int err;
    chip8_t *chip8 = NULL;
    SDL_Window* window = NULL;

    err = chip8_init(chip8, "/Users/orshtrauch/Workspace/Chip-8/roms/ibm_logo.ch8");
    if (err != CHIP8_OK) {
        fprintf(stderr, "failed to init chip8, error: %d", err);
        goto out;
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(
        "My SDL Window",             // Window title
        SDL_WINDOWPOS_UNDEFINED,      // Initial x position
        SDL_WINDOWPOS_UNDEFINED,      // Initial y position
        1920,                         // Width, in pixels
        1080,                         // Height, in pixels
        SDL_WINDOW_SHOWN            // Window flags
    );

    if (window == NULL) {
        fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

out:
    SDL_DestroyWindow(window);
    SDL_Quit();
    chip8_cleanup(chip8);
    return 0;
}