/******************************************************************************
* If we list all the natural numbers below 10 that are multiples of 3 or 5,   *
* we get 3, 5, 6 and 9. The sum of these multiples is 23.                     *
*                                                                             *
* Find the sum of all the multiples of 3 or 5 below 1000.                     *
******************************************************************************/

/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "eulerProblems.h"
#include "eulerSolvers.h"
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
static unsigned sumOfN_Multiples(unsigned m,unsigned max);
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
* Sum of n multiples less than some max
**/
static unsigned sumOfN_Multiples(unsigned m,unsigned max){
	unsigned top = max - (max%m);
	
	return ((top+m)*(top))/(m*2);
}
/**
* Solution for problem 1
**/
struct eulerSol euler_prob1(void){
	struct eulerSol sol = {U64};
	
	sol.val.u64 = 
		sumOfN_Multiples(3,1000-1)+sumOfN_Multiples(5,1000-1)-
		sumOfN_Multiples(3*5,1000-1);
	
	return sol;
}