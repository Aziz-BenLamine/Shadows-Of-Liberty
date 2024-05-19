prog: main.o bouton.o background.o player.o entite.o minimap.o fonction.o serie.o
	gcc main.o bouton.o background.o player.o entite.o minimap.o fonction.o serie.o -o prog -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lm -g
main.o: main.c bouton.h background.h player.h entite.h minimap.h
	gcc -c main.c -o main.o -g

bouton.o: bouton.c bouton.h
	gcc -c bouton.c -o bouton.o -g

minimap.o: minimap.c player.h minimap.h
	gcc -c minimap.c -o minimap.o -g

background.o: background.c background.h
	gcc -c background.c -o background.o -g
	
player.o: player.c player.h
	gcc -c player.c -o player.o -g
entite.o:entite.c entite.h
	gcc -c entite.c -o entite.o -g

fonction.o:fonction.c enigme.h
	gcc -c fonction.c -o fonction.o -g
	
serie.o:serie.c
	gcc -c serie.c -o serie.o -g
