#ifndef _SIMPLE_MATH_H_
#define _SIMPLE_MATH_H_
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include <math.h>
#include <stdbool.h>

/******************************************************************************
*                                   MACROS                                    *
******************************************************************************/
/******************************************************************************
*                              INLINE FUNCTIONS                               *
******************************************************************************/
/**
* Returns a number which is greater than or equal to sqrt of n
*
* Tries to be close to the actual sqrt
**/
static inline unsigned gteSquareRoot(unsigned n){
	unsigned root = (unsigned)ceil(sqrt((double)n));

	while( (root*root) < n){
		root += 1;
	}

	return root;
}
/**
* Slow method of detecting multiply overflow
**/
static inline bool umul_overflow(unsigned a, unsigned b,unsigned* res){
	*res = a*b;
	return (a != 0 && *res / a != b);
}
#endif //_SIMPLE_MATH_H