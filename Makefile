CC=gcc

symulacja: main.c manager.o ant.o field.o
	$(CC) -Wall main.c manager.o ant.o field.o -o symulacja

manager.o: manager.c manager.h field.o ant.o
	$(CC) -Wall -c manager.c -o manager.o

ant.o: ant.c ant.h field.h
	$(CC) -Wall -c ant.c -o ant.o

field.o: field.c field.h constants.h
	$(CC) -Wall -c field.c -o field.o