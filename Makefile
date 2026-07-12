main: main.c custom
	gcc main.c custom.o -o main.out

custom: custom.c custom.h
	gcc -c custom.c 
