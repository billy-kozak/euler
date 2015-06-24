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
static uint64_t collatzNext(uint64_t term);
static int growMap(struct collatzInfo** mPtr,size_t sNew, size_t sOld);
static void collatzAdd(
		struct collatzInfo* map,uint64_t el,uint64_t head,
		uint64_t pos
	);
static uint64_t collatzDistance(
		struct collatzInfo* map,uint64_t* collatzHeads, uint64_t el
	);
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
* Get the next collatz number after the given term
**/
static uint64_t collatzNext(uint64_t term){
	if(term&0x01){
		return 3*term+1;
	}

	return term>>1;
}
/**
* Get the distance to '1' from the given element in the collatz map
**/
static uint64_t collatzDistance(
		struct collatzInfo* map,uint64_t* collatzHeads, uint64_t el
	){

	uint64_t seqSize = collatzHeads[map[el].seqHead];
	uint64_t pos = map[el].seqPosition;

	if(!seqSize){
		//error - we've hit a loop (but more likley a bug...)!
		return 0;
	}

	return seqSize - pos;
}
/**
* Add value to collatz map
**/
static void collatzAdd(
		struct collatzInfo* map,uint64_t el,uint64_t head,
		uint64_t pos
	){
	map[el].seqHead = head;
	map[el].seqPosition = pos;
}
/**
* Grows map to fit the new size, makes sure that new memory is zeroed
**/
static int growMap(struct collatzInfo** mPtr,size_t sNew, size_t sOld){
	struct collatzInfo* tmp = realloc(*mPtr,sNew*sizeof(*tmp));
	if(!tmp){
		return 1;
	}
	*mPtr = tmp;
	memset(tmp+sOld,0,(sNew-sOld));
	return 0;
}
/**
* Finds the longest collatz chain starting on any num <= top
**/
static unsigned longestCollatz(unsigned top){

	uint64_t maxSize = 0;
	uint64_t head = top;
	size_t mapSize = 4*(top+1);
	struct collatzInfo* collatzMap;
	uint64_t* collatzHeads;

	if(head == 1){
		return 1;
	}

	collatzHeads = calloc(sizeof(*collatzHeads),top+1);
	collatzMap = calloc(mapSize,sizeof(*collatzMap));

	if(!collatzMap || !collatzHeads){
		goto fail;
	}

	while(head){
		uint64_t next = head;
		uint64_t count = 1;

		collatzMap[head].seqPosition = 0;
		collatzMap[head].seqHead = head;

		do{
			next = collatzNext(next);

			if(next >= mapSize){
				if(growMap(&collatzMap,next+1,mapSize)){
					goto fail;
				}
				mapSize = next+1;
			}

			if(!collatzMap[next].seqHead){
				collatzAdd(collatzMap,next,head,count);
				count+=1;
			}
			else{
				uint64_t partial = collatzDistance(
						collatzMap,collatzHeads,next
					);

				if(!partial){
					// we actually seem to have a loop!
					goto fail;
				}
				count += partial;
				break;
			}
		}while(next != 1);

		collatzHeads[head] = count;
		maxSize = (maxSize < count) ? count : maxSize;
		for(head = head-1; collatzHeads[head]; head--);
	}


	free(collatzMap);
	free(collatzHeads);
	return maxSize;
fail:
	free(collatzMap);
	free(collatzHeads);
	return 0;
}
/**
* Solution for problem 14
**/
struct eulerSol euler_prob14(void){
	struct eulerSol sol = {UNSIGNED};
	sol.val.u = longestCollatz(PROBLEM14_MAGIC);
	return sol;
}
