#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#define SCREEN_HEIGHT 700
#define SCREEN_WIDTH 1200

#define MENU_BUTTONS_COUNT 4

int point_in_rect(int x, int y, SDL_Rect rect) {
    return (x >= rect.x && x < rect.x + rect.w && y >= rect.y && y < rect.y + rect.h);
}

int main(int argc, char** argv) {
    SDL_Surface *ecran;
    int playing = 1;
    //Initilazing the Menu buttons state to 0:(Normal)
    int button_state[MENU_BUTTONS_COUNT] = {0, 0, 0, 0}; // 0: Normal, 1: Hovered

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Echec d'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }

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
    for(int i = 0; i < 4; i++){
    	button_rects[i] = (SDL_Rect){475 , 230 + i * 50, button_images[i][0]->w, button_images[i][0]->h};
    }
    
 /*   SDL_Rect newGamebutton_rect = {438, 187, newGameButton_image_normal->w, newGameButton_image_hovered->h};
    SDL_Rect loadGamebutton_rect = {488, 187, loadGameButton_image_normal->w, loadGameButton_image_hovered->h};*/
    
    SDL_Event event;
    while (playing) {
    	//Blitting the background
        SDL_BlitSurface(backgroundImage, NULL, ecran, &posecranimg);
	
	//Blitting the buttons
	for(int i = 0; i < MENU_BUTTONS_COUNT; i++){
		SDL_BlitSurface(button_images[i][button_state[i]], NULL, ecran, &button_rects[i]);
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
                    		button_state[i] = 1; // Set button state to hovered if so
                	} 
                	else {
                    		button_state[i] = 0; // Set button state to normal else
                	}
        	}
        	break;
    	}
    	SDL_Flip(ecran);
    }
    
    
    SDL_FreeSurface(backgroundImage);
    //Freeing all the buttonImages
    for(int i = 0; i < MENU_BUTTONS_COUNT; i++){
    	SDL_FreeSurface(button_images[i][0]);
    	SDL_FreeSurface(button_images[i][1]);
    }
    SDL_Quit();
    return 0;
}
