#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

#define SCREEN_HEIGHT 700
#define SCREEN_WIDTH 1200

#define MENU_BUTTONS_COUNT 4

int point_in_rect(int x, int y, SDL_Rect rect) {
    return (x >= rect.x && x < rect.x + rect.w && y >= rect.y && y < rect.y + rect.h);
}

int main(int argc, char** argv) {
    SDL_Surface *ecran;
    int playing = 1;
    int menuHoverSoundPlayed = 0;
    //INIT MENU BUTTONS TO NORMAL STATE
    int button_state[MENU_BUTTONS_COUNT] = {0, 0, 0, 0}; // 0: Normal, 1: Hovered

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Echec d'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }
    
    //INIT MUSIC
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){
    	printf("Audio Error:%s",Mix_GetError());
    }
    Mix_Music *backgroundMusic;
    backgroundMusic = Mix_LoadMUS("../audio/dark-background-sound.wav");
    Mix_PlayMusic(backgroundMusic, -1);
    
    //INIT MENU HOVER SOUND
    Mix_Chunk *menuHoverSound;
    menuHoverSound = Mix_LoadWAV("../audio/menuHoverSound.wav");
    
    //To REDUCE THE SOUND TO HALF
    Mix_VolumeChunk(menuHoverSound, MIX_MAX_VOLUME / 2);
    
    ecran = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    if (ecran == NULL) {
        fprintf(stderr, "ERROR CREATING THE WINDOW %d*%d: %s.\n", SCREEN_HEIGHT, SCREEN_WIDTH, SDL_GetError());
        return 1;
    }
    
    SDL_Surface *backgroundImage = IMG_Load("../assets/menuBackground.png");

    if (backgroundImage == NULL) {
        printf("ERROR LOADING BACKGROUND IMAGE: %s\n", IMG_GetError());
        return 2;
    }

    SDL_Rect posecranimg = {
        .x = 0,
        .y = 0,
        .w = backgroundImage->w,
        .h = backgroundImage->h
    };
    
    //Load Buttons assets
    SDL_Surface *button_images[MENU_BUTTONS_COUNT][2];
    
    //newGameButton
    button_images[0][0] = IMG_Load("../assets/newGameButton.png");
    button_images[0][1] = IMG_Load("../assets/newGameButtonHovered.png");
    
    //loadGameButton
    button_images[1][0] = IMG_Load("../assets/loadGameButton.png");
    button_images[1][1] = IMG_Load("../assets/loadGameButtonHovered.png");
    
    //settingsButton
    button_images[2][0] = IMG_Load("../assets/settingButton.png");
    button_images[2][1] = IMG_Load("../assets/settingButtonHovered.png");
    
    //quitGameButton
    button_images[3][0] = IMG_Load("../assets/quitButton.png");
    button_images[3][1] = IMG_Load("../assets/quitButtonHovered.png");
    
    if(button_images[0][0] == NULL || button_images[0][1] == NULL ||
       button_images[1][0] == NULL || button_images[1][1] == NULL ||
       button_images[2][0] == NULL || button_images[2][1] == NULL ||
       button_images[3][0] == NULL || button_images[3][1] == NULL){
          printf("ERROR LOADING BUTTON IMAGES: %s\n", IMG_GetError());
          return 3;
       }
    SDL_Rect button_rects[MENU_BUTTONS_COUNT];
    for(int i = 0; i < 3; i++){
    	button_rects[i] = (SDL_Rect){475 , 230 + i * 50, button_images[i][0]->w, button_images[i][0]->h};
    }
    
    //Place the Quit Button at the bottom of the menu
    button_rects[3] = (SDL_Rect){475 , 450, button_images[3][0]->w, button_images[3][0]->h};
    
 /*   SDL_Rect newGamebutton_rect = {438, 187, newGameButton_image_normal->w, newGameButton_image_hovered->h};
    SDL_Rect loadGamebutton_rect = {488, 187, loadGameButton_image_normal->w, loadGameButton_image_hovered->h};*/
    
    SDL_Event event;
    while (playing) {
    	//Blitting the background
        SDL_BlitSurface(backgroundImage, NULL, ecran, &posecranimg);
	
	//Blitting the buttons
	for(int i = 0; i < MENU_BUTTONS_COUNT; i++){
		/*SDL_BlitSurface(button_images[i][button_state[i]], NULL, ecran, &button_rects[i]);*/
		SDL_Surface *buttonImage = button_images[i][button_state[i]];
    		SDL_BlitSurface(buttonImage, NULL, ecran, &button_rects[i]);
	}
	
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                playing = 0;
                break;
            case SDL_MOUSEMOTION:
                // Check if the mouse is hovering over any button
                for(int i = 0; i < MENU_BUTTONS_COUNT; i++){
                	if (point_in_rect(event.motion.x, event.motion.y, button_rects[i])) {
                		if(button_state[i] == 0){
                    			button_state[i] = 1; // Set button state to hovered if so
                    			if(!menuHoverSoundPlayed){
                    				Mix_PlayChannel(-1,menuHoverSound,0);
                    				menuHoverSoundPlayed = 1;
                    			}
                    		}
                	}
                	else {
                    		button_state[i] = 0; // Set button state to normal else
                	}
        	}
        	break;
       	    case SDL_MOUSEBUTTONDOWN:
       	    	if(event.button.button == SDL_BUTTON_LEFT && point_in_rect(event.button.x, event.button.y, button_rects[3])){
       	    		playing = 0;
       	    	}
       	    	break;
       	    case SDL_KEYDOWN:
       	    	if(event.key.keysym.sym == SDLK_q){
       	    		playing = 0;
       	    	}
    	}
    	
        menuHoverSoundPlayed = 0;
        
    	SDL_Flip(ecran);
    }
    
    
    SDL_FreeSurface(backgroundImage);
    //Freeing all the buttonImages
    for(int i = 0; i < MENU_BUTTONS_COUNT; i++){
    	SDL_FreeSurface(button_images[i][0]);
    	SDL_FreeSurface(button_images[i][1]);
    }
    Mix_FreeMusic(backgroundMusic);
    Mix_FreeChunk(menuHoverSound);
    SDL_Quit();
    return 0;
}
