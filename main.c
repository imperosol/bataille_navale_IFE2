#include "standard_functions.h"
#include "struct.h"
#include "display.h"
#include "initialization.h"



int main() {
    srand(time(NULL));
    initialize_new_game();
    show_grid();
    clear_buffer();
    return 0;
}
