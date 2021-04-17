cmake_minimum_required(VERSION 3.19)
project(bataille_navale_utbm C)

set(CMAKE_C_STANDARD 99)

add_executable(bataille_navale_utbm main.c headers/struct.h src/standard_functions.c headers/standard_functions.h src/display.c headers/display.h src/missile_attack.c headers/missile_attack.h src/initialization.c headers/initialization.h)