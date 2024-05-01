#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h> 
#include <time.h>
#include "enigme.h"

enigme generer(char *nomfich)
{
    enigme e;
    int taille = 0;
    FILE *fichier = fopen(nomfich,"r");
    if (fichier == NULL)
    {
        printf("erreur d'acces aux fichier\n");

    }
    else
    {
        while (fscanf(fichier, "%s %s %s %s %d", e.quest, e.rep1, e.rep2, e.rep3, &e.bonrep) != EOF)
        {
            taille++;
        }
        srand(time(NULL));

        e.numQuestSelect = (rand() % taille) + 1;

        fclose(fichier);

        fichier = fopen(nomfich,"r");

        if (fichier == NULL)
        {
            printf("erreur d'acces aux fichier\n");
            
        }

        else
        {
            for (int i = 1; i <= e.numQuestSelect; ++i)
            {
                // Lire la question et les réponses générées aléatoirement
                fscanf(fichier, "%s %s %s %s %d", e.quest, e.rep1, e.rep2, e.rep3, &e.bonrep);
            }
            fclose(fichier); 
        }
    }
    return e;
}

void afficherEnigme(enigme e, SDL_Surface *ecran) {

    SDL_Surface * background;
    SDL_Rect posecranimg;
    TTF_Font* font;
    TTF_Init();
     
    e.surface_question = NULL;
    e.surface_reponse1 = NULL;
    e.surface_reponse2 = NULL;
    e.surface_reponse3 = NULL;

    font = TTF_OpenFont("arial.ttf", 25);
    if (font == NULL) {
        printf("Erreur lors du chargement de la police : %s\n", TTF_GetError());
      
        return;
    }
    
    // Charger l'image de fond de l'énigme
    background = IMG_Load("img.png");
    if (background == NULL) {
        printf("Erreur lors du chargement de l'image de fond : %s\n", SDL_GetError());
        return;
    }
    
    //Position de l'image de l'engime
    posecranimg.x = 0;
    posecranimg.y = 0;
    posecranimg.w = 735;
    posecranimg.h = 662;	
    
    // Créer les surfaces de texte pour la question et les réponses
    SDL_Color color = {255, 255, 255};
    e.surface_question = TTF_RenderText_Solid(font, e.quest, color);
    e.surface_reponse1 = TTF_RenderText_Solid(font, e.rep1, color);
    e.surface_reponse2 = TTF_RenderText_Solid(font, e.rep2, color);
    e.surface_reponse3 = TTF_RenderText_Solid(font, e.rep3, color);
    
    int largeur_ecran = ecran->w;
    int hauteur_ecran = ecran->h;
    
    // Calcul de la position verticale centrale pour la question et les réponses
    int centre_vertical = ecran->h / 2;

    // Positionnement de la question au centre horizontalement
    e.pos_quest.x = (ecran->w - e.surface_question->w) / 2;
    e.pos_quest.y = centre_vertical - e.surface_question->h * 2; // Ajustement de la position   verticale

    // Positionnement des réponses centrées horizontalement sous la question
    int espacement_reponses = ecran->h / 10; // Marge entre la question et les réponses
    e.pos_rep1.x = (ecran->w - e.surface_reponse1->w) / 2;
    e.pos_rep1.y = e.pos_quest.y + e.surface_question->h + espacement_reponses;

    e.pos_rep2.x = (ecran->w - e.surface_reponse2->w) / 2;
    e.pos_rep2.y = e.pos_rep1.y + e.surface_reponse1->h + espacement_reponses;

    e.pos_rep3.x = (ecran->w - e.surface_reponse3->w) / 2;
    e.pos_rep3.y = e.pos_rep2.y + e.surface_reponse2->h + espacement_reponses;
    

    SDL_BlitSurface(background, NULL, ecran, &posecranimg);
    SDL_BlitSurface(e.surface_question, NULL, ecran, &e.pos_quest);
    SDL_BlitSurface(e.surface_reponse1, NULL, ecran, &e.pos_rep1);
    SDL_BlitSurface(e.surface_reponse2, NULL, ecran, &e.pos_rep2);
    SDL_BlitSurface(e.surface_reponse3, NULL, ecran, &e.pos_rep3);
    
    SDL_Flip(ecran);
    
    SDL_Delay(2000); //un délai de 2 secondes pour afficher l'énigme
    
    // Libération de la mémoire
    
    SDL_FreeSurface(background);

    TTF_CloseFont(font);

    TTF_Quit();
   
}



void liberer(enigme e)
{
    SDL_FreeSurface(e.surface_question);
    SDL_FreeSurface(e.surface_reponse1);
    SDL_FreeSurface(e.surface_reponse2);
    SDL_FreeSurface(e.surface_reponse3);
}


