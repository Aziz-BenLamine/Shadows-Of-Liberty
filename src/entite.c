#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <math.h>
#include "entite.h"
#include "player.h"



void InitEnnemi(Entity *e){
 e->image[0][0]=IMG_Load("../assets/ennemi/enwalk4.png");
 e->image[0][1]=IMG_Load("../assets/ennemi/enwalk3.png");
 e->image[0][2]=IMG_Load("../assets/ennemi/enwalk2.png");
 e->image[0][3]=IMG_Load("../assets/ennemi/enwalk1.png");
 e->image[0][4]=IMG_Load("../assets/ennemi/enwalk0.png");
 e->image[1][0]=IMG_Load("../assets/ennemi/enleftwalk4.png");
 e->image[1][1]=IMG_Load("../assets/ennemi/enleftwalk3.png");
 e->image[1][2]=IMG_Load("../assets/ennemi/enleftwalk2.png");
 e->image[1][3]=IMG_Load("../assets/ennemi/enleftwalk1.png");
 e->image[1][4]=IMG_Load("../assets/ennemi/enleftwalk0.png");
 /*e->image[2][0]=IMG_Load("s1.png");
 e->image[2][1]=IMG_Load("s2.png");
 e->image[2][2]=IMG_Load("s3.png");
 e->image[2][3]=IMG_Load("s4.png");
 e->image[2][4]=IMG_Load("s5.png");*/
e->pos.x=700;
e->pos.y=200;
e->pos.w=e->image[0][0]->w;
e->pos.h=e->image[0][0]->h;


e->direction=0;
e->num=0;
}

void Initbonus(Entity *e){
e->image[0][0]=IMG_Load("../assets/ennemi/enleftwalk0.png");
/*e->image[0][1]=
e->image[0][2]=
e->image[0][3]=
e->image[0][4]=
*/

e->pos.x=500;
e->pos.y=200;
e->pos.w=e->image[0][0]->w;
e->pos.h=e->image[0][0]->h;


e->direction=0;
e->num=0;

}


void AfficherEnnemi(Entity e, SDL_Surface *screen){
  SDL_BlitSurface(e.image[e.direction][e.num], NULL,screen, &e.pos);

}
void animerEntity(Entity *e){
if (e->num==4){
e->num=0;
}
else{
e->num++;

}
}
void move(Entity *e){
if(e->pos.x>900){
e->direction=1;
}
if(e->pos.x<250){
e->direction=0;
}
if(e->direction==0){
e->pos.x=e->pos.x+10;
}
else{
e->pos.x=e->pos.x-10;
}

}
int collisionBB(Entity e, SDL_Rect r){
if(r.x>=e.pos.x+e.pos.w || r.x+r.w<=e.pos.x || r.y+r.h<=e.pos.y ||r.y>=e.pos.y+e.pos.h){
return 0;
}
else{
return 1;
}

}




int collisionTri(Personne e, SDL_Rect pose){
SDL_Rect rec1;
SDL_Rect rec2;
float r1,r2,d;

rec1.x=e.rect.x+(e.rect.w)/2;
rec1.y=e.rect.y+(e.rect.h)/2;
r1=sqrt(((e.rect.w)/2)*((e.rect.w)/2)+((e.rect.h)/2)*((e.rect.h)/2));

rec2.x=pose.x+(pose.w)/2;
rec2.y=pose.y+(pose.h)/2;
r2=sqrt(((pose.w)/2)*((pose.w)/2)+((pose.h)/2)*((pose.h)/2));

d=sqrt((rec1.x-rec2.x)*(rec1.x-rec2.x)+(rec1.y-rec2.y)*(rec1.y-rec2.y));

if(d<=r1+r2){
return 1;
}
else{
return 0;

}

}

void Afficherbonus(Entity e, SDL_Surface *screen){
 SDL_BlitSurface(e.image[0][e.num], NULL,screen, &e.pos);
}

