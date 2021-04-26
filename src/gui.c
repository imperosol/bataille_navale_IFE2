//
// Created by thgir on 24/04/2021.
//

#include "../headers/gui.h"

void initialize_SDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        printf("window initialization failure due to : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
/*    if (IMG_Init(IMG_INIT_PNG) == -1) {
        printf("window initialization failure due to");
        exit(EXIT_FAILURE);
    }*/
    if (SDL_Init(TTF_Init()) == -1) {
        printf("window initialization failure due to");
        exit(EXIT_FAILURE);
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
}

void create_window(const char *title) {
    app.window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
//    SDL_RenderSetLogicalSize(app.renderer, 1920, 1280);
//    SDL_RenderSetScale(app.renderer, 1, 1);
}

static void set_rect(SDL_Rect *rect, const int x, const int y, const int w, const int h) {
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
}

static Button *create_button(const char *text, _Bool isHovered, const _Bool isBackup,
                             const int x, const int y, const int w,
                             const int h, TTF_Font *font, SDL_Color *fontColor) {
    Button *new = safe_malloc(sizeof(Button));
    strcpy(new->text, text);
    new->isHovered = isHovered;
    new->isActive = 0;
    new->fontColor = fontColor;
    new->font = font;
    new->isBackup = isBackup;
    set_rect(&new->rect, x, y, w, h);
    return new;
}

static void display_homepage_title(TTF_Font *title_font, SDL_Color *color) {
    display_text("Do you want to load", title_font, color, SCREEN_WIDTH / 2, 40, 1);
    display_text("a previous game ?", title_font, color, SCREEN_WIDTH / 2, 80, 1);
}

void display_text(const char *text, TTF_Font *font, SDL_Color *color,
                  const int x, const int y, const _Bool isCentered) {
    SDL_Rect r;
    r.x = x;
    r.y = y;
    SDL_Surface *pageText = TTF_RenderText_Solid(font, text, *color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(app.renderer, pageText);
    SDL_QueryTexture(texture, NULL, NULL, &r.w, &r.h);
    if (isCentered != 0)
        r.x -= r.w / 2;
    r.y -= r.h / 2;
    SDL_RenderCopy(app.renderer, texture, NULL, &r);
    SDL_FreeSurface(pageText);
    SDL_DestroyTexture(texture);
}


void display_button(const Button *button) {
    SDL_RenderDrawRect(app.renderer, &button->rect);
    if (button->isHovered or button->isActive) {
        SDL_Rect hoverRect = button->rect;
        set_rect(&hoverRect, hoverRect.x + 2, hoverRect.y + 2, hoverRect.w - 4, hoverRect.h - 4);
        SDL_RenderDrawRect(app.renderer, &hoverRect);
    }
    display_text(button->text,
                 button->font,
                 button->fontColor,
                 button->rect.x + button->rect.w / 2,
                 button->rect.y + button->rect.h / 2,
                 1);
}

static void display_all_buttons(const Button_list buttonList) {
    for (Button_list_elem *temp = buttonList.first; temp != NULL; temp = temp->next) {
        display_button(temp->this);
    }
}

static Button *get_hovered_button(const Button_list buttonList) {
    for (Button_list_elem *temp = buttonList.first; temp != NULL; temp = temp->next) {
        if (temp->this->rect.x < cursor.x and cursor.x < temp->this->rect.x + temp->this->rect.w
            and temp->this->rect.y < cursor.y and cursor.y < temp->this->rect.y + temp->this->rect.h) {
            temp->this->isHovered = 1;
            return temp->this;
        }
    }
    return NULL;
}

static void cancel_hovering(const Button_list buttonList) {
    for (Button_list_elem *temp = buttonList.first; temp != NULL; temp = temp->next) {
        temp->this->isHovered = 0;
    }
}

static void create_backup_buttons(Button_list *buttonList, TTF_Font *font, SDL_Color *color) {
    struct dirent *backup;
    DIR *directory = opendir("save/");
    if (directory != NULL) {
        for (int y = 105; (backup = readdir(directory)) != NULL; y += 40)
            if (strcmp(backup->d_name, ".") != 0 && strcmp(backup->d_name, "..") != 0)
                button_list_push(buttonList, create_button(backup->d_name,
                                                           0, 1, SCREEN_WIDTH / 2 - 160, y, 100, 30,
                                                           font, color));
    }
    closedir(directory);
}

static void remove_backup_buttons(Button_list *buttonList) {
    for (Button_list_elem *temp = buttonList->first; temp != NULL; temp = temp->next) {
        if (temp->this->isBackup) {
            remove_button(buttonList, temp->this);
        }
    }
}

static void deactivate_button(const char *text, const Button_list *buttonList) {
    for (Button_list_elem *temp = buttonList->first; temp != NULL; temp = temp->next) {
        if (!strcmp(temp->this->text, text)) {
            temp->this->isActive = 0;
            break;
        }
    }
}
static void deactivate_backup_buttons(const Button_list *buttonList) {
    for (Button_list_elem *temp = buttonList->first; temp != NULL; temp = temp->next) {
        if (temp->this->isBackup) {
            temp->this->isActive = 0;
        }
    }
}

static Button * get_button_by_name(const Button_list * buttonList, const char * text) {
    for (Button_list_elem *temp = buttonList->first; temp != NULL; temp = temp->next)
        if (!strcmp(temp->this->text, text))
            return temp->this;
    return NULL;
}

static SDL_bool homepage_button_click(Button *button, Button_list *buttonList, TTF_Font *font, SDL_Color *color) {
    button->isActive = 1;
    if (!strcmp(button->text, "confirm"))
        return SDL_FALSE;
    else
        remove_button(buttonList, get_button_by_name(buttonList, "confirm"));
    if (!strcmp(button->text, "yes")) {
        deactivate_button("no", buttonList);
        create_backup_buttons(buttonList, font, color);
    } else if (!strcmp(button->text, "no")) {
        deactivate_button("yes", buttonList);
        remove_backup_buttons(buttonList);
        button_list_push(buttonList, create_button("confirm", 0, 0,
                                                   SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT - 50, 60, 40,
                                                   font, color));
    } else if (button->isBackup) {
        deactivate_backup_buttons(buttonList);
        button->isActive = 1;
        button_list_push(buttonList, create_button("confirm", 0, 0,
                                                   SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT - 50, 60, 40,
                                                   font, color));
    }
    return SDL_TRUE;
}

static const char * get_file_to_load(const Button_list buttonList) {
    for (Button_list_elem *temp = buttonList.first; temp != NULL; temp = temp->next)
        if (temp->this->isActive and temp->this->isBackup)
            return temp->this->text;
    return NULL;
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
                    if (event.window.event == SDL_WINDOWEVENT_CLOSE)
                        run = SDL_FALSE;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        if (hovered != NULL)
                            if (!hovered->isActive)
                                run = homepage_button_click(hovered, &buttonList, button_font, &color);
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
    TTF_CloseFont(title_font);
    TTF_CloseFont(button_font);
    const char* fileName = get_file_to_load(buttonList);
    while (buttonList.first != NULL)
        remove_button(&buttonList, buttonList.first->this);
    return fileName;
}