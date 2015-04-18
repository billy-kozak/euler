/******************************************************************************
* Implements functions to act on simple mathematical series                   *
*                                                                             *
* Ex: compute sum of first n positive integers                                *
******************************************************************************/
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "simpleSeries.h"
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
* Sum of n multiples less than some max
**/
unsigned sumOfN_Multiples(unsigned m,unsigned max){
	unsigned top = max - (max%m);
	return ((top+m)*(top))/(m*2);
}
/**
* Sum of first n positive integers
**/
unsigned sumOf_firstN(unsigned n){
	return ((n+1)*n)/(2);
}
/**
* Sum of first n squares (1+4+9+16...)
**/
unsigned somOfN_firstSquares(unsigned n){
	return n*(n+1)*(2*n+1)/6;
}