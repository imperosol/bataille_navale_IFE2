cmake_minimum_required(VERSION 3.19)
project(bataille_navale_utbm C)

set(CMAKE_C_STANDARD 99)

add_executable(bataille_navale_utbm main.c headers/struct.h src/nyanpasu_lib.c headers/nyanpasu_lib.h src/display.c headers/display.h src/missile_attack.c headers/missile_attack.h src/initialization.c headers/initialization.h src/player_interaction.c headers/player_interaction.h common_functions.c common_functions.h src/save.c headers/save.h src/active_mode.c headers/active_mode.h)