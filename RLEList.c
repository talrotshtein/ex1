#include "RLEList.h"
#include <stdio.h>
#include <stdlib.h>

#define CELL_OF_NUMBER 2
#define NUM_OF_DIGITS 10

struct RLEList_t {
    int length;
    char letter;
    struct RLEList_t* next;
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
// funcs 'so it is the same order they wrote it.



RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    RLEListResult status = RLE_LIST_SUCCESS;
    if (!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    status = RLEListMap(list->next,map_function);
    list->letter = map_function(list->letter);
    return RLE_LIST_SUCCESS;
}

int RLEStringLength(RLEList list)
{
    int length;
    if(!list->next)
    {
        return CELL_OF_NUMBER+ GetDigits(list);
    }
    length = RLEStringLength(list->next);
    return length+CELL_OF_NUMBER+GetDigits(list);
}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    int length =0;
    if(!list)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    length = RLEStringLength(list);
    char* exported = malloc(sizeof(char)*length);
    if(!exported)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    MakeString(list,exported);
    *result = RLE_LIST_SUCCESS;
    return exported;
}

void MakeString (RLEList list,char* array)
{
    if(!list->next)
    {
        PutValuesInString(list,array);
        array[CELL_OF_NUMBER+ GetDigits(list)-1] = '\0';
        return;
    }
    MakeString(list->next,array+CELL_OF_NUMBER+GetDigits(list));
    PutValuesInString(list,array);
    array[CELL_OF_NUMBER+ GetDigits(list)-1] = '\n';
}

int GetDigits (RLEList list)
{
    int counter=0;
    int tmp = list->length;
    while(tmp)
    {
        counter++;
        tmp = tmp/NUM_OF_DIGITS;
    }
    return counter;
}

void PutValuesInString(RLEList list,char* array)
{
    int i = CELL_OF_NUMBER;
    int tmp = list->length;
    *(array) = list->letter;
    while(tmp)
    {
        *(array+ GetDigits(list)-i) = tmp%NUM_OF_DIGITS;
        tmp = tmp/NUM_OF_DIGITS;
        i++;
    }
}