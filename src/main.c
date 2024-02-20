#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "bouton.h"
#include "background.h"

#define SCREEN_HEIGHT 700
#define SCREEN_WIDTH 1200
#define MENU_BUTTONS_COUNT 4
#define SETTING_BUTTONS_COUNT 3

int main(int argc, char** argv) {
    SDL_Surface *ecran;
    int playing = 1;
    int menuHoverSoundPlayed = 0;
    int fullscreen = 0;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Echec d'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }

    // INIT MUSIC
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
        printf("Audio Error:%s",Mix_GetError());
    }



    // INIT MENU HOVER SOUND
    Mix_Chunk *menuHoverSound;
    menuHoverSound = Mix_LoadWAV("../audio/menuHoverSound.wav");
    Mix_VolumeChunk(menuHoverSound, MIX_MAX_VOLUME / 2);

    ecran = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF| SDL_HWACCEL);
    if (ecran == NULL) {
        fprintf(stderr, "ERROR CREATING THE WINDOW %d*%d: %s.\n", SCREEN_HEIGHT, SCREEN_WIDTH, SDL_GetError());
        return 1;
    }
    
    // INIT BACKGROUND
    Background background;
    InitBackground(&background);

    button menuButtons[MENU_BUTTONS_COUNT];
    if (InitBouton(menuButtons) != 0) {
        printf("ERROR INITIALIZING MENU BUTTONS.\n");
        return 3;
    }
    
    button settingButtons[SETTING_BUTTONS_COUNT];
    if(InitSettingsButtons(settingButtons) != 0){
    	printf("ERROR INITIALIZING MENU BUTTONS \n");
    	return 4;
    }
    
    SDL_Event event;
    while (playing) {
        AfficherBackground(background, ecran);
        
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                playing = 0;
                break;
            }
            
            
        if(background.niveau == 0){
        AfficherBouton(menuButtons, ecran, 0);
	
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                playing = 0;
                break;
            case SDL_MOUSEMOTION:
                for (int i = 0; i < MENU_BUTTONS_COUNT; i++) {
                    if (point_in_rect(event.motion.x, event.motion.y, menuButtons[i].button_rect)) {
                        if (menuButtons[i].actif == 0) {
                            menuButtons[i].actif = 1;
                            if (!menuHoverSoundPlayed) {
                                Mix_PlayChannel(-1, menuHoverSound, 0);
                                menuHoverSoundPlayed = 1;
                            }
                        }
                    } else {
                        menuButtons[i].actif = 0;
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                        if (event.button.button == SDL_BUTTON_LEFT) {
                            if (point_in_rect(event.button.x, event.button.y, menuButtons[0].button_rect)) {
                                background.niveau = 2;
                                for (int i = 0; i < MENU_BUTTONS_COUNT; i++) {
                                    menuButtons[i].actif = 0;
                                }
                            } else if (point_in_rect(event.button.x, event.button.y, menuButtons[2].button_rect)) {
                                background.niveau = 1;
                                for (int i = 0; i < MENU_BUTTONS_COUNT; i++) {
                                    menuButtons[i].actif = 0;
                                }
                            } else if (point_in_rect(event.button.x, event.button.y, menuButtons[3].button_rect)) {
                                playing = 0;
                                for (int i = 0; i < MENU_BUTTONS_COUNT; i++) {
                                    menuButtons[i].actif = 0;
                                }
                            }
                        }
                        break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_q) {
                    playing = 0;
                }
        }
      }
      else if(background.niveau == 1){
      		AfficherBouton(settingButtons, ecran, 1);
     		SDL_PollEvent(&event);
                switch (event.type) {
                  case SDL_QUIT:
                    playing = 0;
                    break;
                  case SDL_MOUSEMOTION:
                	for (int i = 0; i < SETTING_BUTTONS_COUNT; i++) {
                    		if (point_in_rect(event.motion.x, event.motion.y, settingButtons[i].button_rect)) {
                        		if (settingButtons[i].actif == 0) {
                            			settingButtons[i].actif = 1;
                            			if (!menuHoverSoundPlayed) {
                                			Mix_PlayChannel(-1, menuHoverSound, 0);
                                			menuHoverSoundPlayed = 1;
                            			}
                        		}
                    		} else {
                     		   settingButtons[i].actif = 0;
                   		 }
               		 }
                  break;
                  case SDL_MOUSEBUTTONDOWN:
                        if (event.button.button == SDL_BUTTON_LEFT){
                        	if (point_in_rect(event.button.x, event.button.y, settingButtons[2].button_rect)){
                        		background.niveau = 0;
                        	}else if(point_in_rect(event.button.x, event.button.y, settingButtons[0].button_rect)){
                        		toggleFullScreen(&fullscreen);
                        	}
                        }
                  break;
            }
      
      }
        AfficherBoutonActif(menuButtons, ecran);
        menuHoverSoundPlayed = 0;
        SDL_Flip(ecran);
    }
    
    FreeBackground(&background);
    FreeBouton(menuButtons, MENU_BUTTONS_COUNT);
    FreeBouton(settingButtons, SETTING_BUTTONS_COUNT);
    Mix_FreeChunk(menuHoverSound);
    SDL_Quit();
    return 0;
}

