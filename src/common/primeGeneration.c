/******************************************************************************
* Implemements functions relating to prime number generation                  *
******************************************************************************/
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "primeGeneration.h"
#include "w1_vect.h"
#include <stdint.h>
#include <stdio.h>
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#define BITFIELD_SET(bf,n) bf[n>>3] |= (1<<(n&0x07))
#define BITFIELD_CHECK(bf,n) (bf[n>>3]&(1<<(n&0x07)))
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
* Run sieve of eratosthenes algorithm to generate primes
*
* Args:
* top - value at which to stop looking for primes (i.e. will find primes less
* 	than top)
* bot - prime number at which to start counting, will be included in the output
*
* Returns:
* A w1 vector of prime numbers (which must be deallocated)
**/
struct w1_vect* primeGen_sieveOfEratosthenes(unsigned bot, unsigned top){
	
	size_t nBytes = top/8+(top%8?1:0);
	uint8_t* bitField = calloc(nBytes,1);
	struct w1_vect* primes = w1vect_init(AUTO,0,UNSIGNED);
	unsigned n = bot;
	
	if(!bitField || !primes){
		free(bitField);
		free(primes);
		return NULL;
	}
	
	while(n < top){
		w1vect_appendUnsigned(primes,n);
		
		//note that i=n*n is allowed by the algorithm but that this
		//could result in overflow.
		//leave as n+n until we have efficient overflow detection
		for(unsigned i = n+n; i < top; i += n){
			BITFIELD_SET(bitField,i);
		}
		
		for(n = (n+1); BITFIELD_CHECK(bitField,n) && n<top; n++);
	}
	
	free(bitField);
	return primes;
}
