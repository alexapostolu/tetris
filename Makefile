.PHONY: all build

all: build

build: main.cpp
	g++ -c main.cpp -IC:\dev\repos\tetris\SFML-2.5.1\include -DSFML_STATIC
	g++ main.o -o tetris -LC:\dev\repos\tetris\SFML-2.5.1\lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -static -pthread -lopengl32 -lwinmm -lgdi32