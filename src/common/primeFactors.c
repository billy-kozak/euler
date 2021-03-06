/******************************************************************************
* Implements generic algorithms relating to prime factorization               *
******************************************************************************/

/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "primeFactors.h"

#include <math.h>
#include <stdbool.h>
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
* Slow, simple factorization method which is light on memory
**/
uint64_t primeFactorLargest_trialDivision(uint64_t target){
	uint64_t sr = (uint64_t)sqrt(target);
	
	if(target <= 2){
		return target;
	}
	
	//not sure if this bit is really necessarry...
	//I don't totally grasp the nuances of the uint64 to double to uint64
	//conversion but I believe it may be possible that the squareoot
	//can be wrong without this.
	while( (sr*sr) < target){
		sr++;
	}
	
	uint64_t c1;
	uint64_t c2;
	
	for(uint64_t n=sr; n>1; n--){
		
		if(!(target%n)){
			c1 = primeFactorLargest_trialDivision(n);
			c2 = primeFactorLargest_trialDivision(target/c1);
			if(c2 > c1){
				//c2 is prime
				return c2;
			}
			else{
				return c1;
			}
		}
	}
	return target;
}
/**
* Test if value is prime by trail division
**/
bool isPrime_trialDivision(unsigned n){
	for(unsigned k = 2; k < n; k++){
		if( !(n%k) ){
			return false;
		}
	}
	
	return true;
}