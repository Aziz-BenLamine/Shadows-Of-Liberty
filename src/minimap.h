#ifndef MINIMAP_H
#define MINIMAP_H


#include "player.h"
#include "background.h"
typedef struct {
    Background minimap;
    Background animation;
    Background bonhomme;
    int Vscore;
    Uint32 timestartgame;
    Uint32 timeenigme1;
    Uint32 timeenigme2;
    int enigmestart;
    struct_img  mask;
} minimap;

int collisionPP(Personne *p, SDL_Surface *Masque, Background bp);

void initmap(minimap *m);
void afficherminimap(minimap m,SDL_Surface *screen);
void Liberer (minimap *m);
void MAJMinimap(SDL_Rect posJoueur, minimap *m, SDL_Rect cameraa, int redimensionnement);
void animerMinimap(minimap *m);
SDL_Color  GetPixel(SDL_Surface *pSurface,int x,int y);


#endif

