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

#define GRID_TOP 90
#define GRID_LEFT 70
#define CELL_SIDE 20

void main_game_screen(const Game_parameters *gameParameters);

static void validate_turn(int *fireCoord, const char *missileName, const Game_parameters *gameParameters,
                          Button_list *buttonList, _Bool *confirmButtonExists);

#endif //BATAILLE_NAVALE_UTBM_GUI_MAIN_GAME_H
