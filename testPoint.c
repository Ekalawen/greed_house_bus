
#include "includes.h"

int main ()
{
	double x, y, r, t ;
	Point *p1, *p2, *p3, *p4 ;
	Point *p, *t1, *t2 ;
	Point *p_rot, *centre ;

	// test de creerPointXY
	printf("Test de creerPointXY\n") ;
	p1 = creerPointXY(1.0, 0.0) ;
	assert(egalDouble(p1->x, 1.0)) ;
	assert(egalDouble(p1->y, 0.0)) ;

	p2 = creerPointXY(-2.0, 3.0) ;
	assert(egalDouble(p2->x, -2.0)) ;
	assert(egalDouble(p2->y, 3.0)) ;

	// test de creerPointRT
	printf("Test de creerPointRT\n") ;
	p3 = creerPointRT(1.0, 0.0) ;
	assert(egalDouble(p3->x, 1.0)) ;
	assert(egalDouble(p3->y, 0.0)) ;

	p4 = creerPointRT(2.0, PI / 2) ;
	assert(egalDouble(p4->x, 0.0)) ;
	assert(egalDouble(p4->y, 2.0)) ;

	// test de egalPoints
	printf("Test de egalPoints\n") ;
	assert(egalPoints(p1, creerPointXY(1.0, 0.0))) ;
	assert(!egalPoints(p2, p3)) ;

	// test de translaterPointXY
	printf("Test de translaterPointXY\n") ;
	translaterPointXY(p1, 3.0, -4.0) ;
	assert(egalDouble(p1->x, 4.0)) ;
	assert(egalDouble(p1->y, -4.0)) ;

	// test de translaterPointRT
	printf("Test de translaterPointRT\n") ;
	translaterPointRT(p3, 2.0, PI) ;
	assert(egalDouble(p3->x, -1.0)) ;
	assert(egalDouble(p3->y, 0.0)) ;

	// test de rotationPoint
	printf("Test de rotationPoint\n") ;
	p_rot = creerPointXY(1.0, 2.0) ;
	centre = creerPointXY(3.0, 1.0) ;
	rotationPoint(p_rot, -PI / 2.0, centre) ;
	assert(egalDouble(p_rot->x, 4.0)) ;
	assert(egalDouble(p_rot->y, 3)) ;

	p_rot = creerPointXY(1, 1) ;
	centre = creerPointXY(-1, -1) ;
	rotationPoint(p_rot, PI, centre) ;
	assert(egalDouble(p_rot->x, -3)) ;
	assert(egalDouble(p_rot->y, -3)) ;

	p_rot = creerPointXY(2, 0) ;
	centre = creerPointXY(1, -1) ;
	rotationPoint(p_rot, PI / 4, centre) ;
	assert(egalDouble(p_rot->x, 1)) ;
	assert(egalDouble(p_rot->y, sqrt(2) - 1)) ;

	p_rot = creerPointXY(34.15, 80.99) ; 
	centre = creerPointXY(809, 9091.98) ;
	rotationPoint(p_rot, 2*PI, centre) ;
	assert(egalDouble(p_rot->x, 34.15)) ;
	assert(egalDouble(p_rot->y, 80.99)) ;
	rotationPoint(p_rot, 0, centre) ;
	assert(egalDouble(p_rot->x, 34.15)) ;
	assert(egalDouble(p_rot->y, 80.99)) ;

	// test de XYtoRT
	printf("Test de XYtoRT\n") ;
	XYtoRT(2.0, 2.0, &r, &t) ;
	assert(egalDouble(r, sqrt(8.0))) ;
	assert(egalDouble(t, PI / 4)) ;

	XYtoRT(0.0, 0.0, &r, &t) ;
	assert(egalDouble(r, 0.0)) ;
	assert(egalDouble(t, 0.0)) ;

	XYtoRT(-sqrt(2)/2, sqrt(2)/2, &r, &t) ;
	assert(egalDouble(r, 1.)) ;
	assert(egalDouble(t, 3*PI / 4)) ;

	// test de RTtoXY
	printf("Test de RTtoXY\n") ;
	RTtoXY(2., PI / 2, &x, &y) ;
	assert(egalDouble(x, 0.0)) ;
	assert(egalDouble(y, 2.0)) ;

	RTtoXY(0.0, 0.0, &x, &y) ;
	assert(egalDouble(x, 0.0)) ;
	assert(egalDouble(y, 0.0)) ;

	RTtoXY(1.0, 5*PI / 4, &x, &y) ;
	assert(egalDouble(x, -sqrt(2)/2)) ;
	assert(egalDouble(y, -sqrt(2)/2)) ;

	// test de getRT
	printf("Test de getRT\n") ;
	getRT(p1,&r, &t) ;
	assert(egalDouble(r, sqrt(32.0))) ;
	assert(egalDouble(t, 7*PI/4)) ;

	getRT(p3, &r, &t) ;
	assert(egalDouble(r, 1.0)) ;
	assert(egalDouble(t, PI)) ;

	// test de pointInTrancheLarge
	printf("Test de pointInTrancheLarge\n") ;
	p = creerPointXY(3.0, 3.0) ;
	t1 = creerPointXY(2.0, 3.0) ;
	t2 = creerPointXY(4.0, 3.0) ;
	assert(pointInTrancheLarge(p, t1, t2)) ;
	
	translaterPointXY(p, 1.0, 120.0) ;
	assert(pointInTrancheLarge(p, t1, t2)) ;

	translaterPointXY(p, 0.1, 1000.0) ;
	assert(!pointInTrancheLarge(p, t1, t2)) ;


	// test de pointInTrancheStrict
	printf("Test de pointInTrancheStrict\n") ;
	translaterPointXY(p, -1.1, -1120.0) ;
	assert(pointInTrancheStrict(p, t1, t2)) ;
	
	translaterPointXY(p, 1.0, 120.0) ;
	if (pointInTrancheStrict(p, t1, t2) == 1) {
		printf("pointInTrancheStrict(p, t1, t2) est vrai\n") ;}
	assert(!pointInTrancheStrict(p, t1, t2)) ;

	translaterPointXY(p, 0.1, 1000.0) ;
	assert(!pointInTrancheStrict(p, t1, t2)) ;

	return 0 ;
}
