//
// Created by thgir on 23/04/2021.
//

#include "../headers/active_mode.h"
#include "../common_functions.h"

static _Bool is_movable(const Boat* boat) {
    return boat->size == boat->health_points;
}

static int get_nbr_of_movable_boats() {
    short remainingBoats = 0;
    for (int i = 0; i < NBR_OF_BOATS; ++i) {
        if (is_movable(&boatList[i]))
            ++remainingBoats;
    }
    return remainingBoats;
}

static Boat* get_boat_to_move() {
    const int remainingBoats = get_nbr_of_movable_boats();
    int random;
    int chosenBoat;
    /* Get randomly a boat among the remaining boat */
    random = rand() % remainingBoats + 1;
    for (int i=0; random > 0; ++i) {
        if (boatList[i].health_points > 0) {
            --random;
            chosenBoat = i;
        }
    }
    return &boatList[chosenBoat];
}

static int get_direction() {
    /* randomly return -1 or 1 */
    return 1 - 2 * (rand() % 2);
}

static _Bool is_cell_available(const Boat* boat, const int movement_size, const int direction) {
    int x = boat->position[LEFT];
    int y = boat->position[TOP];
    if (boat->orientation == H) {
        if (direction == 1)
            y += boat->size + movement_size - 1;
        else
            y -= movement_size;
    } else {
        if (direction == 1)
            x += boat->size + movement_size - 1;
        else
            x -= movement_size;
    }
    if (is_cell_in_grid(y, x)) {
        char cell = grid.grid[y][x];
        return (cell != OCCUPIED and cell != DAMAGED);
    }
    return 0;
}

static int get_cell_to_move_in(const Boat* boat) {
    int movement[2] = {0, 0};
    for (int h = 0; h < 2; ++h)
        for (int i = 1; i < 4; ++i)
            if (is_cell_available(boat, i, 1-h))
                movement[h]++;
//    printf("%d ; %d\n", movement[BACKWARD]++, movement[FORWARD]++);
    if (movement[FORWARD] != movement[BACKWARD])
        return movement[FORWARD] > movement[BACKWARD] ? movement[FORWARD] : -movement[BACKWARD];
    else
        return rand() % 2 ? movement[FORWARD] : -movement[BACKWARD];
}

static void move_boat(Boat* boat, const int movementSize) {
    int x = boat->position[LEFT];
    int y = boat->position[TOP];
    for (int j = 0; j < boat->size; ++j) {
        grid.grid[y][x] = EMPTY;
        update_x_y_in_boat(&x, &y, boat->orientation);
    }
    if (boat->orientation == V)
        x = boat->position[LEFT] += movementSize;
    else
        y = boat->position[TOP] += movementSize;
    for (int j = 0; j < boat->size; ++j) {
        grid.grid[y][x] = OCCUPIED;
        update_x_y_in_boat(&x, &y, boat->orientation);
    }
}


void active_mode() {
    Boat *toMove = get_boat_to_move();
    int movementSize = get_cell_to_move_in(toMove);
    move_boat(toMove, movementSize);
}