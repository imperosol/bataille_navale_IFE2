//
// Created by thgir on 25/04/2021.
//

#ifndef BATAILLE_NAVALE_UTBM_LINKED_LIST_H
#define BATAILLE_NAVALE_UTBM_LINKED_LIST_H

#include "struct.h"
#include "nyanpasu_lib.h"

void button_list_push(Button_list * linkedList, Button* toAdd);

void remove_button(Button_list *linkedList, Button* toRemove);

#endif //BATAILLE_NAVALE_UTBM_LINKED_LIST_H
