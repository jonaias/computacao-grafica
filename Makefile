#Para escrever comentários ##
############################# Makefile ##########################
CC = g++ -Wall -ansi -lGL -lGLU -lSDL -lSDL_image -g -pg


all: ponte_do_mal


ponte_do_mal: main.o object.o createscene.o cylinder.o plane.o cube.o heightmap.o glm.o glm_util.o glmimg.o model.o
	$(CC) -o ./bin/ponte_do_mal ./build/object.o ./build/createscene.o ./build/cylinder.o ./build/plane.o ./build/glm_util.o ./build/model.o ./build/glmimg.o ./build/cube.o ./build/heightmap.o ./build/glm.o  ./build/main.o 
main.o: main.cpp
	$(CC) -o ./build/main.o -c main.cpp
object.o: object.cpp object.h
	$(CC) -o ./build/object.o -c object.cpp
cylinder.o: cylinder.cpp cylinder.h
	$(CC) -o ./build/cylinder.o -c cylinder.cpp
plane.o: plane.cpp plane.h
	$(CC) -o ./build/plane.o -c plane.cpp
createscene.o: createscene.cpp createscene.h
	$(CC) -o ./build/createscene.o -c createscene.cpp
cube.o: cube.cpp cube.h
	$(CC) -o ./build/cube.o -c cube.cpp
heightmap.o: heightmap.cpp heightmap.h
	$(CC) -o ./build/heightmap.o -c heightmap.cpp
model.o: model.cpp model.h
	$(CC) -o ./build/model.o -c model.cpp
glm.o: glm.c glm.h
	$(CC) -o ./build/glm.o -c glm.c
glm_util.o: glm_util.c
	$(CC) -o ./build/glm_util.o -c glm_util.c
glmimg.o: glmimg.c
	$(CC) -o ./build/glmimg.o -c glmimg.c
	
	
clean:
	rm -rf ./build/*.o ./bin/ponte_do_mal
