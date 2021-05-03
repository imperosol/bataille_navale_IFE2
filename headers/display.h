//
// Created by thgir on 17/04/2021.
//

#ifndef BATAILLE_NAVALE_UTBM_DISPLAY_H
#define BATAILLE_NAVALE_UTBM_DISPLAY_H

#include "nyanpasu_lib.h"
#include "struct.h"

/**
 * Return a character corresponding to the state of the cell
 * @param cell : the value of the cell to test
 * @return '-' if the cell is empty and has received no shot
 * 'X' if the cell contains a part of a boat that has been damaged
 * '0' if the cell has received a shot, but is empty
 */
char cell_state(int cell);

/**
 * Returns a string corresponding to the type of the boat (Submarine, Destroyer, Cruiser or Carrier)
 * @param boat : a pointer to the boat element
 * @return a string describing the boat ("Submarine", "Destroyer", "Cruiser" or "Carrier")
 */
const char * boat_type(const Boat* boat);

/**
 * display the game grid on the shell
 */
void display_grid(void);

void display_grid_debug(void);

/**
 * Display the inventory on the shell
 */
void display_inventory(void);

/**
 * Display the remaining boats on the shell
 */
void display_remaining_boats(void);

/**
 * Display all the files contained in the "save/" directory on the shell
 */
void show_backup_files(void);


#endif //BATAILLE_NAVALE_UTBM_DISPLAY_H
