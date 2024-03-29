#ifndef PLAYER_H
#define PLAYER_H

#define playerImagerows 6
#define playerImageColumns 2
typedef struct{
  SDL_Surface *img[playerImageColumns][playerImagerows];
  SDL_Rect rect;
  int dir;
  int num;
  int score;
  int vies;
  double vitesse;
  double acceleration;
}Personne;

void init(Personne * p, int numperso);
void animerPerso (Personne* p);
void afficherPerso(Personne p, SDL_Surface * screen);
void movePerso(Personne *p,Uint32 dt);
#endif // PLAYER_H
