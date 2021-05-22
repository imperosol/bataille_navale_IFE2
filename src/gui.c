//
// Created by thgir on 24/04/2021.
//

#include "../headers/gui.h"

void initialize_SDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        printf("window initialization failure due to : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if (IMG_Init(IMG_INIT_PNG) == -1) {
        printf("window initialization failure due to");
        exit(EXIT_FAILURE);
    }
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
}

void set_rect(SDL_Rect *rect, const int x, const int y, const int w, const int h) {
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
}

Button *create_button(const char *text, _Bool isHovered, const _Bool isBackup,
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


void
display_text(const char *text, TTF_Font *font, SDL_Color *color, const int x, const int y, const _Bool isCenteredX,
             const _Bool isCenteredY) {
    SDL_Rect r;
    r.x = x;
    r.y = y;
    SDL_Surface *pageText = TTF_RenderText_Solid(font, text, *color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(app.renderer, pageText);
    SDL_QueryTexture(texture, NULL, NULL, &r.w, &r.h);
    if (isCenteredX)
        r.x -= r.w / 2;
    if (isCenteredY)
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
                 1, 1);
}


Button *get_hovered_button(const Button_list buttonList) {
    for (Button_list_elem *temp = buttonList.first; temp != NULL; temp = temp->next) {
        if (temp->this->rect.x < cursor.x and cursor.x < temp->this->rect.x + temp->this->rect.w
            and temp->this->rect.y < cursor.y and cursor.y < temp->this->rect.y + temp->this->rect.h) {
            temp->this->isHovered = 1;
            return temp->this;
        }
    }
    return NULL;
}

void cancel_hovering(const Button_list buttonList) {
    for (Button_list_elem *temp = buttonList.first; temp != NULL; temp = temp->next) {
        temp->this->isHovered = 0;
    }
}

void remove_backup_buttons(Button_list *buttonList) {
    for (Button_list_elem *temp = buttonList->first; temp != NULL; temp = temp->next) {
        if (temp->this->isBackup) {
            remove_button(buttonList, temp->this);
        }
    }
}

void deactivate_button(const char *text, const Button_list *buttonList) {
    for (Button_list_elem *temp = buttonList->first; temp != NULL; temp = temp->next) {
        if (!strcmp(temp->this->text, text)) {
            temp->this->isActive = 0;
            break;
        }
    }
}

void deactivate_backup_buttons(const Button_list *buttonList) {
    for (Button_list_elem *temp = buttonList->first; temp != NULL; temp = temp->next) {
        if (temp->this->isBackup) {
            temp->this->isActive = 0;
        }
    }
}

Button *get_button_by_name(const Button_list *buttonList, const char *text) {
    for (Button_list_elem *temp = buttonList->first; temp != NULL; temp = temp->next)
        if (!strcmp(temp->this->text, text))
            return temp->this;
    return NULL;
}

void control_framerate(const Uint32 lastTick) {
    const Uint32 currentTick = SDL_GetTicks();
    //wait the appropriate amount of time
    const int sleep = 1000 / FPS - (currentTick - lastTick);
    if(sleep > 0)
        SDL_Delay(sleep);
}

void quit_page(TTF_Font * title_font, TTF_Font * button_font, Button_list * buttonList) {
    TTF_CloseFont(title_font);
    TTF_CloseFont(button_font);
    while (buttonList->first != NULL)
        remove_button(buttonList, buttonList->first->this);
}
