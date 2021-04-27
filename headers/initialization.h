//
// Created by thgir on 17/04/2021.
//

#ifndef BATAILLE_NAVALE_UTBM_INITIALIZATION_H
#define BATAILLE_NAVALE_UTBM_INITIALIZATION_H

#include "struct.h"
#include "../common_functions.h"
#include "nyanpasu_lib.h"
#include "display.h"

static void initialize_grid(void);

static void initialize_boat_array(void);

static void initialize_inventory(Difficulty_e difficulty);

void initialize_new_game(Difficulty_e difficulty);

static void set_boats_on_grid(void);

static void place_boat(int i);

static int is_valid_position(int x, int y, int boatSize, int orientation);

void set_inventory(short art, short tact, short bomb, short simple);

void load_game(Difficulty_e *difficulty, Mode_e *mode);

void load_game_gui(Difficulty_e *difficulty, Mode_e *mode, const char* fileName);


#endif //BATAILLE_NAVALE_UTBM_INITIALIZATION_H
