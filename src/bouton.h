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
void FreeBouton(button b[]);

#endif // BOUTON_H

