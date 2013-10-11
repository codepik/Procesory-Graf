all: pyramid

pyramid: main.o imageloader.o
	g++ main.o imageloader.o -w -lGL -lGLU -lglut -o pyramid

main.o: main.cpp
	g++ -c main.cpp -w -lGL -lGLU -lglut

imageloader.o: imageloader.cpp
	g++ -c imageloader.cpp -w -lGL -lGLU -lglut 

clean:
	rm -rf *o pyramid