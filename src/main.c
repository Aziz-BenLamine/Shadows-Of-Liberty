#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h> 
#include "bouton.h"
#include "background.h"
#include "player.h"
#include "entite.h"
#include"minimap.h"
#define SCREEN_HEIGHT 700
#define SCREEN_WIDTH 1600
#define FULL_SCREEN_HEIGHT 1080
#define FULL_SCREEN_WIDTH 1920
#define MENU_BUTTONS_COUNT 4
#define SETTING_BUTTONS_COUNT 5
#define NUM_IMAGES 7

int main(int argc, char** argv) {
    SDL_Surface *ecran;
    
    //MENU VARIABLES
    minimap m;
    int playing = 1;
    int buttonClicked = 0;
    int keysClicked = 0;
    int menuHoverSoundPlayed = 0;
    int delay = 0;
    int selectedButtonIndex = 0;
    int previousButtonIndex = 0;
    int screenState = 0;
    Entity e;
    Entity b;
    int collennemi;
    int collbonus;
    int touchbonus=1;
    int dirr;
    
    //MAIN LOOP VARIABLES
    Uint32 dt, t_prev;
    Uint32 startTime, currentTime, minutes,seconds;
    Personne player;
    int xINIT = 0;
    int yINIT = 0;
    int x0 = 0, y0 = 0;
    int jumpDone = 0;
    int timeIncrement = 50;
    int game = 0;
    int score = 0;
    int jumpAnimation = 0;
    
    init(&player, 0);
    //Texte
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("Ironmonger Black Regular.otf", 20);
    TTF_Font *font2 = TTF_OpenFont("Ironmonger Black Regular.otf", 24);
    if (font == NULL) {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
        return 1;
    }
    SDL_Color textColor = {255, 255, 255};

    //Animation
    SDL_Surface *backgroundImages[NUM_IMAGES];
    int currentImageIndex = 0;
    int currentImageIndex1 = 0;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Echec d'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) == -1) {
        printf("Audio Error:%s", Mix_GetError());
    }

    backgroundSound BS;
    InitBackgroundSound(&BS);

    Mix_Chunk *menuHoverSound;
    menuHoverSound = Mix_LoadWAV("../audio/menuHoverSound.wav");
    if (menuHoverSound == NULL) {
        fprintf(stderr, "Failed to load menu hover sound: %s\n", Mix_GetError());
        return 1;
    }
    Mix_VolumeChunk(menuHoverSound, MIX_MAX_VOLUME / 2);

    ecran = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_HWACCEL);
    if (ecran == NULL) {
        fprintf(stderr, "ERROR CREATING THE WINDOW %d*%d: %s.\n", SCREEN_HEIGHT, SCREEN_WIDTH, SDL_GetError());
        return 1;
    }


    Background background;



    InitBackground(&background);

    button menuButtons[MENU_BUTTONS_COUNT];
    if (InitBouton(menuButtons, SCREEN_WIDTH, SCREEN_HEIGHT)!= 0) {
        printf("ERROR INITIALIZING MENU BUTTONS.\n");
        return 3;
    }

    button settingButtons[SETTING_BUTTONS_COUNT];
    if (InitSettingsButtons(settingButtons) != 0) {
        printf("ERROR INITIALIZING MENU BUTTONS \n");
        return 4;
    }

    //Load animation
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
    
    
    
    //GAME INTRO
    displayImageWithFade("../assets/intro/gameStudioIntro.png", ecran); 	
    displayImageWithFade("../assets/intro/gameIntro.png", ecran); 

	
	InitEnnemi(&e);
	Initbonus(&b);
	initmap(&m);
    
    int lvl = 2;
    int dir,pl;
    int pas = 10;
    SDL_Surface *surfM = IMG_Load("mask.png");
    
    SDL_Event event;
    while (playing) {
    	
    	
        AfficherBackground(background, ecran,lvl);
        //SDL_Delay(1);
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                playing = 0;
                break;
            case SDL_KEYDOWN:
            
            	if(event.key.keysym.sym == SDLK_TAB){
            		if(screenState == 0){
           			toggleFullScreen(menuButtons);
           			screenState = 1;
           		}else if(screenState == 1){
           			toggleWindowedScreen(menuButtons);
           			screenState = 0;
           		}
            	}
            	if (event.key.keysym.sym == SDLK_ESCAPE) {
            		/*menuButtons[selectedButtonIndex].actif = 0;
                       	menuButtons[previousButtonIndex].actif = 0;*/
            		background.niveau = 0;
        		}
        }

        if (background.niveau == 0) {
            background.camera.y = 0;
            background.camera.x = 0;
            AfficherBouton(menuButtons, ecran, 0);
            SDL_BlitSurface(backgroundImages[currentImageIndex], NULL, ecran, &posAnim);
            renderText(ecran, font, "Ares Forge Games", textColor, 1300, 660);
            switch (event.type) {
                case SDL_MOUSEMOTION:
                    for (int i = 0; i < MENU_BUTTONS_COUNT; i++) {
                        if (point_in_rect(event.motion.x, event.motion.y, menuButtons[i].button_rect)) {
                            if (menuButtons[i].actif == 0) {
                                menuButtons[i].actif = 1;
                                if (!menuHoverSoundPlayed) {
                                    Mix_PlayChannel(1, menuHoverSound, 0);
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
                    if (!keysClicked) {
                        if (event.key.keysym.sym == SDLK_DOWN) {
                            previousButtonIndex = selectedButtonIndex;
                            selectedButtonIndex = (selectedButtonIndex + 1) % MENU_BUTTONS_COUNT;
                            Mix_PlayChannel(1, menuHoverSound, 0);
                            menuButtons[selectedButtonIndex].actif = 1;
                            menuButtons[previousButtonIndex].actif = 0;
                        } else if (event.key.keysym.sym == SDLK_UP) {
                            previousButtonIndex = selectedButtonIndex;
                            selectedButtonIndex = (selectedButtonIndex - 1 + MENU_BUTTONS_COUNT) % MENU_BUTTONS_COUNT;
                            Mix_PlayChannel(1, menuHoverSound, 0);
                            menuButtons[selectedButtonIndex].actif = 1;
                            menuButtons[previousButtonIndex].actif = 0;
                        } else if (event.key.keysym.sym == SDLK_RETURN) {
                            menuButtons[selectedButtonIndex].actif = 0;
                            menuButtons[previousButtonIndex].actif = 0;
                            switch (selectedButtonIndex) {
                                case 0:
                                    background.niveau = 2;
                                    selectedButtonIndex = 0;
                                    previousButtonIndex = 0;
                                    break;
                                case 2:
                                    background.niveau = 1;
                                    selectedButtonIndex = 0;
                                    previousButtonIndex = 0;
                                    break;
                                case 3:
                                    playing = 0;
                                    break;
                            }
                        }
                        keysClicked = 1;
                    }
                    //SHORTCUTS FOR THE MAIN MENU
                    
        		
        	    
        	    if (event.key.keysym.sym == SDLK_n) {
        	    	menuButtons[selectedButtonIndex].actif = 0;
                       	menuButtons[previousButtonIndex].actif = 0;
            		background.niveau = 2;
        		}
        		
        	    if (event.key.keysym.sym == SDLK_s) {
        	    	menuButtons[selectedButtonIndex].actif = 0;
                       	menuButtons[previousButtonIndex].actif = 0;
            		background.niveau = 1;
        		}
        		
        		
                    break;
                case SDL_KEYUP:
                    keysClicked = 0;
                    break;
                    
            }
        } else if (background.niveau == 1) {
            background.camera.y = 0;
            background.camera.x = 0;
            AfficherBouton(settingButtons, ecran, 1);
            SDL_Delay(50);
            AfficherSoundSlider(&BS, ecran);
            renderText(ecran, font, "Ares Forge Games", textColor, 1300, 660);
            //SDL_BlitSurface(backgroundImages[currentImageIndex], NULL, ecran, &posAnim);
            switch (event.type) {
                case SDL_MOUSEMOTION:
                    for (int i = 0; i < SETTING_BUTTONS_COUNT; i++) {
                        if (point_in_rect(event.motion.x, event.motion.y, settingButtons[i].button_rect)) {
                            if (settingButtons[i].actif == 0) {
                                settingButtons[i].actif = 1;
                                if (!menuHoverSoundPlayed) {
                                    Mix_PlayChannel(1, menuHoverSound, 0);
                                    menuHoverSoundPlayed = 1;
                                }
                            }
                        } else {
                            settingButtons[i].actif = 0;
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        if (point_in_rect(event.button.x, event.button.y, settingButtons[2].button_rect)) {
                            background.niveau = 0;
                        } else if (point_in_rect(event.button.x, event.button.y, settingButtons[0].button_rect)) {
                            toggleFullScreen(menuButtons);
                        } else if (point_in_rect(event.button.x, event.button.y, settingButtons[1].button_rect)) {
                            toggleWindowedScreen(menuButtons);
                        }
                        if (!buttonClicked) {
                            if (point_in_rect(event.button.x, event.button.y, settingButtons[3].button_rect) && BS.soundLevel != 0) {
                                changeBackgroundSoundLevel(&BS, 0);
                            } else if (point_in_rect(event.button.x, event.button.y, settingButtons[4].button_rect) && BS.soundLevel != 4) {
                                changeBackgroundSoundLevel(&BS, 1);
                            }
                            buttonClicked = 1;
                            delay = 0;
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    if (!keysClicked) {
                        if (event.key.keysym.sym == SDLK_DOWN) {
                            previousButtonIndex = selectedButtonIndex;
                            selectedButtonIndex = (selectedButtonIndex + 1) % SETTING_BUTTONS_COUNT;
                            Mix_PlayChannel(1, menuHoverSound, 0);
                            settingButtons[selectedButtonIndex].actif = 1;
                            settingButtons[previousButtonIndex].actif = 0;
                        } else if (event.key.keysym.sym == SDLK_UP) {
                            previousButtonIndex = selectedButtonIndex;
                            selectedButtonIndex = (selectedButtonIndex - 1 + SETTING_BUTTONS_COUNT) % SETTING_BUTTONS_COUNT;
                            Mix_PlayChannel(1, menuHoverSound, 0);
                            settingButtons[selectedButtonIndex].actif = 1;
                            settingButtons[previousButtonIndex].actif = 0;
                        } else if (event.key.keysym.sym == SDLK_RETURN) {
                            settingButtons[selectedButtonIndex].actif = 0;
                            settingButtons[previousButtonIndex].actif = 0;
                            switch (selectedButtonIndex) {
                                case 0:
                                    toggleFullScreen(menuButtons);
                                    break;
                                case 1:
                                    toggleWindowedScreen(menuButtons);
                                    break;
                                case 2:
                                    background.niveau = 0;
                                    break;
                            }
                            keysClicked = 1;
                        }
                    }
                    break;
                case SDL_KEYUP:
                    keysClicked = 0;
                    break;
            }
        }
        //MAIN GAME
        else if (background.niveau == 2) {
        printf("camera.x: %d\n",background.camera.x);
        animerBackground(ecran,currentImageIndex1);
	currentImageIndex1 = (currentImageIndex1 + 1) % NUM_IMAGES;
        //printf("JUmpanimation=%d\n",jumpAnimation);
        //printf("player.dir = %d\n",player.dir);
        background.camera.y = 100;
        
        //Collision Check
        for (int i = 0; i < 4; i++) {
    	    //player.tab[i] = 0;
	    printf("tab[%d]=%d \n",i,player.tab[i]);
       }
       
        //START , TRACK AND DISPLAY TIMER
        if(game != 1){
        	startTime = SDL_GetTicks();
        	game = 1;
        }
        currentTime = (SDL_GetTicks() - startTime)/1000;
	minutes = currentTime / 60;
	seconds = currentTime % 60;
	
        //printf("\nCurrent time: %d",currentTime);
        char timerText[100];
	sprintf(timerText, "Timer: %02d:%02d", minutes, seconds);
        renderText(ecran, font2, timerText, textColor, 700, 25);
        
        //DISPLAY SCORE
        score = 1000 - ((3 -player.vies) * 100) - currentTime;  //FORMULE SCORE
        if(score <= 0){
        	score = 0;
        }
        char scoreText[100];
        sprintf(scoreText, "Score: %d", score);
        renderText(ecran, font2, scoreText, textColor, 700, 75);
        
        //DISPLAY HEALTH
        SDL_BlitSurface(player.healthImage[player.vies], NULL, ecran, &(player.healthRect));
    	// PLAYER MOVEMENT 
	    switch (event.type) {
		case SDL_KEYDOWN:
		    if (event.key.keysym.sym == SDLK_LSHIFT) {
		        player.acceleration += 0.005;
		        dt += timeIncrement;
		        animerPerso(&player);
		        movePerso(&player, dt);
		    } else if (event.key.keysym.sym == SDLK_LCTRL) {
		        player.acceleration -= 0.01;
		        dt += timeIncrement;
		        animerPerso(&player);
		        movePerso(&player, dt);
			
		    }

		    player.acceleration -= 0.001;

		    // AVOID NEGATIVE ACCELERATION
		    if (player.acceleration < 0) {
		        player.acceleration = 0;
		    }

		    // HANDLE MOVEMENTS 
		    if (event.key.keysym.sym == SDLK_RIGHT) {
		    	//MOUVEMENT A DROITE
		    	dt += timeIncrement;
		        player.dir = 0;
		        if(player.tab[0] != 1){
				animerPerso(&player);
				movePerso(&player, dt);
				pl = 1;
				dir = 0;
				scrolling(&background,pas,dir,pl);
				if(background.camera.x < 1600){
					b.pos.x -= pas;
					e.pos.x -= pas;
				}
			}
			//e.pos.x += pas;
		    } else if (event.key.keysym.sym == SDLK_LEFT) {
		    	//MOUVEMENT A GAUCHE
		    	dt += timeIncrement;
		        player.dir = 1;
		        if(player.tab[1] != 1){
		        	animerPerso(&player);
		        	movePerso(&player, dt);
		        	pl = 1;
				dir = 1;
				scrolling(&background,pas,dir,pl);
				
				if(background.camera.x > 0){
					
					b.pos.x += pas;
					e.pos.x += pas;
				}	
			}
			//e.pos.x -= pas;
		    }else if (event.key.keysym.sym == SDLK_d) {
			dir = 0;
			pl = 2;
			scrolling(&background,pas,dir,pl);

		    }else if (event.key.keysym.sym == SDLK_q) {
			dir = 1;
			pl = 2;
			scrolling(&background,pas,dir,pl);

		    } else if(event.key.keysym.sym == SDLK_UP){
			if(player.dir == 0){
		    		player.dir = 2;
		    		player.num = 0;
		    	}else if(player.dir == 1){
		    		player.dir = 3;
		    		player.num = 0;
		    	}
			if(jumpAnimation < playerImagerows){
		    		animerPerso(&player);
		    		jumpAnimation++;
		    		//printf("player.num=%d, player.dir=%d\n",player.num,player.dir);
		    	}
		    	//SAUT HORIZONTAL
		    	
		    	if(!jumpDone){
		    	
				  	if(player.up == 0){
				  		yINIT = player.rect.y;
				  	}
				  	//printf("yINIT = %d| y = %d | player.up = %d\n",yINIT, player.rect.y ,player.up);
				  	printf("player.up = %d |",player.up);
				    	dt += timeIncrement;
				  	player.up = 1;
				  	saut(&player, dt, yINIT);
				  		if(player.up == 0 || player.tab[2] == 1){
				  			jumpDone = 1;
				  	}
					}
		    	
		    
		    
		    }
		    //SAUT PARABOLIQUE
		    else if(event.key.keysym.sym ==  SDLK_SPACE){
		    	if(player.dir == 0){
		    		player.dir = 2;
		    		player.num = 0;
		    	}else if(player.dir == 1){
		    		player.dir = 3;
		    		player.num = 0;
		    	}
			if(jumpAnimation < playerImagerows){
		    		animerPerso(&player);
		    		jumpAnimation++;
		    		//printf("player.num=%d, player.dir=%d\n",player.num,player.dir);
		    	}
			sautParabolique(&player, &jumpDone, &x0, &y0, &xINIT, &yINIT);
			
		    }
		    break;
		    case SDL_KEYUP:
		    	if(event.key.keysym.sym ==  SDLK_SPACE || event.key.keysym.sym == SDLK_UP){
		    		jumpDone = 0;
		    		if(player.dir == 2){
		    			player.dir = 0;
		    		}else if(player.dir == 3){
		    			player.dir = 1;
		    		}

		    	}
		    	dt = 0;
		    	jumpAnimation = 0;
					break;
		    
	    }
	    //GRAVITE
	  	if (player.rect.y < 510 && player.tab[3] != 1) {
		   player.rect.y += 8.5;
	    
	    	}
	    	
	    afficherPerso(player, ecran);
	    afficherminimap(m,ecran);
            MAJMinimap(player.rect, &m, background.camera, 20);
            animerMinimap(&m);
            
            collisionPP(&player,surfM,background);
            background.mask.positionfromimage =   background.camera;
	//entitesecondaire

	/*
	AfficherEnnemi(e,ecran);
	move(&e);
	animerEntity(&e);
	collennemi=collisionBB(e,player.rect);
	if (collennemi==1){
	player.rect.x=200;
	player.rect.y=510;
	player.dir=0;
	player.vies--;
	}*/
	//e.pos.x += background.camera.x;
	collbonus=collisionTri(player,b.pos);
	if (touchbonus==1){
		Afficherbonus(b,ecran);
	}
	if (collbonus==1){
		touchbonus=0;
	}

	/*if(e.pos.x-(player.rect.x+player.rect.w)<20){
		dirr=e.direction;
		e.direction=2;

		

	}*/




	}
	
	if(player.vies < 0){
		player.vies = 0;
	}

        if (delay > 50) {
            buttonClicked = 0;
        }
        delay++;

        AfficherBoutonActif(menuButtons, ecran);
        menuHoverSoundPlayed = 0;
        currentImageIndex = (currentImageIndex + 1) % NUM_IMAGES;

        //TEXT BLIT
        SDL_Flip(ecran);
        t_prev = (SDL_GetTicks() - t_prev)/4;
        //printf("t_prev = %d |dt = %d\n",t_prev,dt);
        
    }

    for (int i = 0; i < NUM_IMAGES; i++) {
        SDL_FreeSurface(backgroundImages[i]);
    }
    Liberer(&m);
    freePlayer(&player);
    FreeBackground(&background);
    FreeBouton(menuButtons, MENU_BUTTONS_COUNT);
    FreeBouton(settingButtons, SETTING_BUTTONS_COUNT);
    Mix_FreeChunk(menuHoverSound);
    Mix_FreeMusic(BS.music);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
