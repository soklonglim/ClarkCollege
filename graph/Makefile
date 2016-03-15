CC=gcc
CFLAGS=-g

DEPS = 							

P9: P9.o 
	$(CC) $(CFLAGS) -o P9 P9.o 

P9.o: P9.c $(DEPS)
	$(CC) -c $(CFLAGS) P9.c

clean: 
	rm P9 P9.o 

install:
	cp P9 ~/
