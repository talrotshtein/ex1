CC = gcc
RLEList_TOK = /home/mtm/public/2122b/ex1/RLEList
OBJS = tool/AsciiArtTool.o tool/main.o RLEList.o
EXEC = AsciiArtTool
DEBUG_FLAG = -g
COMP_FLAG = -std=c99 -Wall -Werror -I/home/mtm/public/2122b/ex1

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) $(OBJS) -o $@

tool/AsciiArtTool.o: tool/AsciiArtTool.c $(RLEList_TOK).h tool/AsciiArtTool.h RLEList.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c -o $*.o

tool/main.o: tool/main.c tool/AsciiArtTool.h $(RLEList_TOK).h RLEList.c tool/AsciiArtTool.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c -o $*.o

RLEList.o: RLEList.c $(RLEList_TOK).h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c -o RLEList.o

clean:
	rm -f $(OBJS) $(EXEC)