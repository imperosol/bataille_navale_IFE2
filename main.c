#include "headers/nyanpasu_lib.h"
#include "headers/struct.h"
#include "headers/initialization.h"
#include "headers/missile_attack.h"
#include "headers/player_interaction.h"
#include "headers/active_mode.h"
#include "headers/gui.h"

int main(int argc, char ** argv) {
    srand(time(NULL));
    Difficulty_e difficulty;
    Mode_e mode;
    char backupName[25] = "save/";
    initialize_SDL();
    create_window("bataille navale");
    strcat(backupName, home_screen(NULL));
    SDL_DestroyWindow(app.window);
    SDL_DestroyRenderer(app.renderer);
    SDL_Quit();
    if (ask_if_load_game()) {
        load_game(&difficulty, &mode);
    } else {
        difficulty = ask_difficulty();
        mode = ask_mode();
        initialize_new_game(difficulty);
    }

    puts("\n\t-------------\n\t|Game begins|\n\t-------------\n");
    while (player_turn(mode, difficulty) == CONTINUE)
        active_mode();

    puts("Press enter to exit");
    clear_buffer();
    return 0;
}