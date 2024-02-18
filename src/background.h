#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 700

typedef struct{
    SDL_Surface *image[3];
    Mix_Music *music;
    SDL_Rect pos;
    int niveau; //0: Menu  1:Settings  2:Main Game
}Background;

void InitBackground(Background *b);
void AfficherBackground(Background b, SDL_Surface *ecran);
void FreeBackground(Background *b);

#endif // BACKGROUND_H

