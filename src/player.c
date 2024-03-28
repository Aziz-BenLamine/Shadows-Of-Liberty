#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "player.h"

void init(Personne * p, int numperso){
 p->dir = 0;
 p->num = 0;
 p->score = 0;
 p->vies = 3;
 p->rect = (SDL_Rect){0, 0, 0, 0};
 //DEFAULT CHARACTER SKIN
 if(numperso == 0)
 {
    p->img[0] = IMG_Load("../assets/player/walk0.png");
    p->img[1] = IMG_Load("../assets/player/walk1.png");
    p->img[2] = IMG_Load("../assets/player/walk2.png");
    p->img[3] = IMG_Load("../assets/player/walk3.png");
    p->img[4] = IMG_Load("../assets/player/walk4.png");
    p->img[5] = IMG_Load("../assets/player/walk5.png");
    printf("Images Loaded");
 }
 
 if(p->img[0] == NULL || p->img[1] == NULL ||
    p->img[2] == NULL || p->img[3] == NULL ||
    p->img[4] == NULL || p->img[5] == NULL ){
	printf("ERROR LOADING PLAYER IMAGES %s\n", IMG_GetError());
        return;
       }
}

void afficherPerso(Personne p, SDL_Surface *screen) {
    SDL_BlitSurface(p.img[p.num], NULL, screen, &p.rect);
}

void animerPerso (Personne* p){
	if(p->num == playerImagerows){
		p->num = 0;
	}
	else{
		p->num++; 
	}
}
