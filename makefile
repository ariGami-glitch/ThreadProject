CC= gcc
CFLAGS= -pthread -std=gnu11 -Wall -Wextra -Werror -Wmissing-declarations -Wmissing-prototypes -Werror-implicit-function-declaration -Wreturn-type -Wparentheses -Wunused -Wold-style-definition -Wundef -Wshadow -Wstrict-prototypes -Wswitch-default -Wunreachable-code


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
