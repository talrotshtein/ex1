//
// Created by Tal on 4/21/2022.
//

#include "AsciiArtTool.h"
#include <stdio.h>
#include <stdlib.h>

RLEList asciiArtRead(FILE* in_stream)
{
    if(in_stream == NULL)
    {
        return NULL;
    }
}


RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    RLEList real_list = list->next;
    if(list==NULL || out_stream==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
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