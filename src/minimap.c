#include"minimap.h"
#include "background.h"
#include "player.h"

void initmap (minimap * m)
{
m->minimap.image[3]= IMG_Load("minimap.png");
m->minimap.camera.x = 0;
m->minimap.camera.y = 0;


m->bonhomme.image[3]= IMG_Load("walk0.png");
m->bonhomme.camera.x = 0;
m->bonhomme.camera.y = 0;



m->animation.image[3]=IMG_Load("spritecolors.png");
   
m->animation.camera.x = 250;
m->animation.camera.y = 60;
m->animation.positionfromimage.h = 47;
m->animation.positionfromimage.w = 30;
m->animation.camera.x = 200;
m->animation.camera.y = 50;

}

void afficherminimap(minimap m,SDL_Surface *ecran)
{
 SDL_BlitSurface(m.minimap.image[3],NULL,ecran,&m.minimap.camera);
 SDL_BlitSurface(m.bonhomme.image[3],NULL,ecran,&m.bonhomme.camera);
 SDL_BlitSurface(m.animation.image[3],&m.animation.positionfromimage, ecran, &m.animation.camera);


}
void Liberer (minimap * m)
{
SDL_FreeSurface(m->bonhomme.image[3]);
SDL_FreeSurface(m->minimap.image[3]);
}
void MAJMinimap(SDL_Rect posJoueur, minimap *m, SDL_Rect cameraa, int redimensionnement)
{
SDL_Rect posJoueurABS;
    posJoueurABS.x = posJoueur.x + cameraa.x;
    posJoueurABS.y = posJoueur.y + cameraa.y;
    m->bonhomme.camera.x = posJoueurABS.x * redimensionnement / 100;
    m->bonhomme.camera.y = posJoueurABS.y * redimensionnement / 100;

}





