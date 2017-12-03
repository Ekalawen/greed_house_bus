
#include "includes.h"

Polygone* creerPolygone(int nb_sommets, Point **sommets) {
	int i ;
	Polygone *p = malloc(sizeof(Polygone)) ;
	Polygone *copy = malloc(sizeof(Polygone)) ;
	p->n = nb_sommets ;
	copy->n = nb_sommets ;
	p->a = malloc(sizeof(Segment) * nb_sommets) ;
	copy->a = malloc(sizeof(Segment) * nb_sommets) ;

	for(i = 0 ; i < nb_sommets - 1 ; i++) {
		p->a[i] = creerSegment(sommets[i], sommets[i+1]) ;
		copy->a[i] = creerSegment(sommets[i], sommets[i+1]) ;
	}
	p->a[nb_sommets-1] = creerSegment(sommets[nb_sommets-1], sommets[0]) ;
	copy->a[nb_sommets-1] = creerSegment(sommets[nb_sommets-1], sommets[0]) ;

	// effectuer le maillage
	p->nb_triangles = 0 ;
	copy->nb_triangles = 0 ;
	// on extrait les triangles de la copy en les retirant de ce polygone
	p->maillage = extraireTriangles(copy, &p->nb_triangles) ;		

	return p ;
}

Triangle** extraireTriangles(Polygone *p, int *nb_triangles) {
	int i, num_triangle ;
	int sommet_actuel, sommet_prec, sommet_suiv ;
	Point *ps1 = malloc(sizeof(Point)) ;
	Point *ps2 = malloc(sizeof(Point)) ;
	Segment *s_externe = malloc(sizeof(Segment)) ;
	Triangle **triangles = malloc(sizeof(Triangle) * p->n * 3) ;

	num_triangle = -1 ;
	// tant qu'il reste des sommets à découper en triangles
	while(p->n >= 3) {
		// on passe au triangle suivant
		num_triangle ++ ;

		// si la taille du polygone est 3, c'est donc un triangle
		if(p->n == 3) {
			// récupérer le triangle et vider le polygone
			triangles[num_triangle] = malloc(sizeof(Triangle)) ;
			triangles[num_triangle]->a1 = creerPointXY(p->a[2]->p1->x, p->a[2]->p1->y) ;
			triangles[num_triangle]->a2 = creerPointXY(p->a[0]->p1->x, p->a[0]->p1->y) ;
			triangles[num_triangle]->a3 = creerPointXY(p->a[1]->p1->x, p->a[1]->p1->y) ;
			p->n = 2 ; // le polygone est vide, enfin il n'est plus valide car ce n'est plus qu'un segment
		// sinon
		} else {
			// on veut parcourir les sommets jusqu'à trouver un triangle de
			// centre ce sommet qui soit entièrement inclus dans le polygone.
			// L'existence de ce sommet est assuré
			sommet_actuel = 0 ;
			sommet_prec = p->n - 1 ;
			sommet_suiv = 1 ;
			ps1 = creerPointXY(p->a[sommet_prec]->p1->x, p->a[sommet_prec]->p1->y) ;
			ps2 = creerPointXY(p->a[sommet_suiv]->p1->x, p->a[sommet_suiv]->p1->y) ;
			s_externe = creerSegment(ps1, ps2) ;
			// tant que le segment qui n'appartient pas au polygone n'est pas
			// dans le polygone, on cherche un autre triangle
			while(segIntersectePoly(s_externe, p)) {
				// on change le sommet actuel
				sommet_actuel++ ;
				if(sommet_actuel == p->n - 1) {
					// et on adapte ses sommets adjacents
					sommet_prec = sommet_actuel - 1 ;
					sommet_suiv = 0 ;
				} else if (sommet_actuel >= p->n) {
					// on a déjà épuisé tous les sommets du triangle
					//printf("Imposible de faire la triangulation du polygone suivant !\n") ;
					*nb_triangles = 0 ;
					return NULL ;
				} else {
					sommet_prec = sommet_actuel - 1 ;
					sommet_suiv = sommet_actuel + 1 ;
				}
				// on récupère le segment qui n'appartient pas au polygone
				ps1 = creerPointXY(p->a[sommet_prec]->p1->x, p->a[sommet_prec]->p1->y) ;
				ps2 = creerPointXY(p->a[sommet_suiv]->p1->x, p->a[sommet_suiv]->p1->y) ;
				s_externe = creerSegment(ps1, ps2) ;
			}
			// on a une oreille

			// créer le triangle correspondant
			triangles[num_triangle] = malloc(sizeof(Triangle)) ;
			triangles[num_triangle]->a1 = creerPointXY(p->a[sommet_prec]->p1->x, p->a[sommet_prec]->p1->y) ;
			triangles[num_triangle]->a2 = creerPointXY(p->a[sommet_actuel]->p1->x, p->a[sommet_actuel]->p1->y) ;
			triangles[num_triangle]->a3 = creerPointXY(p->a[sommet_suiv]->p1->x, p->a[sommet_suiv]->p1->y) ;

			// oter ce point du polygone
			// on redirige le segment précédent
			p->a[sommet_prec]->p2 = p->a[sommet_actuel]->p2 ;
			// pour tous les segments après l'actuel
			for(i = sommet_actuel; i < p->n - 1 ; i++) {
				// on copie le segment suivant dans le segment actuel
				p->a[i] = creerSegment(creerPointXY(p->a[i+1]->p1->x, p->a[i+1]->p1->y),
									   creerPointXY(p->a[i+1]->p2->x, p->a[i+1]->p2->y)) ;
			}
			// et on supprime le dernier
			p->n = p->n - 1 ;
		}
	}

	// compter le nombre de triangle
	*nb_triangles = num_triangle + 1 ;

	// renvoyer les triangles
	return triangles ;
}

void printPolygone(Polygone *p) {
	int i ;
	printf("POLY (n=%d)\n", p->n) ;
	for(i = 0 ; i < p->n ; i++) {
		printf("%.40f, %.40f\n", p->a[i]->p1->x, p->a[i]->p1->y) ;
	}
}

double* getVxPoly(Polygone *p) {
	int i ;
	Point **sommets = getSommetsPoly(p) ;
	double *vx = malloc(sizeof(double) * p->n) ;
	for(i = 0 ; i < p->n ; i++) {
		vx[i] = sommets[i]->x ;
	}
	return vx ;
}
	
double* getVyPoly(Polygone *p) {
	int i ;
	Point **sommets = getSommetsPoly(p) ;
	double *vy = malloc(sizeof(double) * p->n) ;
	for(i = 0 ; i < p->n ; i++) {
		vy[i] = sommets[i]->y ;
	}
	return vy ;
}

Pos* getPositionPoly(Polygone *p) {
	Pos *pos = malloc(sizeof(Pos)) ;
	Point **sommets = getSommetsPoly(p) ;
	double *vx, *vy ;
	vx = getVxPoly(p) ;
	vy = getVyPoly(p) ;
	pos->x = mint(vx, p->n) ;
	pos->y = mint(vy, p->n) ;
	pos->w = maxt(vx, p->n) - pos->x ;
	pos->h = maxt(vy, p->n) - pos->y ;
	return pos ;
}

Point** getSommetsPoly(Polygone *p) {
	int i ;
	Point **t = malloc(sizeof(Point) * p->n) ;
	for(i = 0 ; i < p->n ; i++) {
		t[i] = creerPointXY(p->a[i]->p1->x, p->a[i]->p1->y) ;
	}
	return t ;
}

//int egalPolygones(Polygone *p1, Polygone *p2) ;
// A FAIRE !!


void translaterPolygoneXY(Polygone *p, double vx, double vy) {
	int i ;
	for(i = 0 ; i < p->n ; i ++) {
		translaterSegmentXY(p->a[i], vx, vy) ;
	}
	for(i = 0 ; i < p->nb_triangles ; i ++) {
		translaterPointXY(p->maillage[i]->a1, vx, vy) ;
		translaterPointXY(p->maillage[i]->a2, vx, vy) ;
		translaterPointXY(p->maillage[i]->a3, vx, vy) ;
	}
}

void translaterPolygoneRT(Polygone *p, double vr, double vt) {
	int i ;
	for(i = 0 ; i < p->n ; i ++) {
		translaterSegmentRT(p->a[i], vr, vt) ;
	}
	for(i = 0 ; i < p->nb_triangles ; i ++) {
		translaterPointXY(p->maillage[i]->a1, vr, vt) ;
		translaterPointXY(p->maillage[i]->a2, vr, vt) ;
		translaterPointXY(p->maillage[i]->a3, vr, vt) ;
	}
}

void rotationPolygone(Polygone *p, double teta, Point *centre) {
	int i ;
	for(i = 0 ; i < p->n ; i++) {
		rotationSegment(p->a[i], teta, centre) ;
	}
	for(i = 0 ; i < p->nb_triangles ; i ++) {
		rotationPoint(p->maillage[i]->a1, teta, centre) ;
		rotationPoint(p->maillage[i]->a2, teta, centre) ;
		rotationPoint(p->maillage[i]->a3, teta, centre) ;
	}
}

int polygoneInPolygone(Polygone *p1, Polygone *p2) {
	int i, j ;
	for(i = 0 ; i < p1->n ; i++) {
		for(j = 0 ; j < p2->n ; j++) {
			if(segmentInSegment(p1->a[i], p2->a[j])) {
				// si au moins deux arrêtes des polynômes s'intersectent alors
				// il y a collision
				return true ;
			}
		}
	}
	// sinon il n'y a pas collision
	return false ;
}

int polyInPoly2(Polygone *p1, Polygone *p2) {
	int i ;
	// un polygone est dans un autre si au moins l'un des points des deux
	// polygone est dans l'autre polygone
	for(i = 0 ; i < p1->n ; i++) {
		if(pointInPoly(p1->a[i]->p1, p2)) {
			return true ;
		}
	}
	// puis on inverse les rôles
	for(i = 0 ; i < p2->n ; i++) {
		if(pointInPoly(p2->a[i]->p1, p1)) {
			return true ;
		}
	}
	// sinon les poly ne s'intersectent pas !
	return false ;
}

int pointInTriangle(Point *p, Triangle *t) {
	double det ;
	Point *v_arrete = malloc(sizeof(Point)) ; // ce sont des vecteurs
	Point *v_point = malloc(sizeof(Point)) ;
	// pour chaque arrête du triangle
		// vérifier que le point est à droite
		// calculer le vecteur de l'arrete
		v_arrete->x = t->a2->x - t->a1->x ;
		v_arrete->y = t->a2->y - t->a1->y ;
		// calculer le vecteur "début arrete/point"
		v_point->x = p->x - t->a1->x ;
		v_point->y = p->y - t->a1->y ;
		// on veut que le point soit toujours à droite (ou sur le segment)
		// on calcul le déterminant de ces 2 vecteurs
		det = v_arrete->x * v_point->y - v_arrete->y * v_point->x ;
		// le point est à droite si det < 0
		// le point est sur l'arrete si det = 0 
		// si le point est à gauche renvoyer false
		if(det > 0) {
			return false ;
		}
		v_arrete->x = t->a3->x - t->a2->x ;
		v_arrete->y = t->a3->y - t->a2->y ;
		v_point->x = p->x - t->a2->x ;
		v_point->y = p->y - t->a2->y ;
		det = v_arrete->x * v_point->y - v_arrete->y * v_point->x ;
		if(det > 0) {
			return false ;
		}
		v_arrete->x = t->a1->x - t->a3->x ;
		v_arrete->y = t->a1->y - t->a3->y ;
		v_point->x = p->x - t->a3->x ;
		v_point->y = p->y - t->a3->y ;
		det = v_arrete->x * v_point->y - v_arrete->y * v_point->x ;
		if(det > 0) {
			return false ;
		}
	// renvoyer true
	return true ;
}

int pointInPoly(Point *point, Polygone *poly) {
	int i ;
	// le point n'est pas dans le poly si il appartient à son bord
	for(i = 0 ; i < poly->n ; i++) {
		if(pointInSegment(point, poly->a[i])) {
			return false ;
		}
	}
	// sinon, le point est dans le poly si il est dans son maillage
	for(i = 0 ; i < poly->nb_triangles ; i++) {
		// donc si il est dans au moins un triangle
		if(pointInTriangle(point, poly->maillage[i])) {
			return true ;
		}
	}
	// sinon il n'est pas dans le poly
	return false ;
}

int segIntersectePoly(Segment *s, Polygone *p) {
	int i ;
	for(i = 0 ; i < p->n ; i++) { 
		if(segmentInSegment(s, p->a[i])) {
			return true ;
		}
	}
	return false ;
}
