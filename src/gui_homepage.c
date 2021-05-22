//
// Created by thgir on 28/04/2021.
//

#include "../headers/gui_homepage.h"

static void display_all_buttons(const Button_list buttonList) {
    for (Button_list_elem *temp = buttonList.first; temp != NULL; temp = temp->next) {
        display_button(temp->this);
        if (!strcmp(temp->this->text, "no"))
            if (temp->this->isActive) {
                SDL_Color color = {240, 240, 240};
                TTF_Font *font = TTF_OpenFont("./font/SEGOEUI.ttf", 18);
                display_text("Difficulty :", font, &color, SCREEN_WIDTH / 2 + 10, 170, 0, 1);
                display_text("Game mode :", font, &color, SCREEN_WIDTH / 2 + 10, 250, 0, 1);
                TTF_CloseFont(font);
            }
    }
}

static void display_homepage_title(TTF_Font *title_font, SDL_Color *color) {
    display_text("Do you want to load", title_font, color, SCREEN_WIDTH / 2, 40, 1, 1);
    display_text("a previous game ?", title_font, color, SCREEN_WIDTH / 2, 80, 1, 1);
}

static void create_backup_buttons(Button_list *buttonList, TTF_Font *font, SDL_Color *color) {
    struct dirent *backup;
    DIR *directory = opendir("save/");
    if (directory != NULL) {
        for (int y = 170; (backup = readdir(directory)) != NULL; y += 40)
            if (strcmp(backup->d_name, ".") != 0 && strcmp(backup->d_name, "..") != 0)
                button_list_push(buttonList, create_button(backup->d_name,
                                                           0, 1, SCREEN_WIDTH / 2 - 160, y, 100, 30,
                                                           font, color));
            else
                y -= 45;
    }
    closedir(directory);
}

static void create_new_game_buttons(Button_list *buttonList, TTF_Font *font, SDL_Color *color) {
    button_list_push(buttonList, create_button("easy", 0, 0,
                                               SCREEN_WIDTH / 2 + 10, 190, 100, 30,
                                               font, color));
    button_list_push(buttonList, create_button("medium", 0, 0,
                                               SCREEN_WIDTH / 2 + 120, 190, 100, 30,
                                               font, color));
    button_list_push(buttonList, create_button("hard", 0, 0,
                                               SCREEN_WIDTH / 2 + 230, 190, 100, 30,
                                               font, color));
    button_list_push(buttonList, create_button("classic", 0, 0,
                                               SCREEN_WIDTH / 2 + 10, 270, 100, 30,
                                               font, color));
    button_list_push(buttonList, create_button("blind", 0, 0,
                                               SCREEN_WIDTH / 2 + 120, 270, 100, 30,
                                               font, color));
    button_list_push(buttonList, create_button("active", 0, 0,
                                               SCREEN_WIDTH / 2 + 230, 270, 100, 30,
                                               font, color));
}

static _Bool is_new_game_button(const Button* button) {
    return !strcmp(button->text, "easy") or !strcmp(button->text, "medium")
           or !strcmp(button->text, "hard") or !strcmp(button->text, "classic")
           or !strcmp(button->text, "blind") or !strcmp(button->text, "active");
}

static _Bool all_parameters_given(Button_list* buttonList) {
    short nbrOfParameters = 0;
    for (Button_list_elem *temp = buttonList->first; temp != NULL; temp = temp->next)
        if (is_new_game_button(temp->this) and temp->this->isActive)
            ++nbrOfParameters;
    return nbrOfParameters == 2;
}

static void remove_new_game_button(Button_list *buttonList) {
    for (Button_list_elem *temp = buttonList->first; temp != NULL; temp = temp->next) {
        if (is_new_game_button(temp->this)) {
            remove_button(buttonList, temp->this);
        }
    }
}

static void
deactivate_other_parameters(Button_list *buttonList, const char *parameter, Game_parameters *gameParameters) {
    if (!strcmp(parameter, "easy")) {
        gameParameters->difficulty = EASY;
        deactivate_button("medium", buttonList);
        deactivate_button("hard", buttonList);
    } else if (!strcmp(parameter, "medium")) {
        gameParameters->difficulty = MEDIUM;
        deactivate_button("easy", buttonList);
        deactivate_button("hard", buttonList);
    } else if (!strcmp(parameter, "hard")) {
        gameParameters->difficulty = HARD;
        deactivate_button("medium", buttonList);
        deactivate_button("easy", buttonList);
    }
    if (!strcmp(parameter, "classic")) {
        gameParameters->mode = CLASSIC;
        deactivate_button("blind", buttonList);
        deactivate_button("active", buttonList);
    } else if (!strcmp(parameter, "blind")) {
        gameParameters->mode = BLIND;
        deactivate_button("classic", buttonList);
        deactivate_button("active", buttonList);
    } else if (!strcmp(parameter, "active")) {
        gameParameters->mode = ACTIVE;
        deactivate_button("classic", buttonList);
        deactivate_button("blind", buttonList);
    }
}

static char *get_file_to_load(const Button_list buttonList) {
    for (Button_list_elem *temp = buttonList.first; temp != NULL; temp = temp->next){
        if (temp->this->isActive and temp->this->isBackup)
            return temp->this->text;
    }
    return NULL;
}

static SDL_bool homepage_button_click(Button *button, Button_list *buttonList, TTF_Font *font, SDL_Color *color,
                                      Game_parameters *gameParameters) {
    button->isActive = 1;
    if (!strcmp(button->text, "confirm"))
        return SDL_FALSE;
    else
        remove_button(buttonList, get_button_by_name(buttonList, "confirm"));
    if (!strcmp(button->text, "yes")) {
        deactivate_button("no", buttonList);
        create_backup_buttons(buttonList, font, color);
        remove_new_game_button(buttonList);
    } else if (!strcmp(button->text, "no")) {
        deactivate_button("yes", buttonList);
        remove_backup_buttons(buttonList);
        create_new_game_buttons(buttonList, font, color);
    } else if (button->isBackup) {
        deactivate_backup_buttons(buttonList);
        button->isActive = 1;
        button_list_push(buttonList, create_button("confirm", 0, 0,
                                                   SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT - 50, 60, 40,
                                                   font, color));
    } else if (is_new_game_button(button)) {
        deactivate_other_parameters(buttonList, button->text, gameParameters);
        if (all_parameters_given(buttonList))
            button_list_push(buttonList, create_button("confirm", 0, 0,
                                                       SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT - 50, 60, 40,
                                                       font, color));
    }
    return SDL_TRUE;
}


const char *home_screen(Game_parameters *gameParameters) {
    TTF_Font *title_font = TTF_OpenFont("./font/SEGOEUI.ttf", 24);
    TTF_Font *button_font = TTF_OpenFont("./font/SEGOEUI.ttf", 12);
    SDL_Color color = {240, 240, 240};
    Button_list buttonList = {NULL};
    Button *hovered = NULL;
    button_list_push(&buttonList, create_button("yes", 0, 0, SCREEN_WIDTH / 2 - 160,
                                                110, 150, 40, title_font, &color));
    button_list_push(&buttonList, create_button("no", 1, 0, SCREEN_WIDTH / 2 + 10,
                                                110, 150, 40, title_font, &color));
    SDL_Event event;
    SDL_bool run = SDL_TRUE;
    while (run) {
        if (SDL_WaitEvent(&event)) {
            SDL_RenderClear(app.renderer);
            cancel_hovering(buttonList);
            SDL_GetMouseState(&cursor.x, &cursor.y);
            hovered = get_hovered_button(buttonList);
            switch (event.type) {
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                        quit_page(title_font, button_font, &buttonList);
                        exit(0);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        if (hovered != NULL)
                            if (!hovered->isActive)
                                run = homepage_button_click(hovered, &buttonList, button_font, &color, gameParameters);
                    }
                default:
                    break;
            }
            display_homepage_title(title_font, &color);
            SDL_SetRenderDrawColor(app.renderer, 240, 240, 240, 250);
            display_all_buttons(buttonList);
            SDL_SetRenderDrawColor(app.renderer, 40, 40, 40, 250);
            SDL_RenderPresent(app.renderer);
        }
    }
    gameParameters->fileName = get_file_to_load(buttonList);
    quit_page(title_font, button_font, &buttonList);
}