cmake_minimum_required(VERSION 3.19)
project(bataille_navale_utbm C)

set(CMAKE_C_STANDARD 99)

set(SDL2_PATH "C:\\Program Files (x86)\\CodeBlocks\\SDL2-devel-2.0.12-mingw\\SDL2-2.0.12\\x86_64-w64-mingw32")
SET(SDL_SEARCH_PATH ${SDL2_PATH})
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)


find_package(SDL2 REQUIRED)
#target_include_directories(${PROJECT_NAME} PRIVATE )
#target_link_libraries(${PROJECT_NAME} "C:\\Program Files (x86)\\CodeBlocks\\SDL2-devel-2.0.12-mingw\\SDL2-2.0.12\\x86_64-w64-mingw32\\lib")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include_directories(${PROJECT_SOURCE_DIR}/include)          #Include project include directory(headers)
link_directories(${PROJECT_SOURCE_DIR}/lib -lmingw32 -lSDL2main -lSDL2)                 #Include lib folder (for .lib 's and .a 's)
#include_directories(${PROJECT_SOURCE_DIR}/SDL_image/include)          #Include project include directory(headers)
#link_directories(${PROJECT_SOURCE_DIR}/SDL_image/lib)                 #Include lib folder (for .lib 's and .a 's)


add_executable(bataille_navale_utbm main.c headers/struct.h src/nyanpasu_lib.c headers/nyanpasu_lib.h src/display.c headers/display.h src/missile_attack.c headers/missile_attack.h src/initialization.c headers/initialization.h src/player_interaction.c headers/player_interaction.h common_functions.c common_functions.h src/save.c headers/save.h src/active_mode.c headers/active_mode.h headers/gui.h src/gui.c src/linked_list.c headers/linked_list.h)
