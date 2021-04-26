//
// Created by thgir on 24/04/2021.
//

#ifndef BATAILLE_NAVALE_UTBM_GUI_H
#define BATAILLE_NAVALE_UTBM_GUI_H

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 500

#include <dirent.h>
#include <stdio.h>
#include "linked_list.h"
#include "struct.h"
#ifndef WIN32
#include <sys/types.h>
#endif

void initialize_SDL();

void create_window(const char* title);

void create_home_page(TTF_Font* title_font, TTF_Font* button_font);

void display_text(const char* text, TTF_Font* font, SDL_Color* color,
                  const int x, const int y, const _Bool isCentered);

void display_button(const Button* button);

const char *home_screen(Game_parameters *gameParameters);

struct App {
    SDL_Renderer * renderer;
    SDL_Window * window;
};
struct App app;

SDL_Point cursor;

#endif //BATAILLE_NAVALE_UTBM_GUI_H
