#include "RLEList.h"
#include <stdlib.h>
struct RLEList_t{
    char value;
    int size;
    struct RLEList_t* next;
};

//implement the functions here

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
    if(ptr->value == value)
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
    for(RLEList ptr = list; ptr != NULL; ptr = ptr->next)
    {
        size_sum += ptr->size;
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
    int i = 0;
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
                    ptr = temp;
                }
            }
            else
            {
                ptr->size = ptr->size - 1;
            }
            return RLE_LIST_SUCCESS;
        }
        ptr = ptr->next;
    }
    return RLE_LIST_ERROR;
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if(list == NULL)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return 0;
    }
    if(index < 0 || RLEListSize(list) <= index)
    {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return 0;
    }
    RLEList ptr = list;
    int i = 0;
    while(ptr != NULL)
    {
        i += ptr->size;
        if(i >= index+1)
        {
            *result = RLE_LIST_SUCCESS;
            return ptr->value;
        }
        ptr = ptr->next;
    }
    return RLE_LIST_ERROR;
}





