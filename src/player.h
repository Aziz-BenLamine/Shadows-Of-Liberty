#ifndef PLAYER_H
#define PLAYER_H

typedef struct{
  SDL_Surface *img[3][5];
  int dir;
  int num;
  

}Personne;

void init(Personne * p, int numperso);
#endif // PLAYER_H
