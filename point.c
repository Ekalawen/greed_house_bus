
#include "includes.h"

Point* creerPointXY(double x, double y) {
	Point *p = malloc(sizeof(Point)) ;
	p->x = x ;
	p->y = y ;
	return p ;
}

Point* creerPointRT(double r, double t) {
	Point *p = malloc(sizeof(Point)) ;
	double x, y ;
	RTtoXY(r, t, &x, &y) ;
	p->x = x ;
	p->y = y ;
	return p ;
}

void printPoint(Point *p) {
	printf("Point (%.40f, %.40f)\n", p->x, p->y) ;
}

int egalPoints(Point *p1, Point *p2) {
	return egalDouble(p1->x, p2->x) && egalDouble(p1->y, p2->y) ;
}

void translaterPointXY(Point *p, double vx, double vy) {
	p->x += vx ;
	p->y += vy ;
}

void translaterPointRT(Point *p, double vr, double vt) {
	double vx, vy ;
	RTtoXY(vr, vt, &vx, &vy) ;
	p->x += vx ;
	p->y += vy ;
}

void rotationPoint(Point *p, double teta, Point *centre) {
	Point *vecteur ;
	double r, t ;
	// trouver le vecteur centre->p
	vecteur = creerPointXY(p->x - centre->x, p->y - centre->y) ;

	// le convertir en coordonnées polaires
	getRT(vecteur, &r, &t) ;
	
	// lui faire effectuer la rotation
	vecteur = creerPointRT(r, t + teta) ;
	
	// le reconvertir en coordonnées cartésiennes
	// ça se fait tout seul !
	
	// renvoyer la translation de ce vecteur depuis le centre	
	p->x = centre->x + vecteur->x ;
	p->y = centre->y + vecteur->y ;
}

void XYtoRT(double const x, double const y, double *r, double *t) {
	if (!(x==0.0 && y==0.0)) {
		*r = sqrt(pow(x, 2) + pow(y, 2)) ;
		if (x > 0 && y >= 0) {
			*t = atan(y / x) ;
		} else if (x > 0 && y < 0) {
			*t = atan(y / x) + 2 * PI ;
		} else if (x < 0) {
			*t = atan(y / x) + PI ;
		} else if (x == 0 && y > 0) {
			*t = PI / 2 ;
		} else { // (x == 0 && y < 0)
			*t = 3 * PI / 2 ;
		}
	} else {
		*r = 0.0 ;
		*t = 0.0 ;
	}
}

void RTtoXY(double const r, double const t, double *x, double *y) {
	if (!(r==0.0 && t==0.0)) {
		*x = r * cos(t) ;
		*y = r * sin(t) ;
	} else {
		*x = 0.0 ;
		*y = 0.0 ;
	}
}

void getRT(Point *p, double *r, double *t) {
	XYtoRT(p->x, p->y, r, t) ;
}

int pointInTrancheLarge(Point *elem, Point *tranche1, Point *tranche2) {
	return (tranche1->x <= elem->x && elem->x <= tranche2->x)
		|| (tranche2->x <= elem->x && elem->x <= tranche1->x) ;

}
int pointInTrancheStrict(Point *elem, Point *tranche1, Point *tranche2) {
	return !(egalDouble(elem->x, tranche1->x))
		&& !(egalDouble(elem->x, tranche2->x))
		&& (pointInTrancheLarge(elem, tranche1, tranche2)) ;
}
