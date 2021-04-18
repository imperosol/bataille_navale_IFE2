//
// Created by thgir on 18/04/2021.
//

#include "common_functions.h"

void update_x_y_in_boat(int *x, int *y, const int orientation) {
    *x += orientation == V ? 0 : 1;
    *y += orientation == H ? 0 : 1;
}
