//
// Created by thgir on 17/04/2021 at 14:18.
//

#ifndef BATAILLE_NAVALE_UTBM_STRUCT_H
#define BATAILLE_NAVALE_UTBM_STRUCT_H

#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define and &&
#define or ||

#define V 0
#define H 1

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
Boat boatList[NBR_OF_BOATS];

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

/* structs for the gui */


typedef struct {
    char text[20];
    _Bool isHovered;
    _Bool isBackup;
    _Bool isActive;
    SDL_Rect rect;
    TTF_Font * font;
    SDL_Color * fontColor;
} Button;

typedef struct Button_list_elem Button_list_elem;
struct Button_list_elem {
    Button* this;
    Button_list_elem* next;
};

typedef struct {
    Button_list_elem * first;
} Button_list;

typedef struct {
    Mode_e mode;
    Difficulty_e difficulty;
    char *fileName;
} Game_parameters;



#endif //BATAILLE_NAVALE_UTBM_STRUCT_H
