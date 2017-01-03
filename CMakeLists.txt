cmake_minimum_required(VERSION 3.5)
project(hello_asm)
enable_language(ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_ASM_COMPILER yasm)
set(CMAKE_ASM_COMPILER_ARG1 "-f elf64")
set(CMAKE_ASM_FLAGS_DEBUG "")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native -mtune=native")

set(SOURCE_FILES main.c string.asm register.asm matrix.c)
add_executable(hello_asm ${SOURCE_FILES})
