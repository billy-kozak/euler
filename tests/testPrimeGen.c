/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "common/primeGeneration.c"

//directly include dependencies also
#include "common/w1_vect.c"

//all other includes should come after the source file include!
#include "mySimpleTestFramework.h"

#include <stdio.h>
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
static unsigned nthPrime_byTrialDivideGen(unsigned n);
/******************************************************************************
*                                    TESTS                                    *
******************************************************************************/
/**
* Uses trial divide gen functions to get nth prime
**/
static unsigned nthPrime_byTrialDivideGen(unsigned n){
	struct trialPrimeGen* gen = trialDivideGenInit();
	unsigned prime = 0;

	for(unsigned i = 0; i < n; i++){
		prime = tailDivideGenNext(gen);
	}

	trialDivideGenFree(gen);
	return prime;
}
/**
* Test entry point
**/
int main(int argc, char** argv){
	 MSTF_START();
	 	MSTF_RUN(
	 			"failed p1 == 2",
	 			nthPrime_byTrialDivideGen(1)==2
	 		);
	 	MSTF_RUN(
	 			"failed p24 == 89",
	 			nthPrime_byTrialDivideGen(24)==89
	 		);
	 	MSTF_RUN(
	 			"failed p200 == 1223",
	 			nthPrime_byTrialDivideGen(200)==1223
	 		);
	 	MSTF_RUN(
	 			"failed p433 == 3019",
	 			nthPrime_byTrialDivideGen(433)==3019
	 		);

	 MSTF_END();

	 return 0;
}