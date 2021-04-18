//
// Created by thgir on 17/04/2021.
//

#ifndef BATAILLE_NAVALE_UTBM_INITIALIZATION_H
#define BATAILLE_NAVALE_UTBM_INITIALIZATION_H

#include "struct.h"
#include "standard_functions.h"

static void initialize_grid(void);

static void initialize_boat_array(void);

static void initialize_inventory(Difficulty_e difficulty);

void initialize_new_game(Difficulty_e difficulty);

static void set_boats_on_grid(void);

static void place_boat(const int i);

static int is_valid_position(int x, int y, const int boatSize, const int orientation);

void set_inventory(const short art, const short tact, const short bomb, const short simple);


#endif //BATAILLE_NAVALE_UTBM_INITIALIZATION_H
