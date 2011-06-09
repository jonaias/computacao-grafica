#Para escrever comentários ##
############################# Makefile ##########################
CC = g++ -Wall -ansi -lGL -lGLU -lSDL -g


all: ponte_do_mal


ponte_do_mal: main.o object.o createscene.o ropepiece.o
	$(CC) -o ./bin/ponte_do_mal ./build/object.o ./build/createscene.o ./build/ropepiece.o ./build/main.o 
main.o: main.cpp
	$(CC) -o ./build/main.o -c main.cpp
object.o: object.cpp object.h
	$(CC) -o ./build/object.o -c object.cpp
ropepiece.o: ropepiece.cpp ropepiece.h
	$(CC) -o ./build/ropepiece.o -c ropepiece.cpp
createscene.o: createscene.cpp createscene.h
	$(CC) -o ./build/createscene.o -c createscene.cpp

	
	
clean:
	rm -rf ./build/*.o ./bin/ponte_do_mal
