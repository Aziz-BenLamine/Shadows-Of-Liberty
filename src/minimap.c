#include"minimap.h"
#include "background.h"
#include "player.h"

void initmap (minimap * m)
{
m->minimap.image[3]= IMG_Load("min.png");
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
void afficherpoint(SDL_Surface * img, int x,int y,SDL_Surface *screen) {


    SDL_Rect destRect ;
	destRect.x=x;
	destRect.y=y;

  SDL_BlitSurface(img,NULL, screen, &destRect);

}
void animerMinimap(minimap *m) {

 
  m->animation.positionfromimage.x = m->animation.positionfromimage.x + m->animation.positionfromimage.w;
  if (m->animation.positionfromimage.x >  m->animation.image[3]->w - m->animation.positionfromimage.w)
  {
    m->animation.positionfromimage.x = 0;
 }
}

/*int collisionPP(Personne *p, SDL_Surface *Masque, Background bp)
{
int persowidth = 40;
int persoheight = 64;

SDL_Color color;
    
    int x = p->player.rect.x + persowidth + bp.background.positionfromimage.x;
    int y = p->player.rect.y+persoheight/2 + bp.background.positionfromimage.y;

	color = GetPixel(Masque, x, y);

if (color.r == 0 && color.g == 0 && color.b == 0) {
      
      p->tab[0]=1;
    }  else {
       p->tab[0]=0;
    }

    int x2 = p->player.rect.x + bp.background.positionfromimage.x;
    int y2 = p->player.rect.y +persoheight/2+ bp.background.positionfromimage.y;
   
     color = GetPixel(Masque, x2, y2);

    
    if (color.r == 0 && color.g == 0 && color.b == 0) {
        
            
         p->tab[1]=1;
    }  else {
       p->tab[1]=0;
    }

    int x3 = p->player.rect.x+persowidth/2 + bp.background.positionfromimage.x;
    int y3 = p->player.rect.y+ bp.background.positionfromimage.y-5;
    
     color = GetPixel(Masque, x3, y3);

    
    if (color.r == 0 && color.g == 0 && color.b == 0) {
        
         p->tab[2]=1;
    }  else {
       p->tab[2]=0;
    }
   
    int x4 = p->player.rect.x+persowidth/2 + bp.background.positionfromimage.x;
    int y4 = p->player.rect.y+persoheight+ bp.background.positionfromimage.y-5;
   

    
     color = GetPixel(Masque, x4, y4);

    
    if (color.r == 0 && color.g == 0 && color.b == 0) {
       
            p->tab[3]=1;
    }  else {
       p->tab[3]=0;
    } 

}*/


