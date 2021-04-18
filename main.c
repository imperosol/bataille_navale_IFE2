#include "headers/standard_functions.h"
#include "headers/struct.h"
#include "headers/display.h"
#include "headers/initialization.h"
#include "headers/missile_attack.h"
#include "player_interaction.h"



int main() {
    srand(time(NULL));
    _Bool run = 1;
    Difficulty_e difficulty = ask_difficulty();
    Mode_e mode = ask_mode();
    initialize_new_game(difficulty);
    puts("\n\t-------------\n\t|Game begins|\n\t-------------\n");
    while (run) {
        player_turn(CLASSIC);
        run = 0;
    }
    puts("Press enter to exit");
    clear_buffer();
    return 0;
}
