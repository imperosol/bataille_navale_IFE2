//
// Created by thgir on 18/04/2021.
//

#ifndef BATAILLE_NAVALE_UTBM_PLAYER_INTERACTION_H
#define BATAILLE_NAVALE_UTBM_PLAYER_INTERACTION_H

#include "headers/struct.h"
#include "headers/standard_functions.h"
#include "headers/missile_attack.h"
#include "headers/display.h"

Difficulty_e ask_difficulty(void);

Mode_e ask_mode(void);

void player_turn(Mode_e mode);

#endif //BATAILLE_NAVALE_UTBM_PLAYER_INTERACTION_H
