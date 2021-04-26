//
// Created by thgir on 18/04/2021.
//

#ifndef BATAILLE_NAVALE_UTBM_COMMON_FUNCTIONS_H
#define BATAILLE_NAVALE_UTBM_COMMON_FUNCTIONS_H

#include "headers/struct.h"

void update_x_y_in_boat(int *x, int *y, const int orientation);

_Bool is_cell_in_grid(const int line, const int row);
#endif //BATAILLE_NAVALE_UTBM_COMMON_FUNCTIONS_H
