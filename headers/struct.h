//
// Created by thgir on 17/04/2021 at 14:18.
//

#ifndef BATAILLE_NAVALE_UTBM_STRUCT_H
#define BATAILLE_NAVALE_UTBM_STRUCT_H

#include <time.h>

#define and &&
#define or ||

#define H 0
#define V 1

#define TOP 0
#define LEFT 1

#define EMPTY 0
#define OCCUPIED 1
#define DAMAGED 2
#define MISSED_SHOT 3

#define EXIT 0
#define CONTINUE 1

#define NBR_OF_BOATS 5

typedef struct {
    int height;
    int width;
    char ** grid;
} Grid;
Grid grid;

typedef struct {
    unsigned short artillery;
    unsigned short tactical;
    unsigned short bomb;
    unsigned short simple_missile;
} Inventory;
Inventory inventory;

typedef struct {
    unsigned short position[2];
    unsigned short size;
    unsigned short orientation;
    unsigned health_points;
} Boat;
Boat boatList[5];

typedef enum {
    EASY,
    MEDIUM,
    HARD
} Difficulty_e;

typedef enum {
    CLASSIC,
    BLIND,
    ACTIVE
} Mode_e;

typedef enum {
    ARTILLERY,
    TACTICAL,
    BOMB,
    SIMPLE_MISSILE
} AttackType_e;

#endif //BATAILLE_NAVALE_UTBM_STRUCT_H
