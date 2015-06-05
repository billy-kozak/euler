/******************************************************************************
* Tests the w1_vect module                                                    *
******************************************************************************/
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "common/w1_vect.c"

//all other includes should come after the source file include!
#include "mySimpleTestFramework.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#define RAND_WR_COUNT (1024*1024)
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
static unsigned seedFromClock(void);
static bool mstf_test_intRandWR(enum w1_indexMode im,bool updateInd);
static bool mstf_test_intRandWR_iter(enum w1_indexMode im);
/******************************************************************************
*                                    TESTS                                    *
******************************************************************************/
/**
* Get "random" (i.e. not at all random) seed from system clock for srand
**/
static unsigned seedFromClock(void){
	unsigned seed;
	struct timespec spec;

	clock_gettime(CLOCK_REALTIME, &spec);
	seed = (spec.tv_sec)*1000 + (spec.tv_nsec)/1000000;

	return seed;
}
/**
* Tests writing random data to a w1_vect and reading it back
**/
static bool mstf_test_intRandWR(enum w1_indexMode im,bool updateInd){

	bool ret = true;
	struct w1_vect* v = w1vect_init(im,INTEGER);
	unsigned seed = seedFromClock();

	srand(seed);

	for(int i = 0; i < RAND_WR_COUNT; i++){
		w1vect_appendInteger(v,rand());
	}

	if(updateInd){
		w1vect_updateIndex(v);
	}

	srand(seed);
	for(int i = 0; i < RAND_WR_COUNT; i++){
		if(w1vect_getIndInteger(v,i) != rand()){
			ret = false;
			break;
		}
	}

	w1vect_free(v);

	return ret;
}
/**
* Tests writing random data to a w1_vect and reading it back though an iterator
**/
static bool mstf_test_intRandWR_iter(enum w1_indexMode im){

	bool ret = true;

	struct w1_vect* v = w1vect_init(im,INTEGER);
	struct w1_iter* itr = w1vect_initIter(v);
	unsigned seed = seedFromClock();

	srand(seed);
	for(int i = 0; i < RAND_WR_COUNT; i++){
		w1vect_appendInteger(v,rand());
	}

	srand(seed);
	for(int i = 0; i < RAND_WR_COUNT; i++){
		if(*w1vect_nextInteger(itr) != rand()){
			ret = false;
			break;
		}
	}

	w1vect_freeIter(itr);
	w1vect_free(v);

	return ret;
}
/**
*
**/
static bool mstf_test_resetWR(void){

	struct w1_vect* v = w1vect_init(AUTO,UNSIGNED);
	unsigned seed = seedFromClock();
	bool ret = true;

	srand(seed);
	for(int i = 0; i < RAND_WR_COUNT; i++){
		w1vect_appendUnsigned(v,rand());
	}
	srand(seed);
	for(int i = 0; i < RAND_WR_COUNT; i++){
		if(w1vect_getIndUnsigned(v,i) != rand()){
			ret = false;
			goto done;
			break;
		}
	}

	w1vect_reset(v);

	seed = seedFromClock();
	srand(seed);
	for(int i = 0; i < RAND_WR_COUNT; i++){
		w1vect_appendUnsigned(v,rand());
	}
	srand(seed);
	for(int i = 0; i < RAND_WR_COUNT; i++){
		if(w1vect_getIndUnsigned(v,i) != rand()){
			ret = false;
			goto done;
			break;
		}
	}

done:
	w1vect_free(v);
	return ret;
}

/**
* Test entry point
**/
int main(int argc, char** argv){

	MSTF_START();
		//tests go here
		MSTF_RUN(
				"Failed integer write readback with "
				"cache enabled",
				mstf_test_intRandWR(AUTO,false)
			);
		MSTF_RUN(
				"Failed integer write readback with "
				"cache in manual mode",
				mstf_test_intRandWR(MANUAL,false)
			);
		MSTF_RUN(
				"Failed integer write readback with "
				"cache disabled",
				mstf_test_intRandWR(OFF,false)
			);
		MSTF_RUN(
				"Failed integer write iterator readback with "
				"cache disabled",
				mstf_test_intRandWR_iter(OFF)
			);
		MSTF_RUN(
				"Failed integer write iterator readback with "
				"cache disabled",
				mstf_test_intRandWR_iter(AUTO)
			);
		MSTF_RUN(
				"Failed integer write readback with "
				"cache in manual mode and a cache update",
				mstf_test_intRandWR(MANUAL,true)
			);
		MSTF_RUN(
				"Failed reset vector write readback ",
				mstf_test_resetWR()
			);
	MSTF_END();

	return 0;
}