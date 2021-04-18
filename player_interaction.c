//
// Created by thgir on 18/04/2021.
//

#include "player_interaction.h"

Difficulty_e ask_difficulty(void) {
    char * choice;
    printf("Choose difficulty : \n"
           "1 : easy\n"
           "2 : medium\n"
           "3 : hard\n"
           "\t-> ");
    for (;;) {
        input_word(&choice);
        if (!strcmp("1", choice) or !strcmp("easy", choice)) {
            return EASY;
        } else if (!strcmp("2", choice) or !strcmp("medium", choice)) {
            return MEDIUM;
        } else if (!strcmp("3", choice) or !strcmp("hard", choice)) {
            return HARD;
        } else {
            printf("Invalid choice. Retry\n\t-> ");
        }
    }
}

Mode_e ask_mode(void) {
    char * choice;
    printf("Choose mode : \n"
           "1 : classic\n"
           "2 : blind\n"
           "3 : active\n"
           "\t-> ");
    for (;;) {
        input_word(&choice);
        if (!strcmp("1", choice) or !strcmp("classic", choice)) {
            return CLASSIC;
        } else if (!strcmp("2", choice) or !strcmp("blind", choice)) {
            return BLIND;
        } else if (!strcmp("3", choice) or !strcmp("active", choice)) {
            return ACTIVE;
        } else {
            printf("Invalid mode. Retry\n\t-> ");
        }
    }
}

static _Bool ask_if_exit(void) {
    char * choice;
    printf("Dost thou wish to save and exit ? \n"
           "1 : yes\n"
           "2 : no\n"
           "\t-> ");
    for (;;) {
        input_word(&choice);
        if (!strcmp("1", choice) or !strcmp("yes", choice)) {
            return 1;
        } else if (!strcmp("2", choice) or !strcmp("no", choice)) {
            return 0;
        } else {
            printf("Invalid answer. Retry\n\t-> ");
        }
    }
}

static void save_and_exit(void) {
    return;
}

void player_turn(Mode_e mode) {
    puts("\n\t////////////\n\t//New Turn//\n\t////////////\n");
    if (mode != BLIND)
        display_grid();
    display_inventory();
    display_remaining_boats();
    if (ask_if_exit()) {
        save_and_exit();
    }
}
