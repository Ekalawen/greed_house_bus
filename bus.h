

#ifndef BUS_H
#define BUS_H

typedef struct
{
	Polygone *poly ; // la taille et la position du bus
	SDL_Surface *image ; // l'image du bus
	SDL_Surface *image_originelle ; // l'image à partir de laquelle on va effectuer les rotations
	double v_lin, v_rot ; // la vitesse linéaire et la vitesse de rotation
	Pos *pos ; // la position réel du bus (pas celle d'affichage) 
	// /!\ la position est la position du CENTRE du bus !! (w et h sont inchangés)
	double rot ; // la rotation actuelle du bus (0° = vers la droite)
	// /!\ le repère est dans le sens TRIGONOMÉTRIQUE !!
	int nb_passagers ; // permet de tenir le compte du nombre de passagers récupérés 
	SDL_Surface *image_passagers ; // charge une mini image du passager !
} Bus ;

/* Crée un bus avec une image nomImageBus à une position initiale (x_ini, y_ini)
 * La taille d'un bus est fixe. */
Bus* creerBus(char *nomImageBus, double x_ini, double y_ini) ;

/* Deplacer un bus
 * La rotation est en gradiant. 
 * Renvoie true si le déplacement s'est effectué, false sinon */
int deplacerBus(Map *m, Bus* bus, double avancee, double rotation) ;

/* Fait effectuer une avancée dans le sens de rotation du bus.
 * Renvoie true si l'avancée s'est effectuée, false sinon */
int avancerBus(Map *m, Bus *bus, double avancee) ;

/* Fait effectuer une rotation dans le sens trigonométrique au bus.
 * La rotation s'effectue par rapport au point le plus à l'arrière au centre.
 * La rotation est en gradiant.
 * Renvoie true si la rotation s'est effectuée, false sinon. */
int rotationBus(Map *m, Bus *bus, double rotation) ;

/* Affiche un bus à sa position actuelle sur la carte */
void afficherBus(SDL_Surface *ecran, Map *m, Bus *bus) ;

/* Met à jour le point de vue de la map */
void majStandpointMap(Map *m, Bus *bus) ;



#endif

