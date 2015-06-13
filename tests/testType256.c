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
static bool testAdd(
		struct unsigned256 a,struct unsigned256 b,
		struct unsigned256 exp
	);
static bool testCSub(
		struct unsigned256 a,struct unsigned256 b,
		struct unsigned256 exp
	);
static bool testCMul(
		struct unsigned256 a,struct unsigned256 b,
		struct unsigned256 exp
	);
static bool testCDiv(
		struct unsigned256 a,struct unsigned256 b,
		struct unsigned256 exp
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
* Used to test adding of unsigned 256 types
**/
static bool testAdd(
		struct unsigned256 a,struct unsigned256 b,
		struct unsigned256 exp
	){
	struct unsigned256 answer1 = _c_uadd256(&a,&b);
	struct unsigned256 answer2 = uadd256(&a,&b);

	if( ucmp256(&answer1,&exp) || ucmp256(&answer2,&exp) ){
		return false;
	}
	return true;
}
/**
* Used to test adding with pure C implementation
**/
static bool testCSub(
		struct unsigned256 a,struct unsigned256 b,
		struct unsigned256 exp
	){
	struct unsigned256 answer = _c_usub256(&a,&b);
	return memcmp(&answer,&exp,sizeof(struct unsigned256)) == 0;
}
/**
* Used to test adding with pure C implementation
**/
static bool testCMul(
		struct unsigned256 a,struct unsigned256 b,
		struct unsigned256 exp
	){
	struct unsigned256 answer = _c_umul256(&a,&b);
	return memcmp(&answer,&exp,sizeof(struct unsigned256)) == 0;
}
/**
* Used to test adding with pure C implementation
**/
static bool testCDiv(
		struct unsigned256 n,struct unsigned256 d,
		struct unsigned256 exp
	){
	struct unsigned256 answer = _c_udiv256(&n,&d);

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
	 	 	testAdd(
	 	 	 	build256(0,0,0,0xFF),build256(0,0,0,0xFF),
	 	 	 	build256(0,0,0,0x1FE)
	 	 	 )
	 	 );

	 MSTF_RUN(
	 		"Failed to add large random numbers",
	 	 	testAdd(
	 	 	 	build256(
	 	 	 		0x013770a75bd398e3ULL,
	 	 	 		0x4ae68eb17d2d8b7eULL,
	 	 	 		0x22dd3fa14da9ac82ULL,
	 	 	 		0x462c2861a7f4e22dULL
	 	 	 	),
	 	 	 	build256(
	 	 	 		0x00a561d6ffb65e5aULL,
	 	 	 		0x868ddc591cc4b822ULL,
	 	 	 		0x65869f56452ff2d9ULL,
	 	 	 		0xe3426bae736a8c40ULL
	 	 	 	),
	 	 	 	build256(
	 	 	 		0x01dcd27e5b89f73dULL,
	 	 	 		0xd1746b0a99f243a0ULL,
	 	 	 		0x8863def792d99f5cULL,
	 	 	 		0x296e94101b5f6e6dULL
	 	 	 	)
	 	 	 )
	 	 );
	 MSTF_RUN(
	 		"Failed to subtract large random numbers",
	 	 	testCSub(
	 	 	 	build256(
	 	 	 		0x1dd3a6df243e5a3ULL,
	 	 	 		0xfc2f6fdadaa91281ULL,
	 	 	 		0x7fa1a9dcf7612928ULL,
	 	 	 		0x269d8ea792de7febULL
	 	 	 	),
	 	 	 	build256(
	 	 	 		0x8f05f7341d1afULL,
	 	 	 		0x973f0ade53e5f0e0ULL,
	 	 	 		0x9b7b4a2e71abbf91ULL,
	 	 	 		0x7d1e16c75afe171dULL
	 	 	 	),
	 	 	 	build256(
	 	 	 		0x1d44a0e7f0213f4ULL,
	 	 	 		0x64f064fc86c321a0ULL,
	 	 	 		0xe4265fae85b56996ULL,
	 	 	 		0xa97f77e037e068ceULL
	 	 	 	)
	 	 	 )
	 	 );
	  MSTF_RUN(
	 		"Failed to multiply large random numbers",
	 	 	testCMul(
	 	 	 	build256(
	 	 	 		0x0ULL,0x0ULL,
	 	 	 		0x3680c7eded497696ULL,
	 	 	 		0x33b07bdd1fc3bbe4ULL
	 	 	 	),
	 	 	 	build256(
	 	 	 		0x0ULL,0x0ULL,
	 	 	 		0x9239add0173a31f6ULL,
	 	 	 		0x948478c8bca70189ULL
	 	 	 	),
	 	 	 	build256(
	 	 	 		0x1f21b9b389fdeb6fULL,
	 	 	 		0x539cb0f522c4b7e9ULL,
	 	 	 		0xf280457dcabf85f5ULL,
	 	 	 		0xcd0f4740c5377104ULL
	 	 	 	)
	 	 	 )
	 	 );
	  MSTF_RUN(
	 		"Failed to divide large random numbers",
	 	 	testCDiv(
	 	 	 	build256(
	 	 	 		0x4a45a555f1bb654dULL,
	 	 	 		0x158e4d4c026ad335ULL
	 	 	 		,0x2ae3008d92cdb1aeULL,
	 	 	 		0x686cb016eba70c39ULL
	 	 	 	),
	 	 	 	build256(
	 	 	 		0x3b30cec0900dfdfULL,
	 	 	 		0x94e2fca59b235d11ULL,
	 	 	 		0xa13675879cf04827ULL,
	 	 	 		0x29b6c0938113930eULL
	 	 	 	),
	 	 	 	build256(
	 	 	 		0x0ULL,0x0ULL,0x0ULL,0x14ULL
	 	 	 	)
	 	 	 )
	 	 );
	 MSTF_END();

	 return 0;
}