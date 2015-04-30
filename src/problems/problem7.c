/******************************************************************************
* By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see  *
* that the 6th prime is 13.                                                   *
*                                                                             *
* What is the 10 001st prime number?                                          *
******************************************************************************/

/****************************************************************************** 
*                                  INCLUDES                                   * 
******************************************************************************/ 
#include "eulerProblems.h"                                                      
#include "eulerSolvers.h"

#include "primeFactors.h"
#include "primeGeneration.h"
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#define PROBLEM_7_MAGIC 10000
/****************************************************************************** 
*                            FUNCTION DEFINITIONS                             * 
******************************************************************************/
/**                                                                             
* Solution for problem 7                                                        
**/                                                                             
struct eulerSol euler_prob7(void){
	struct eulerSol sol = {U64};

	sol.val.u64 = primeN_trialDivision(PROBLEM_7_MAGIC);
	
	return sol;
}
