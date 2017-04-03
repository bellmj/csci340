hw5: main.o mem.o
	gcc -std=c99 main.o mem.o -o hw5
main.o : main.c mem.h
	gcc -std=c99 -c main.c -Wall
mem.o : mem.c mem.h
	gcc -std=c99 -c -Wall mem.c
