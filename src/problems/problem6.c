/******************************************************************************
*                                                                             *
*                                                                             *
* The sum of the squares of the first ten natural numbers is,                 *
* 12 + 22 + ... + 102 = 385                                                   *
*                                                                             *
* The square of the sum of the first ten natural numbers is,                  *
* (1 + 2 + ... + 10)2 = 552 = 3025                                            *
*                                                                             *
* Hence the difference between the sum of the squares of the first ten        *
* natural numbers and the square of the sum is 3025 - 385 = 2640.             *
*                                                                             *
* Find the difference between the sum of the squares of the first one hundred *
* natural numbers and the square of the sum.                                  *
******************************************************************************/
/****************************************************************************** 
*                                  INCLUDES                                   * 
******************************************************************************/ 
#include "eulerProblems.h"                                                      
#include "eulerSolvers.h"

#include "simpleSeries.h"
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#define PROBLEM_6_MAGIC 100
/****************************************************************************** 
*                            FUNCTION DEFINITIONS                             * 
******************************************************************************/
/**                                                                             
* Solution for problem 6                                                        
**/                                                                             
struct eulerSol euler_prob6(void){
	struct eulerSol sol = {INTEGER};
	
	unsigned s1 = sumOf_firstN(PROBLEM_6_MAGIC);
	unsigned s2 = somOfN_firstSquares(PROBLEM_6_MAGIC);
	
	sol.val.i = s1*s1-s2;
	
	return sol;
}
