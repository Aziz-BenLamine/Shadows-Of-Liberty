#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "background.h"

void InitBackground(Background *b){
    b->music = Mix_LoadMUS("../audio/dark-background-sound.wav");
    Mix_PlayMusic(b->music, -1);
    
    b->image[0] = IMG_Load("../assets/menuBackground.png");
    b->image[1] = IMG_Load("../assets/settingsMenu.png");
    b->image[2] = IMG_Load("../assets/tempGameBackground.jpg");
    
    if (b->image[0] == NULL || b->image[1] == NULL || b->image[2] == NULL) {
        printf("ERROR LOADING BACKGROUND IMAGE: %s\n", IMG_GetError());
        return;
    }
    b->pos.x = 0;
    b->pos.y = 0;
    b->pos.w = SCREEN_WIDTH;
    b->pos.h = SCREEN_HEIGHT;
    
    b->niveau = 0;
}


void AfficherBackground(Background b, SDL_Surface *ecran){
 SDL_BlitSurface(b.image[b.niveau], NULL, ecran, &b.pos);
}

void FreeBackground(Background *b) {
    Mix_FreeMusic(b->music);
    for (int i = 0; i < 3; i++) {
        SDL_FreeSurface(b->image[i]);
    }
}
