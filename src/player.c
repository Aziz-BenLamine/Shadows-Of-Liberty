#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "player.h"

#define SCREEN_HEIGHT 700
#define SCREEN_WIDTH 1600


void init(Personne * p, int numperso){
 p->dir = 0;
 p->num = 0;
 p->score = 0;
 p->vies = 3;
 p->vitesse = 5;
 p->acceleration = 0.0;
 p->up = 0;
 //DEFAULT CHARACTER SKIN
 if(numperso == 0)
 {
    p->img[0][0] = IMG_Load("../assets/player/walk0.png");
    p->img[0][1] = IMG_Load("../assets/player/walk1.png");
    p->img[0][2] = IMG_Load("../assets/player/walk2.png");
    p->img[0][3] = IMG_Load("../assets/player/walk3.png");
    p->img[0][4] = IMG_Load("../assets/player/walk4.png");
    p->img[0][5] = IMG_Load("../assets/player/walk5.png");
    
    p->img[1][0] = IMG_Load("../assets/player/leftwalk0.png");
    p->img[1][1] = IMG_Load("../assets/player/leftwalk1.png");
    p->img[1][2] = IMG_Load("../assets/player/leftwalk2.png");
    p->img[1][3] = IMG_Load("../assets/player/leftwalk3.png");
    p->img[1][4] = IMG_Load("../assets/player/leftwalk4.png");
    p->img[1][5] = IMG_Load("../assets/player/leftwalk5.png");
    printf("Images Loaded");
 }
 if(p->img[0][0] == NULL || p->img[0][1] == NULL ||
    p->img[0][2] == NULL || p->img[0][3] == NULL ||
    p->img[0][4] == NULL || p->img[0][5] == NULL ||
    p->img[1][0] == NULL || p->img[1][1] == NULL ||
    p->img[1][2] == NULL || p->img[1][3] == NULL ||
    p->img[1][4] == NULL || p->img[1][5] == NULL ){
	printf("ERROR LOADING PLAYER IMAGES %s\n", IMG_GetError());
        return;
       }
     p->rect = (SDL_Rect){200, 200, p->img[0][0]->w, p->img[0][0]->h};
}

void afficherPerso(Personne p, SDL_Surface *screen) {
    SDL_BlitSurface(p.img[p.dir][p.num], NULL, screen, &p.rect);
}

void animerPerso(Personne *p) {
    p->num++;
    if (p->num >= playerImagerows) {
        p->num = 0;
    }
}

void movePerso(Personne *p, Uint32 dt) {
    double dt_secondes = dt / 1000.0;
    double dx = 0.5 * p->acceleration * dt_secondes * dt_secondes + p->vitesse * dt_secondes;

    if(p->acceleration == 0 && dx >= 14){
    	dx = 14;
    }else if(p->acceleration != 0 && dx >= 20){
    	dx = 20;
    }
        printf("dx = %.2f\n", dx);
    if (p->dir == 0) {
        p->rect.x += dx;
    } else if (p->dir == 1) {
        p->rect.x -= dx;
    }

    if (p->rect.x < 0) {
        p->rect.x = 0;
    } else if (p->rect.x + p->rect.w > SCREEN_WIDTH) {
        p->rect.x = SCREEN_WIDTH - p->rect.w;
    }
}


void saut(Personne *P, int dt, int posinit) {
    double g = 9.81;
    double t = dt / 1000.0;

    int jump_height = 120;
    printf("P->rect.y = %d | posinit + jump_height = %d \n",P->rect.y,posinit-jump_height);
    if(P->up == 1){
    	if(P->rect.y > posinit - jump_height){
    		P->rect.y -= 20;
    	}else{
    		P->up = 0;
    	}
    }

}
