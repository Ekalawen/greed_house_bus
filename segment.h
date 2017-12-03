

#ifndef SEGMENT_H
#define SEGMENT_H

typedef struct
{
	Point *p1 ;
	Point *p2 ;
} Segment ;

typedef struct
{
	bool verticale ; // test si la pente est verticale
	double a ; // le coefficiant directeur de la pente si elle n'est pas verticale
	double b ; // l'ordonnée à l'origine de la pente si elle n'est pas verticale
} Droite ;

/* Créer un segment à partir de 2 points */
Segment* creerSegment(Point *p1, Point *p2) ;

/* Affiche un segment dans le terminal */
void printSegment(Segment *s) ;

/* Test si deux segments sont égaux */
int egalSegments(Segment *s1, Segment *s2) ;

/* Translater un segment */
void translaterSegmentXY(Segment *s, double vx, double vy) ;
void translaterSegmentRT(Segment *s, double vr, double vt) ;

/* Fait effectuer une rotation d'angle teta dans le sens TRIGO et autour du
 * centre centre au Segment
 * La rotation est en gradiant. */
void rotationSegment(Segment *p, double teta, Point *centre) ;

/* Test le chevauchement stricte de deux intervalles non ordonnées (x1, x2) et
 * (y1, y2) */
int chevauchement(double x1, double x2, double y1, double y2) ;

/* Récupère la droite issue d'un segment 
 * /!\ Si les deux points sont superposés, renvoie une droite verticale */
Droite* segmentToDroite(Segment const *s) ;

/* Récupère un segment à partir d'une droite et d'un intervalle [x1, x2]
 * /!\ Si la droite est verticale, les valeurs x1 et x2 seront les limites en
 * ordonnées du segment verticale. */
Segment* droiteToSegment(Droite const *d, double x1, double x2) ;

/* Test si un point est dans un segment */
int pointInSegment(Point *p, Segment *s) ;

/* Test si deux droites sont parallèles */
int sontParalleles(Droite *d1, Droite *d2) ;

/* Test si un segment intersecte strictement un autre segment 
 * J'entends par strictement que les 2 segments ne font pas que se juxtaposer
 * mais se coupent l'un l'autre. */
int segmentInSegment(Segment *s1, Segment *s2) ;

#endif


