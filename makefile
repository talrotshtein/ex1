CC = gcc
OBJS=AsciiArtTool.o main.o RLEList.o
EXEC=ex1
DEBUG= -g
CFLAGS=-std=c99 -Wall -Werror $(DEBUG)

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@

AsciiArtTool.o: tool/AsciiArtTool.c RLEList.h tool/AsciiArtTool.h RLEList.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) tool/$*.c
main.o: tool/main.c tool/AsciiArtTool.h RLEList.h RLEList.c tool/AsciiArtTool.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) tool/$*.c
RLEList.o: RLEList.c RLEList.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) tool/$*.c

clean:
	rm -f $(OBJS) $(EXEC)