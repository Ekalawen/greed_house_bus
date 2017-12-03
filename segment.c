
#include "includes.h"

Segment* creerSegment(Point *p1, Point *p2) {
	Segment *s = malloc(sizeof(Segment)) ;
	s->p1 = creerPointXY(p1->x, p1->y) ;
	s->p2 = creerPointXY(p2->x, p2->y) ;
	return s ;
}

void printSegment(Segment *s) {
	printf("Segment (%.40f, %.40f)::(%.40f, %.40f)\n", s->p1->x, s->p1->y, s->p2->x, s->p2->y) ;
}

int egalSegments(Segment *s1, Segment *s2) {
	return (egalPoints(s1->p1, s2->p1) && egalPoints(s1->p2, s2->p2))
		 ||(egalPoints(s1->p1, s2->p2) && egalPoints(s1->p2, s2->p1)) ;
}

void translaterSegmentXY(Segment *s, double vx, double vy) {
	translaterPointXY(s->p1, vx, vy) ;
	translaterPointXY(s->p2, vx, vy) ;
}

void translaterSegmentRT(Segment *s, double vr, double vt) {
	translaterPointRT(s->p1, vr, vt) ;
	translaterPointRT(s->p2, vr, vt) ;
}

void rotationSegment(Segment *p, double teta, Point *centre) {
	rotationPoint(p->p1, teta, centre) ;
	rotationPoint(p->p2, teta, centre) ;
}

int chevauchement(double x1, double x2, double y1, double y2) {
	// si on a un points
	if(egalDouble(x1, x2)) {
		return (min(y1, y2) < x1) && (x1 < max(y1, y2)) ;
	}
	if(egalDouble(y1, y2)) {
		return (min(x1, x2) < y1) && (y1 < max(x1, x2)) ;
	}

	// si on a deux intervales
	if ((max(x1, x2) <= min(y1, y2)) || (min(x1, x2) >= max(y1, y2))) {
		return false ;
	}
	else if ((max(x1, x2) < max(y1, y2) && min(x1, x2) > min(y1, y2))
		 || (max(y1, y2) < max(x1, x2) && min(y1, y2) > min(x1, x2))
		 || (egalDouble(min(x1, x2), min(y1, y2)) && egalDouble(max(x1, x2), max(y1, y2)))) {
		 return true ;
	}
	else
		return true ;
}

Droite* segmentToDroite(Segment const *s) {
	Droite *d = malloc(sizeof(Droite)) ;
	// si le segment est vertical
	if (egalDouble(s->p1->x, s->p2->x)) {
		d->verticale = true ;
		d->a = 0.0 ;
		d->b = s->p1->x ;
	} else {
		d->verticale = false ;
		d->a = (s->p2->y - s->p1->y) / (s->p2->x - s->p1->x) ;
		d->b = s->p1->y - (d->a * s->p1->x) ;
	}
	return d ;
}

Segment* droiteToSegment(Droite const *d, double x1, double x2) {
	Segment *s ;
	Point *p1, *p2 ;
	// si la droite est verticale
	if (d->verticale) {
		p1 = creerPointXY(d->b, x1) ;
		p2 = creerPointXY(d->b, x2) ;
		s = creerSegment(p1, p2) ;
	} else {
		p1 = creerPointXY(x1, x1*d->a + d->b) ;
		p2 = creerPointXY(x2, x2*d->a + d->b) ;
		s = creerSegment(p1, p2) ;
	}
}

int pointInSegment(Point *p, Segment *s) {
	Droite *d ;
	// si l'abscisse du point est entre les abscisses du segment
	if (pointInTrancheLarge(p, s->p1, s->p2)) {
		d = segmentToDroite(s) ;
		// si le segment est vertical
		if (d->verticale) {
			// il faut que le point ait la même abscisse et soit entre les
			// ordonnées des points du segment
			return (egalDouble(p->x, s->p1->x)) && ((s->p1->y <= p->y && p->y <= s->p2->y) || (s->p2->y <= p->y && p->y <= s->p1->y)) ;
		// si le segment n'est pas vertical
		} else {
			// il faut que ses coordonnées vérifies l'équation de la droite
			return (egalDouble(p->y, p->x*d->a + d->b)) ;
		}
	}
	else 
		return false ;
}

int sontParalleles(Droite *d1, Droite *d2) {
	return (d1->verticale && d2->verticale)
		|| ((egalDouble(d1->a, d2->a)) && !d1->verticale && !d2->verticale) ;
}


int segmentInSegment(Segment *s1, Segment *s2) {
	double trancheG, trancheD ;
	double extremites[] = {s1->p1->x, s1->p2->x, s2->p1->x, s2->p2->x} ;
	Droite *d1, *d2 ;
	Point *ptIntersection ;
	// si les segments se chevauchent
	if (chevauchement(s1->p1->x, s1->p2->x, s2->p1->x, s2->p2->x)) {
		// trouver la zone de chevauchement
		trieInsertion(extremites, 4) ;
		trancheG = extremites[1] ;
		trancheD = extremites[2] ;
		//déterminer l'abscisse de l'intersection si elle existe
		d1 = segmentToDroite(s1) ;
		d2 = segmentToDroite(s2) ;
		// il y a toujours intersection entre les droites sauf si elles sont parallèles
		if (!sontParalleles(d1, d2)) {
			// comme elles ne sont pas parallèles, elles ne peuvent pas être
			// toutes les deux verticales
			// si aucune n'est verticale
			if (!d1->verticale && !d2->verticale) {
				ptIntersection = creerPointXY((d2->b - d1->b) / (d1->a - d2->a), 
										      (d2->b - d1->b) / (d1->a - d2->a) * d1->a + d1->b) ;
				// il y a intersection si l'intersection est dans la tranche
				return (trancheG < ptIntersection->x && ptIntersection->x < trancheD)
				    || (egalDouble(trancheG, trancheD) && egalDouble(ptIntersection->x, trancheG)) ;
			// si d1 est verticale
			} else if (d1->verticale) {
				ptIntersection = creerPointXY(s1->p1->x, 
										      s1->p1->x * d2->a + d2->b) ; 
				return chevauchement(ptIntersection->y, ptIntersection->y, s1->p1->y, s1->p2->y) ;
			// donc si d2 est verticale
			} else {
				ptIntersection = creerPointXY(s2->p2->x, 
										      s2->p2->x * d1->a + d1->b) ; 
				return chevauchement(ptIntersection->y, ptIntersection->y, s2->p1->y, s2->p2->y) ;
			}
		// si les droites sont parallèles
		} else {
			// si les droites sont parallèles, comme elles ne peuvent pas
			// s'intersecter strictement, on renvoie forcément faux
			return false ;
			/*// si elles ne sont pas verticales
			if (!d1->verticale) {
				// comme elles se chevauchent et sont parallèles, elles se
				// coupent ssi elles ont même ordonnée à l'origine
				return (d1->b == d2->b) ;
			// si elles sont toutes les deux verticales
			} else {
				// comme elles se chevauchent et sont verticales, elles se
				// coupent ssi elles se chevauchent verticalement
				return chevauchement(s1->p1->y, s1->p2->y, s2->p1->y, s2->p2->y) ;
			}*/
		}
	// si elles ne se chevauchent pas
	} else {
		return false ;
	}
}

