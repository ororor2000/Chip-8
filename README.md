# Chip-8 Emulator

## Overview
This project is a Chip-8 emulator written in C, utilizing SDL2 for rendering. The Chip-8 is an interpreted programming language, developed in the 1970s, primarily used for creating simple games. This emulator allows you to run and play Chip-8 programs on modern hardware.

## Features
- **Emulation of Chip-8 instructions**: Supports all standard Chip-8 instructions.
- **SDL2 rendering**: Uses SDL2 to render the Chip-8 display.
- **Keyboard input**: Maps the Chip-8 keypad to your keyboard.
- **Sound**: Emulates the Chip-8 sound system.

## Requirements
- C compiler (e.g., GCC)
- SDL2 libraries
- CMake (for building the project)

## Installation
1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/Chip-8.git
    ```
2. Navigate to the project directory:
    ```sh
    cd Chip-8
    ```
3. Build the project using CMake:
    ```sh
    mkdir build
    cd build
    cmake ..
    make
    ```

## Usage
1. Run the emulator:
    ```sh
    ./chip8 path/to/rom
    ```
2. Use the following keys to interact with the emulator:
    - `1-4`, `Q-R`, `A-F`, `Z-V` to simulate the Chip-8 keypad.

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request.

## Acknowledgements
- [Cowgod's Chip-8 Technical Reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM) for detailed information on Chip-8 instructions.
- [Wikipedia](https://en.wikipedia.org/wiki/CHIP-8) for historical context and additional resources.

