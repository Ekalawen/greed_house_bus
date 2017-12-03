
#include "includes.h"

int main ()
{
	Point *p1, *p2, *p3, *p4, *p5 ;
	Segment *s1, *s2, *s3, *s4, *s5, *s6 ;
	Droite *d1, *d2, *d3 ;

	p1 = creerPointXY(0.0, 0.0) ;
	p2 = creerPointXY(2.0, 0.0) ;
	p3 = creerPointXY(2.0, 2.0) ;
	p4 = creerPointXY(0.0, 2.0) ;
	p5 = creerPointXY(-4.0, -4.0) ;

	// test de creerSegment
	printf("Test de creerSegment\n") ;
	s1 = creerSegment(p1, p2) ;
	assert(egalDouble(s1->p1->x, p1->x)) ;
	assert(egalDouble(s1->p1->y, p1->y)) ;
	assert(egalDouble(s1->p2->x, p2->x)) ;
	assert(egalDouble(s1->p2->y, p2->y)) ;

	s2 = creerSegment(p1, p3) ;
	assert(egalDouble(s2->p1->x, p1->x)) ;
	assert(egalDouble(s2->p1->y, p1->y)) ;
	assert(egalDouble(s2->p2->x, p3->x)) ;
	assert(egalDouble(s2->p2->y, p3->y)) ;

	// test de egalSegments
	printf("Test de egalSegments\n") ;
	assert(egalSegments(s1, creerSegment(p1, p2))) ;
	assert(egalSegments(s1, creerSegment(p2, p1))) ;
	assert(!egalSegments(s1, s2)) ;

	// test de translaterSegmentXY
	printf("Test de translaterSegmentXY\n") ;
	translaterSegmentXY(s1, 3.0, 4.0) ;
	assert(egalDouble(s1->p1->x, p1->x + 3.0)) ;
	assert(egalDouble(s1->p1->y, p1->y + 4.0)) ;
	assert(egalDouble(s1->p2->x, p2->x + 3.0)) ;
	assert(egalDouble(s1->p2->y, p2->y + 4.0)) ;

	translaterSegmentXY(s2, -2.0, 0.0) ;
	assert(egalDouble(s2->p1->x, p1->x - 2.0)) ;
	assert(egalDouble(s2->p1->y, p1->y)) ;
	assert(egalDouble(s2->p2->x, p3->x - 2.0)) ;
	assert(egalDouble(s2->p2->y, p3->y)) ;

	// test de translaterPointRT
	printf("Test de translaterSegmentRT\n") ;
	translaterSegmentRT(s1, 2.0, PI) ;
	assert(egalDouble(s1->p1->x, p1->x + 1.0)) ;
	assert(egalDouble(s1->p1->y, p1->y + 4.0)) ;
	assert(egalDouble(s1->p2->x, p2->x + 1.0)) ;
	assert(egalDouble(s1->p2->y, p2->y + 4.0)) ;

	translaterSegmentRT(s2, 1.0, 0.0) ;
	assert(egalDouble(s2->p1->x, p1->x - 1.0)) ;
	assert(egalDouble(s2->p1->y, p1->y)) ;
	assert(egalDouble(s2->p2->x, p3->x - 1.0)) ;
	assert(egalDouble(s2->p2->y, p3->y)) ;

	// test de rotationSegment
	printf("Test de rotationSegment\n") ;
	s6 = creerSegment(creerPointXY(1, 1), creerPointXY(2, 3)) ;
	rotationSegment(s6, PI / 2, creerPointXY(0, 0)) ;
	assert(egalSegments(s6, creerSegment(creerPointXY(-1, 1), creerPointXY(-3, 2)))) ;

	// test de chevauchement
	printf("Test de chevauchement\n") ;
	assert(chevauchement(0, 2, 1, 3)) ;
	assert(chevauchement(3, 1, 2, 0)) ;
	assert(chevauchement(3, 1, 0, 2)) ;
	assert(chevauchement(0, 3, 1, 2)) ;
	assert(chevauchement(1, 2, 0, 3)) ;
	assert(!chevauchement(0, 1, 2, 3)) ;
	assert(!chevauchement(3, 2, 0, 1)) ;
	assert(chevauchement(2, 2, 1, 3)) ;
	assert(chevauchement(2, 2, 3, 1)) ;
	assert(chevauchement(1, 2, 1.5, 1.5)) ;
	assert(chevauchement(2, 1, 1.5, 1.5)) ;
	assert(!chevauchement(1, 2, 2, 2)) ;
	assert(!chevauchement(2, 2, 2, 2)) ;
	assert(!chevauchement(1, 2, 2, 3)) ;
	assert(chevauchement(1, 3, 2, 3)) ;
	assert(chevauchement(3.0, 5.0, 2.0, 4.0)) ;
	assert(chevauchement(3.0, 5.0, 4.0, 2.0)) ;
	assert(chevauchement(3.0, 5.0, 2.0, 6.0)) ;
	assert(chevauchement(3.0, 5.0, 6.0, 2.0)) ;
	assert(chevauchement(6.0, 2.0, 3.0, 5.0)) ;
	assert(!chevauchement(0.0, 3.0, 4.0, 6.0)) ;
	assert(!chevauchement(0.0, 3.0, 3.0, 6.0)) ;
	assert(!chevauchement(3.0, 3.0, 3.0, 3.0)) ;

	// test de segmentToDroite
	printf("Test de segmentToDroite\n") ;
	s3 = creerSegment(p1, p3) ;
	d1 = segmentToDroite(s3) ;
	assert(d1->verticale == false) ;
	assert(egalDouble(d1->a, 1.0)) ;
	assert(egalDouble(d1->b, 0.0)) ;

	s4 = creerSegment(p2, p4) ;
	d2 = segmentToDroite(s4) ;
	assert(d2->verticale == false) ;
	assert(egalDouble(d2->a, -1.0)) ;
	assert(egalDouble(d2->b, 2.0)) ;
	
	//printf("p3 (%f, %f)\n", p3->x, p3->y) ;
	s5 = creerSegment(p2, p3) ;
	d3 = segmentToDroite(s5) ;
	//printf("d3 %d::%f::%f\n", d3->verticale, d3->a, d3->b) ;
	assert(d3->verticale == true) ;
	assert(egalDouble(d3->a, 0.0)) ;
	assert(egalDouble(d3->b, 2.0)) ;

	// test de droiteToSegment
	printf("Test de droiteToSegment\n") ;
	s1 = droiteToSegment(d1, 0.0, 3.0) ;
	assert(egalDouble(s1->p1->x, 0.0)) ;
	assert(egalDouble(s1->p1->y, 0.0)) ;
	assert(egalDouble(s1->p2->x, 3.0)) ;
	assert(egalDouble(s1->p2->y, 3.0)) ;

	s2 = droiteToSegment(d2, -20.0, 42.0) ;
	d1 = segmentToDroite(s2) ;
	assert(d1->verticale == d2->verticale) ;
	assert(egalDouble(d1->a, d2->a)) ;
	assert(egalDouble(d2->b, d2->b)) ;

	s3 = droiteToSegment(d3, 3.0, 5.0) ;
	assert(egalDouble(s3->p1->x, 2.0)) ;
	assert(egalDouble(s3->p1->y, 3.0)) ;
	assert(egalDouble(s3->p2->x, 2.0)) ;
	assert(egalDouble(s3->p2->y, 5.0)) ;

	// test de pointInSegment
	printf("Test de pointInSegment\n") ;
	s1 = creerSegment(p1, p3) ;

	p5 = creerPointXY(1.0, 1.0) ;
	assert(pointInSegment(p5, s1)) ;
	
	p5 = creerPointXY(2.0, 2.0) ;
	assert(pointInSegment(p5, s1)) ;

	p5 = creerPointXY(0.0, 0.0) ;
	assert(pointInSegment(p5, s1)) ;

	p5 = creerPointXY(0.0, 2.0) ;
	assert(!pointInSegment(p5, s1)) ;

	p5 = creerPointXY(-1.0, -1.0) ;
	assert(!pointInSegment(p5, s1)) ;

	// test de sontParalleles
	printf("Test de sontParalleles\n") ;
	s1 = creerSegment(p1, p2) ;
	s2 = creerSegment(p3, p4) ;
	d1 = segmentToDroite(s1) ;
	d2 = segmentToDroite(s2) ;
	assert(sontParalleles(d1, d2)) ;

	s1 = creerSegment(p1, p4) ;
	s2 = creerSegment(p2, p3) ;
	d1 = segmentToDroite(s1) ;
	d2 = segmentToDroite(s2) ;
	assert(sontParalleles(d1, d2)) ;

	s1 = creerSegment(p1, p3) ;
	s2 = creerSegment(p2, p4) ;
	d1 = segmentToDroite(s1) ;
	d2 = segmentToDroite(s2) ;
	assert(!sontParalleles(d1, d2)) ;

	// test de segmentInSegment
	printf("Test de segmentInSegment\n") ;
	p5 = creerPointXY(1.0, 1.0) ;

	s1 = creerSegment(p1, p3) ;
	s2 = creerSegment(p5, p2) ;
	assert(!segmentInSegment(s1, s2)) ;

	s2 = creerSegment(creerPointXY(0.25, 0.75), creerPointXY(0.75, 0.25)) ;
	assert(segmentInSegment(s1, s2)) ;

	s2 = creerSegment(p3, creerPointXY(4.0, 0.0)) ;
	assert(!segmentInSegment(s1, s2)) ;

	s2 = creerSegment(creerPointXY(-2.0, 4.0), creerPointXY(4.0, -2.0)) ;
	assert(segmentInSegment(s1, s2)) ;

	s2 = creerSegment(p5, creerPointXY(4.0, -2.0)) ;
	assert(!segmentInSegment(s1, s2)) ;

	s2 = creerSegment(creerPointXY(-2.0, 4.0), creerPointXY(0.75, 0.1)) ;
	assert(segmentInSegment(s1, s2)) ;

	s2 = creerSegment(creerPointXY(1.0, 5.0), creerPointXY(3.0, 1.0)) ;
	assert(!segmentInSegment(s1, s2)) ;

	s2 = creerSegment(creerPointXY(3.0, 2.0), creerPointXY(5.0, 0.0)) ;
	assert(!segmentInSegment(s1, s2)) ;
	
	return 0 ;
}
