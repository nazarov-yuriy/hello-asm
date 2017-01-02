cmake_minimum_required(VERSION 3.5)
project(hello_asm)
enable_language(ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_ASM_COMPILER yasm)
set(CMAKE_ASM_COMPILER_ARG1 "-f elf64")
set(CMAKE_ASM_FLAGS_DEBUG "")


set(SOURCE_FILES main.c string.asm register.asm)
add_executable(hello_asm ${SOURCE_FILES})
