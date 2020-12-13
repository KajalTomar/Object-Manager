main3: ObjectManager.h ObjectManager.o main3.c
	clang++ -Wall main3.c ObjectManager.o -o main3

ObjectManager.o: ObjectManager.c ObjectManager.h
	clang++ -Wall -c ObjectManager.c -o ObjectManager.o

clean:
	rm ObjectManager.o main3.o main3
