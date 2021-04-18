//
// Created by thgir on 17/04/2021.
//

#include "../headers/initialization.h"
#include "../headers/display.h"

static void initialize_grid(void) {
    /* grid initialization */
    grid.height = grid.width = 10;
    grid.grid = safe_malloc(grid.height * sizeof(_Bool *));
    for (int i = 0; i < grid.height; ++i) {
        grid.grid[i] = safe_malloc(grid.width * sizeof(_Bool));
        memset(grid.grid[i], EMPTY, grid.width * sizeof(_Bool));
    }
}

static void initialize_boat_array(void) {
    for (int i = 0; i < 2; ++i)
        boatList[i].size = i + 2;
    for (int i = 2; i < 5; ++i)
        boatList[i].size = i + 1;
    for (int i = 0; i < 5; ++i)
        boatList[i].health_points = boatList[i].size;
}

static int is_valid_position(int x, int y, const int boatSize, const int orientation) {
    for (int j = 1; j < boatSize; ++j) {
        x = orientation == H ? x : x + 1;
        y = orientation == V ? y : y + 1;
        if (grid.grid[y][x]) {
            /* A boat is already at the tested place */
            return 0;
        }
    }
    return 1;
}

static void place_boat(const int i) {
    int x = boatList[i].position[LEFT];
    int y = boatList[i].position[TOP];
    for (int j = 0; j < boatList[i].size; ++j) {
        grid.grid[y][x] = 1;
        x += (boatList[i].orientation == H);
        y += (boatList[i].orientation == V);
    }
}

static void set_boats_on_grid(void) {
    int x, y;
    for (int i = 4; i >= 0; --i) {
        /* Boats are placed from the end of the list because the biggest boats are more likely
         * to get blocked by already placed boats */
         do {
             boatList[i].orientation = rand() % 2;
            /* According to the orientation of the boat, the top left of the boat can't be placed on
             * some zones in order to avoid to have the back of the boat out of the grid*/
            x = rand() % (grid.width - (boatList[i].size * (boatList[i].orientation == H)));
            y = rand() % (grid.height - (boatList[i].size * (boatList[i].orientation == V)));
        } while (!is_valid_position(x, y, boatList[i].size, boatList[i].orientation));
        boatList[i].position[TOP] = x;
        boatList[i].position[LEFT] = y;

        place_boat(i);
    }
}

static void initialize_inventory(void){
    inventory.artillery = 10;
    inventory.tactical = 10;
    inventory.bomb = 10;
    inventory.simple_missile = 10;
}

void initialize_new_game(void) {
    initialize_grid();
    initialize_boat_array();
    set_boats_on_grid();
    initialize_inventory();
}