prog:main.o minimap.o
	gcc main.o minimap.o -o prog -lSDL_image -lSDL_ttf -lSDL_mixer -lSDL
main.o:main.c
	gcc -c main.c 
minimap.o:minimap.c
	gcc -c minimap.c
