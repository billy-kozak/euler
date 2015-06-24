/******************************************************************************
* The following iterative sequence is defined for the set of positive         *
* integers:                                                                   *
*                                                                             *
* n -> n/2 (n is even)                                                        *
* n -> 3n + 1 (n is odd)                                                      *
*                                                                             *
* Using the rule above and starting with 13, we generate the following        *
* sequence:                                                                   *
* 13 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1                         *
*                                                                             *
* It can be seen that this sequence (starting at 13 and finishing at 1)       *
* contains 10 terms. Although it has not been proved yet (Collatz Problem),   *
* it is thought that all starting numbers finish at 1.                        *
*                                                                             *
* Which starting number, under one million, produces the longest chain?       *
*                                                                             *
* NOTE: Once the chain starts the terms are allowed to go above one million.  *
******************************************************************************/
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "eulerProblems.h"
#include "eulerSolvers.h"
#include "simpleMath.h"

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
/******************************************************************************
*                                    TYPES                                    *
******************************************************************************/
struct collatzInfo{
	// zero only when unintilized
	unsigned seqHead;
	uint64_t seqPosition;
};
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#define PROBLEM14_MAGIC (1000000-1)
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
static unsigned longestCollatz(unsigned top);
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
* COunts length of collatz sequence which starts with the given term
**/
static uint64_t collatzLen(uint64_t term){
	uint64_t count = 1;
	uint64_t next = term;

	while(next != 1){
		int tz = count_tzll(next);
		if(tz){
			count += tz;
			next = next>>tz;
		}
		else{
			count += 1;
			next = next*3+1;
		}
	}

	return count;
}
/**
* Finds the longest collatz chain starting on any num <= top
**/
static unsigned longestCollatz(unsigned top){

	uint64_t maxSize = 0;
	uint64_t head = top;

	while(head){
		uint64_t count = collatzLen(head);
		maxSize = (maxSize < count) ? count : maxSize;

		head -=1;
	}

	return maxSize;
}
/**
* Solution for problem 14
**/
struct eulerSol euler_prob14(void){
	struct eulerSol sol = {UNSIGNED};
	sol.val.u = longestCollatz(PROBLEM14_MAGIC);
	return sol;
}
