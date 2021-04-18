//
// Created by thgir on 17/04/2021.
//

#include "../headers/display.h"

void display_grid(void) {
    for (int i = 0; i < grid.height; ++i) {
        for (int j = 0; j < grid.width; ++j) {
            switch (grid.grid[i][j]) {
                case EMPTY:
                    printf(" _");
                    break;
                case MISSED_SHOT:
                    printf(" 0");
                    break;
                default:
                    printf(" X");
                    break;
            }
        }
        puts("");
    }
}

void display_inventory(void) {
    printf("Inventory : \n"
           "simple missiles :\t%hd\n"
           "bombs :\t%hd\n"
           "tactical missiles :\t%hd\n"
           "artillery missiles :\t%hd\n",
           inventory.simple_missile, inventory.bomb, inventory.tactical, inventory.artillery);
}
