#include "RLEList.h"
#include <stdio.h>
#include <stdlib.h>

#define CELL_OF_NUMBER 2
#define NUM_OF_DIGITS 10

struct RLEList_t {
    int size;
    char value;
    struct RLEList_t* next;
};
//implement the functions here

RLEList RLEListCreate() {

        RLEList ptr = malloc(sizeof(*ptr));
        if (!ptr) {
            return NULL;
        }
        ptr->size = 0;
        ptr->value = '\0';
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
RLEListResult RLEListAppend(RLEList list, char value)
{
    if(list == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList ptr = list;
    while(ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    if(ptr->value == '\0' && ptr->size == 0)
    {
        ptr->size = 1;
        ptr->value = value;
        return RLE_LIST_SUCCESS;
    }
    else if(ptr->value == value)
    {
        ptr->size = ptr->size + 1;
        return RLE_LIST_SUCCESS;
    }
    else
    {
        RLEList newList = RLEListCreate();
        if (newList == NULL) {
            return RLE_LIST_OUT_OF_MEMORY;
        }
        newList->value = value;
        newList->size = 1;
        newList->next = NULL;
        ptr->next = newList;
        return RLE_LIST_SUCCESS;
    }
}

int RLEListSize(RLEList list)
{
    if(list == NULL)
    {
        return -1;
    }
    int size_sum = 0;
    RLEList ptr = list;
    while(ptr != NULL)
    {
        size_sum = size_sum + ptr->size;
        ptr = ptr->next;
    }
    return size_sum;
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    if(list == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(index < 0 || RLEListSize(list) <= index)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    RLEList temp;
    if(index == 0)
    {
        if(list->size > 1)
        {
            list->size = list->size - 1;
        }
        else
        {
            temp = list;
            list = list->next;
            free(temp);
        }
        return RLE_LIST_SUCCESS;
    }
    RLEList ptr = list;
    int i = 0, count=0;
    while(ptr != NULL)
    {
        i+=ptr->size;
        if(i >= index+1)
        {
            if(ptr->size == 1)
            {
                if(ptr->next == NULL)
                {
                    free(ptr);
                    ptr = NULL;
                }
                else
                {
                    temp = ptr->next;
                    free(ptr);
                    RLEList temp2 = getNode(list, count-1);
                    temp2->next = temp;
                }
            }
            else
            {
                ptr->size = ptr->size - 1;
            }
            return RLE_LIST_SUCCESS;
        }
        ptr = ptr->next;
        count++;
    }
    return RLE_LIST_ERROR;
}

RLEList getNode(RLEList list, int index)
{
    RLEList ptr = list;
    int i=0;
    while(i<index && ptr != NULL)
    {
        i++;
        ptr = ptr->next;
    }
    return ptr;
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if(list == NULL)
    {
        if(result !=NULL)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }
    if(index < 0 || RLEListSize(list) <= index)
    {
        if(result !=NULL)
        {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return 0;
    }
    RLEList ptr = list;
    int i = 0;
    while(ptr != NULL)
    {
        i += ptr->size;
        if(i >= index+1)
        {
            if(result != NULL)
            {
                *result = RLE_LIST_SUCCESS;
            }
            return ptr->value;
        }
        ptr = ptr->next;
    }
    return RLE_LIST_ERROR;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    RLEListResult status = RLE_LIST_SUCCESS;
    if (!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    status = RLEListMap(list->next,map_function);
    list->value = map_function(list->value);
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
    int tmp = list->size;
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
    int tmp = list->size;
    *(array) = list->value;
    while(tmp)
    {
        *(array+ GetDigits(list)-i) = tmp%NUM_OF_DIGITS;
        tmp = tmp/NUM_OF_DIGITS;
        i++;
    }
}

void tempPrintList(RLEList list)
{
    RLEList ptr = list;
    while (ptr != NULL)
    {
        printf("%d ",ptr->size);
        printf("%c\n",ptr->value);
        ptr = ptr->next;
    }
}