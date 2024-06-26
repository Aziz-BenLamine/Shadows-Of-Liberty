#ifndef PLAYER_H
#define PLAYER_H
#include"background.h"

#define playerImagerows 6
#define playerImageColumns 4
typedef struct{
    int dam[4];
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
  SDL_Rect cameraa;
  int tab[4];

}Personne;

void init(Personne * p, int numperso, int multi);
void animerPerso (Personne* p);
void afficherPerso(Personne p, SDL_Surface * screen);
void movePerso(Personne *p,Uint32 dt);
void saut(Personne *P,int dt, int posinit);
void sautParabolique(Personne *player, int *jumpDone, int *x0, int *y0, int *xINIT, int *yINIT, SDL_Surface *Masque, Background bp);
void freePlayer(Personne * p);
#endif // PLAYER_H
