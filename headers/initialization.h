//
// Created by thgir on 17/04/2021.
//

#ifndef BATAILLE_NAVALE_UTBM_INITIALIZATION_H
#define BATAILLE_NAVALE_UTBM_INITIALIZATION_H

#include "struct.h"
#include "standard_functions.h"

static void initialize_grid(void);

static void initialize_boat_array(void);

static void initialize_inventory(void);

void initialize_new_game(void);

static void set_boats_on_grid(void);

static void place_boat(const int i);

static int is_valid_position(int x, int y, const int boatSize, const int orientation);


#endif //BATAILLE_NAVALE_UTBM_INITIALIZATION_H
