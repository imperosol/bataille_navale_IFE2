//
// Created by thgir on 18/04/2021.
//

#include "common_functions.h"

void update_x_y_in_boat(int *x, int *y, const int orientation) {
    *x += orientation == H ? 0 : 1;
    *y += orientation == V ? 0 : 1;
}

_Bool is_cell_in_grid(const int line, const int row) {
    return (0 <= line and line < grid.height and 0 <= row and row < grid.width);
}