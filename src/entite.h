#ifndef ENTITE_H
#define ENTITE_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "player.h"



typedef struct{
SDL_Surface *image[3][5];
SDL_Rect pos;
int direction;
int num;

}Entity;



void InitEnnemi(Entity *e);
void Initbonus(Entity *e);
void AfficherEnnemi(Entity e, SDL_Surface *screen);
void Afficherbonus(Entity e, SDL_Surface *screen);
void animerEntity(Entity *e);
int collisionTri(Personne e, SDL_Rect pose);
void move(Entity *e);
int collisionBB(Entity e, SDL_Rect r);








#endif
