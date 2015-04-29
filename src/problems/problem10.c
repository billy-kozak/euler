/******************************************************************************
* The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.                       *
*                                                                             *
* Find the sum of all the primes below two million.                           *
******************************************************************************/
/****************************************************************************** 
*                                  INCLUDES                                   * 
******************************************************************************/ 
#include "eulerProblems.h"                                                      
#include "eulerSolvers.h"

#include "primeGeneration.h"
#include "w1_vect.h"

#include <stdint.h>
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#define PROBLEM10_MAGIC 2000000
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
static uint64_t addUnsignedVector(struct w1_vect* v){
	uint64_t sum = 0;
	struct w1_iter* itr = w1vect_initIter(v);
	unsigned* n;
	
	if(!itr){
		//memory error
		return 0;
	}
	
	while((n=w1vect_nextUnsigned(itr))!=NULL){
		sum += *n;
	}
	
	w1vect_freeIter(itr);
	
	return sum;
}
/****************************************************************************** 
*                            FUNCTION DEFINITIONS                             * 
******************************************************************************/
/**                                                                             
* Solution for problem 10                                                        
**/                                                                             
struct eulerSol euler_prob10(void){
	struct eulerSol sol = {U64};
	
	struct w1_vect* primes = primeGen_sieveOfEratosthenes(
			2,PROBLEM10_MAGIC+1
		);
	
	sol.val.u64 = addUnsignedVector(primes);
	
	w1vect_free(primes);
	
	return sol;
}
