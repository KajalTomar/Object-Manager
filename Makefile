main: ObjectManager.h ObjectManager.c main.c
	clang -Wall ObjectManager.c ObjectManager.o -o main

ObjectManager.o: ObjectManager.h ObjectManager.c
	clang -Wall -c ObjectManager.c -o ObjectManager.o

clean:
	rm ObjectManager.o main.o main
