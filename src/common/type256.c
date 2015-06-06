/******************************************************************************
* Implements a 256 bit integer type                                           *
******************************************************************************/
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "type256.h"
#include <stdbool.h>
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
* Pure C implementation of 256 bit type unsigned addition
**/
struct unsigned256 _c_uadd256(struct unsigned256* a, struct unsigned256* b){

	struct unsigned256 y;
	uint64_t carry = 0;

	for(int i = 0; i < 4; i++){
		y.words[i] = a->words[i]+b->words[i]+carry;
		carry = (y.words[i] < a->words[i]);
	}

	return y;
}
/**
*
**/
struct unsigned256 _c_umul256(struct unsigned256* a, struct unsigned256* b){
	struct unsigned256 y = {{0}};

	for(int i = 0; i < 4; i++){
		//uint64_t carry = 0;

		for(int n = 0; n < 4; n++){
		}
	}

	return y;
}