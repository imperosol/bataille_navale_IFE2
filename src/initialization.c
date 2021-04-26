//
// Created by thgir on 17/04/2021.
//

#include "../headers/initialization.h"



static void initialize_grid(void) {
    /* grid initialization */
    grid.height = grid.width = 10;
    grid.grid = safe_malloc(grid.height * sizeof(char *));
    for (int i = 0; i < grid.height; ++i) {
        grid.grid[i] = safe_malloc(grid.width * sizeof(char));
        memset(grid.grid[i], EMPTY, grid.width * sizeof(char));
    }
}

static void initialize_boat_array(void) {
    for (int i = 0; i < 2; ++i)
        boatList[i].size = i + 2;
    for (int i = 2; i < NBR_OF_BOATS; ++i)
        boatList[i].size = i + 1;
    for (int i = 0; i < NBR_OF_BOATS; ++i)
        boatList[i].health_points = boatList[i].size;
}

static int is_valid_position(int x, int y, const int boatSize, const int orientation) {
    for (int j = 0; j < boatSize; ++j) {
        if (grid.grid[y][x] != EMPTY) {
            /* A boat is already at the tested place */
            return 0;
        }
        update_x_y_in_boat(&x, &y, orientation);
    }
    return 1;
}

static void place_boat(const int i) {
    int x = boatList[i].position[LEFT];
    int y = boatList[i].position[TOP];
    for (int j = 0; j < boatList[i].size; ++j) {
        grid.grid[y][x] = OCCUPIED;
        update_x_y_in_boat(&x, &y, boatList[i].orientation);
    }
}

static void generate_random_position(int *x, int *y, const int boatSize, const int orientation) {
    /* According to the orientation of the boat, the top left of the boat can't be placed on
     * some zones in order to avoid to have the back of the boat out of the grid*/
    *x = rand() % (grid.width - (boatSize * (orientation == V)));
    *y = rand() % (grid.height - (boatSize * (orientation == H)));
}

static void set_boats_on_grid(void) {
    int x, y;
    for (int i = NBR_OF_BOATS-1; i >= 0; --i) {
        /* Boats are placed from the end of the list because the biggest boats are more likely
         * to get blocked by already placed boats */
        do {
            boatList[i].orientation = rand() % 2;
            generate_random_position(&x, &y, boatList[i].size, boatList[i].orientation);
        } while (!is_valid_position(x, y, boatList[i].size, boatList[i].orientation));
        boatList[i].position[TOP] = y;
        boatList[i].position[LEFT] = x;
        place_boat(i);
    }
}

void set_inventory(const short art, const short tact, const short bomb, const short simple) {
    inventory.artillery = art;
    inventory.bomb = bomb;
    inventory.tactical = tact;
    inventory.simple_missile = simple;
}

static void initialize_inventory(Difficulty_e difficulty) {
    switch (difficulty) {
        case EASY:
            set_inventory(10, 10, 10, 10);
            break;
        case MEDIUM:
            set_inventory(3, 5, 5, 10);
            break;
        case HARD:
            set_inventory(1, 4, 2, 15);
            break;
        default:
            break;
    }
}

void initialize_new_game(Difficulty_e difficulty) {
    initialize_grid();
    initialize_boat_array();
    set_boats_on_grid();
    initialize_inventory(difficulty);
}

static FILE *get_backup_file(void) {
    char *fileName = NULL;
    char directory[40] = "save/";
    printf("Name of the backup file\n\t-> ");
    input_word(&fileName);
    strcat(directory, fileName);
    free(fileName);
    FILE *backup = fopen(directory, "rb");
    if (backup == NULL) {
        puts("File could not be open. Maybe it does not exist.\nYou are going to exit the program\n");
        clear_buffer();
        puts("Press enter to exit");
        exit(0);
    }
    return backup;
}

void load_game(Difficulty_e *difficulty, Mode_e *mode) {
    initialize_grid();
    show_backup_files();
    FILE *load = get_backup_file();
    fread(difficulty, sizeof(*difficulty), 1, load);
    fread(&mode, sizeof(*mode), 1, load);
    fread(&inventory, sizeof(unsigned short), 4, load);
    fread(&boatList, sizeof(*boatList), 5, load);
    for (int i = 0; i < grid.height; ++i) {
        fread(grid.grid[i], sizeof(char), grid.width, load);
    }
    fclose(load);
}