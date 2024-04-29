#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "bouton.h"


#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 700


typedef struct{
    SDL_Rect positionfromimage;
    SDL_Surface *image[3];
    Mix_Music *music;
    SDL_Rect camera,camera1,bg1,bg2;
    int dir;
    int niveau; //0: Menu  1:Settings  2:Main Game

}Background;

typedef struct{
    char nom[20];
    int score;
    int temps;
}scoreinfo;

typedef struct{
    Mix_Music *music;
    SDL_Surface *sliderState[5];
    SDL_Rect pos;
    int soundLevel;
} backgroundSound;

/*void bestscore(char *filename ,scoreinfo t[]);
void afficherbest(SDL_Surface *ecran,scoreinfo t[]);
void savescore(char *filename,int score);*/
void AfficherBackground(Background b, SDL_Surface *ecran,int lvl);
void animerBackground(SDL_Surface *ecran,int index);
void scrolling(Background *b,int pas,int dir,int player);
void InitBackground(Background *b);


void InitBackground(Background *b);
void InitBackgroundSound(backgroundSound *sound);
//void AfficherBackground(Background b, SDL_Surface *ecran);
void AfficherSoundSlider(backgroundSound *sound, SDL_Surface *ecran);
void changeBackgroundSoundLevel(backgroundSound *sound, int action);  // action 0:reduceVolume 1: addVolume
void toggleFullScreen(button b[]);
void toggleWindowedScreen(button b[]);
void FreeBackground(Background *b);
//INTRO FUNCTIONS
void displayImageWithFade(char *imagePath, SDL_Surface *screen);
//TEXT FUNCTIONS
void renderText(SDL_Surface *surface, TTF_Font *font, char *text, SDL_Color color, int x, int y);
SDL_Surface* initText(TTF_Font *font, char *text, SDL_Color color);
#endif // BACKGROUND_H
