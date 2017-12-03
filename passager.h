

#ifndef PASSAGER_H
#define PASSAGER_H

typedef struct
{
	int nb ; // le nombre de passagers
	int nb_max ; // le nombre maximum de passagers
	SDL_Surface **image ; // leurs images
	Pos **pos ; // leurs positions
	Polygone **poly ; // leurs polygones
	double *rotation ; // leurs rotation actuelles
	double *vitesse ; // leurs vitesses actuelles
} Passagers ;

/* Initialiser une liste vide de passagers
 * Les passagers sont immobiles, où peuvent avoir des vitesses variables qui
 * changent lorsqu'ils touchent des murs.
 * Les passagers peuvent être "ramassés" par les bus pour gagner des points */
Passagers* initPassagers() ;

/* Ajoute un passager à la liste.
 * Lorsqu'un passager est ajouté, il lui est automatiquement adjoint une image,
 * une position sur la map dans un espace vide, une rotation et une vitesse
 * unique. */
void ajouterPassager(Passagers *psg, Map *m, Bus *bus) ;

/* Déplacer les passagers selon leurs mouvements actuels. 
 * Si un passager entre en collision avec un mur, alors il change de mouvement
 */
void deplacerPassagers(Passagers *psg, Map *m, Bus *bus) ;

/* Fait avancer le passager numéro num dans sa direction de rotation si il
 * n'entre pas en collision avec la map, le bus, ou les autres passagers.
 * Renvoie true si le déplacement à eus lieu, false sinon */
int avancerPassager(Map *m, Bus *bus, Passagers *psg, int num, double avancee) ;

/* Fait récupérer des passagers à un bus.
 * Si un bus est rentre en collision avec un passager, alors il le récupère si
 * il en a la capacité. Si un bus n'a plus de capacité, le passager est perdu !
 * Pour le moment on fait ça, après on ajoutera la collision */
void recupererPassagersBus(Bus *bus, Passagers *psg) ;

/* Affiche les passagers à leurs positions actuelles sur la carte */
void afficherPassagers(SDL_Surface *ecran, Map *m, Passagers *psg) ;

/* Permet de ramener les passagers aux checkpoints */
void ramenerPassagers(Map *m, Bus *bus) ;


#endif


