#include <stdio.h>
#include <stdlib.h>
#include <SDL_rotozoom.h>
#include "tic.h"

void initialisation(tic * t)
{
    int i,j,k,h;
    for(i=0;i<9;i++)

       t-> tabsuivi[i]=0;
    t->image1=IMG_Load("background.png");
    for(h=0;h<NUM_TIME;h++){
	char filenametime[50];
	sprintf(filenametime,"time%d.png",h);
	t->time[h]=IMG_Load(filenametime);
	if(t->time[h]){
	printf("erreur loading timeimages %d:%s\n",h,IMG_GetError());
         }
       }
    
    t->posAnim.x=1000;
    t->posAnim.y=0;
    t->posAnim.w=t->time[0]->w;
    t->posAnim.h=t->time[0]->h; 
    for(j=0;j<NUM_IMAGE;j++){
	char filenameplayer[50];
        sprintf(filenameplayer,"playerImage%d.png",j);
	t->image2[j]= IMG_Load(filenameplayer);
	if(t->image2[j]==NULL){
	printf("erreur loading playerImages %d: %s\n",j,IMG_GetError());
        }
    }
     for(k=0;k<NUM_IMAGE;k++){
	char filenamecomputer[50];
        sprintf(filenamecomputer,"computerImage%d.png",k);
	t->image3[k]= IMG_Load(filenamecomputer);
	if(t->image3[k]==NULL){
	printf("erreur loading playerImages %d: %s\n",k,IMG_GetError());
        }
    }		
    t->joueur=1;
    t->tour=0;
    t->font=TTF_OpenFont("arial.ttf",40);
    t->couleur.r=255;
    t->couleur.g=255;
    t->couleur.b=255;
    t->posMSG.x=300;
    t->posMSG.y=300;
}
void affichage(tic t,SDL_Surface *ecran ) 
{
    int i,indeximage2,indeximage3,indextime;
    
         SDL_BlitSurface(t.image1,NULL,ecran,NULL);
         for(indextime=0;indextime<NUM_TIME;indextime++){
		SDL_BlitSurface(t.time[indextime],NULL,ecran,&t.posAnim);
                SDL_Flip(ecran);
                }
            indextime=0;

    for(i=0;i<9;i++)
   {
		t.pos.x=185*(i%3); //calculer la position d'affichgage de chaque petit carreau
		t.pos.y=177*(i/3);
                printf("valeur de tabsuiv[%d]=%d dans fct ",i,t.tabsuivi[i]);
        	switch(t.tabsuivi[i])// selon 
        	{
            		case -1:
                                for(indeximage2=0;indeximage2<NUM_IMAGE;indeximage2++){
                		SDL_BlitSurface(t.image2[indeximage2],NULL,ecran,&t.pos);
                                SDL_Flip(ecran);

                                }
				indeximage2=0;
                                
            		break;
            		case 1: 
                                for(indeximage3=0;indeximage3<NUM_IMAGE;indeximage3++){
                		SDL_BlitSurface(t.image3[indeximage3],NULL,ecran,&t.pos);
                                SDL_Flip(ecran);
                                }
                                indeximage3=0;
                               
            		break;
        	}

	
    }
    
}



int atilganer(int tabsuivi[])
{
//remplir cette matrice avec les combinaisons de succees
    int lignes_gagnantes[8][3]={{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i=0;i<8;++i)
        if(tabsuivi[lignes_gagnantes[i][0]]!=0&&
           tabsuivi[lignes_gagnantes[i][0]]==tabsuivi[lignes_gagnantes[i][1]]&&
           tabsuivi[lignes_gagnantes[i][0]]==tabsuivi[lignes_gagnantes[i][2]])
                return tabsuivi[lignes_gagnantes[i][2]];
    return 0;
}



void Resultat(tic t, SDL_Surface *ecran) {
    int resultat = atilganer(t.tabsuivi);
    char message[50];
    if (resultat == 1) {
        strcpy(message, "defaite");
        for (int angle = 0; angle <= 360; angle += 10) { 
            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0)); 
            afficherTexteRotZoom(t,ecran, message, angle, 2.5, 600, 350); 
            SDL_Flip(ecran); 
            SDL_Delay(30); 
        }
    } else if (resultat == -1) {
        strcpy(message, "victoire");
        for (int angle = 0; angle <= 360; angle += 10) { 
            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0)); 
            afficherTexteRotZoom(t,ecran,message, angle, 2.5, 600, 350); 
            SDL_Flip(ecran); 
            SDL_Delay(30); 
        }
    } else {
        strcpy(message, "Match null !");
        for (int angle = 0; angle <= 360; angle += 10) {
            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0)); 
            afficherTexteRotZoom(t,ecran, message, angle, 2.5, 600, 350); 
            SDL_Flip(ecran);
            SDL_Delay(30); 
        }
    }
}


void liberationmemoire(tic *t)
{
    int indeximage2,indeximage3;
    SDL_FreeSurface(t->image1);
    for(indeximage2=0;indeximage2<NUM_IMAGE;indeximage2++){
    SDL_FreeSurface(t->image2[indeximage2]);
    }
    for(indeximage3=0;indeximage3<NUM_IMAGE;indeximage3++){
    SDL_FreeSurface(t->image3[indeximage3]);
    }
}
int minimax(int tabsuivi[],int joueur)
{
    int gagnant=atilganer(tabsuivi);
    if(gagnant!=0)
        return gagnant*joueur;
    int coup=-1;
    int score=-2;
    int i;
    for(i=0;i<9;++i)
    {
        if(tabsuivi[i]==0)
        {
            tabsuivi[i]=joueur;
            int mmscore=-minimax(tabsuivi,joueur*-1);
            if(mmscore>score)
            {
                score=mmscore;
                coup=i;
            }
            tabsuivi[i]=0;
        }
    }
    if(coup==-1)
        return 0;
    return score;
}
///////////////////////////////////////////////////////////////
void calcul_coup(int tabsuivi[])
{
    int coup=-1;
    int score=-2;
    int i;
    for(i=0;i<9;++i)
    {
        if(tabsuivi[i]==0)
        {
            tabsuivi[i]=1;
            int mmscore=-minimax(tabsuivi,-1);
            tabsuivi[i]=0;
            if(mmscore>score)
            {
                score=mmscore;
                coup=i;
            }
        }
    }
    tabsuivi[coup]=1;
}
/////////////////////////////////////////////////////////////////////////
////////
void afficherTexteRotZoom(tic t,SDL_Surface *ecran, char *texte, double angle, double zoom, int x, int y) {
    
    SDL_Surface *surfaceTexte = TTF_RenderText_Blended(t.font, texte,t.couleur);
    if (surfaceTexte == NULL) {
        printf("Erreur lors du rendu du texte : %s\n", TTF_GetError());
        return;
    }
    SDL_Surface *surfaceRotZoom = rotozoomSurface(surfaceTexte, angle, zoom, 1);
    SDL_FreeSurface(surfaceTexte);
    if (surfaceRotZoom == NULL) {
        printf("Erreur lors de la rotation et du zoom du texte : %s\n", SDL_GetError());
        return;
    }
    
    t.posMSG.x = x;
    t.posMSG.y = y;
    SDL_BlitSurface(surfaceRotZoom, NULL, ecran, &t.posMSG);
    SDL_FreeSurface(surfaceRotZoom);
}
