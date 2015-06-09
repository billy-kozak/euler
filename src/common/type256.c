/******************************************************************************
* Implements a 256 bit integer type                                           *
******************************************************************************/
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "type256.h"
#include <stdbool.h>
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#define MASK_32LOW  (0x00000000FFFFFFFFULL)
#define MASK_32HIGH (0xFFFFFFFF00000000ULL)
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
		y.words.w64[i] = a->words.w64[i]+b->words.w64[i]+carry;
		carry = (y.words.w64[i] < a->words.w64[i]);
	}

	return y;
}
/**
* Pure C implementation of 256 bit type unsigned subtraction
**/
struct unsigned256 _c_usub256(struct unsigned256* a, struct unsigned256* b){

	struct unsigned256 y;
	uint64_t carry = 0;

	for(int i = 0; i < 4; i++){
		y.words.w64[i] = a->words.w64[i]-b->words.w64[i]-carry;
		carry = (a->words.w64[i] < b->words.w64[i]);
	}

	return y;
}
/**
* Pure C implementation of 256 bit unsigned multiply
**/
struct unsigned256 _c_umul256(struct unsigned256* a, struct unsigned256* b){

	struct unsigned256 y = {{{0}}};

	for(int i = 0; i < 8; i++){
		uint64_t carry = 0;
		uint64_t bWord = b->words.w32[i];

		for(int n = 0; n < 8-i; n++){
			uint64_t aWord = a->words.w32[n];
			uint64_t tmp  = (aWord*bWord);
			tmp += carry+(uint64_t)y.words.w32[n+i];

			y.words.w32[n+i] = (tmp&MASK_32LOW);
			carry = (tmp&MASK_32HIGH)>>32;
		}
	}

	return y;
}
/**
* Pure C implementation of right shift
**/
struct unsigned256 _c_rshift256(struct unsigned256* a, unsigned n){
	struct unsigned256 y = {{{0}}};

	uint64_t spillMask = (1<<n)-1;
	uint64_t spill = 0;

	for(int i = 0; i < 4; i++){
		y.words.w64[i] = (a->words.w64[i]>>n) | spill;
		spill = ((a->words.w64[i])&spillMask)<<(8*sizeof(spill)-1);
	}

	return y;
}