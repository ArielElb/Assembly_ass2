cmake_minimum_required(VERSION 3.17)
project(assembly-3 C ASM)

set(CMAKE_C_STANDARD 99)
set(GCC_COVERAGE_COMPILE_FLAGS "-no-pie")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

add_executable(assembly-3 testPstringFunc.c  func_select.s run_main.s pstring.h pstring.s testPstringFunc.c)