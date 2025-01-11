cmake_minimum_required(VERSION 3.10)
project(Chip-8)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_BUILD_PARALLEL_LEVEL $(sysctl -n hw.logicalcpu))

# Add SDL as a subdirectory
add_subdirectory(sdl)

# Add include directories
include_directories(include)

# Add source files
add_executable(chip8
    src/chip8.c
    src/chip8_handlers.c
    src/chip8_io.c
    main.c
)

# Link with SDL libraries
target_link_libraries(chip8 SDL2main SDL2)

target_compile_options(SDL2main PRIVATE -w)
target_compile_options(SDL2 PRIVATE -w)