#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "player.h"
#include"minimap.h"
#define SCREEN_HEIGHT 700
#define SCREEN_WIDTH 1600


void init(Personne * p, int numperso, int multi){
 int y;
 p->dir = 0;
 p->num = 0;
 p->score = 0;
 p->vies = 3;
 p->vitesse = 10;
 p->acceleration = 0.0;
 p->up = 0;
 //INIT PLAYER HEALTH IMAGES
 p->healthImage[0] = IMG_Load("../assets/vies/HEART0.png");
 p->healthImage[1] = IMG_Load("../assets/vies/HEART1.png");
 p->healthImage[2] = IMG_Load("../assets/vies/HEART2.png");
 p->healthImage[3] = IMG_Load("../assets/vies/HEART3.png");
 p->healthRect = (SDL_Rect){1350, 25, p->healthImage[0]->w, p->healthImage[0]->h};
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
    
    p->img[2][0] = IMG_Load("../assets/player/jump/rightjump0.png");
    p->img[2][1] = IMG_Load("../assets/player/jump/rightjump1.png");
    p->img[2][2] = IMG_Load("../assets/player/jump/rightjump2.png");
    p->img[2][3] = IMG_Load("../assets/player/jump/rightjump3.png");
    p->img[2][4] = IMG_Load("../assets/player/jump/rightjump4.png");
    p->img[3][5] = IMG_Load("../assets/player/jump/rightjump5.png");
    
    p->img[3][0] = IMG_Load("../assets/player/jump/leftjump0.png");
    p->img[3][1] = IMG_Load("../assets/player/jump/leftjump1.png");
    p->img[3][2] = IMG_Load("../assets/player/jump/leftjump2.png");
    p->img[3][3] = IMG_Load("../assets/player/jump/leftjump3.png");
    p->img[3][4] = IMG_Load("../assets/player/jump/leftjump4.png");
    p->img[3][5] = IMG_Load("../assets/player/jump/leftjump5.png");
    y = 430;
    printf("Images Loaded");
 } 
 else if(numperso == 1)
 {
    p->img[0][0] = IMG_Load("../assets/player2/walk0.png");
    p->img[0][1] = IMG_Load("../assets/player2/walk1.png");
    p->img[0][2] = IMG_Load("../assets/player2/walk2.png");
    p->img[0][3] = IMG_Load("../assets/player2/walk3.png");
    p->img[0][4] = IMG_Load("../assets/player2/walk4.png");
    p->img[0][5] = IMG_Load("../assets/player2/walk5.png");
    
    p->img[1][0] = IMG_Load("../assets/player2/leftwalk0.png");
    p->img[1][1] = IMG_Load("../assets/player2/leftwalk1.png");
    p->img[1][2] = IMG_Load("../assets/player2/leftwalk2.png");
    p->img[1][3] = IMG_Load("../assets/player2/leftwalk3.png");
    p->img[1][4] = IMG_Load("../assets/player2/leftwalk4.png");
    p->img[1][5] = IMG_Load("../assets/player2/leftwalk5.png");
    
    p->img[2][0] = IMG_Load("../assets/player2/jump/rightjump0.png");
    p->img[2][1] = IMG_Load("../assets/player2/jump/rightjump1.png");
    p->img[2][2] = IMG_Load("../assets/player2/jump/rightjump2.png");
    p->img[2][3] = IMG_Load("../assets/player2/jump/rightjump3.png");
    p->img[2][4] = IMG_Load("../assets/player2/jump/rightjump4.png");
    p->img[3][5] = IMG_Load("../assets/player2/jump/rightjump5.png");
    
    p->img[3][0] = IMG_Load("../assets/player2/jump/leftjump0.png");
    p->img[3][1] = IMG_Load("../assets/player2/jump/leftjump1.png");
    p->img[3][2] = IMG_Load("../assets/player2/jump/leftjump2.png");
    p->img[3][3] = IMG_Load("../assets/player2/jump/leftjump3.png");
    p->img[3][4] = IMG_Load("../assets/player2/jump/leftjump4.png");
    p->img[3][5] = IMG_Load("../assets/player2/jump/leftjump5.png");
    y = 440;
    printf("Images Loaded");
 }
 if(p->img[0][0] == NULL || p->img[0][1] == NULL ||
    p->img[0][2] == NULL || p->img[0][3] == NULL ||
    p->img[0][4] == NULL || p->img[0][5] == NULL ||
    
    p->img[1][0] == NULL || p->img[1][1] == NULL ||
    p->img[1][2] == NULL || p->img[1][3] == NULL ||
    p->img[1][4] == NULL || p->img[1][5] == NULL ||
    
    p->img[2][0] == NULL || p->img[2][1] == NULL ||
    p->img[2][2] == NULL || p->img[2][3] == NULL ||
    p->img[2][4] == NULL || p->img[2][5] == NULL ||
    
    p->img[3][0] == NULL || p->img[3][1] == NULL ||
    p->img[3][2] == NULL || p->img[3][3] == NULL ||
    p->img[3][4] == NULL || p->img[3][5] == NULL
    ){
	printf("ERROR LOADING PLAYER IMAGES %s\n", IMG_GetError());
        return;
       }
     if(multi == 0){
     	p->rect = (SDL_Rect){200, y, p->img[0][0]->w, p->img[0][0]->h};
     }else if(multi == 1){
        p->rect = (SDL_Rect){850, y, p->img[0][0]->w, p->img[0][0]->h};
     }

	for (int i = 0; i < 4; i++) {
		p->tab[i] = 1;
	    }
	
	/*p->damage[0]=1;
	p->damage[1]=1;
	p->damage[2]=1;
	p->damage[3]=1;*/
}

void afficherPerso(Personne p, SDL_Surface *screen) {
    SDL_BlitSurface(p.img[p.dir][p.num], NULL, screen, &p.rect);
}

void animerPerso(Personne *p) {
    p->num++;
    if (p->num >= playerImagerows) {
    	printf("YO");
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
    //printf("dx = %.2f\n", dx);
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
    //double g = 9.81;
    //double t = dt / 1000.0;

    int jump_height = 120;
    //printf("P->rect.y = %d | posinit + jump_height = %d \n",P->rect.y,posinit-jump_height);
    if(P->up == 1){
    	if(P->rect.y > posinit - jump_height){
    		P->rect.y -= 20;
    	}else{
    		P->up = 0;
    	}
    }

}

void sautParabolique(Personne *player, int *jumpDone, int *x0, int *y0, int *xINIT, int *yINIT, SDL_Surface *Masque, Background bp) {
    if (!(*jumpDone)) {
    	//printf("PLAYER x0 = %d | x = %d PLAYER.UP = %d\n",x0,player.rect.x,player.up);
	//printf("PLAYER y0 = %d | y = %d PLAYER.UP = %d\n",y0,player.rect.y,player.up);
	/*player->tab[0] == 1 collision a droite
	  player->tab[1] == 1 collision a gauche
	  player->tab[2] == 1 collision en haut
	  player->tab[3] == 1 collision en bas
	*/
	player->rect.y -= 20;
        if (player->up == 0) {
            *xINIT = player->rect.x;
            *yINIT = player->rect.y;
            *x0 = -50;
            *y0 = 0;
            player->up = 1;
        }
        
        
	collisionPP(player,Masque,bp);
	
	
        if (player->up == 1) {
            *x0 += 10;
            *y0 = -0.04 * (*x0) * (*x0) + 100;
            if(player->tab[0] != 1 && player->tab[1] != 1 && player->tab[2] != 1 && player->tab[3] != 1){
		    if (player->dir == 0 || player->dir == 2) {
		        player->rect.x += 10;
		    } else {
		        player->rect.x -= 10;
		    }
	    player->rect.y = *yINIT - *y0;
	    }
	    
            
            
            if (player->rect.x < 0) {
        	player->rect.x = 0;
    	    } else if (player->rect.x + player->rect.w > SCREEN_WIDTH) {
        	player->rect.x = SCREEN_WIDTH - player->rect.w;
    		}
            if (*x0 >= 50) {
                player->up = 0;
                *jumpDone = 1;
            }
        }
    }
}

void freePlayer(Personne *p) {
    for (int i = 0; i < playerImageColumns; i++) {
        for (int j = 0; j < playerImagerows; j++) {
            if (p->img[i][j]) {
                printf("Freeing img[%d][%d]\n", i, j);
                SDL_FreeSurface(p->img[i][j]);
                p->img[i][j] = NULL; // Set to NULL after freeing
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        if (p->healthImage[i]) {
            printf("Freeing healthImage[%d]\n", i);
            SDL_FreeSurface(p->healthImage[i]);
            p->healthImage[i] = NULL; // Set to NULL after freeing
        }
    }
}
