
#ifndef POINT_H
#define POINT_H

#define PI M_PI

typedef struct
{
	double x ;
	double y ;
} Point ;

/* Le repère polaire est dans le sens trigonométrique */

/* Créer un point avec ses coordonnées en x et en y */
Point* creerPointXY(double x, double y) ;

/* Créer un point avec ses coordonnées en r et teta */
Point* creerPointRT(double r, double t) ;

/* Affiche un point dans le terminal */
void printPoint(Point *p) ;

/* Test si deux Points sont égaux */
int egalPoints(Point *p1, Point *p2) ;

/* Translater un point avec les coordonnées en x et y */
void translaterPointXY(Point *p, double vx, double vy) ; 

/* Translater un point avec les coorodonnées en r et t */
void translaterPointRT(Point *p, double vr, double vt) ;

/* Fait effectuer une rotation d'angle teta dans le sens TRIGO et autour du
 * centre centre au point p
 * La rotation est en gradiant. */
void rotationPoint(Point *p, double teta, Point *centre) ;

/* Convertit un couple (x, y) en un couple (r, t) et le renvoie dans les
 * pointeurs r et t */
void XYtoRT(double const x, double const y, double *r, double *t) ;

/* Convertit un couple (r, t) en un couple (x, y) et le renvoie dans les
 * pointeurs x et y */
void RTtoXY(double const r, double const t, double *x, double *y) ;

/* Récupère le couple (r, t) des coordonnées d'un point */
void getRT(Point *p, double *r, double *t) ;

/* Test si un point est dans la tranche d'abscisse composé par deux autre points
 * non ordonnées, extrémités comprises */
int pointInTrancheLarge(Point *elem, Point *tranche1, Point *tranche2) ;

/* Test si un point est strictement dans la tranche d'abscisse composé par deux
 * autre points non ordonnées */
int pointInTrancheStrict(Point *elem, Point *tranche1, Point *tranche2) ;

#endif


