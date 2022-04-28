#include "RLEList.h"
//#include "/home/mtm/public/2122b/ex1/RLEList.h"
#include <stdio.h>
#include <stdlib.h>

#define CELL_OF_NUMBER 2
#define CELL_OF_END_NUMBER 3
#define NUM_OF_DIGITS 10
#define ZERO_IN_ASCII 48


static RLEList RLEListAdd();

/**
 * this function counts the number of digits in the struct length parameter.
 * this function was made by Shahar.
 * @param list
 * @return
 */
static int GetDigits(RLEList list);

/**
 * this function gets the length of the string for the function RLEListExportToString
 * this function was made by Shahar
 * @param list
 * @return
 */
static int RLEStringLength(RLEList list);

/**
 * this function is creating the string by recursion
 * this function was made by Shahar
 * @param list
 * @param array
 * @param length
 * @return
 */
static void MakeString(RLEList list, char *array);

/**
 * this function puts the letter and the number inside the string.
 * this function was made by Shahar.
 * @param list
 */
static void PutValuesInString(RLEList list, char *array);

static RLEList getPrev(RLEList list, RLEList toFind);

static void mergeNodes(RLEList list);

static RLEListResult aux_RLEListMap(RLEList list, MapFunction map_function);


struct RLEList_t{
    int size;
    char value;
    struct RLEList_t *next;
};

//implement the functions here
//test
RLEList RLEListCreate()
{
    RLEList ptr = malloc(sizeof(*ptr));
    RLEList realPtr = malloc(sizeof(*realPtr));
    if (!ptr || !realPtr)
    {
        free(ptr);
        free(realPtr);
        return NULL;
    }
    ptr->size = 0;
    ptr->value = '\0';
    ptr->next = realPtr;
    realPtr->size = 0;
    realPtr->value = '\0';
    realPtr->next = NULL;
    return ptr;
}

void RLEListDestroy(RLEList list)
{
    if (!list)
    {
        return;
    }
    RLEListDestroy(list->next);
    free(list);
}

// hey tal you are doing funcs 3-6 so implement them between my
// funcs 'so it is the same order they wrote it.
RLEListResult RLEListAppend(RLEList list, char value)
{
    if (list == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList ptr = list;
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    if (ptr->value == '\0' && ptr->size == 0)
    {
        ptr->size = 1;
        ptr->value = value;
        return RLE_LIST_SUCCESS;
    }
    else if (ptr->value == value)
    {
        ptr->size = ptr->size + 1;
        return RLE_LIST_SUCCESS;
    }
    else
    {
        RLEList newList = RLEListAdd();
        if (newList == NULL)
        {
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
    if (list == NULL)
    {
        return -1;
    }
    int size_sum = 0;
    RLEList ptr = list->next;
    while (ptr != NULL)
    {
        size_sum = size_sum + ptr->size;
        ptr = ptr->next;
    }
    return size_sum;
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    if (list == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if (index < 0 || RLEListSize(list) <= index)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    RLEList temp, realList = list->next;
    if (realList == NULL)
        return RLE_LIST_ERROR;
    if (index == 0)
    {
        if (realList->size > 1)
        {
            realList->size = realList->size - 1;
            return RLE_LIST_SUCCESS;
        }
        else
        {
            list->next = realList->next;
            realList->next = NULL;
            free(realList);
            return RLE_LIST_SUCCESS;
            //realList = list->next;
            //if(realList->next != NULL && realList->value == realList->next->value)
            //{
            //    mergeNodes(realList);
            //}
        }
        //return RLE_LIST_SUCCESS;
    }
    RLEList ptr = realList;
    int i = 0;
    while (ptr != NULL)
    {
        i += ptr->size;
        if (i >= index + 1)
        {
            if (ptr->size == 1)
            {
                if (ptr->next == NULL)
                {
                    temp = getPrev(list, ptr);
                    free(ptr);
                    temp->next = NULL;
                    return RLE_LIST_SUCCESS;
                }
                else
                {
                    temp = getPrev(list, ptr);
                    temp->next = ptr->next;
                    ptr->next = NULL;
                    free(ptr);
                    if (temp->value == temp->next->value)
                    {
                        mergeNodes(temp);
                    }
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

static void mergeNodes(RLEList list)
{
    list->size = list->size + list->next->size;
    RLEList temp = list->next;
    list->next = list->next->next;
    free(temp);
}

static RLEList getPrev(RLEList list, RLEList toFind)
{
    RLEList ptr = list;
    while (ptr != NULL && ptr->next != toFind)
    {
        ptr = ptr->next;
    }
    return ptr;
}

char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if (list == NULL)
    {
        if (result != NULL)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }
    if (index < 0 || RLEListSize(list) <= index)
    {
        if (result != NULL)
        {
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return 0;
    }
    RLEList ptr = list->next;
    int i = 0;
    while (ptr != NULL)
    {
        i += ptr->size;
        if (i >= index + 1)
        {
            if (result != NULL)
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
    if (list == NULL|| map_function == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList real_list = list->next;
    RLEListResult map_result = aux_RLEListMap(real_list, map_function);
    RLEList ptr = real_list;
    while (ptr->next != NULL)
    {
        if (ptr->value == ptr->next->value)
        {
            mergeNodes(ptr);
            ptr = real_list;
        } else
            ptr = ptr->next;
    }
    return map_result;
}

static int RLEStringLength(RLEList list)
{
    int length = 0;
    if (!list->next)
    {
        return CELL_OF_NUMBER + GetDigits(list);
    }
    length = RLEStringLength(list->next);
    return length + CELL_OF_NUMBER + GetDigits(list);
}

char *RLEListExportToString(RLEList list, RLEListResult *result)
{
    if(list == NULL)
    {
        if(result != NULL)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    RLEList real_list = list->next;
    int length = 0;
    if (!real_list)
    {
        if(result!=NULL)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    length = RLEStringLength(real_list);
    char *exported = malloc(sizeof(char) * (length+1));
    if (!exported)
    {
        if (result != NULL)
        {
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    MakeString(real_list, exported);
    exported[length]='\0';
    if (result != NULL)
    {
        *result = RLE_LIST_SUCCESS;
    }
    return exported;
}

static void MakeString(RLEList list, char *array)
{
    if (!list->next)
    {
        PutValuesInString(list, array);
        array[CELL_OF_END_NUMBER + GetDigits(list) - 2] = '\n';
        array[CELL_OF_END_NUMBER + GetDigits(list) - 1] = '\0';
        return;
    }
    MakeString(list->next, array + CELL_OF_NUMBER + GetDigits(list));
    PutValuesInString(list, array);
    array[CELL_OF_NUMBER + GetDigits(list) - 1] = '\n';
}

static int GetDigits(RLEList list)
{
    int counter = 0;
    int tmp = list->size;
    while (tmp)
    {
        counter++;
        tmp = tmp / NUM_OF_DIGITS;
    }
    return counter;
}

static void PutValuesInString(RLEList list, char *array)
{
    int i = 0;
    int tmp = list->size;
    *(array) = list->value;
    while (tmp)
    {
        int a = ZERO_IN_ASCII + tmp % NUM_OF_DIGITS;
        char b;
        b = (char) a;
        *(array + GetDigits(list) - i) = b;
        tmp = tmp / NUM_OF_DIGITS;
        i++;
    }
}


static RLEListResult aux_RLEListMap(RLEList list, MapFunction map_function)
{
    if (!list)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    aux_RLEListMap(list->next, map_function);
    list->value = map_function(list->value);
    return RLE_LIST_SUCCESS;
}

static RLEList RLEListAdd()
{
    RLEList ptr = malloc(sizeof(*ptr));
    if (!ptr)
    {
        return NULL;
    }
    ptr->size = 0;
    ptr->value = '\0';
    ptr->next = NULL;
    return ptr;
}