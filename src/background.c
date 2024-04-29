#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "background.h"
#include "bouton.h"
#include"minimap.h"
#define NUM_IMAGES 7

#define FULL_SCREEN_HEIGHT 944
#define FULL_SCREEN_WIDTH 1920

void InitBackground(Background *b){
    
    b->image[0] = IMG_Load("../assets/menuBackground.png");
    b->image[1] = IMG_Load("../assets/settingsMenu.png");
    b->image[2] = IMG_Load("../assets/level 31.png");
    
    if (b->image[0] == NULL || b->image[1] == NULL || b->image[2] == NULL) {
        printf("ERROR LOADING BACKGROUND IMAGE: %s\n", IMG_GetError());
        return;
    }

    b->niveau = 0;

    b->bg1.x = 0;
    b->bg1.y = 0;
    b->bg2.x = 800;
    b->bg2.y = 0;
    
    b->niveau = 0;
//ajouter init camera
    b->camera.x = 0;
    b->camera.y = 0;
    b->camera.w = SCREEN_WIDTH;
    b->camera.h = SCREEN_HEIGHT;
    b->camera1.x = 0;
    b->camera1.y = 0;
    b->camera1.w = SCREEN_WIDTH;
    b->camera1.h = SCREEN_HEIGHT;
}


void AfficherBackground(Background b, SDL_Surface *ecran,int lvl){
 	SDL_BlitSurface(b.image[b.niveau], &b.camera, ecran, &b.bg1);
	//SDL_BlitSurface(b.image[lvl], &b.camera1, ecran, &b.bg2);
}

void toggleFullScreen(button b[]) {
    if (SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_FULLSCREEN | SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_HWACCEL) == NULL) {
        printf("FAILED TO TOGGLE FULL SCREEN: %s\n", SDL_GetError());
        return;
    }

    // Update button positions for fullscreen mode
    InitBouton(b, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void toggleWindowedScreen(button b[]) {
    if (SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0) == NULL) {
        printf("FAILED TO TOGGLE WINDOWED SCREEN: %s\n", SDL_GetError());
        return;
    }

    // Update button positions for windowed mode
    InitBouton(b, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void FreeBackground(Background *b) {
    for (int i = 0; i < 3; i++) {
        SDL_FreeSurface(b->image[i]);
    }
}

//SOUND

void InitBackgroundSound(backgroundSound *sound){
    sound->music = Mix_LoadMUS("../audio/gameSound.mp3");
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
    sound->pos = (SDL_Rect){500 , 502, sound->sliderState[0]->w, sound->sliderState[0]->h};
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
        //SDL_Delay(1); // Adjusted delay for longer fade
    }

    // Free the image surface
    SDL_FreeSurface(image);
}


//TEXT

SDL_Surface* initText(TTF_Font *font, char *text, SDL_Color color) {
    SDL_Surface *surfaceTexte = TTF_RenderText_Solid(font, text, color);
    if (surfaceTexte == NULL) {
        fprintf(stderr, "Failed to render text: %s\n", TTF_GetError());
        return NULL;
    }
    return surfaceTexte;
}


void renderText(SDL_Surface *surface, TTF_Font *font, char *text, SDL_Color color, int x, int y) {
    SDL_Surface *textSurface = initText(font, text, color);
    if (textSurface == NULL) {
        return;
    }
    SDL_Rect position = {x, y, 0, 0};
    SDL_BlitSurface(textSurface, NULL, surface, &position);
    SDL_FreeSurface(textSurface);
}

void scrolling(Background *b,int pas,int dir,int player){
	if(player == 1){
		if(dir==0){
	    	b->camera.x+=pas;
		}
		if(dir==1){
	 	   b->camera.x-=pas;
		}
		if(dir== 0 && (b->image[2]->w)-1600 <=(b->camera.x)){
		    b->camera.x=b->image[2]->w-1600;
		}
		if((dir==1) && (b->camera.x <= 0)){
		    b->camera.x=0;
		}
		if(dir==2){
		    b->camera.y+=pas;
		}
		if(dir==3){
		    b->camera.y-=pas;
		}
		if(dir==2 && (b->image[2]->h)-700<=b->camera.y){
		    b->camera.y=b->image[2]->h-700;
		}
		if(dir==3 && b->camera.y <= 0){
		    b->camera.y=0;
		}
	}else{
		if(dir==0){
	    	b->camera1.x+=pas;
		}
		if(dir==1){
	 	   b->camera1.x-=pas;
		}
		if(dir== 0 && (b->image[2]->w)-1600 <=(b->camera1.x)){
		    b->camera1.x=b->image[2]->w-1600;
		}
		if((dir==1) && (b->camera1.x <= 0)){
		    b->camera1.x=0;
		}
		if(dir==2){
		    b->camera1.y+=pas;
		}
		if(dir==3){
		    b->camera1.y-=pas;
		}
		if(dir==2 && (b->image[2]->h)-700<=b->camera1.y){
		    b->camera1.y=b->image[2]->h-700;
		}
		if(dir==3 && b->camera1.y <= 0){
		    b->camera1.y=0;
		}
	}
}

void animerBackground(SDL_Surface *ecran,int index){
        int currentImageIndex = 0;
	SDL_Surface *backgroundImages[NUM_IMAGES];
	int i;
	for (int i = 0; i < NUM_IMAGES; i++) {
        char filename[50];
        sprintf(filename, "../assets/moon%d.png", i);
        backgroundImages[i] = IMG_Load(filename);
        if (backgroundImages[i] == NULL) {
            printf("Error loading background image %d: %s\n", i, IMG_GetError());
        }
    }
    SDL_Rect posAnim;
    posAnim.x = 1010;
    posAnim.y = 70;
    posAnim.w = backgroundImages[0]->w;
    posAnim.h = backgroundImages[0]->h;

    SDL_BlitSurface(backgroundImages[index], NULL, ecran, &posAnim);
    
}
/*void animerBackground(background *e, SDL_Surface *ecran)
{
	for (int j = 0; j < 5; j++)
	{
		switch (j)
		{
		case 0:
			SDL_FreeSurface(e->img_b);
			e->img = IMG_Load("");
			break;
		case 1:
			SDL_FreeSurface(e->img_b);
			e->img = IMG_Load("");
		case 2:

			SDL_FreeSurface(e->img_b);
			e->img = IMG_Load("");
			break;
		case 3:
			SDL_FreeSurface(e->img_b);
			e->img = IMG_Load("");
			break;
		case 4:
			SDL_FreeSurface(e->img_b);
			e->img = IMG_Load("");
			break;
		}
		SDL_BlitSurface(e->img, &e->bg1, ecran, NULL);
		SDL_Flip(ecran);
		SDL_Delay(100);
		}
	}
}


void savescore(char *filename,int score){
	FILE* f = open(filename, "a");
	
	if (f == NULL){
		printf("error");
	}
	fprintf(f,"%d %d %s \n",s.score,s.temps,s.nom);

	fclose(f);
}

void bestscore(char * filename , scoreinfo t[3]){
	FILE *f = open(filename,"r");
	if(f == NULL){
		printf("errorr");	
	}
	int i = 0;
	while (fscanf(f, "%d %d %s", &t[i].score, &t[i].temps, t[i].nom) != EOF) {
        t[i].surface = NULL;
        t[i].x = 0;
        t[i].y = 0;
        i++;
    }
    fclose(f);


    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            if (t[i].score == t[j].score) {
                if (t[i].temps > t[j].temps) {
                    ScoreInfo temp = t[i];
                    t[i] = t[j];
                    t[j] = temp;
                }
            }
        }
    }

    char str[100];
    for (int i = 0; i < 3; i++) {
        sprintf(str, "%s %d %d", t[i].nom, t[i].score, t[i].temps);
    }

}

void afficherbest(SDL_Surface *ecran,scoreinfo t[]){
	
}*/
