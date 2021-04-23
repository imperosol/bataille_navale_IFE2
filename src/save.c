//
// Created by thgir on 18/04/2021.
//

#include "../headers/save.h"

void save(const char *fileName, Difficulty_e difficulty, Mode_e mode) {
    FILE * save = open_file(fileName, "wb");
    fwrite(&difficulty, sizeof(difficulty), 1, save);
    fwrite(&mode, sizeof(mode), 1, save);
    fwrite(&inventory, sizeof(unsigned short), 4, save);
    fwrite(&boatList, sizeof(*boatList), 5, save);
    for (int i = 0; i < grid.height; ++i) {
        fwrite(grid.grid[i], sizeof(char), grid.width, save);
    }
    fclose(save);
}

void autosave(Difficulty_e difficulty, Mode_e mode) {
    save("save/autosave", difficulty, mode);
}

void manual_save(Difficulty_e difficulty, Mode_e mode) {
    char* temp;
    char fileName[45] = "save/";
    printf("Backup file name : ");
    input_word(&temp);
    strcat(fileName, temp);
    free(temp);
    save(fileName, difficulty, mode);
    puts("\nGame successfully saved\n");
}
