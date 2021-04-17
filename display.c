//
// Created by thgir on 17/04/2021.
//

#include "display.h"

void show_grid() {
    for (int i = 0; i < grid.height; ++i) {
        for (int j = 0; j < grid.width; ++j) {
            printf(" %d", grid.grid[i][j]);
        }
        puts("");
    }
}