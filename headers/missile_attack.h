//
// Created by thgir on 17/04/2021.
//

#ifndef BATAILLE_NAVALE_UTBM_MISSILE_ATTACK_H
#define BATAILLE_NAVALE_UTBM_MISSILE_ATTACK_H

#include "struct.h"
#include "../common_functions.h"
#include <stdio.h>

void fire_artillery(const int line, const int row);
void fire_bomb(const int line, const int row);
void fire_tactical(const int line, const int row);
void fire_simple_missile(const int line, const int row);
void tenno_heika_banzai(const int line, const int row, const AttackType_e attackType);


#endif //BATAILLE_NAVALE_UTBM_MISSILE_ATTACK_H
