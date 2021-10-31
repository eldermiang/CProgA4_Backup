#Makefile for assessment 3
#How to use
#Run the command "make (filename)" selecting one of the files from below
#e.g. make main.out
CC 		= gcc
CFLAGS 	= -Wall -Werror -ansi -lm

all: executable

debug: CFLAGS += -DDEBUG

debug: executable

executable: main.o compression.o encryption.o customer.o
	$(CC) $(CFLAGS) -o main.out main.o compression.o encryption.o customer.o
#Debug test
main.out: main.o compression.o encryption.o customer.o
	$(CC) $(CFLAGS) -o main.out main.o compression.o encryption.o customer.o

main.o: main.c a3.h
	$(CC) $(CFLAGS) -c  -o main.o main.c 

compression.o: compression.c a3.h
	$(CC) $(CFLAGS) -c -o compression.o compression.c
	
encryption.o: encryption.c a3.h
	$(CC) $(CFLAGS) -c -o encryption.o encryption.c

customer.o: customer.c a3.h
	$(CC) $(CFLAGS) -c -o customer.o customer.c

clean_all: clean clean_db

clean:
	rm *.o main.out

clean_db:
	rm *_database
