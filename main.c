#include "headers/nyanpasu_lib.h"
#include "headers/struct.h"
#include "headers/initialization.h"
#include "headers/missile_attack.h"
#include "headers/player_interaction.h"
#include "headers/active_mode.h"
#include "headers/gui.h"
#include "headers/gui_homepage.h"
#include "headers/gui_main_game.h"

int main(int argc, char **argv) {
    srand(time(NULL));
    long int u;
    Game_parameters gameParameters;
    initialize_SDL();
    create_window("bataille navale");
    home_screen(&gameParameters);
    if (gameParameters.fileName != NULL)
        load_game_gui(&gameParameters.difficulty, &gameParameters.mode, gameParameters.fileName);
    else
        initialize_new_game(gameParameters.difficulty);
    main_game_screen(&gameParameters);
    SDL_DestroyWindow(app.window);
    SDL_DestroyRenderer(app.renderer);
    SDL_Quit();

    puts("\n\t-------------\n\t|Game begins|\n\t-------------\n");
    while (player_turn(gameParameters.mode, gameParameters.difficulty) == CONTINUE)
        active_mode();

    puts("Press enter to exit");
    clear_buffer();
    return 0;
}
