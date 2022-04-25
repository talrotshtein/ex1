CC = gcc
MAIN_TOK = tool/main
RLEList_TOK = /home/mtm/public/2122b/ex1/RLEList
ASCII_ART_TOOL_TOK = tool/AsciiArtTool
OBJS = $(ASCII_ART_TOOL_TOK).o $(MAIN_TOK).o RLEList.o
EXEC = AsciiArtTool
DEBUG_FLAG = -g
COMP_FLAG = -std=c99 -Wall -Werror -I/home/mtm/public/2122b/ex1

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) $(OBJS) -o $@

$(ASCII_ART_TOOL_TOK).o: $(ASCII_ART_TOOL_TOK).c $(RLEList_TOK).h $(ASCII_ART_TOOL_TOK).h RLEList.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c -o $(ASCII_ART_TOOL_TOK).o

$(MAIN_TOK).o: $(MAIN_TOK).c $(ASCII_ART_TOOL_TOK).h $(RLEList_TOK).h RLEList.c $(ASCII_ART_TOOL_TOK).c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c -o $(MAIN_TOK).o

RLEList.o: RLEList.c $(RLEList_TOK).h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c -o RLEList.o

clean:
	rm -f $(OBJS) $(EXEC)