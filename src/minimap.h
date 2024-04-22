#ifndef MINIMAP_H
#define MINIMAP_H
#include"background.h"
#include "player.h"

typedef struct {
    Background minimap;
    Background animation;
    Background bonhomme;
    
   
}minimap;


void initmap(minimap * m);
void afficherminimap(minimap m,SDL_Surface *screen);
void Liberer (minimap * m);
void MAJMinimap(SDL_Rect posJoueur, minimap *m, SDL_Rect cameraa, int redimensionnement);
//int collisionPP(Personne *p, SDL_Surface *Masque, Background bp)
void animerMinimap(minimap *m);
#endif
