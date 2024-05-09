#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

#include "player.h"
#include "minimap.h"
#include "background.h"

void initmap (minimap * m)
{
m->minimap.image[3]= IMG_Load("min.png");
m->minimap.camera.x = 0;
m->minimap.camera.y = 0;


m->bonhomme.image[3]= IMG_Load("walk0.png");
m->bonhomme.camera.x = 0;
m->bonhomme.camera.y = 0;



m->animation.image[3]=IMG_Load("spritecolors.png");
   
m->animation.camera.x = 100;
m->animation.camera.y = 60;
m->animation.camera.h = 47;
m->animation.camera.w = 30;
m->animation.bg1.x = 200;
m->animation.bg1.y = 50;

}

SDL_Color  GetPixel(SDL_Surface *pSurface,int x,int y)
{
	SDL_Color color;
	Uint32 col=0;
	//Determine position
	char* pPosition=(char* ) pSurface->pixels;
	pPosition+= (pSurface->pitch * y);
	pPosition+= (pSurface->format->BytesPerPixel *x);
	memcpy(&col ,pPosition ,pSurface->format->BytesPerPixel);
	//convertir color
	SDL_GetRGB(col,pSurface->format, &color.r, &color.g, &color.b);
	return (color); 
}

void afficherminimap(minimap m,SDL_Surface *ecran)
{
 SDL_BlitSurface(m.minimap.image[3],NULL,ecran,&m.minimap.camera);
 SDL_BlitSurface(m.bonhomme.image[3],NULL,ecran,&m.bonhomme.camera);
 
 SDL_BlitSurface(m.animation.image[3],&m.animation.camera, ecran, &m.animation.camera);

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
void afficherpoint(SDL_Surface * img, int x,int y,SDL_Surface *ecran) {


    SDL_Rect destRect ;
	destRect.x=x;
	destRect.y=y;

  SDL_BlitSurface(img,NULL, ecran, &destRect);

}
void animerMinimap(minimap *m) {

 
  m->animation.camera.x = m->animation.camera.x + m->animation.camera.w;
  if (m->animation.camera.x >  m->animation.image[3]->w - m->animation.camera.w)
  {
    m->animation.camera.x = 0;
 }
}

int collisionPP(Personne *p, SDL_Surface *Masque, Background bp)
{
    int persowidth = p->img[0][0]->w;
    int persoheight = p->img[0][0]->h;

    SDL_Color color;

    int x = p->rect.x + persowidth + bp.camera.x;
    int y = p->rect.y + persoheight/2 + bp.camera.y;

    color = GetPixel(Masque, x, y);

    if (color.r == 0 && color.g == 0 && color.b == 0) {
        p->tab[0] = 1;
    } else {
        p->tab[0] = 0;
    }

    int x2 = p->rect.x + bp.camera.x;
    int y2 = p->rect.y + persoheight/2 + bp.camera.y;

    color = GetPixel(Masque, x2, y2);

    if (color.r == 0 && color.g == 0 && color.b == 0) {
        p->tab[1] = 1;
    } else {
        p->tab[1] = 0;
    }

    int x3 = p->rect.x + persowidth/2 + bp.camera.x;
    int y3 = p->rect.y + bp.camera.y - 5;

    color = GetPixel(Masque, x3, y3);

    if (color.r == 0 && color.g == 0 && color.b == 0) {
        p->tab[2] = 1;
    } else {
        p->tab[2] = 0;
    }

    int x4 = p->rect.x + persowidth/2 + bp.camera.x;
    int y4 = p->rect.y + persoheight + bp.camera.y - 5;

    color = GetPixel(Masque, x4, y4);

    if (color.r == 0 && color.g == 0 && color.b == 0) {
        p->tab[3] = 1;
    } else {
        p->tab[3] = 0;
    }

    return 0;
}
void sauvgarder(Personne p,Background b,char *nomfichier) {

//save the next value at the end of the file in this format value:value:value....;
 FILE *file = fopen(nomfichier, "w"); // Open the file in append mode

    // Check if file opened successfully
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Write the values to the file in the specified format
    fprintf(file, "%d:%d:%d:%d:%d:%d\n",
            b.camera.x, b.camera.y,
            b.niveau,
            p.cameraa.x, p.cameraa.y,
            p.dir);

    fclose(file); // Close the file
};
void charger(Personne *p,Background *b,char *nomfichier) {
//the opposit of the save now ched read from the file and save in the variable
     // Open the file in read mode
    FILE *file = fopen(nomfichier, "r");

    // Check if file opened successfully
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Read the values from the file in the specified format
    fscanf(file, "%hd:%hd:%d:%hd:%hd:%d\n",
           &b->camera.x, &b->camera.y,
           &b->niveau,
           &p->cameraa.x, &p->cameraa.y,
           &p->dir);

    fclose(file); // Close the file
};


