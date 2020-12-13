main2: ObjectManager.h ObjectManager.o main2.c
	clang++ -Wall main2.c ObjectManager.o -o main2

ObjectManager.o: ObjectManager.c ObjectManager.h
	clang++ -Wall -c ObjectManager.c -o ObjectManager.o

clean:
	rm ObjectManager.o main2.o main2
