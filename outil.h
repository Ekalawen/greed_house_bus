
#ifndef OUTIL_H
#define OUTIL_H

	#define EPSILON 0.000001

typedef enum {false = 0, true = 1} bool ;

typedef struct
{
	double x, y, w, h ;
} Pos ;

typedef struct
{
	SDL_Surface *surface;//la surface à blitter
	TTF_Font *police;
	int taille;//taille de la police lors de ttf_openfont
	SDL_Color couleur;
	Pos pos;//la taille et l'emplacement
	char *chaine; //ce que l'on écrit
	int n; //longueur de la chaine
	int curseur; //emplacement du curseur d'écriture
}s_texte;

/* Renvoie true si les deux floattants sont EPSILON proches */
bool egalDouble(double a, double b) ;

/* Renvoie la valeur absolue */
double absd(double a) ;

/* Renvoie le signe
 * 1 si positif, -1 si négatif */
double signe(double a) ;

/* Renvoie le max de deux double */
double max(double a, double b) ;

/* Renvoie le min de deux double */
double min(double a, double b) ;

/* Renvoie le max d'un tableau de double de taille n 
 * n > 0 */
double maxt(double *t, int n) ;

/* Renvoie le min d'un tableau de double de taille n 
 * n > 0 */
double mint(double *t, int n) ;

/* Renvoie l'indice max d'un tableau de double de taille n 
 * n > 0 */
double imax(double *t, int n) ;

/* Renvoie l'indice min d'un tableau de double de taille n 
 * n > 0 */
double imin(double *t, int n) ;

/* Trie par insertion un tableau de double de taille n 
 * n > 0 */
void trieInsertion(double *t, int n) ;

/* Renvoie un entier aléatoire entre min et max inclus */
int randint(int min, int max) ;

/* Test si elem est strictement dans le segment non ordonnée x1, x2 */
int entreStrict(double elem, double x1, double x2) ;

/* Test si elem est dans le segment non ordonnée x1, x2
 * avec les extrémités inclues */
int entreLarge(double elem, double x1, double x2) ;

/* Permet d'afficher une surface avec des Pos (en double) pluôt que des SDL_Rect
 * (en int) */
void SDL_Blit(SDL_Surface *surface, Pos *rect, SDL_Surface *ecran, Pos *pos) ;

/* Initialise un texte */
void inits_texte (s_texte *t, int r, int g, int b, char message[], char police[], int taille, int x, int y, int longueur) ;

/* permet de changer un texte */
void changerTexte(s_texte *txt, char newTexte[]) ;

#endif

