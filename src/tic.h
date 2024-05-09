#ifndef TIC_H_INCLUDED
#define TIC_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#define NUM_IMAGE 15
#define NUM_TIME 7
typedef struct
{
int joueur;
SDL_Surface * image1,*image2[NUM_IMAGE] ,*image3[NUM_IMAGE],*time[NUM_TIME];
int tabsuivi[9];
SDL_Rect pos;
SDL_Rect posAnim;
int tour;
TTF_Font *font;
SDL_Color couleur;
SDL_Rect posMSG;
}tic;

void initialisation(tic *t);
void affichage(tic t,SDL_Surface *ecran ) ;
int atilganer(int tabsuivi[]);
void Resultat (tic t,SDL_Surface* ecran);
void liberationmemoire(tic *t);
int minimax(int tabsuivi[],int joueur);
void calcul_coup(int tabsuivi[]);
void afficherTexteRotZoom(tic t,SDL_Surface *ecran, char *texte, double angle, double zoom, int x, int y); 
#endif // TIC_H
