//
// Created by thgir on 17/04/2021 at 14:18.
//

#ifndef BATAILLE_NAVALE_UTBM_STRUCT_H
#define BATAILLE_NAVALE_UTBM_STRUCT_H

#include <time.h>

#define H 0
#define V 1

#define TOP 0
#define LEFT 1

#define EMPTY 0
#define OCCUPIED 1
#define DAMAGED 2

#define CLASSIC 0
#define BLIND 1
#define ACTIVE 2

typedef struct {
    int height;
    int width;
    _Bool ** grid;
} Grid;
Grid grid;

typedef struct {
    unsigned short artillery;
    unsigned short tactical;
    unsigned short bomb;
    unsigned short simple_missile;
} Inventory;

typedef struct {
    unsigned short position[2];
    unsigned short size;
    unsigned short orientation;
    unsigned health_points;
} Boat;
Boat boatList[5];

#endif //BATAILLE_NAVALE_UTBM_STRUCT_H
