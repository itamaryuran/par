par: par.o
	./par.o
par.o: par.c
	gcc -g -Wall -ansi -pedantic par.c -o par.o
