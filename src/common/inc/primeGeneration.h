#ifndef _PRIME_GENERATION_H_
#define _PRIME_GENERATION_H_
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "w1_vect.h"
/******************************************************************************
*                                    TYPES                                    *
******************************************************************************/
struct trialPrimeGen{
	struct w1_vect* v;
	struct w1_iter* itr;
	unsigned last;
};
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
struct w1_vect* primeGen_sieveOfEratosthenes(unsigned bot, unsigned top);
unsigned primeN_trialDivision(unsigned n);
struct trialPrimeGen* trialDivideGenInit(void);
unsigned trailDivideGenNext(struct trialPrimeGen* gen);
void trialDivideGenFree(struct trialPrimeGen* gen);
#endif //_PRIME_GENERATION_H_