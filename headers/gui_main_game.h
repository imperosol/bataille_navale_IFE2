//
// Created by thgir on 28/04/2021.
//

#ifndef BATAILLE_NAVALE_UTBM_GUI_MAIN_GAME_H
#define BATAILLE_NAVALE_UTBM_GUI_MAIN_GAME_H

#include "gui.h"
#include "nyanpasu_lib.h"
#include "struct.h"
#include "display.h"
#include "save.h"
#include "missile_attack.h"
#include "active_mode.h"

#define GRID_TOP 90
#define GRID_LEFT 70
#define CELL_SIDE 20

#define GAME_NOT_FINISHED 0
#define HAS_WON 1
#define HAS_LOST 2

static void display_all_buttons(const Button_list buttonList);

void main_game_screen(const Game_parameters *gameParameters);

static void validate_turn(int *fireCoord, const char *missileName, const Game_parameters *gameParameters,
                          Button_list *buttonList, _Bool *confirmButtonExists);

typedef struct {
    SDL_Texture * water;
    SDL_Texture * fire;
} Textures;

#endif //BATAILLE_NAVALE_UTBM_GUI_MAIN_GAME_H
