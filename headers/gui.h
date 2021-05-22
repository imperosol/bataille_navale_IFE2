//
// Created by thgir on 24/04/2021.
//

#ifndef BATAILLE_NAVALE_UTBM_GUI_H
#define BATAILLE_NAVALE_UTBM_GUI_H

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 500

#define FPS 60

#include <dirent.h>
#include <stdio.h>
#include "linked_list.h"
#include "struct.h"
#ifndef WIN32
    #include <sys/types.h>
#endif

void initialize_SDL();

void create_window(const char* title);

void set_rect(SDL_Rect *rect, const int x, const int y, const int w, const int h);

Button *create_button(const char *text, _Bool isHovered, const _Bool isBackup,
                             const int x, const int y, const int w,
                             const int h, TTF_Font *font, SDL_Color *fontColor);


void display_text(const char *text, TTF_Font *font, SDL_Color *color, const int x, const int y, const _Bool isCenteredX,
                  const _Bool isCenteredY);

void display_button(const Button* button);

//void display_all_buttons(const Button_list buttonList);

Button *get_hovered_button(const Button_list buttonList);

void cancel_hovering(const Button_list buttonList);

void remove_backup_buttons(Button_list *buttonList);

void deactivate_button(const char *text, const Button_list *buttonList);

void deactivate_backup_buttons(const Button_list *buttonList);

Button *get_button_by_name(const Button_list *buttonList, const char *text);

void control_framerate(const Uint32 lastTick);

void quit_page(TTF_Font * title_font, TTF_Font * button_font, Button_list * buttonList);


struct App {
    SDL_Renderer * renderer;
    SDL_Window * window;
};
struct App app;

SDL_Point cursor;

#endif //BATAILLE_NAVALE_UTBM_GUI_H
