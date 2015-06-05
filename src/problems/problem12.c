/******************************************************************************
* The sequence of triangle numbers is generated by adding the natural         *
* numbers. So the 7th triangle number would be 1 + 2 + 3 + 4 + 5 + 6 + 7 =    *
* 28. The first ten terms would be:                                           *
*                                                                             *
* 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...                                    *
*                                                                             *
* Let us list the factors of the first seven triangle numbers:                *
*                                                                             *
*      1: 1                                                                   *
*      3: 1,3                                                                 *
*      6: 1,2,3,6                                                             *
*     10: 1,2,5,10                                                            *
*     15: 1,3,5,15                                                            *
*     21: 1,3,7,21                                                            *
*     28: 1,2,4,7,14,28                                                       *
*                                                                             *
* We can see that 28 is the first triangle number to have over five divisors. *
*                                                                             *
* What is the value of the first triangle number to have over five hundred    *
* divisors?                                                                   *
******************************************************************************/
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "eulerProblems.h"
#include "eulerSolvers.h"

#include "primeGeneration.h"
#include "simpleMath.h"

#include <assert.h>
#include <stdio.h>
/******************************************************************************
*                                    TYPES                                    *
******************************************************************************/
struct primeCount{
	unsigned primes;
	struct w1_vect* powers;
};
/******************************************************************************
*                                   DEINFES                                   *
******************************************************************************/
#define PROBLEM12_MAGIC 500
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
static struct primeCount countPrimeFactors(
		struct trialPrimeGen* gen, unsigned n,
		struct w1_vect* mem
	);
static unsigned divCount(unsigned n, unsigned b,unsigned d);
static unsigned factorsFromCounts(
		const struct primeCount* pc1,const struct primeCount* pc2
	);
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
*
*
* TODO - handle possible memory error
**/
static struct primeCount countPrimeFactors(
		struct trialPrimeGen* gen, unsigned n,
		struct w1_vect* mem
	){

	struct primeCount counts = {0,mem};
	unsigned root = gteSquareRoot(n);
	unsigned prime;
	unsigned pInd = 0;

	w1vect_reset(mem);

	if(!gen->v->len){
		prime = trailDivideGenNext(gen);
	}
	else{
		prime = w1vect_getIndUnsigned(gen->v,pInd);
	}

	do{
		pInd += 1;

		if(!(n%prime)){
			//note that we know that this won't overflow because
			//we are less than the square root of n
			unsigned power = prime*prime;
			unsigned powerCount = divCount(n,power,prime);
			counts.primes += 1;
			w1vect_appendUnsigned(counts.powers,powerCount);
		}

		if(pInd >= gen->v->len){
			prime = trailDivideGenNext(gen);
		}
		else{
			prime = w1vect_getIndUnsigned(gen->v,pInd);
		}

	}while(prime <= root);

	if(!counts.primes){
		//n is prime!
		//in a perfect world we would feed it back into our generator!
		counts.primes += 1;
	}

	return counts;
}
/**
*
**/
static unsigned divCount(unsigned n, unsigned b, unsigned d){
	unsigned count = 0;
	unsigned last = b;
	unsigned next = last;

	do{
		if(n%next){
			break;
		}

		count += 1;

		if(umul_overflow(last,d,&next)){
			//overflow occured
			return count;
		}

		last = next;
	}while(next <= n);

	return count;
}
/**
* This is wrong...
**/
static unsigned factorsFromCounts(
		const struct primeCount* pc1,const struct primeCount* pc2
	){

	unsigned c1 = 1<<(pc1->primes+pc2->primes);

	unsigned c2 = 0;

	unsigned levFact = c1>>1;

	//for first vector
	for(unsigned i = 0; i < pc1->powers->len; i++){
		unsigned powers = w1vect_getIndUnsigned(pc1->powers,i);

		for(unsigned n = 0; n < powers; n++){
			c2 += levFact;
		}
		levFact += (levFact>>1);
	}


	//for second vector
	for(unsigned i = 0; i < pc2->powers->len; i++){
		unsigned powers = w1vect_getIndUnsigned(pc2->powers,i);

		for(unsigned n = 0; n < powers; n++){
			c2 += levFact;
		}
		levFact += (levFact>>1);
	}

	return c1+c2;
}
/**
*
* TODO - handle possible memory errors
**/
static unsigned findTriangleDiv(unsigned limit){

	unsigned triN = 1;
	struct primeCount evenCount = {0,NULL};
	struct primeCount oddCount = {0,NULL};

	unsigned factors = 1;

	struct trialPrimeGen* gen = trialDivideGenInit();
	struct w1_vect* mem1 = w1vect_init(AUTO,UNSIGNED);
	struct w1_vect* mem2 = w1vect_init(AUTO,UNSIGNED);

	evenCount.powers = mem1;
	evenCount.powers = mem2;

	if(!gen){
		return 0;
	}

	while(factors < limit){

		triN += 1;
		oddCount = countPrimeFactors(gen,triN+1,mem1);
		factors = factorsFromCounts(&oddCount,&evenCount);

		if(factors >= limit){
			break;
		}

		triN +=1;
		evenCount = countPrimeFactors(gen,(triN+1)>>1,mem2);
		factors = factorsFromCounts(&oddCount,&evenCount);
	}

	trialDivideGenFree(gen);
	w1vect_free(mem1);
	w1vect_free(mem2);

	return ((triN+1)*triN)/2;
}
/**
* Solution for problem 12
**/
struct eulerSol euler_prob12(void){
	struct eulerSol sol = {UNSIGNED};

	sol.val.u = findTriangleDiv(7);

	return sol;
}
