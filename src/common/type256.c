/******************************************************************************
* Implements a 256 bit integer type                                           *
******************************************************************************/
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "type256.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
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
static void type256bitSet(struct u256* a, unsigned n, bool val);
static bool type256bitGet(struct u256* a, unsigned n);
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
* Sets bit to some value
**/
static void type256bitSet(struct u256* a, unsigned n, bool val){
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
static bool type256bitGet(struct u256* a, unsigned n){
	unsigned ind = (n>>6);

	return !! ( a->words.w64[ind]&(1ULL<<(n&0x3F)) );
}
/**
* Makes a 256 bit type from individual 64 bit words
**/
struct u256 build256(uint64_t a,uint64_t b,uint64_t c,uint64_t d){
	struct u256 y;
	y.words.w64[3] = a;
	y.words.w64[2] = b;
	y.words.w64[1] = c;
	y.words.w64[0] = d;
	return y;
}
/**
* Compares numbers
*
* returns 0 if equal, 1 if a>b and -1 if b>a
**/
int ucmp256(struct u256* a,struct u256* b){
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
struct u256 _c_uadd256(struct u256* a, struct u256* b){

	struct u256 y;
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
struct u256 _c_usub256(struct u256* a, struct u256* b){

	struct u256 y;
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
struct u256 _c_umul256(struct u256* a, struct u256* b){

	struct u256 y = {{{0}}};

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
struct u256 _c_rshift256(struct u256* a, unsigned n){
	struct u256 y = {{{0}}};

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
struct u256 _c_lshift256(struct u256* a, unsigned n){
	struct u256 y = {{{0}}};

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
struct u256 _c_udiv256(struct u256* n, struct u256* d){
	struct u256 q = {{{0}}};
	struct u256 r = {{{0}}};

	for(int i = 255; i >= 0; i--){
		r = _c_lshift256(&r,1);

		type256bitSet(&r,0,type256bitGet(n,i));

		if(ucmp256(&r,d) >= 0){
			r = usub256(&r,d);
			type256bitSet(&q,i,1);
		}
	}

	return q;
}
/**
* Converts a string to 256 bit num
**/
int strToU256(const char*nptr,char** endptr,struct u256* y){

	struct u256 output = {{{0}}};
	struct u256 tenPow = build256(0,0,0,1);
	int firstD;
	int lastD;

	for(firstD = 0; isspace(nptr[firstD]); firstD++);
	if(!nptr[firstD]){
		//error, string is invalid
		return 1;
	}

	if(!isdigit(firstD)){
		//error, string is invalid
		return 1;
	}

	for(lastD = firstD; isdigit(nptr[lastD+1]); lastD++);
	if(nptr[lastD+1] && !isspace(nptr[lastD+1])){
		//error, string is invalid
		return 1;
	}

	memset(y,0,sizeof(*y));

	for(int i = lastD; i >= firstD; i--){
		struct u256 digit = build256(0,0,0,nptr[i]-'0');
		struct u256 digVal = umul256(&tenPow,&digit);

		output = uadd256(&output,&digVal);
	}

	*endptr = (char*)(&nptr[lastD+1]);
	memcpy(y,&output,sizeof(output));

	return 0;
}