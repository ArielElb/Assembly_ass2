cmake_minimum_required(VERSION 3.17)
project(opt4 C)

set(CMAKE_C_STANDARD 11)

add_library(opt4 myfunction1.c myfunction.h  myfunction.c myfunction.h readBMP.c readBMP.h writeBMP.c writeBMP.h)
