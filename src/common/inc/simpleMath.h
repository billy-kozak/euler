#ifndef _SIMPLE_MATH_H_
#define _SIMPLE_MATH_H_
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include <math.h>
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
#endif //_SIMPLE_MATH_H