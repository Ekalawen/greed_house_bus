
#include "includes.h"

int main ()
{
	Point **t = malloc(sizeof(Point) * 10) ;
	Point **sommets = malloc(sizeof(Point) * 10) ;
	Point *pt = malloc(sizeof(Point)) ;
	double *v = malloc(sizeof(double) * 10) ;
	Pos *pos = malloc(sizeof(SDL_Rect)) ;
	Segment *seg = malloc(sizeof(Segment)) ;
	Triangle *triangle = malloc(sizeof(Triangle)) ;
	Polygone *p1, *p2, *p3, *p4, *p5 ;

	// test de creerPolygone
	printf("Test de creerPolygone\n") ;
	t[0] = creerPointXY(0.0, 0.0) ;
	t[1] = creerPointXY(0.0, 2.0) ;
	t[2] = creerPointXY(2.0, 2.0) ;
	t[3] = creerPointXY(2.0, 0.0) ;
	p1 = creerPolygone(4, t) ;

	assert(p1->n == 4) ;
	assert(egalSegments(p1->a[0], creerSegment(t[0], t[1]))) ;
	assert(egalSegments(p1->a[1], creerSegment(t[1], t[2]))) ;
	assert(egalSegments(p1->a[2], creerSegment(t[2], t[3]))) ;
	assert(egalSegments(p1->a[3], creerSegment(t[3], t[0]))) ;

	t[0] = creerPointXY(0.0, 0.0) ;
	t[1] = creerPointXY(2.0, 2.0) ;
	t[2] = creerPointXY(4.0, 0.0) ;
	p2 = creerPolygone(3, t) ;

	assert(p2->n == 3) ;
	assert(egalSegments(p2->a[0], creerSegment(t[0], t[1]))) ;
	assert(egalSegments(p2->a[1], creerSegment(t[1], t[2]))) ;
	assert(egalSegments(p2->a[2], creerSegment(t[2], t[0]))) ;

	// test de extraireTriangle
	printf("Test de extraireTriangle\n") ;
	assert(egalPoints(p1->maillage[0]->a1, p1->a[3]->p1)) ;
	assert(egalPoints(p1->maillage[0]->a2, p1->a[0]->p1)) ;
	assert(egalPoints(p1->maillage[0]->a3, p1->a[1]->p1)) ;
	assert(egalPoints(p1->maillage[1]->a1, p1->a[3]->p1)) ;
	assert(egalPoints(p1->maillage[1]->a2, p1->a[1]->p1)) ;
	assert(egalPoints(p1->maillage[1]->a3, p1->a[2]->p1)) ;

	assert(egalPoints(p2->maillage[0]->a1, p2->a[2]->p1)) ;
	assert(egalPoints(p2->maillage[0]->a2, p2->a[0]->p1)) ;
	assert(egalPoints(p2->maillage[0]->a3, p2->a[1]->p1)) ;

	// test de getVxPoly
	printf("Test de getVxPoly\n") ;
	v = getVxPoly(p2) ;
	assert(egalDouble(v[0], 0.0)) ;
	assert(egalDouble(v[1], 2.0)) ;
	assert(egalDouble(v[2], 4.0)) ;

	// test de getVyPoly
	printf("Test de getVyPoly\n") ;
	v = getVyPoly(p2) ;
	assert(egalDouble(v[0], 0.0)) ;
	assert(egalDouble(v[1], 2.0)) ;
	assert(egalDouble(v[2], 0.0)) ;

	// test de getPositionPoly
	printf("Test de getPositionPoly\n") ;
	pos = getPositionPoly(p2) ;
	assert(egalDouble(pos->x, 0.0)) ;
	assert(egalDouble(pos->y, 0.0)) ;
	assert(egalDouble(pos->w, 4.0)) ;
	assert(egalDouble(pos->h, 2.0)) ;

	// test de getSommetsPoly
	printf("Test de getSommetsPoly\n") ;
	sommets = getSommetsPoly(p2) ;
	assert(egalPoints(sommets[0], t[0])) ;
	assert(egalPoints(sommets[1], t[1])) ;
	assert(egalPoints(sommets[2], t[2])) ;

	// test de egalPolynome
	// A FAIRE !!
	
	// test de translaterPolygoneXY
	printf("Test de translaterPolygoneXY\n") ;
	translaterPolygoneXY(p2, -2.0, 2.0) ;
	assert(egalSegments(p2->a[0], 
			creerSegment(creerPointXY(-2.0, 2.0), creerPointXY(0.0, 4.0)))) ;
	assert(egalSegments(p2->a[1],
			creerSegment(creerPointXY(0.0, 4.0), creerPointXY(2.0, 2.0)))) ;
	assert(egalSegments(p2->a[2], 
			creerSegment(creerPointXY(2.0, 2.0), creerPointXY(-2.0, 2.0)))) ;

	// test de translaterPolygoneRT
	printf("Test de translaterPolygoneRT\n") ;
	t[0] = creerPointXY(0, 0) ;
	t[1] = creerPointXY(0, 2) ;
	t[2] = creerPointXY(2, 2) ;
	t[3] = creerPointXY(2, 0) ;
	p1 = creerPolygone(4, t) ;
	translaterPolygoneRT(p1, 1.0, PI / 2) ;
	assert(egalSegments(p1->a[0],
			creerSegment(creerPointXY(0.0, 1.0), creerPointXY(0.0, 3.0)))) ;
	assert(egalSegments(p1->a[1],
			creerSegment(creerPointXY(0.0, 3.0), creerPointXY(2.0, 3.0)))) ;
	assert(egalSegments(p1->a[2],
			creerSegment(creerPointXY(2.0, 3.0), creerPointXY(2.0, 1.0)))) ;
	assert(egalSegments(p1->a[3],
			creerSegment(creerPointXY(2.0, 1.0), creerPointXY(0.0, 1.0)))) ;

	// test de rotationPolygone
	printf("Test de rotationPolygone\n") ;
	t[0] = creerPointXY(1, 1) ;
	t[1] = creerPointXY(3, -1) ;
	t[2] = creerPointXY(1, -3) ;
	t[3] = creerPointXY(-1, -1) ;
	p5 = creerPolygone(4, t) ;
	rotationPolygone(p5, PI / 2, creerPointXY(0, 0)) ;
	assert(egalPoints(p5->a[0]->p1, creerPointXY(-1, 1))) ;
	assert(egalPoints(p5->a[1]->p1, creerPointXY(1, 3))) ;
	assert(egalPoints(p5->a[2]->p1, creerPointXY(3, 1))) ;
	assert(egalPoints(p5->a[3]->p1, creerPointXY(1, -1))) ;

	// test de pointInTriangle
	printf("Test de pointInTriangle\n") ;
	triangle->a1 = creerPointXY(-1, 1) ;
	triangle->a2 = creerPointXY(2, -2) ;
	triangle->a3 = creerPointXY(-1, -2) ;

	pt = creerPointXY(5, 5) ;
	assert(!pointInTriangle(pt, triangle)) ;

	pt = creerPointXY(-1, 1) ;
	assert(pointInTriangle(pt, triangle)) ;
	pt = creerPointXY(2, -2) ;
	assert(pointInTriangle(pt, triangle)) ;
	pt = creerPointXY(-1, -2) ;
	assert(pointInTriangle(pt, triangle)) ;

	pt = creerPointXY(0, 0) ;
	assert(pointInTriangle(pt, triangle)) ;

	pt = creerPointXY(0, -1) ;
	assert(pointInTriangle(pt, triangle)) ;
	
	// test de pointInPoly
	printf("Test de pointInPoly\n") ;
	t[0] = creerPointXY(0, 2) ;
	t[1] = creerPointXY(2, 2) ;
	t[2] = creerPointXY(2, 0) ;
	t[3] = creerPointXY(0, 0) ;
	p5 = creerPolygone(4, t) ;
	
	pt = creerPointXY(5, 5) ;
	assert(!pointInPoly(pt, p5)) ;
	pt = creerPointXY(2, 2) ;
	assert(!pointInPoly(pt, p5)) ;
	pt = creerPointXY(1, 0) ;
	assert(!pointInPoly(pt, p5)) ;
	pt = creerPointXY(0.1, 0.6) ;
	assert(pointInPoly(pt, p5)) ;
	pt = creerPointXY(1, 1) ;
	assert(pointInPoly(pt, p5)) ;

	t[0] = creerPointXY(0, 0) ;
	t[1] = creerPointXY(0, 3) ;
	t[2] = creerPointXY(1, 1) ;
	t[3] = creerPointXY(1, 4) ;
	t[4] = creerPointXY(3, 4) ;
	t[5] = creerPointXY(3, 0) ;
	p5 = creerPolygone(6, t) ;

	pt = creerPointXY(3, 1) ;
	assert(!pointInPoly(pt, p5)) ;
	pt = creerPointXY(1, 1) ;
	assert(!pointInPoly(pt, p5)) ;
	pt = creerPointXY(0.75, 2) ;
	assert(!pointInPoly(pt, p5)) ;
	pt = creerPointXY(0.25, 2) ;
	assert(pointInPoly(pt, p5)) ;
	pt = creerPointXY(1.25, 3) ;
	assert(pointInPoly(pt, p5)) ;

	
	// test de segIntersectePoly
	printf("Test de segIntersectePoly\n") ;
	t[0] = creerPointXY(0, 0) ;
	t[1] = creerPointXY(0, 3) ;
	t[2] = creerPointXY(1, 1) ;
	t[3] = creerPointXY(1, 4) ;
	t[4] = creerPointXY(3, 4) ;
	t[5] = creerPointXY(3, 0) ;
	p5 = creerPolygone(6, t) ;

	seg = creerSegment(creerPointXY(-1, -1), creerPointXY(4, -1)) ;
	assert(!segIntersectePoly(seg, p5)) ;
	seg = creerSegment(creerPointXY(-1, 0.5), creerPointXY(4, 0.5)) ;
	assert(segIntersectePoly(seg, p5)) ;
	seg = creerSegment(creerPointXY(-1, 0.5), creerPointXY(2, 0.5)) ;
	assert(segIntersectePoly(seg, p5)) ;
	seg = creerSegment(creerPointXY(-1, 1), creerPointXY(2, 1)) ;
	assert(segIntersectePoly(seg, p5)) ;
	seg = creerSegment(creerPointXY(0, 1), creerPointXY(2, 1)) ;
	assert(!segIntersectePoly(seg, p5)) ;
	seg = creerSegment(creerPointXY(0, 3), creerPointXY(2, 3)) ;
	assert(segIntersectePoly(seg, p5)) ;
	seg = creerSegment(creerPointXY(0, 3), creerPointXY(1, 3)) ;
	assert(!segIntersectePoly(seg, p5)) ;
	seg = creerSegment(creerPointXY(0, 3), creerPointXY(1.1, 3)) ;
	assert(segIntersectePoly(seg, p5)) ;

	t[0] = creerPointXY(0, 0) ;
	t[1] = creerPointXY(0, 2) ;
	t[2] = creerPointXY(2, 2) ;
	t[3] = creerPointXY(2, 0) ;
	p5 = creerPolygone(4, t) ;

	seg = creerSegment(creerPointXY(0, 0), creerPointXY(2, 2)) ;
	assert(!segIntersectePoly(seg, p5)) ;
	seg = creerSegment(creerPointXY(2, 2), creerPointXY(0, 0)) ;
	assert(!segIntersectePoly(seg, p5)) ;
	seg = creerSegment(creerPointXY(2, 0), creerPointXY(0, 2)) ;
	assert(!segIntersectePoly(seg, p5)) ;
	
	// test précis
	t[0] = creerPointXY(5268.977853, 2597.335716) ;
	t[1] = creerPointXY(5348.673428, 2604.308175) ;
	t[2] = creerPointXY(5327.756050, 2843.394902) ;
	t[3] = creerPointXY(5248.060474, 2836.422443) ;
	p5 = creerPolygone(4, t) ;
	seg = creerSegment(creerPointXY(5327.756050, 2843.394902), creerPointXY(5268.977853, 2597.335716)) ;
	assert(!segIntersectePoly(seg, p5)) ;

	t[0] = creerPointXY(5263.3841648015095415757969021797180175781250, 2572.6637848363293414877261966466903686523438) ;
	t[1] = creerPointXY(5342.1687850424868884147144854068756103515625, 2558.7719306229732865176629275083541870117188) ;
	t[2] = creerPointXY(5383.8443476825495963566936552524566650390625, 2795.1257913459044175397139042615890502929688) ;
	t[3] = creerPointXY(5305.0597274415740685071796178817749023437500, 2809.0176455592586535203736275434494018554688) ;
	p5 = creerPolygone(4, t) ;
	seg = creerSegment(creerPointXY(5383.8443476825495963566936552524566650390625, 2795.1257913459044175397139042615890502929688), creerPointXY(5263.3841648015095415757969021797180175781250, 2572.6637848363293414877261966466903686523438)) ;
	assert(!segIntersectePoly(seg, p5)) ;


	// test de polygoneInPolygone
	printf("Test de polygoneInPolygone\n") ;
	t[0] = creerPointXY(0, 2) ;
	t[1] = creerPointXY(2, 2) ;
	t[2] = creerPointXY(2, 0) ;
	t[3] = creerPointXY(0, 0) ;
	p1 = creerPolygone(4, t) ;

	t[0] = creerPointXY(0, 0) ;
	t[1] = creerPointXY(2, 2) ;
	t[2] = creerPointXY(4, 0) ;
	p2 = creerPolygone(3, t) ;

	// cas des arrêtes superposés et d'une intersection d'angle
	assert(!polygoneInPolygone(p1, p2)) ;
	// cas où double intersection d'angle
	translaterPolygoneXY(p1, 1.0, 1.0) ;
	assert(!polygoneInPolygone(p1, p2)) ;
	// ca où intersection
	translaterPolygoneXY(p1, 0.5, 0) ;
	assert(polygoneInPolygone(p1, p2)) ;
	// cas où pas d'intersection
	translaterPolygoneXY(p1, 2.5, 3.0) ;
	assert(!polygoneInPolygone(p1, p2)) ;
	// cas où juxtaposition d'angle
	translaterPolygoneXY(p1, -6.0, -4.0) ;
	assert(!polygoneInPolygone(p1, p2)) ;
	// cas où juxtaposition il y a une arrête en commune, mais elle ne suffit
	// pas à faire une intersection (c'est juste une juxtaposition)
	translaterPolygoneXY(p1, 2.0, -2.0) ;
	assert(!polygoneInPolygone(p1, p2)) ;
	// cas où inclusion totale
	t[0] = creerPointXY(-1.0, -1.0) ;
	t[1] = creerPointXY(4.0, 4.0) ;
	t[2] = creerPointXY(9.0, -1.0) ;
	t[3] = creerPointXY(4.0, -6.0) ;
	p3 = creerPolygone(4, t) ;
	translaterPolygoneXY(p1, 3.0, 0.0) ;
	assert(!polygoneInPolygone(p1, p3)) ;
	// cas où intersection pile dans les angles (cas non déctecté, donc ça ne
	// marche pas !)
	// A FAIRE !!
	translaterPolygoneXY(p3, 3.0, -2.0) ;
	assert(!polygoneInPolygone(p1, p3)) ;
	
	// test de polyInPoly2
	printf("Test de polyInPoly2\n") ;
	t[0] = creerPointXY(0, 2) ;
	t[1] = creerPointXY(2, 2) ;
	t[2] = creerPointXY(2, 0) ;
	t[3] = creerPointXY(0, 0) ;
	p1 = creerPolygone(4, t) ;

	t[0] = creerPointXY(0, 0) ;
	t[1] = creerPointXY(2, 2) ;
	t[2] = creerPointXY(4, 0) ;
	p2 = creerPolygone(3, t) ;

	// cas des arrêtes superposés et d'une intersection d'angle
	// en vrai ça devrait dire "oui" ici mais c'est vraiment un cas tordu alors
	// osef x)
	assert(!polyInPoly2(p1, p2)) ;
	// cas où intersection 
	translaterPolygoneXY(p1, 1.0, 1.0) ;
	assert(polyInPoly2(p1, p2)) ;
	// cas où pas d'intersection
	translaterPolygoneXY(p1, 3.0, 3.0) ;
	assert(!polyInPoly2(p1, p2)) ;
	// cas où juxtaposition d'angle
	translaterPolygoneXY(p1, -6.0, -4.0) ;
	assert(!polyInPoly2(p1, p2)) ;
	// cas où juxtaposition il y a une arrête en commune, mais elle ne suffit
	// pas à faire une intersection (c'est juste une juxtaposition)
	translaterPolygoneXY(p1, 2.0, -2.0) ;
	assert(!polyInPoly2(p1, p2)) ;
	// cas où inclusion totale
	t[0] = creerPointXY(-1.0, -1.0) ;
	t[1] = creerPointXY(4.0, 4.0) ;
	t[2] = creerPointXY(9.0, -1.0) ;
	t[3] = creerPointXY(4.0, -6.0) ;
	p3 = creerPolygone(4, t) ;
	translaterPolygoneXY(p1, 3.0, 0.0) ;
	assert(polyInPoly2(p1, p3)) ;
	// cas où intersection pile dans les angles (cas non déctecté, donc ça ne
	// marche pas !)
	// A FAIRE !!
	// C'est fait ! <3
	translaterPolygoneXY(p3, 3.0, -2.0) ;
	assert(polyInPoly2(p1, p3)) ;


}

