#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "background.h"



void InitBackground(Background *b){
    
    b->image[0] = IMG_Load("../assets/menuBackground.png");
    b->image[1] = IMG_Load("../assets/settingsMenu.png");
    b->image[2] = IMG_Load("../assets/tempGameBackground.jpg");
    
    if (b->image[0] == NULL || b->image[1] == NULL || b->image[2] == NULL) {
        printf("ERROR LOADING BACKGROUND IMAGE: %s\n", IMG_GetError());
        return;
    }
    b->pos.x = 0;
    b->pos.y = 0;
    b->pos.w = SCREEN_WIDTH;
    b->pos.h = SCREEN_HEIGHT;
    
    b->niveau = 0;
}


void AfficherBackground(Background b, SDL_Surface *ecran){
 SDL_BlitSurface(b.image[b.niveau], NULL, ecran, &b.pos);
}

void toggleFullScreen() {
    if (SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_FULLSCREEN) == NULL) {
        printf("FAILED TO TOGGLE FULL SCREEN: %s\n", SDL_GetError());

    }
}

void toggleWindowedScreen() {
    if (SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0) == NULL) {
        printf("FAILED TO TOGGLE WINDOWED SCREEN: %s\n", SDL_GetError());
    }
}

void FreeBackground(Background *b) {
    for (int i = 0; i < 3; i++) {
        SDL_FreeSurface(b->image[i]);
    }
}

//SOUND

void InitBackgroundSound(backgroundSound *sound){
    sound->music = Mix_LoadMUS("../audio/dark-background-sound.wav");
    Mix_PlayMusic(sound->music, -1);
    
    // Load slider images
    sound->sliderState[0] = IMG_Load("../assets/sound/sound1.png");
    sound->sliderState[1] = IMG_Load("../assets/sound/sound2.png");
    sound->sliderState[2] = IMG_Load("../assets/sound/sound3.png");
    sound->sliderState[3] = IMG_Load("../assets/sound/sound4.png");
    sound->sliderState[4] = IMG_Load("../assets/sound/sound5.png");
    
    for (int i = 0; i < 5; ++i) {
        if (sound->sliderState[i] == NULL) {
            printf("Failed to load slider image %d: %s\n", i, IMG_GetError());
            return;
        }
    }
    
    sound->soundLevel = 3;
    sound->pos = (SDL_Rect){520 , 400, sound->sliderState[0]->w, sound->sliderState[0]->h};
}


void AfficherSoundSlider(backgroundSound *sound, SDL_Surface *ecran){    
    SDL_Surface *sliderImage = sound->sliderState[sound->soundLevel];
    SDL_BlitSurface(sliderImage, NULL, ecran, &sound->pos);

}

void changeBackgroundSoundLevel(backgroundSound *sound, int action) {
    if (action == 0 && sound->soundLevel != 0) {
        sound->soundLevel--;
    } else if (action == 1 && sound->soundLevel != 4) {
        sound->soundLevel++;
    }

    switch(sound->soundLevel) {
        case 0:
            Mix_VolumeMusic(0);
            break;
        case 1: 
            Mix_VolumeMusic(MIX_MAX_VOLUME * 0.25);
            break;
        case 2: 
            Mix_VolumeMusic(MIX_MAX_VOLUME * 0.5);
            break;
        case 3: 
            Mix_VolumeMusic(MIX_MAX_VOLUME * 0.75);
            break;
        case 4: 
            Mix_VolumeMusic(MIX_MAX_VOLUME);
            break;
    }
}

// INTRO


void displayImageWithFade(char *imagePath, SDL_Surface *screen) {
    SDL_Surface *image = IMG_Load(imagePath);
    if (image == NULL) {
        fprintf(stderr, "Error loading image: %s\n", IMG_GetError());
        return;
    }

    // Set initial alpha value
    int alpha = 255; // Start with full opacity

    // Calculate the number of steps based on FADE_DURATION and a desired frame rate
    int num_steps = 150;
    int alpha_step = 255 / num_steps;

    SDL_Rect fadeRect = {0, 0, screen->w, screen->h};

    // Fade out effect
    for (int i = 0; i <= num_steps; ++i) {
        // Calculate alpha value
        alpha = 255 - i * alpha_step;  // Fading out from full opacity to transparent

        // Fill the screen with black color and adjusted alpha
        SDL_FillRect(screen, &fadeRect, SDL_MapRGBA(screen->format, 0, 0, 0, alpha));

        // Blit the image onto the screen with adjusted alpha
        SDL_SetAlpha(image, SDL_SRCALPHA, alpha);
        SDL_BlitSurface(image, NULL, screen, NULL);

        // Update the screen after filling the fade rect and blitting the image
        SDL_Flip(screen);

        // Delay for smoother animation
        SDL_Delay(1); // Adjusted delay for longer fade
    }

    // Free the image surface
    SDL_FreeSurface(image);
}