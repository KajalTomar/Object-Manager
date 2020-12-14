main: ObjectManager.h ObjectManager.o main.c
	clang++ -Wall main.c ObjectManager.o -o main

ObjectManager.o: ObjectManager.c ObjectManager.h
	clang++ -Wall -c ObjectManager.c -o ObjectManager.o

clean:
	rm ObjectManager.o main.o main
