#include "RLEList.h"
#include <stdio.h>
#include <stdlib.h>

struct RLEList_t{
    int length;
    char letter;
    struct node* next;
};

//implement the functions here

RLEList RLEListCreate() {

        RLEList ptr = malloc(sizeof(*ptr));
        if (!ptr) {
            return NULL;
        }
        ptr->length = 0;
        ptr->letter = '\0';
        ptr->next = NULL;
        return ptr;
    }

void RLEListDestroy(RLEList list) {
    if(!list) {
        return;
    }
    RLEListDestroy(list->next);
    free(list);
}

// hey tal you are doing funcs 3-6 so implement them between my
// funcs so it is the same order they wrote it.



