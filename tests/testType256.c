/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "common/type256.c"

//all other includes should come after the source file include!
#include "mySimpleTestFramework.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
static struct unsigned256 build256(
		uint64_t a,uint64_t b,uint64_t c,uint64_t d
	);
/******************************************************************************
*                                    TESTS                                    *
******************************************************************************/
/**
* Makes a 256 bit type from individual 64 bit words
**/
static struct unsigned256 build256(
		uint64_t a,uint64_t b,uint64_t c,uint64_t d
	){
	struct unsigned256 y;
	y.words.w64[3] = a;
	y.words.w64[2] = b;
	y.words.w64[1] = c;
	y.words.w64[0] = d;
	return y;
}
/**
* Used to test adding with pure C implementation
**/
static bool testCAdd(
		struct unsigned256 a,struct unsigned256 b,
		struct unsigned256 exp
	){
	struct unsigned256 answer = _c_uadd256(&a,&b);
	return memcmp(&answer,&exp,sizeof(struct unsigned256)) == 0;
}
/**
* Uses trial divide gen functions to get nth prime
**/
/**
* Test entry point
**/
int main(int argc, char** argv){
	 MSTF_START();
	 MSTF_RUN(
	 	 "Failed to add numbers 0xFF and 0xFF",
	 	 testCAdd(
	 	 	 	build256(0,0,0,0xFF),build256(0,0,0,0xFF),
	 	 	 	build256(0,0,0,0x1FE)
	 	 	 )
	 	 );
	 MSTF_END();

	 return 0;
}