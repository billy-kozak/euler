/******************************************************************************
* Implemements functions relating to prime number generation                  *
******************************************************************************/
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "primeGeneration.h"
#include "w1_vect.h"
#include "simpleMath.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#define BITFIELD_SET(bf,n) bf[n>>3] |= (1<<(n&0x07))
#define BITFIELD_CHECK(bf,n) (bf[n>>3]&(1<<(n&0x07)))
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
static bool trialDivideVect(struct w1_vect* v,struct w1_iter* itr,unsigned n);
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
	struct w1_vect* primes = w1vect_init(AUTO,UNSIGNED);
	unsigned n = bot;

	if(!bitField || !primes){
		w1vect_free(primes);
		free(bitField);
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
/**
* Find nth prime by trial division
**/
unsigned primeN_trialDivision(unsigned n){
	struct w1_vect* primes = NULL;
	struct w1_iter* itr = NULL;
	unsigned count = 1;
	unsigned last = 3;

	if(n <= 1){
		return 2;
	}

	primes = w1vect_init(AUTO,UNSIGNED);
	if(!primes){
		goto fail;
	}
	itr = w1vect_initIter(primes);
	if(!itr){
		goto fail;
	}

	while(count < n){

		w1vect_appendUnsigned(primes,last);

		do{
			last += 2;
		}while(!trialDivideVect(primes,itr,last));

		count++;
	}

	w1vect_free(primes);
	w1vect_freeIter(itr);

	return last;

	fail:
	w1vect_free(primes);
	w1vect_freeIter(itr);
	return 0;
}
/**
* Returns next greatest prime after next
*
* maintains list of all known primes in gen and uses it to find the next prime
* number by trial division. The vector in gen can be used as a list of all
* primes up to n.
*
* Args:
* gen - structure containing state of the generator
*
* Returns:
* next prime number after last (first number is 2). Will return 0 on memory
* error.
**/
unsigned trailDivideGenNext(struct trialPrimeGen* gen){

	unsigned next;

	if(!gen->v->len){
		if(w1vect_appendUnsigned(gen->v,2)){
			goto memFail;
		}
		gen->last = 2;
		return 2;
	}
	else if(gen->v->len == 1){
		if(w1vect_appendUnsigned(gen->v,3)){
			goto memFail;
		}
		gen->last = 3;
		return 3;
	}

	for(next = gen->last+2;!trialDivideVect(gen->v,gen->itr,next);next+=2);

	if(w1vect_appendUnsigned(gen->v,next)){
		goto memFail;
	}

	gen->last = next;

	return next;

	memFail:
		trialDivideGenFree(gen);
		return 0;
}
/**
* Initilizes structure for generating prime numbers
**/
struct trialPrimeGen* trialDivideGenInit(void){
	struct trialPrimeGen* gen = calloc(sizeof(*gen),1);
	if(!gen){
		goto fail;
	}

	gen->v = w1vect_init(AUTO,UNSIGNED);
	if(!gen->v){
		goto fail;
	}

	gen->itr = w1vect_initIter(gen->v);
	if(!gen->itr){
		goto fail;
	}

	return gen;

	fail:
		trialDivideGenFree(gen);
		return NULL;
}
/**
* Frees trial divide generator memory
**/
void trialDivideGenFree(struct trialPrimeGen* gen){

	if(!gen){
		return;
	}

	w1vect_free(gen->v);
	w1vect_freeIter(gen->itr);
	free(gen);
}
/**
* Test if prime by dividing n from list of primes
*
* given iterator must have been initilized (allocated) and will be modified
* by this routine
**/
static bool trialDivideVect(struct w1_vect* v,struct w1_iter* itr,unsigned n){
	unsigned *next;
	unsigned root = gteSquareRoot(n);

	w1vect_resetIter(itr);

	while( (next = w1vect_nextUnsigned(itr)) ){

		if(*next > root){
			break;
		}
		else if( !(n%(*next)) ){
			return false;
		}
	}
	return true;
}
