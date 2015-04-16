/******************************************************************************
* Implements generic algorithms relating to prime factorization               *
******************************************************************************/

/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "primeFactors.h"
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
* Slow, simple factorization method which is (very) light on memory
**/
uint64_t primeFactorLargest_trialDivision(uint64_t target){
	for(uint64_t n=(target/2); n>1; n--){
		
		if(!(target%n)){
			return primeFactorLargest_trialDivision(n);
		}
	}
	return target;
}