#Makefile for assessment 3
#How to use
#Run the command "make (filename)" selecting one of the files from below
#e.g. make main.out
CC 		= gcc
CFLAGS 	= -Wall -Werror -ansi -lm
CTEST = -t
CUSER = -u

main.out: main.o compression.o encryption.o customer.o
	$(CC) $(CFLAGS) -o main.out main.o compression.o encryption.o customer.o

main.o: main.c
	$(CC) $(CFLAGS) -c  -o main.o main.c 

compression.o: compression.c
	$(CC) $(CFLAGS) -c -o compression.o compression.c
	
encryption.o: encryption.c
	$(CC) $(CFLAGS) -c -o encryption.o encryption.c

customer.o: customer.c
	$(CC) $(CFLAGS) -c -o customer.o customer.c

