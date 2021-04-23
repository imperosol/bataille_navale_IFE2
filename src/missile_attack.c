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
        update_x_y_in_boat(&x, &y, boat->orientation);
    }
}

static void  damage_boat(Boat * boat, const int line, const int row){
    boat->health_points--;
    grid.grid[line][row] = DAMAGED;
}

static int shot_on_boat(Boat * boat, const int line, const int row, const _Bool isTactical) {
    int x = boat->position[LEFT];
    int y = boat->position[TOP];
    for (int i = 0; i < boat->size; ++i) {
        if (x == row and y == line) {
            isTactical ? destroy_boat(boat) : damage_boat(boat, line, row);
            printf("%c%d : hit ", 'A' + line, row + 1);
            printf(boat->health_points ? "\n" : "and sunk\n");
            return 1;
        }
        update_x_y_in_boat(&x, &y, boat->orientation);
    }
    return 0;
}

static void shot_on_cell(const int line, const int row, const _Bool isTactical) {
    if (grid.grid[line][row] == OCCUPIED) {
        for (int i = 0; i < NBR_OF_BOATS; ++i) {
            if (shot_on_boat(&boatList[i], line, row, isTactical))
                break;
        }
    } else if (grid.grid[line][row] == EMPTY) {
        grid.grid[line][row] = MISSED_SHOT;
    }
}

void fire_artillery(const int line, const int row) {
    for (int i = 0; i < grid.width; ++i) {
        shot_on_cell(line, i, 0);
    }
    for (int i = 0; i < grid.height; ++i) {
        shot_on_cell(i, row, 0);
    }
    inventory.artillery--;
}

void fire_bomb(const int line, const int row){
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            if (0 <= line + i and line + i < grid.height
            and 0 <= row + j and row + j < grid.width) {
                shot_on_cell(line + i, row + j, 0);
            }
        }
        if (i != 0) {
            shot_on_cell(line + i * 2, row, 0);
            shot_on_cell(line, row + i * 2, 0);
        }
    }
    inventory.bomb--;
}

void fire_tactical(const int line, const int row){
    shot_on_cell(line, row, 1);
    inventory.tactical--;
}

void fire_simple_missile(const int line, const int row) {
    shot_on_cell(line, row, 0);
    inventory.simple_missile--;
}

void tenno_heika_banzai(const int line, const int row, const AttackType_e attackType) {
    switch (attackType) {
        case ARTILLERY:
            fire_artillery(line, row);
            break;
        case TACTICAL:
            fire_tactical(line, row);
            break;
        case BOMB:
            fire_bomb(line, row);
            break;
        case SIMPLE_MISSILE:
            fire_simple_missile(line, row);
            break;
        default:
            break;
    }
}