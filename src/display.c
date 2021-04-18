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
                case DAMAGED:
                    printf(" X");
                    break;
                case MISSED_SHOT:
                    printf(" 0");
                    break;
                default:
                    printf(" 1");
                    break;
            }
        }
        puts("");
    }
    puts("");
}

void display_inventory(void) {
    printf("Inventory : \n"
           "\t---------------------------------\n"
           "\tsimple missiles :\t|  %hd\t|\n"
           "\t------------------------|-------|\n"
           "\tbombs :\t\t\t|  %hd\t|\n"
           "\t------------------------|-------|\n"
           "\ttactical missiles :\t|  %hd\t|\n"
           "\t------------------------|-------|\n"
           "\tartillery missiles :\t|  %hd\t|\n"
           "\t---------------------------------\n\n",
           inventory.simple_missile, inventory.bomb, inventory.tactical, inventory.artillery);
}

static const char * boat_type(const Boat* boat) {
    switch (boat->size) {
        case 2:
            return "Submarine";
        case 3:
            return "Destroyer";
        case 4:
            return "Cruiser  ";
        case 5:
            return "Carrier  ";
        default:
            return "";
    }
}

void display_remaining_boats(void) {
    puts("Remaining boats :");
    for (int i = 0; i < NBR_OF_BOATS; ++i) {
        if (boatList[i].health_points) {
            printf("\t%s\t->\t%d HP\n", boat_type(&boatList[i]), boatList[i].health_points);
        }
    }
}

