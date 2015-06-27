/******************************************************************************
* 215 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.            *
*                                                                             *
* What is the sum of the digits of the number 21000?                          *
******************************************************************************/
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "eulerProblems.h"
#include "eulerSolvers.h"

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#define UKB_WORDS 32

#define PROBLEM_16_MAGIC 1000
/******************************************************************************
*                                    TYPES                                    *
******************************************************************************/
struct uKB{
	uint32_t words[UKB_WORDS];
};

struct uKB_div32Ret{
	struct uKB   q;
	uint32_t     r;
};
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
static struct uKB_div32Ret udivMod_KBby32(struct uKB* n,uint32_t d);
static bool uKB_NonZero(struct uKB* a);
static unsigned sum_uKB_decDigits(struct uKB* n);
static unsigned sum_pow2_digits(unsigned e);
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
* Returns true if struct is not equal to zero
**/
static bool uKB_NonZero(struct uKB* a){
	uint32_t* words = a->words;
	for(int i = 0; i < UKB_WORDS; i++){
		if(words[i]){
			return true;
		}
	}

	return false;
}
/**
* Divides KB integer by a 32 bit number
**/
static struct uKB_div32Ret udivMod_KBby32(struct uKB* n,uint32_t d){

	struct uKB_div32Ret ret;
	struct uKB q = {{0}};
	uint64_t remain = 0;
	size_t typeSize = UKB_WORDS;

	for(int i = typeSize-1; i >= 0; i--){
		uint64_t next = (remain<<32)|(n->words[i]);
		q.words[i] = next/(uint64_t)d;
		remain = next%(uint64_t)d;
	}

	ret.r = remain;
	ret.q = q;

	return ret;
}
/**
* Sums digits (as expressed in decimal) of a KB sized integer
**/
static unsigned sum_uKB_decDigits(struct uKB* n){

	unsigned sum = 0;
	struct uKB_div32Ret acc;

	memcpy(&(acc.q),n,sizeof(acc.q));

	do{
		uint32_t digit;

		acc = udivMod_KBby32(&(acc.q),10);
		digit = acc.r;

		assert(digit < 10);

		sum += digit;
	}while(uKB_NonZero(&(acc.q)));

	return sum;
}
/**
* Sum digigs (as expressed in decimal) of 2^e
*
* takes numbers up to 2**1023
**/
static unsigned sum_pow2_digits(unsigned e){
	struct uKB n = {{0}};
	unsigned wordInd = e/32;
	unsigned bitInd  = e%32;

	if(e > 1023){
		return 0;
	}

	n.words[wordInd] = 1<<bitInd;

	return sum_uKB_decDigits(&n);
}
/**
* Solution for problem 16
**/
struct eulerSol euler_prob16(void){
	struct eulerSol sol = {U64};
	sol.val.u64 = sum_pow2_digits(PROBLEM_16_MAGIC);

	return sol;
}
