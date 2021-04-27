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

static void set_rect(SDL_Rect *rect, const int x, const int y, const int w, const int h);

static Button *create_button(const char *text, _Bool isHovered, const _Bool isBackup,
                             const int x, const int y, const int w,
                             const int h, TTF_Font *font, SDL_Color *fontColor);

static void display_homepage_title(TTF_Font *title_font, SDL_Color *color);

void display_text(const char* text, TTF_Font* font, SDL_Color* color,
                  const int x, const int y, const _Bool isCentered);

void display_button(const Button* button);

static void display_all_buttons(const Button_list buttonList);

static Button *get_hovered_button(const Button_list buttonList);

static void cancel_hovering(const Button_list buttonList);

static void create_backup_buttons(Button_list *buttonList, TTF_Font *font, SDL_Color *color);

static void create_new_game_buttons(Button_list *buttonList, TTF_Font *font, SDL_Color *color);

static _Bool is_new_game_button(const Button* button);

static _Bool all_parameters_given(Button_list* buttonList);

static void remove_new_game_button(Button_list *buttonList);

static void remove_backup_buttons(Button_list *buttonList);

static void deactivate_button(const char *text, const Button_list *buttonList);

static void deactivate_backup_buttons(const Button_list *buttonList);

static void deactivate_other_parameters(Button_list *buttonList, const char *parameter,
                            Game_parameters *gameParameters);

static Button *get_button_by_name(const Button_list *buttonList, const char *text);

static SDL_bool homepage_button_click(Button *button, Button_list *buttonList, TTF_Font *font, SDL_Color *color,
                                      Game_parameters *gameParameters);

static char *get_file_to_load(const Button_list buttonList);

const char *home_screen(Game_parameters *gameParameters);

struct App {
    SDL_Renderer * renderer;
    SDL_Window * window;
};
struct App app;

SDL_Point cursor;

#endif //BATAILLE_NAVALE_UTBM_GUI_H
