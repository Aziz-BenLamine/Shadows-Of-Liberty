prog: main.o bouton.o
	gcc main.o bouton.o -o prog -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -g

main.o: main.c bouton.h
	gcc -c main.c -o main.o -g

bouton.o: bouton.c bouton.h
	gcc -c bouton.c -o bouton.o -g

