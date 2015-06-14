/******************************************************************************
* Implements a 256 bit integer type                                           *
******************************************************************************/
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "type256.h"
#include "archDetails.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>
/******************************************************************************
*                                    TYPES                                    *
******************************************************************************/
struct _u256_rep32{
	uint32_t words[8];
};
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#define MASK_32LOW  (0x00000000FFFFFFFFULL)
#define MASK_32HIGH (0xFFFFFFFF00000000ULL)

#define type256dbgPrint(a) \
	printf( \
		"0x%016lx%016lx%016lx%016lx", \
		(a)->words[3],(a)->words[2], \
		(a)->words[1],(a)->words[0] \
	)
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
static void type256bitSet(struct u256* a, unsigned n, bool val);
static bool type256bitGet(struct u256* a, unsigned n);
static bool type256NonZero(struct u256* a);
static struct _u256_rep32 rep64to32(struct u256* a);
static struct u256 rep32to64(struct _u256_rep32* a);
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
* Converts from (standard) 64 bit word representation to 32 bit representation
**/
static struct _u256_rep32 rep64to32(struct u256* a){
	struct _u256_rep32 ret = {{0}};
	if(ARCH_LITTLE_ENDIAN){
		memcpy(&ret,a,sizeof(ret));
	}
	else{
		for(int i = 0; i < 4; i++){
			uint32_t low32  = a->words[i]&MASK_32LOW;
			uint32_t high32 = (a->words[i]&MASK_32HIGH)>>32;
			ret.words[2*i] = low32;
			ret.words[2*i+1] = high32;
		}
	}
	return ret;
}
/**
* Converts from 32 bit word representation to (standard) 64 bit representation
**/
static struct u256 rep32to64(struct _u256_rep32* a){
	struct u256 ret = {{0}};
	if(ARCH_LITTLE_ENDIAN){
		memcpy(&ret,a,sizeof(ret));
	}
	else{
		for(int i = 0; i < 4; i++){
			uint64_t low32  = a->words[2*i];
			uint64_t high32 = ((uint64_t)a->words[2*i+1])<<32;
			ret.words[i] = high32|low32;
		}
	}
	return ret;
}
/**
* Returns true if struct is equal to zero
**/
static bool type256NonZero(struct u256* a){
	uint64_t* words = a->words;
	return words[3]||words[2]||words[1]||words[0];
}
/**
* Sets bit to some value
**/
static void type256bitSet(struct u256* a, unsigned n, bool val){
	if(val){
		a->words[n>>6] |= 1<<(n&0x3F);
	}
	else{
		a->words[n>>6] &= ~(1<<(n&0x3F));
	}
}
/**
* Returns value of nth bit
**/
static bool type256bitGet(struct u256* a, unsigned n){
	unsigned ind = (n>>6);

	return !! ( a->words[ind]&(1ULL<<(n&0x3F)) );
}
/**
* Makes a 256 bit type from individual 64 bit words
**/
struct u256 build256(uint64_t a,uint64_t b,uint64_t c,uint64_t d){
	struct u256 y;
	y.words[3] = a;
	y.words[2] = b;
	y.words[1] = c;
	y.words[0] = d;
	return y;
}
/**
* Compares numbers
*
* returns 0 if equal, 1 if a>b and -1 if b>a
**/
int ucmp256(struct u256* a,struct u256* b){
	for( int i = 3; i >= 0; i-- ){
		if(a->words[i] > b->words[i]){
			return 1;
		}
		else if(a->words[i] < b->words[i]){
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
		y.words[i] = a->words[i]+b->words[i]+carry;
		carry = (y.words[i] < a->words[i]);
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
		y.words[i] = a->words[i]-b->words[i]-carry;
		carry = (a->words[i] < b->words[i]);
	}

	return y;
}
/**
* Pure C implementation of 256 bit unsigned multiply
**/
struct u256 _c_umul256(struct u256* a, struct u256* b){

	struct _u256_rep32 y = {{0}};
	struct _u256_rep32 a32 = rep64to32(a);
	struct _u256_rep32 b32 = rep64to32(b);

	for(int i = 0; i < 8; i++){
		uint64_t carry = 0;
		uint64_t bWord = b32.words[i];

		for(int n = 0; n < 8-i; n++){
			uint64_t aWord = a32.words[n];
			uint64_t tmp  = (aWord*bWord);
			tmp += carry+(uint64_t)y.words[n+i];

			y.words[n+i] = (tmp&MASK_32LOW);
			carry = (tmp&MASK_32HIGH)>>32;
		}
	}

	return rep32to64(&y);
}
/**
* Pure C implementation of multiplication by a 64 bit word
**/
struct u256 _c_umul256by32(struct u256* a, uint32_t b){

	struct _u256_rep32 y = {{0}};
	struct _u256_rep32 a32 = rep64to32(a);

	uint64_t carry = 0;
	uint64_t bWord = b;

	for(int n = 0; n < 8; n++){
		uint64_t aWord = a32.words[n];
		uint64_t tmp  = (aWord*bWord);

		tmp += carry+(uint64_t)y.words[n];

		y.words[n] = (tmp&MASK_32LOW);
		carry = (tmp&MASK_32HIGH)>>32;
	}

	return rep32to64(&y);
}
/**
* Pure C implementation of right shift
**/
struct u256 _c_rshift256(struct u256* a, unsigned n){
	struct u256 y = {{0}};

	uint64_t spillShift = 8*sizeof(uint64_t)-n;
	uint64_t spillMask = (1ULL<<n)-1ULL;
	uint64_t spill = 0;

	for(int i = 3; i >= 0; i--){
		y.words[i] = (a->words[i]>>n) | spill;
		spill = ((a->words[i])&spillMask)<<(spillShift);
	}

	return y;
}
/**
* Pure C implementation of right shift
**/
struct u256 _c_lshift256(struct u256* a, unsigned n){
	struct u256 y = {{0}};

	uint64_t spillShift = 8*sizeof(uint64_t)-n;
	uint64_t spillMask = ~((1ULL<<(spillShift))-1ULL);
	uint64_t spill = 0;

	for(int i = 0; i < 4; i++){
		y.words[i] = (a->words[i]<<n) | spill;
		spill = ((a->words[i])&spillMask)>>(spillShift);
	}

	return y;
}
/**
* Pure C imlementation of unsigned division
**/
struct u256_divRet _c_udivMod256(struct u256* n, struct u256* d){
	struct u256_divRet ret;
	struct u256 q = {{0}};
	struct u256 r = {{0}};

	for(int i = 255; i >= 0; i--){
		r = _c_lshift256(&r,1);

		type256bitSet(&r,0,type256bitGet(n,i));

		if(ucmp256(&r,d) >= 0){
			r = usub256(&r,d);
			type256bitSet(&q,i,1);
		}
	}

	ret.q = q;
	ret.r = r;

	return ret;
}
/**
* Pure C imlementation of unsigned division by a 32 bit number
**/
struct u256_divRet _c_udivMod256by32(struct u256* n,uint32_t d){
	struct u256_divRet ret;

	struct _u256_rep32 n32 = rep64to32(n);
	struct _u256_rep32 q = {{0}};
	struct u256 r = {{0}};

	uint64_t remain = 0;
	for(int i = 7; i >= 0; i--){
		uint64_t next = (remain<<32)|(n32.words[i]);
		q.words[i] = next/(uint64_t)d;
		remain = next%(uint64_t)d;
	}

	r.words[0] = remain;

	ret.q = rep32to64(&q);
	ret.r = r;

	return ret;
}
/**
* Converts a string to 256 bit num
**/
int strToU256(const char*nptr,char** endptr,struct u256* y){

	struct u256 output = {{0}};
	struct u256 tenPow = build256(0,0,0,1);
	int firstD;
	int lastD;

	for(firstD = 0; isspace(nptr[firstD]); firstD++);
	if(!nptr[firstD]){
		//error, string is invalid
		return 1;
	}

	if(!isdigit(nptr[firstD])){
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
		struct u256 digVal = umul256by32(&tenPow,nptr[i]-'0');

		output = uadd256(&output,&digVal);
		tenPow = umul256by32(&tenPow,10);
	}
	if(endptr){
		*endptr = (char*)(&(nptr[lastD+1]));
	}
	memcpy(y,&output,sizeof(output));
	return 0;
}
/**
* Convert u256 to a decimal string
**/
char* u256ToStr_dec(struct u256* n){

	struct u256_divRet acc;
	char* outStr = malloc((MAX_256_UDECSTR+1)*sizeof(char));
	int strLen = 0;
	if(!outStr){
		return NULL;
	}

	memcpy(&(acc.q),n,sizeof(acc.q));

	do{
		strLen += 1;
		acc = udivMod256by32(&(acc.q),10);
		uint64_t rem = acc.r.words[0];
		char digit = '0'+rem;
		assert(rem < 10);

		outStr[MAX_256_UDECSTR-strLen] = digit;
	}while(type256NonZero(&(acc.q)));

	if(strLen != MAX_256_UDECSTR){
		int strShift = MAX_256_UDECSTR-strLen;
		for(int i = 0; i < strLen; i++){
			outStr[i] = outStr[i+strShift];
		}
	}
	outStr[strLen] = '\0';

	return outStr;
}
/**
*
**/
char* u256ToStr_hex(struct u256* n){
	bool firstDigit = false;
	char * s = calloc(MAX_256_UHEXSTR+1,sizeof(*s));
	int strInd = 0;

	if(!s){
		return NULL;
	}

	for(int i = 3; i >= 0; i--){
		if(!firstDigit && !n->words[i]){
			continue;
		}

		if(!firstDigit){
			int pLen = sprintf(
					s+strInd,"%llx",
					(unsigned long long)n->words[i]
				);
			firstDigit = true;
			strInd += pLen;
		}
		else{
			int pLen = sprintf(
					s+strInd,"%016llx",
					(unsigned long long)n->words[i]
				);
			strInd += pLen;
		}
	}

	return s;
}