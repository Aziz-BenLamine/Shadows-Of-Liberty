#ifndef BOUTON_H
#define BOUTON_H

#include <SDL/SDL.h>

typedef struct{
    SDL_Surface *button_images[2];
    SDL_Rect button_rect;
    int actif;
} button;

int InitBouton(button b[]);
void AfficherBouton(button b[], SDL_Surface *ecran, int niveau);
void AfficherBoutonActif(button b[], SDL_Surface *ecran);
void FreeBouton(button b[]);
int point_in_rect(int x, int y, SDL_Rect rect);
#endif // BOUTON_H

