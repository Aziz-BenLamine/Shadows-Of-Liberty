#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "bouton.h"

#define MENU_BUTTONS_COUNT 4
#define SETTING_BUTTONS_COUNT 5

int point_in_rect(int x, int y, SDL_Rect rect) {
    return (x >= rect.x && x < rect.x + rect.w && y >= rect.y && y < rect.y + rect.h);
}

int InitBouton(button b[]) {
    //INIT newGameButton
    b[0].button_images[0] = IMG_Load("../assets/newGameButton.png");
    b[0].button_images[1] = IMG_Load("../assets/newGameButtonHovered.png");
    b[0].actif = 0;

    //INIT loadGameButton
    b[1].button_images[0] = IMG_Load("../assets/loadGameButton.png");
    b[1].button_images[1] = IMG_Load("../assets/loadGameButtonHovered.png");
    b[1].actif = 0;

    //INIT settingsButton
    b[2].button_images[0] = IMG_Load("../assets/settingButton.png");
    b[2].button_images[1] = IMG_Load("../assets/settingButtonHovered.png");
    b[2].actif = 0;

    //INIT quitButton
    b[3].button_images[0] = IMG_Load("../assets/quitButton.png");
    b[3].button_images[1] = IMG_Load("../assets/quitButtonHovered.png");
    b[3].actif = 0;

    if(b[0].button_images[0] == NULL || b[0].button_images[1] == NULL ||
       b[1].button_images[0] == NULL || b[1].button_images[1] == NULL ||
       b[2].button_images[0] == NULL || b[2].button_images[1] == NULL ||
       b[3].button_images[0] == NULL || b[3].button_images[1] == NULL) {
        printf("ERROR LOADING BUTTON IMAGES: %s\n", IMG_GetError());
        return 3;
    }

    for(int i = 0; i < 3; i++) {
        b[i].button_rect = (SDL_Rect){475 , 230 + i * 50, b[i].button_images[0]->w, b[i].button_images[0]->h};
    }

    b[3].button_rect = (SDL_Rect){475 , 450, b[3].button_images[0]->w, b[3].button_images[0]->h};

    return 0;
}

int InitSettingsButtons(button b[]){
    //INIT FULL SCREEN BUTTON
    b[0].button_images[0] = IMG_Load("../assets/fullScreenButton.png");
    b[0].button_images[1] = IMG_Load("../assets/fullScreenHoveredButton.png");
    b[0].actif = 0;

    //INIT WINDOWED SCREEN BUTTON
    b[1].button_images[0] = IMG_Load("../assets/windowedButton.png");
    b[1].button_images[1] = IMG_Load("../assets/windowedHoveredButton.png");
    b[1].actif = 0;

    //INIT RETURN BUTTON 
    b[2].button_images[0] = IMG_Load("../assets/returnButton.png");
    b[2].button_images[1] = IMG_Load("../assets/returnHoveredButton.png");
    b[2].actif = 0;
    
    //INIT SOUNDDOWN BUTTONS
    b[3].button_images[0] = IMG_Load("../assets/sound/soundDownButton.png");
    b[3].button_images[1] = IMG_Load("../assets/sound/soundDownButton.png");
    b[3].actif=0;
    //INIT SOUNDUP BUTTONS
    b[4].button_images[0] = IMG_Load("../assets/sound/soundUpButton.png");
    b[4].button_images[1] = IMG_Load("../assets/sound/soundUpButton.png");
    b[4].actif=0;
    
    if(b[0].button_images[0] == NULL || b[0].button_images[1] == NULL ||
       b[1].button_images[0] == NULL || b[1].button_images[1] == NULL ||
       b[2].button_images[0] == NULL || b[2].button_images[1] == NULL ||
       b[3].button_images[0] == NULL || b[4].button_images[0] == NULL) {
        printf("ERROR LOADING BUTTON IMAGES: %s\n", IMG_GetError());
        return 4;
    }
    
    //DISPLAY BUTTONS RECT
    for(int i = 0; i < 2; i++) {
        b[i].button_rect = (SDL_Rect){490 , 230 + i * 80, b[i].button_images[0]->w, b[i].button_images[0]->h};
    }
    
    //RETURN BUTTON RECT
    b[2].button_rect = (SDL_Rect){490 , 530, b[2].button_images[0]->w, b[2].button_images[0]->h};
    
    //DISPLAY SOUND BUTTON RECT
    b[3].button_rect = (SDL_Rect){480 , 230 + 170, b[3].button_images[0]->w, b[3].button_images[0]->h};
    b[4].button_rect = (SDL_Rect){775 , 230 + 170, b[4].button_images[0]->w, b[4].button_images[0]->h};

    return 0;
}

void AfficherBouton(button b[], SDL_Surface *ecran, int niveau) {
    int buttonsCount;
    if(niveau == 0){
        buttonsCount = MENU_BUTTONS_COUNT;
    } else if (niveau == 1){
        buttonsCount = SETTING_BUTTONS_COUNT;
    }
    for(int i = 0; i < buttonsCount; i++) {
        SDL_Surface *buttonImage = b[i].button_images[b[i].actif];
        SDL_BlitSurface(buttonImage, NULL, ecran, &b[i].button_rect);
    }
}


void AfficherBoutonActif(button b[], SDL_Surface *ecran) {

    for(int i = 0; i < 4; i++) {

        if (b[i].actif) {

            SDL_Surface *buttonImage = b[i].button_images[b[i].actif];

            SDL_BlitSurface(buttonImage, NULL, ecran, &b[i].button_rect);

        }

    }
}

void FreeBouton(button b[], int nb) {
    for(int i = 0; i < nb; i++) {
        SDL_FreeSurface(b[i].button_images[0]);
        SDL_FreeSurface(b[i].button_images[1]);
    }
}


