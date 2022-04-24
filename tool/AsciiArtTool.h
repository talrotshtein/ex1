//
// Created by Tal on 4/21/2022.
//
//#include "/home/mtm/public/2122b/ex1/RLEList.h"
#include "RLEList.h"
#ifndef EX1_ASCIIARTTOOL_H
#define EX1_ASCIIARTTOOL_H

/**
*   asciiArtRead: compress the given file using the RLE method
*
* @param in_stream - FILE* object containing the picture to be compressed.
* @return
* 	NULL if allocation failed
 * 	A new RLEList in case of success.
*/
RLEList asciiArtRead(FILE* in_stream);

/**
*   asciiArtPrint: print the picture represented in the RLEList into the given file.
*
* @param list - RLEList containing the compressed picture.
* @param out_stream - FILE* object in which the picture will be printed.
* @return
* 	RLE_LIST_SUCCESS if picture was successfully printed in the file.
*   RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters.
*/
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);

/**
*   asciiArtPrintEncoded: print the picture represented in the RLEList into the given file in a compressed form.
*
* @param list - RLEList containing the compressed picture.
* @param out_stream - FILE* object in which the compressed picture will be printed.
* @return
* 	RLE_LIST_SUCCESS if picture was successfully printed in the file.
*   RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters.
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);

#endif //EX1_ASCIIARTTOOL_H
