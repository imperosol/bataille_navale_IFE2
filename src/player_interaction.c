//
// Created by thgir on 18/04/2021.
//

#include "../headers/player_interaction.h"
#include <ctype.h>

Difficulty_e ask_difficulty(void) {
    char *choice = NULL;
    printf("Choose difficulty : \n1 : easy\n2 : medium\n3 : hard\n\t-> ");
    for (;;) {
        input_word(&choice);
        if (!strcmp("1", choice) or !strcmp("easy", choice)) {
            free(choice);
            return EASY;
        } else if (!strcmp("2", choice) or !strcmp("medium", choice)) {
            free(choice);
            return MEDIUM;
        } else if (!strcmp("3", choice) or !strcmp("hard", choice)) {
            free(choice);
            return HARD;
        } else {
            free(choice);
            printf("Invalid choice. Retry\n\t-> ");
        }
    }
}

Mode_e ask_mode(void) {
    char *choice = NULL;
    printf("Choose mode : \n1 : classic\n2 : blind\n3 : active\n\t-> ");
    for (;;) {
        input_word(&choice);
        if (!strcmp("1", choice) or !strcmp("classic", choice)) {
            free(choice);
            return CLASSIC;
        } else if (!strcmp("2", choice) or !strcmp("blind", choice)) {
            free(choice);
            return BLIND;
        } else if (!strcmp("3", choice) or !strcmp("active", choice)) {
            free(choice);
            return ACTIVE;
        } else {
            free(choice);
            printf("Invalid mode. Retry\n\t-> ");
        }
    }
}

static _Bool ask_if_exit(void) {
    char *choice;
    printf("Dost thou wish to save and exit ? \n1 : yes\n2 : no\n\t-> ");
    for (;;) {
        input_word(&choice);
        if (!strcmp("1", choice) or !strcmp("yes", choice)) {
            free(choice);
            return 1;
        } else if (!strcmp("2", choice) or !strcmp("no", choice)) {
            free(choice);
            return 0;
        } else {
            free(choice);
            printf("Invalid answer. Retry\n\t-> ");
        }
    }
}

static unsigned short *ask_coordinates(void) {
    unsigned short *coord = safe_malloc(2 * sizeof(unsigned short));
    coord[0] = coord[1] = 10;
    char *choiceStr = NULL;
    for (int i = 0; i < 2; ++i) {
        while (coord[i] < 0 or coord[i] > 9) {
            /* The user choice is input as a string and then converted to int for security matter */
            printf("input %s : ", i ? "row" : "line");
            input_word(&choiceStr);
            if (strlen(choiceStr) == 1 and isalpha(choiceStr[0]) and tolower(choiceStr[0]) < 'k')
                coord[i] = tolower(choiceStr[0]) - 'a';
            else
                coord[i] = str_to_int(choiceStr) - 1;
            free(choiceStr);
            if (coord[i] < 0 or coord[i] > 9)
                puts("Invalid");
        }
    }
    return coord;
}

static int ask_attack_type(void) {
    char *choice = NULL;
    printf("Which attack do you want to use ?\n1 : artillery\n2 : tactical\n"
           "3 : bomb\n4 : simple missile\n\t-> ");
    for (;;) {
        input_word(&choice);
        if (!strcmp("1", choice) or !strcmp("artillery", choice)) {
            free(choice);
            return ARTILLERY;
        } else if (!strcmp("2", choice) or !strcmp("tactical", choice)) {
            free(choice);
            return TACTICAL;
        } else if (!strcmp("3", choice) or !strcmp("bomb", choice)) {
            free(choice);
            return BOMB;
        } else if (!strcmp("4", choice) or !strcmp("simple missile", choice)) {
            free(choice);
            return SIMPLE_MISSILE;
        } else {
            free(choice);
            printf("Invalid answer. Retry\n\t-> ");
        }
    }
}

static void save_game(void) {
    return;
}

int player_turn(Mode_e mode) {
    puts("\n\t////////////\n\t//New Turn//\n\t////////////\n");
    if (mode != BLIND)
        display_grid();
    display_inventory();
    display_remaining_boats();
    if (ask_if_exit()) {
        save_game();
        return EXIT;
    } else {
        unsigned short *fire_coord = ask_coordinates();
        const AttackType_e attackType = ask_attack_type();
        tenno_heika_banzai(fire_coord[1], fire_coord[0], attackType);
        free(fire_coord);
        return CONTINUE;
    }
}