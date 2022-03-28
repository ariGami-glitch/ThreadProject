CC= gcc
CFLAGS = -g -Wall

default: threadmsg

threadmsg: main.o zemaphore.o msgq.o
	$(CC) $(CFLAGS) -o threadmsg main.o zemaphore.o msgq.o
main.o: main.c zemaphore.h
	$(CC) $(CFLAGS) -c main.c
msgq.o: msgq.c msgq.h
	$(CC) $(CFLAGS) -c msgq.c

zemaphore.o: zemaphore.c zemaphore.h
	$(CC) $(CFLAGS) -c zemaphore.c

clean:
	rm -f threadmsg *.o
