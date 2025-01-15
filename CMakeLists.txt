cmake_minimum_required(VERSION 3.10)
project(chip8)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_BUILD_PARALLEL_LEVEL $(sysctl -n hw.logicalcpu))

set(SUBMOD_DIR submodules)

# Add SDL as a subdirectory
add_subdirectory(${SUBMOD_DIR}/sdl)

# Add include directories
include_directories(include)

# Add source files
file(GLOB
    CHIP8_SRCS
    "src/*.c")

message(" [*] Compiling Chip8 Executable")

add_executable(chip8 ${CHIP8_SRCS} main.c)

# Link with SDL libraries
target_link_libraries(chip8 SDL2main SDL2)

target_compile_options(SDL2main PRIVATE -w)
target_compile_options(SDL2 PRIVATE -w)

message(" [*] Finished Compiling Chip8 Executable")

################ Unit Tests ######################
enable_testing()

message(" [*] Compiling Chip8 Unit Tests")

# Add Cmocka as a subdirectory
add_subdirectory(${SUBMOD_DIR}/cmocka)

# Collect test source files
file(GLOB CHIP8_TESTS_SRCS "tests/src/test_*.c")

# Add a test executable
add_executable(chip8_tests ${CHIP8_TESTS_SRCS})

target_include_directories(chip8_tests PUBLIC src)

target_link_options(chip8_tests PRIVATE
    -Wl,-wrap=srand
    -Wl,-wrap=time
)

# Link Unit Tests with cmocka
target_link_libraries(chip8_tests cmocka)

# Add a test target
add_test(NAME chip8_tests COMMAND chip8_tests)

message(" [*] Finished Compiling Chip8 Unit Tests")