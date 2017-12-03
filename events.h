

#ifndef EVENTS_H
#define EVENTS_H

	// defines d'events
    #define ATTENTE                 250
    #define REPETITION              75

typedef struct
{
	char key[SDLK_LAST]; // touches du clavier
	int cooldownTemps[SDLK_LAST];
	char cooldownActive[SDLK_LAST];
	char quit; // input pour tuer le programme
	int mouseX, mouseY; // position du curseur
	//garde en tête le denier vecteur de déplacement de la souris
	int mouseRelX, mouseRelY; // dernier déplacement du curseur
	char button[8]; // boutons de la souris
}Input;

void initInput (Input *in) ;
void updateEvents (Input *in) ;
void repetitionDeTouche(Input *in) ;

#endif 
