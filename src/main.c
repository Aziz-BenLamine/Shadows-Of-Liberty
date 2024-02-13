#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#define SCREEN_HEIGHT 700
#define SCREEN_WIDTH 1200

int point_in_rect(int x, int y, SDL_Rect rect) {
    return (x >= rect.x && x < rect.x + rect.w && y >= rect.y && y < rect.y + rect.h);
}

int main(int argc, char** argv) {
    SDL_Surface *ecran;
    int playing = 1;
    int button_state = 0; // 0: Normal, 1: Hovered

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
    
    //INIT BUTTONS
    SDL_Surface *button_image_normal = IMG_Load("../assets/newGameButton.png");
    SDL_Surface *button_image_hovered = IMG_Load("../assets/newGameButtonClicked.png");

    if (button_image_normal == NULL || button_image_hovered == NULL ) {
        printf("ERROR LOADING BUTTON IMAGE: %s\n", IMG_GetError());
        return 3;
    }

    SDL_Rect button_rect = {438, 187, button_image_normal->w, button_image_normal->h};

    SDL_Event event;
    while (playing) {
        SDL_BlitSurface(backgroundImage, NULL, ecran, &posecranimg);

        // Determine which button image to blit based on button state
        switch (button_state) {
            case 0:
                SDL_BlitSurface(button_image_normal, NULL, ecran, &button_rect);
                break;
            case 1:
                SDL_BlitSurface(button_image_hovered, NULL, ecran, &button_rect);
                break;
        }

        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                playing = 0;
                break;
            case SDL_MOUSEMOTION:
                // Check if the mouse is hovering over the button
                if (point_in_rect(event.motion.x, event.motion.y, button_rect)) {
                    button_state = 1; // Set button state to hovered
                } else {
                    button_state = 0; // Set button state to normal
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                // Check if the mouse click is inside the button rectangle
                if (event.button.button == SDL_BUTTON_LEFT &&
                    point_in_rect(event.button.x, event.button.y, button_rect)) {
                    button_state = 2; // Set button state to clicked
                    printf("Button clicked!\n");
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (button_state == 2) {
                    button_state = 1; // Reset button state to hovered after click
                }
                break;
        }

        SDL_Flip(ecran);
    }

    SDL_FreeSurface(backgroundImage);
    SDL_FreeSurface(button_image_normal);
    SDL_FreeSurface(button_image_hovered);
    SDL_Quit();
    return 0;
}

