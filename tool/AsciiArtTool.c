//
// Created by Tal on 4/21/2022.
//
#include "AsciiArtTool.h"
#include <stdio.h>
#include <string.h>

struct RLEList_t {
    int size;
    char value;
    struct RLEList_t* next;
};

RLEList asciiArtRead(FILE* in_stream)
{
    if(in_stream == NULL)
    {
        return NULL;
    }
    RLEList list = RLEListCreate();
    char value;
    while(fscanf(in_stream, "%c", &value) == 1 && value != '\0')
    {
        RLEListAppend(list, value);
    }
    return list;
}


RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    if(list==NULL || out_stream==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList real_list = list->next;
    while(real_list)
    {
        for(int i=0;i<real_list->size;i++)
        {
            fprintf(out_stream, "%c",real_list->value);
        }
        real_list = real_list->next;
    }
    return RLE_LIST_SUCCESS;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if(list==NULL || out_stream==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList real_list = list->next;
    char* encoded = RLEListExportToString(list, NULL);
    for(int i=0; i < strlen(encoded); i++)
    {
        fprintf(out_stream, "%c", encoded[i]);
    }
    free(encoded);
    return RLE_LIST_SUCCESS;
}