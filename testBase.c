
#include "includes.h"

bool testDouble(double a, double b) {
	return (a > b - EPSILON) && (a < b + EPSILON) ;
}
