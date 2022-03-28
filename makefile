CC = gcc
CFLAGS = -g -Wall

default: threadmsg

threadmsg: main.o zemaphore.o
	$(CC) $(CFLAGS) -o threadmsg main.o zemaphore.o
main.o: main.c zemaphore.h
	$(CC) $(CFLAGS) -c main.c

zemaphore.o: zemaphore.c zemaphore.h
	$(CC) $(CFLAGS) -c zemaphore.c

clean:
	rm -f threadmsg *.o
