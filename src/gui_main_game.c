//
// Created by thgir on 28/04/2021.
//

#include "../headers/gui_main_game.h"

static char cell_state_debug(int cell) {
    switch (cell) {
        case EMPTY:
            return '-';
        case DAMAGED:
            return 'X';
        case MISSED_SHOT:
            return '0';
        default:
            return '1';
    }
}

static void display_grid_lines(int *fireCoord) {
    SDL_Rect rect;
    set_rect(&rect, GRID_LEFT - CELL_SIDE / 2, GRID_TOP - CELL_SIDE / 2,
             grid.width * CELL_SIDE, grid.height * CELL_SIDE);
    SDL_RenderDrawRect(app.renderer, &rect);
    if (fireCoord[0] != -1) {
        set_rect(&rect, GRID_LEFT + fireCoord[0] * CELL_SIDE - 10, GRID_TOP + fireCoord[1] * CELL_SIDE - 10,
                 CELL_SIDE, CELL_SIDE);
        SDL_RenderDrawRect(app.renderer, &rect);
    }
}

static void display_grid_gui(TTF_Font *font, int *fireCoord, const _Bool isBlind) {
    char symbol[2];
    SDL_Color color = {240, 240, 240};
    display_grid_lines(fireCoord);
    display_text("A    B     C    D    E     F    G    H     I     J",
                 font, &color, GRID_LEFT - 5, GRID_TOP - CELL_SIDE, 0, 1);
    for (int i = 0, posY = GRID_TOP; i < grid.height; ++i, posY += CELL_SIDE) {
        symbol[0] = '1' + i;
        display_text(symbol, font, &color, GRID_LEFT - CELL_SIDE, posY, 1, 1);
        if (!isBlind) {
            for (int j = 0, posX = GRID_LEFT; j < grid.width; ++j, posX += CELL_SIDE) {
                symbol[0] = cell_state_debug(grid.grid[i][j]);
                if (symbol[0] != '-') {
                    if (symbol[0] == 'X') {
                        SDL_RenderDrawLine(app.renderer, posX - CELL_SIDE / 4, posY - CELL_SIDE / 4,
                                           posX + CELL_SIDE / 4, posY + CELL_SIDE / 4);
                        SDL_RenderDrawLine(app.renderer, posX - CELL_SIDE / 4, posY + CELL_SIDE / 4,
                                           posX + CELL_SIDE / 4, posY - CELL_SIDE / 4);
                    } else if (symbol[0] == '0') {
                        SDL_RenderDrawPoint(app.renderer, posX - 1, posY);
                        SDL_RenderDrawPoint(app.renderer, posX + 1, posY);
                        SDL_RenderDrawPoint(app.renderer, posX, posY - 1);
                        SDL_RenderDrawPoint(app.renderer, posX, posY + 1);
                    } else {
                        display_text(symbol, font, &color, posX, posY, 1, 1);
                    }
                }
            }
        }
    }
}

static void display_remaining_missiles(TTF_Font *font, SDL_Color *color) {
    char missileNumber[6];
    sprintf(missileNumber, "-> %d", inventory.simple_missile);
    display_text(missileNumber, font, color, GRID_LEFT + (grid.width + 2) * CELL_SIDE + 160,
                 GRID_TOP + 15, 0, 1);
    sprintf(missileNumber, "-> %d", inventory.bomb);
    display_text(missileNumber, font, color, GRID_LEFT + (grid.width + 2) * CELL_SIDE + 160,
                 GRID_TOP + 55, 0, 1);
    sprintf(missileNumber, "-> %d", inventory.tactical);
    display_text(missileNumber, font, color, GRID_LEFT + (grid.width + 2) * CELL_SIDE + 160,
                 GRID_TOP + 95, 0, 1);
    sprintf(missileNumber, "-> %d", inventory.artillery);
    display_text(missileNumber, font, color, GRID_LEFT + (grid.width + 2) * CELL_SIDE + 160,
                 GRID_TOP + 135, 0, 1);
}

static void display_remaining_boats_gui(TTF_Font *font, SDL_Color *color) {
    SDL_Rect rect;
    char healthPoints[5];
    int posY = GRID_TOP + grid.height * CELL_SIDE + 10;
    const int posX = GRID_LEFT - CELL_SIDE;
    for (int i = 0; i < NBR_OF_BOATS; ++i) {
        if (boatList[i].health_points) {
            set_rect(&rect, posX, posY, 220, 30);
            SDL_RenderDrawRect(app.renderer, &rect);
            display_text(boat_type(&boatList[i]), font, color, posX + 10, posY + 15, 0, 1);
            sprintf(healthPoints, "%d HP", boatList[i].health_points);
            display_text(healthPoints, font, color, posX + 180, posY + 15, 0, 1);
            posY += 29;
        }
    }
}

static _Bool is_mouse_in_grid(void) {
    return GRID_LEFT - CELL_SIDE / 2 < cursor.x and cursor.x < GRID_LEFT + grid.width * CELL_SIDE - CELL_SIDE / 2
           and GRID_TOP - CELL_SIDE / 2 < cursor.y and cursor.y < GRID_TOP + grid.height * CELL_SIDE - CELL_SIDE / 2;
}

static void grid_hovering(int *hoveredCell) {
    if (is_mouse_in_grid()) {
        SDL_Rect rect;
        rect.x = cursor.x - (cursor.x) % CELL_SIDE;
        rect.y = cursor.y - (cursor.y) % CELL_SIDE;
        rect.h = rect.w = CELL_SIDE;
        SDL_RenderDrawRect(app.renderer, &rect);
        hoveredCell[0] = (rect.x + 10 - GRID_LEFT) / CELL_SIDE; // x
        hoveredCell[1] = (rect.y + 10 - GRID_TOP) / CELL_SIDE; // y
    }
}

static void create_button_list(Button_list *buttonList, TTF_Font *font, SDL_Color *color) {
    button_list_push(buttonList, create_button("simple missile", 0, 0,
                                               GRID_LEFT + (grid.width + 2) * CELL_SIDE, GRID_TOP,
                                               150, 30, font, color));
    button_list_push(buttonList, create_button("bombs", 0, 0,
                                               GRID_LEFT + (grid.width + 2) * CELL_SIDE, GRID_TOP + 40,
                                               150, 30, font, color));
    button_list_push(buttonList, create_button("tactical missile", 0, 0,
                                               GRID_LEFT + (grid.width + 2) * CELL_SIDE, GRID_TOP + 80,
                                               150, 30, font, color));
    button_list_push(buttonList, create_button("artillery missile", 0, 0,
                                               GRID_LEFT + (grid.width + 2) * CELL_SIDE, GRID_TOP + 120,
                                               150, 30, font, color));
    button_list_push(buttonList, create_button("save", 0, 0, SCREEN_WIDTH - 200,
                                               200, 75, 40, font, color));
}

static _Bool is_missile_button(const Button *button) {
    return (!strcmp(button->text, "simple missile") or !strcmp(button->text, "bombs")
            or !strcmp(button->text, "tactical missile") or !strcmp(button->text, "artillery missile"));
}

static void create_confirm_button(Button_list* buttonList, TTF_Font* font, SDL_Color* color, _Bool * buttonExists) {
    button_list_push(buttonList, create_button("confirm", 0, 0,
                                               GRID_LEFT + (grid.width + 2) * CELL_SIDE + 35,
                                               GRID_TOP + (grid.height + 2) * CELL_SIDE,
                                               75, 40, font, color));
    *buttonExists = 1;
}

static void deactivate_other_missile_button(const Button_list *buttonList, const char *remainActive) {
    for (Button_list_elem *temp = buttonList->first; temp != NULL; temp = temp->next) {
        if (is_missile_button(temp->this) and strcmp(temp->this->text, remainActive))
            temp->this->isActive = 0;
    }
}

static void deactivate_all_missile_buttons(const Button_list * buttonList){
    for (Button_list_elem *temp = buttonList->first; temp != NULL; temp = temp->next)
        if (is_missile_button(temp->this))
            temp->this->isActive = 0;
}

static Button *get_chosen_missile(Button_list * buttonList) {
    for (Button_list_elem* temp = buttonList->first; temp != NULL; temp = temp->next) {
        if (is_missile_button(temp->this))
            if (temp->this->isActive)
                return temp->this;
    }
    return NULL;
}
static void main_game_button_push(Button *button, Button_list *buttonList, TTF_Font *font, SDL_Color *color,
                                  _Bool *confirmButtonExists, int *fireCoord,
                                  const Game_parameters *gameParameters) {
    button->isActive = 1;
    if (is_missile_button(button)) {
        deactivate_other_missile_button(buttonList, button->text);
        if (fireCoord[0] != -1 and !*confirmButtonExists)
            create_confirm_button(buttonList, font, color, confirmButtonExists);
    } else if (!strcmp("confirm", button->text)) {
        validate_turn(fireCoord, get_chosen_missile(buttonList)->text, gameParameters, buttonList,
                      confirmButtonExists);
    }
}

static _Bool is_missile_chosen(Button_list * buttonList) {
    for (Button_list_elem* temp = buttonList->first; temp != NULL; temp = temp->next) {
        if (is_missile_button(temp->this))
            if (temp->this->isActive)
                return 1;
    }
    return 0;
}

static void grid_click(int *fireCoord, int *hoveredCell, Button_list *buttonList, TTF_Font *font, SDL_Color *color,
                       _Bool *confirmButtonExists) {
    fireCoord[0] = hoveredCell[0];
    fireCoord[1] = hoveredCell[1];
    if (!*confirmButtonExists)
        if (is_missile_chosen(buttonList))
            create_confirm_button(buttonList, font, color, confirmButtonExists);
}

static void remove_confirm_button(Button_list* buttonList, _Bool *confirmButtonExists) {
    for (Button_list_elem * temp = buttonList->first; temp != NULL; temp = temp->next) {
        if (!strcmp("confirm", temp->this->text)){
            remove_button(buttonList, temp->this);
        }
    }
    *confirmButtonExists = 0;
}

static void stop_hovering_button_if_no_missile(Button * button) {
    if (button != NULL)
        if (is_missile_button(button)) {
            if (inventory.simple_missile == 0 and !strcmp("simple missile", button->text))
                button->isHovered = 0;
            else if (inventory.bomb == 0 and !strcmp("bombs", button->text))
                button->isHovered = 0;
            else if (inventory.tactical == 0 and !strcmp("tactical missile", button->text))
                button->isHovered = 0;
            else if (inventory.artillery == 0 and !strcmp("artillery missile", button->text))
                button->isHovered = 0;
        }
}

static void validate_turn(int *fireCoord, const char *missileName, const Game_parameters *gameParameters,
                          Button_list *buttonList, _Bool *confirmButtonExists) {
    autosave(gameParameters->difficulty, gameParameters->mode);
    AttackType_e attackType;
    if (!strcmp("simple missile", missileName))
        attackType = SIMPLE_MISSILE;
    else if (!strcmp("bombs", missileName))
        attackType = BOMB;
    else if (!strcmp("tactical missile", missileName))
        attackType = TACTICAL;
    else if (!strcmp("artillery missile", missileName))
        attackType = ARTILLERY;
    tenno_heika_banzai(fireCoord[1], fireCoord[0], attackType);
    remove_confirm_button(buttonList, confirmButtonExists);
    fireCoord[0] = -1;
    fireCoord[1] = -1;
    deactivate_all_missile_buttons(buttonList);
}

void main_game_screen(const Game_parameters *gameParameters) {
    TTF_Font *title_font = TTF_OpenFont("./font/SEGOEUI.ttf", 24);
    TTF_Font *button_font = TTF_OpenFont("./font/SEGOEUI.ttf", 12);
    SDL_Color color = {240, 240, 240};
    Button_list buttonList = {NULL};
    create_button_list(&buttonList, button_font, &color);
    int fireCoord[2] = {-1}, hoveredCell[2];
    char backupFileName[20] = "";
    _Bool confirmButtonExists = 0;
    Button *hovered = NULL;
    Uint32 lastTicks, currentTicks;
    SDL_Event event;
    SDL_bool run = SDL_TRUE;
    while (run) {
        if (SDL_WaitEvent(&event)) {
            lastTicks = SDL_GetTicks();
            SDL_RenderClear(app.renderer);
            SDL_SetRenderDrawColor(app.renderer, 240, 240, 240, 250);
            cancel_hovering(buttonList);
            SDL_GetMouseState(&cursor.x, &cursor.y);
            hovered = get_hovered_button(buttonList);
            stop_hovering_button_if_no_missile(hovered);
            grid_hovering(hoveredCell);
            switch (event.type) {
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                        run = SDL_FALSE;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        if (hovered != NULL) {
                            if (!hovered->isActive and hovered->isHovered)
                                main_game_button_push(hovered, &buttonList, button_font,
                                                      &color, &confirmButtonExists, fireCoord, gameParameters);
                        } else if (is_mouse_in_grid())
                            grid_click(fireCoord, hoveredCell, &buttonList, button_font, &color, &confirmButtonExists);
                    }
                default:
                    break;
            }
//            display_text("C'est Yamato !", title_font, &color, SCREEN_WIDTH / 2, 40, 1, 1);
            display_grid_gui(button_font, fireCoord, gameParameters->mode);
            display_all_buttons(buttonList);
            display_remaining_missiles(button_font, &color);
            display_remaining_boats_gui(button_font, &color);
            SDL_SetRenderDrawColor(app.renderer, 40, 40, 40, 250);
            SDL_RenderPresent(app.renderer);
//            printf("%d\n", SDL_GetTicks() - lastTicks);
        }
    }
    TTF_CloseFont(title_font);
    TTF_CloseFont(button_font);
    while (buttonList.first != NULL)
        remove_button(&buttonList, buttonList.first->this);
}
