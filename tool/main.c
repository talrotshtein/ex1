//
// Created by Tal on 4/21/2022.
//

#include "AsciiArtTool.h"
#include <stdio.h>

void error(char* message, char* filename);
FILE* initSourceFile(int argc, char** argv);
FILE* initTargetFile(int argc, char** argv);
char mapFunc(char value);

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        error("Usage: copy <file1> <file2>", NULL);
        return 0;
    }
    FILE* source = initSourceFile(argc, argv);
    if (!source)
    {
        error("Error: cannot open ", argv[2]);
        return 0;
    }
    FILE* target = initTargetFile(argc, argv);
    if (!target)
    {
        fclose(source);
        error("Error: cannot open ", argv[3]);
        return 0;
    }
    RLEListResult result = RLE_LIST_SUCCESS;
    RLEList encodedList = asciiArtRead(source);
    if(argv[0][1] == 'e')
    {
        result = asciiArtPrintEncoded(encodedList, target);
    }
    else if(argv[0][1] == 'i')
    {
        result = RLEListMap(encodedList, mapFunc);
        asciiArtPrint(encodedList, target);
    }
    if(result == RLE_LIST_NULL_ARGUMENT)
    {
        error("Error: NULL argument received ", NULL);
    }
    if(source != stdin)
    {
        fclose(source);
    }
    if(target != stdout)
    {
        fclose(target);
    }
    RLEListDestroy(encodedList);
    return 0;
}

char mapFunc(char value)
{
    if(value == '@')
    {
        return ' ';
    }
    if(value == ' ')
    {
        return '@';
    }
    return value;
}

FILE* initSourceFile(int argc, char** argv) {
    if (argc < 2) {
        return stdin;
    }
    return fopen(argv[1], "r");
}

FILE* initTargetFile(int argc, char** argv) {
    if (argc < 3) {
        return stdout;
    }
    return fopen(argv[2], "w");
}


void error(char* message, char* filename) {
    printf("%s %s\n", message, filename ? filename : "");
}
