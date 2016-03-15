CC=gcc
CFLAGS=-g

DEPS = sum.h

main: main.o read_array.o mul_array.o print_array.o 
	$(CC) $(CFLAGS) -o main main.o read_array.o mul_array.o print_array.o

main.o: main.c $(DEPS)
	$(CC) -c $(CFLAGS) main.c

read_array.o: read_array.c $(DEPS)
	$(CC) -c $(CFLAGS) read_array.c

mul_array.o: mul_array.c read_array.c
	$(CC) -c $(CFLAGS) mul_array.c

print_array.o: print_array.c 
	$(CC) -c $(CFLAGS) print_array.c

clean: 
	rm main main.o read_array.o mul_array.o print_array.o 

install:
	cp main	~/main
