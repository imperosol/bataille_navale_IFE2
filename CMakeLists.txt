cmake_minimum_required(VERSION 3.19)
project(bataille_navale_utbm C)

set(CMAKE_C_STANDARD 99)

add_executable(bataille_navale_utbm main.c struct.h standard_functions.c standard_functions.h display.c display.h missile_attack.c missile_attack.h initialization.c initialization.h)