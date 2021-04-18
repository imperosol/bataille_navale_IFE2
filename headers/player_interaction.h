//
// Created by thgir on 18/04/2021.
//

#ifndef BATAILLE_NAVALE_UTBM_PLAYER_INTERACTION_H
#define BATAILLE_NAVALE_UTBM_PLAYER_INTERACTION_H

#include "struct.h"
#include "nyanpasu_lib.h"
#include "missile_attack.h"
#include "display.h"
#include "save.h"

Difficulty_e ask_difficulty(void);

Mode_e ask_mode(void);

int player_turn(Mode_e mode, Difficulty_e difficulty);

_Bool ask_if_load_game(void);

#endif //BATAILLE_NAVALE_UTBM_PLAYER_INTERACTION_H
