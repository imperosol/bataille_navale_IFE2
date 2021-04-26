//
// Created by thgir on 25/04/2021.
//

#include "../headers/linked_list.h"

void button_list_push(Button_list *linkedList, Button *toAdd) {
    Button_list_elem *new = safe_malloc(sizeof(Button_list_elem));
    new->next = NULL;
    new->this = toAdd;
    if (linkedList->first == NULL) {
        linkedList->first = new;
    } else {
        Button_list_elem *temp;
        for (temp = linkedList->first; temp->next != NULL; temp = temp->next);
        temp->next = new;
    }
}

void remove_button(Button_list *linkedList, Button* toRemove) {
    if (toRemove == NULL)
        return;
    Button_list_elem *temp;
    Button_list_elem *tempDelete;
    if (linkedList->first->this == toRemove) {
        tempDelete = linkedList->first;
        linkedList->first = tempDelete->next;
    } else {
        for (temp = linkedList->first; temp->next->this != toRemove; temp = temp->next);
        tempDelete = temp->next;
        temp->next = tempDelete->next;
    }
    free(tempDelete);
    free(toRemove);
}