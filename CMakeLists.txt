cmake_minimum_required(VERSION 3.10)
project(chip8)

# set(CMAKE_C_COMPILER /usr/bin/clang)
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


###############################################################
message(" [*] Compiling Chip8 Unit Tests: chip8_handlers_tests")
set(CHIP8_HANDLERS_TESTS chip8_handlers_tests)
add_executable(${CHIP8_HANDLERS_TESTS} ${CHIP8_TESTS_SRCS})
target_include_directories(${CHIP8_HANDLERS_TESTS} PRIVATE src)
target_link_libraries(${CHIP8_HANDLERS_TESTS} cmocka)

# if(CMAKE_C_COMPILER_ID MATCHES "GNU")
#   target_link_options(${CHIP8_HANDLERS_TESTS} PRIVATE
#     -Wl,-wrap=srand
#     -Wl,-wrap=time
#   )
# elseif(CMAKE_C_COMPILER_ID MATCHES "Clang")
#   target_compile_options(${CHIP8_HANDLERS_TESTS} PRIVATE
#     -Xlinker -wrap,srand
#     -Xlinker -wrap,time
#   )
# endif()

add_test(NAME ${CHIP8_HANDLERS_TESTS} COMMAND ${CHIP8_HANDLERS_TESTS})
message(" [+] Finished Chip8 Unit Tests: ${CHIP8_HANDLERS_TESTS}")
###############################################################
message(" [+] Finished Compiling Chip8 Unit Tests")


message(" [+] Finished Compiling Chip8")

