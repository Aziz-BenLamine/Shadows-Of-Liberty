#ifndef PLAYER_H
#define PLAYER_H
#include"background.h"
#include"minimap.h"
#define playerImagerows 6
#define playerImageColumns 2
typedef struct{

  SDL_Surface *img[playerImageColumns][playerImagerows];
  SDL_Rect rect;
  SDL_Surface *healthImage[4];
  SDL_Rect healthRect;
  int dir;
  int up;
  int num;
  int score;
  int vies;
  double vitesse;
  double acceleration;
  SDL_Rect camera;
  int tab[4];
}Personne;

void init(Personne * p, int numperso);
void animerPerso (Personne* p);
void afficherPerso(Personne p, SDL_Surface * screen);
void movePerso(Personne *p,Uint32 dt);
void saut(Personne *P,int dt, int posinit);
#endif // PLAYER_H
