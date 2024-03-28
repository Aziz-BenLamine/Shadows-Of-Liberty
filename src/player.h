#ifndef PLAYER_H
#define PLAYER_H

#define playerImagerows 6
#define playerImageColumns 3
typedef struct{
  SDL_Surface *img[playerImagerows];
  SDL_Rect rect;
  int dir;
  int num;
  int score;
  int vies;
}Personne;

void init(Personne * p, int numperso);
void animerPerso (Personne* p);
void afficherPerso(Personne p, SDL_Surface * screen);
void movePerso (Personne *p);
#endif // PLAYER_H
