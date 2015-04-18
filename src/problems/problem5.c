/******************************************************************************
* 2520 is the smallest number that can be divided by each of the numbers from *
* 1 to 10 without any remainder.                                              *
*                                                                             *
* What is the smallest positive number that is evenly divisible by all of the *
* numbers from 1 to 20?                                                       *
*                                                                             *
******************************************************************************/

/****************************************************************************** 
*                                  INCLUDES                                   * 
******************************************************************************/ 
#include "eulerProblems.h"                                                      
#include "eulerSolvers.h"
#include "primeFactors.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#define PROBLEM_5_MAGIC 20
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
static unsigned lcm_firstN(unsigned n);
/****************************************************************************** 
*                            FUNCTION DEFINITIONS                             * 
******************************************************************************/
/**
* Gets lowest common multiple of first n positive integers
**/
static unsigned lcm_firstN(unsigned n){
	
	unsigned lcm = 1;
	
	for(unsigned x = 2; x <= n ; x++){
		if(isPrime_trialDivision(x)){
			unsigned k = x;
			unsigned next = k*x;
			
			while(next <= n){
				k = next;
				next*= x;
			}
			lcm *= k;
		}
	}
	
	return lcm;
}
/**                                                                             
* Solution for problem 5                                                        
**/                                                                             
struct eulerSol euler_prob5(void){
	struct eulerSol sol = {UNSIGNED};
	
	sol.val.u = lcm_firstN(PROBLEM_5_MAGIC);
	
	return sol;
}
