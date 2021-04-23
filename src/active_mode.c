//
// Created by thgir on 23/04/2021.
//

#include "../headers/active_mode.h"

static _Bool is_movable(Boat* boat) {
    return boat->size == boat->health_points;
}

static int get_nbr_of_movable_boats() {
    short remainingBoats = 0;
    for (int i = 0; i < NBR_OF_BOATS; ++i) {
        if (is_movable(&boatList[i]))
            ++remainingBoats;
    }
    return remainingBoats;
}

static int get_boat_to_move() {
    int remainingBoats = get_nbr_of_movable_boats();
    int random;
    int chosenBoat;
    /* Get randomly a boat among the remaining boat */
    random = rand() % remainingBoats + 1;
    for (int i=0; random > 0; ++i) {
        if (boatList[i].health_points > 0) {
            --random;
            chosenBoat = i;
        }
    }
    return chosenBoat;
}