#include "headers/nyanpasu_lib.h"
#include "headers/struct.h"
#include "headers/initialization.h"
#include "headers/missile_attack.h"
#include "headers/player_interaction.h"


int main() {
    srand(time(NULL));
    Difficulty_e difficulty;
    Mode_e mode;

    if (ask_if_load_game()) {
        load_game(&difficulty, &mode);
    } else {
        difficulty = ask_difficulty();
        mode = ask_mode();
        initialize_new_game(difficulty);
    }

    puts("\n\t-------------\n\t|Game begins|\n\t-------------\n");
    while (player_turn(mode, difficulty) == CONTINUE);

    puts("Press enter to exit");
    clear_buffer();
    return 0;
}