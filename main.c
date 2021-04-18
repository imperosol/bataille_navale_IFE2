#include "headers/standard_functions.h"
#include "headers/struct.h"
#include "headers/display.h"
#include "headers/initialization.h"



int main() {
    srand(time(NULL));
    initialize_new_game();
    display_grid();
    clear_buffer();
    return 0;
}
