
#ifndef MAP_H
#define MAP_H

typedef struct
{
	int nb_blocs ; // le nombre de blocs
	int *tailles_blocs ; // leurs tailles respectives
	Point ***blocs ; // les blocs comme ensemble de points
} Blocs ;

typedef struct
{
	double w, h ; // la largeur et la hauteur de la carte
	Pos *standpoint ;
	SDL_Surface *fond ; // le fond d'écran à afficher, soit le fond d'écran
	int nb_poly ; // le nombre de polygones
	Polygone **poly ; // les différents polygones de la carte
	SDL_Surface **surf_poly ; // les surfaces correspondants aux polygones
	Polygone *checkpoint[2] ; // les 2 checkpoints
	SDL_Surface *image_checkpoint ; // l'image des checkpoints
	int passagers_recuperes ; // le nombre de passagers qu'a rammasse le joueur
	Polygone *ligneL1 ; // la ligne L1
	SDL_Surface *image_ligneL1 ; // l'image de la ligne L1
	s_texte *texte_temps_jeu ; // le texte qui donne le temps restant
	s_texte *texte_convertit ; // le texte qui indique le nombre de passagers attrapés !
} Map ;

/* Lit les blocs dans un fichier blocs.txt et les initialises
 * Il s'agit d'une procédure, donc comme on veut pouvoir modifier les arguments,
 * on rajoute un "pointeur en plus" soit une étoile à chaque fois.
 * /!\ Lors de l'écriture du fichier, veuiller à incrémenter le nombre total de
 * polygones.
 * /!\ Lors de l'écriture du fichier, veuiller placer le point le plus en haut à
 * gauche en premier et à les ajouter dans le sens des aiguilles d'une montre.
 */
Blocs* initBlocs() ;

/* Crée une map de taille taille_x/taille_y, avec un fond, et nb_poly polygones */
Map* creerMap(char *nom_fond_ecran,
			  int nb_poly,
			  int *tailles_polys, // un tableau de la taille des polygones
			  Point ***sommets_polygones, // un tableau de liste de pointeurs sur sommets
			  SDL_Surface *ecran) ; // l'écran !

/* Afficher une map */
void afficherMap(SDL_Surface *ecran, Map *m) ;


#endif

