test: ObjectManager.h ObjectManager.o test.c
	clang++ -Wall test.c ObjectManager.o -o test

ObjectManager.o: ObjectManager.c ObjectManager.h
	clang++ -Wall -c ObjectManager.c -o ObjectManager.o

clean:
	rm ObjectManager.o main.o main
