//
// Created by thgir on 28/04/2021.
//

#ifndef BATAILLE_NAVALE_UTBM_GUI_HOMEPAGE_H
#define BATAILLE_NAVALE_UTBM_GUI_HOMEPAGE_H

#include "gui.h"

static void display_homepage_title(TTF_Font *title_font, SDL_Color *color);

static void create_backup_buttons(Button_list *buttonList, TTF_Font *font, SDL_Color *color);

static void create_new_game_buttons(Button_list *buttonList, TTF_Font *font, SDL_Color *color);

static _Bool is_new_game_button(const Button* button);

static void display_all_buttons(const Button_list buttonList);

static _Bool all_parameters_given(Button_list* buttonList);

static void remove_new_game_button(Button_list *buttonList);

static void deactivate_other_parameters(Button_list *buttonList, const char *parameter,
                                        Game_parameters *gameParameters);

static char *get_file_to_load(const Button_list buttonList);

static SDL_bool homepage_button_click(Button *button, Button_list *buttonList, TTF_Font *font, SDL_Color *color,
                                      Game_parameters *gameParameters);

const char *home_screen(Game_parameters *gameParameters);


#endif //BATAILLE_NAVALE_UTBM_GUI_HOMEPAGE_H
