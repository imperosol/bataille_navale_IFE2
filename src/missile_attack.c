//
// Created by thgir on 17/04/2021.
//

#include "../headers/missile_attack.h"

static void destroy_boat(Boat * boat){
    boat->health_points = 0;
    int x = boat->position[LEFT];
    int y = boat->position[TOP];
    for (int i = 0; i < boat->size; ++i) {
        grid.grid[y][x] = DAMAGED;
        x += (boat->orientation == H);
        y += (boat->orientation == V);
    }
}

static void  damage_boat(Boat * boat, const int line, const int row){
    boat->health_points--;
    grid.grid[row][line] = DAMAGED;
}

static int shot_on_boat(Boat * boat, const int line, const int row, const _Bool isTactical) {
    int x = boat->position[LEFT];
    int y = boat->position[TOP];
    for (int i = 0; i < boat->size; ++i) {
        if (x == row and y == line) {
            isTactical ? destroy_boat(boat) : damage_boat(boat, line, row);
            printf("%c%d : hit ", 'A' + row, line);
            printf(boat->health_points ? "\n" : "and sunk\n");
            return 1;
        }
        x += (boat->orientation == H);
        y += (boat->orientation == V);
    }
    return 0;
}

static void shot_on_cell(const int line, const int row, const _Bool isTactical) {
    if (grid.grid[row][line] == OCCUPIED) {
        for (int i = 0; i < 5; ++i) {
            if (shot_on_boat(&boatList[i], line, row, isTactical))
                break;
        }
    }
}

void fire_artillery(const int line, const int row) {
    for (int i = 0; i < grid.width; ++i) {
        shot_on_cell(line, i, 0);
    }
    for (int i = 0; i < grid.height; ++i) {
        shot_on_cell(i, row, 0);
    }
}

void fire_bomb(const int line, const int row){
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            if (0 <= line + i and line + i < 10 and 0 <= row + j and row + j < 10) {
                shot_on_cell(line + i, row + j, 0);
            }
        }
    }
}

void fire_tactical(const int line, const int row){
    shot_on_cell(line, row, 1);
}

void fire_simple_missile(const int line, const int row) {
    shot_on_cell(line, row, 0);
}
