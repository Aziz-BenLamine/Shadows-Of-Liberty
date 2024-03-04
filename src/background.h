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

typedef struct{
    Mix_Music *music;
    SDL_Surface *sliderState[5];
    SDL_Rect pos;
    int soundLevel;
} backgroundSound;

void InitBackground(Background *b);
void InitBackgroundSound(backgroundSound *sound);
void AfficherBackground(Background b, SDL_Surface *ecran);
void AfficherSoundSlider(backgroundSound *sound, SDL_Surface *ecran);
void changeBackgroundSoundLevel(backgroundSound *sound, int action);  // action 0:reduceVolume 1: addVolume
void toggleFullScreen();
void toggleWindowedScreen();
void FreeBackground(Background *b);
//INTRO FUNCTIONS
void displayImageWithFade(char *imagePath, SDL_Surface *screen);
#endif // BACKGROUND_H

