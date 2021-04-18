//
// Created by thgir on 18/04/2021.
//

#ifndef BATAILLE_NAVALE_UTBM_SAVE_H
#define BATAILLE_NAVALE_UTBM_SAVE_H

#include "nyanpasu_lib.h"
#include "struct.h"

void save(const char * fileName, Difficulty_e difficulty, Mode_e mode);

void autosave();

void manual_save();

#endif //BATAILLE_NAVALE_UTBM_SAVE_H
