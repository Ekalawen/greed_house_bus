

#ifndef POLYGONE_H
#define POLYGONE_H

typedef struct
{
	Point *a1, *a2, *a3 ;
} Triangle ;

typedef struct
{
	int n ; // le nombre de sommets
	Segment **a ; // un tableau de pointeurs d'arrêtes
	int nb_triangles ; // le nombre de triangles du maillage
	Triangle **maillage ; // un ensemble de triangles qui forment une partition de notre polygone
} Polygone ;
/* les arrêtes correspondent aux sommets (l'arrete 0 relie le
sommet 0 au sommet 1, l'arrete n-1 relie le sommet n-1 au sommet 0) */

/* Cree un Polygone à partir de ses n sommets 
 * précondition : n >= 3
 * /!\      	  les arrêtes ne doivent pas se couper entre elles !! */
Polygone* creerPolygone(int nb_sommets, Point **sommets) ;

/* A partir d'un polygone, en forme une partition composé d'un de ses triangle
 * et du reste du polygone.
 * Retourne le triangle extrait.
 * Le polygone est modifié. */
Triangle** extraireTriangles(Polygone *p, int *nb_triangles) ;

/* Affiche un polygone dans le terminal */
void printPolygone(Polygone *p) ;

/* Renvoie le vecteur des valeurs des sommets en X (en Y) */
double* getVxPoly(Polygone *p) ;
double* getVyPoly(Polygone *p) ;

/* Renvoie la position d'un polygone sous la forme d'un rectangle */
Pos* getPositionPoly(Polygone *p) ;

/* Renvoie les sommets d'un polygone sous la forme d'un tableau de pointeurs de
 * sommets */
Point** getSommetsPoly(Polygone *p) ;

/* Test si deux polygones sont égaux */
//int egalPolygones(Polygone *p1, Polygone *p2) ;
// A FAIRE !!

/* Translate un polynome */
void translaterPolygoneXY(Polygone *p, double vx, double vy) ;
void translaterPolygoneRT(Polygone *p, double vr, double vt) ;

/* Fait effectuer une rotation d'angle teta dans le sens TRIGO et autour du
 * centre centre au polygone
 * La rotation est en gradiant. */
void rotationPolygone(Polygone *p, double teta, Point *centre) ;

/* Test si deux polygones s'intersectent 
 * /!\ il est quand même possible que des polygones s'intersectent précisémment
 * en leurs angles, ce cas là n'est pas détecté ! 
 * /!\ il est aussi possible qu'un polygone soit entièrement inclus dans un
 * autre, ce cas là n'est pas détecté ! */
int polygoneInPolygone(Polygone *p1, Polygone *p2) ;

/* Test si deux polygones s'intersectent, sans bugs je l'espère ! */
int polyInPoly2(Polygone *p1, Polygone *p2) ;

/* Test si un point est LARGEMENT dans un triangle */
int pointInTriangle(Point *p, Triangle *t) ;

/* Test si un point est strictement à l'intérieur d'un polygone */
int pointInPoly(Point *point, Polygone *poly) ;

/* Test si un segment s'intersecte strictement avec un polygone */
int segIntersectePoly(Segment *s, Polygone *p) ;

#endif


