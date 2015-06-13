/******************************************************************************
* Implements a 256 bit integer type                                           *
******************************************************************************/
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "type256.h"
#include <stdbool.h>
#include <stdio.h>
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#define MASK_32LOW  (0x00000000FFFFFFFFULL)
#define MASK_32HIGH (0xFFFFFFFF00000000ULL)

#define type256dbgPrint(a) \
	printf( \
		"0x%016lx%016lx%016lx%016lx", \
		(a)->words.w64[3],(a)->words.w64[2], \
		(a)->words.w64[1],(a)->words.w64[0] \
	)
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
static void type256bitSet(struct unsigned256* a, unsigned n, bool val);
static bool type256bitGet(struct unsigned256* a, unsigned n);
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
* Sets bit to some value
**/
static void type256bitSet(struct unsigned256* a, unsigned n, bool val){
	if(val){
		a->words.w64[n>>6] |= 1<<(n&0x3F);
	}
	else{
		a->words.w64[n>>6] &= ~(1<<(n&0x3F));
	}
}
/**
* Returns value of nth bit
**/
static bool type256bitGet(struct unsigned256* a, unsigned n){
	unsigned ind = (n>>6);

	return !! ( a->words.w64[ind]&(1ULL<<(n&0x3F)) );
}
/**
* Compares numbers
*
* returns 0 if equal, 1 if a>b and -1 if b>a
**/
int type256cmp(struct unsigned256* a,struct unsigned256* b){
	for( int i = 3; i >= 0; i-- ){
		if(a->words.w64[i] > b->words.w64[i]){
			return 1;
		}
		else if(a->words.w64[i] < b->words.w64[i]){
			return -1;
		}
	}

	return 0;
}
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

	uint64_t spillShift = 8*sizeof(uint64_t)-n;
	uint64_t spillMask = (1ULL<<n)-1ULL;
	uint64_t spill = 0;

	for(int i = 3; i >= 0; i--){
		y.words.w64[i] = (a->words.w64[i]>>n) | spill;
		spill = ((a->words.w64[i])&spillMask)<<(spillShift);
	}

	return y;
}
/**
* Pure C implementation of right shift
**/
struct unsigned256 _c_lshift256(struct unsigned256* a, unsigned n){
	struct unsigned256 y = {{{0}}};

	uint64_t spillShift = 8*sizeof(uint64_t)-n;
	uint64_t spillMask = ~((1ULL<<(spillShift))-1ULL);
	uint64_t spill = 0;

	for(int i = 0; i < 4; i++){
		y.words.w64[i] = (a->words.w64[i]<<n) | spill;
		spill = ((a->words.w64[i])&spillMask)>>(spillShift);
	}

	return y;
}
/**
* Pure C imlementation of unsigned division
**/
struct unsigned256 _c_udiv256(struct unsigned256* n, struct unsigned256* d){
	struct unsigned256 q = {{{0}}};
	struct unsigned256 r = {{{0}}};

	for(int i = 255; i >= 0; i--){
		r = _c_lshift256(&r,1);

		type256bitSet(&r,0,type256bitGet(n,i));

		if(type256cmp(&r,d) >= 0){
			r = usub256(&r,d);
			type256bitSet(&q,i,1);
		}
	}

	return q;
}