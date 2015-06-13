#ifndef _TYPE_256_H_
#define _TYPE_256_H_
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include <stdint.h>
/******************************************************************************
*                                    TYPES                                    *
******************************************************************************/
struct u256{
	union{
		uint64_t w64[4];
		uint32_t w32[8];
	}words;
};
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#if ( defined(__GNUC__) && defined(__x86_64__) )
#define	_GNU_X86_64_ 1
#endif

/* public API functions */
#ifndef _GNU_X86_64_
#define uadd256   _c_uadd256
#else
#define uadd256   _x64_uadd256
#endif

#ifndef _GNU_X86_64_
#define  usub256  _c_usub256
#else
#define  usub256  _x64_usub256
#endif

#define umul256   _c_umul256
#define udiv256   _c_udiv256
#define lshift256 _c_lshift256
#define rshift256 _c_rshift256
/******************************************************************************
*                              INLINE FUNCTIONS                               *
******************************************************************************/
#ifdef _GNU_X86_64_
static inline struct u256 _x64_uadd256(struct u256* a, struct u256* b){
	struct u256 y;

	y.words.w64[0] = a->words.w64[0];
	y.words.w64[1] = a->words.w64[1];
	y.words.w64[2] = a->words.w64[2];
	y.words.w64[3] = a->words.w64[3];

	__asm(
			"add %4, %0\n\t"
			"adc %5, %1\n\t"
			"adc %6, %2\n\t"
			"adc %7, %3\n\t"

			: /*        0                    1        */
			  "=r"(y.words.w64[0]),"=r"(y.words.w64[1]),
			  /*        2                    3        */
			  "=r"(y.words.w64[2]),"=r"(y.words.w64[3])

			: /*        4                    5        */
			  "m"(b->words.w64[0]),"m"(b->words.w64[1]),
			  /*        6                    7        */
			  "m"(b->words.w64[2]),"m"(b->words.w64[3]),

			  "0"(y.words.w64[0]),"1"(y.words.w64[1]),
			  "2"(y.words.w64[2]),"3"(y.words.w64[3])
			:
		);

	return y;
}
static inline struct u256 _x64_usub256(struct u256* a, struct u256* b){
	struct u256 y;

	y.words.w64[0] = a->words.w64[0];
	y.words.w64[1] = a->words.w64[1];
	y.words.w64[2] = a->words.w64[2];
	y.words.w64[3] = a->words.w64[3];

	__asm(
			"sub %4, %0\n\t"
			"sbb %5, %1\n\t"
			"sbb %6, %2\n\t"
			"sbb %7, %3\n\t"

			: /*        0                    1        */
			  "=r"(y.words.w64[0]),"=r"(y.words.w64[1]),
			  /*        2                    3        */
			  "=r"(y.words.w64[2]),"=r"(y.words.w64[3])

			: /*        4                    5        */
			  "m"(b->words.w64[0]),"m"(b->words.w64[1]),
			  /*        6                    7        */
			  "m"(b->words.w64[2]),"m"(b->words.w64[3]),

			  "0"(y.words.w64[0]),"1"(y.words.w64[1]),
			  "2"(y.words.w64[2]),"3"(y.words.w64[3])
			:
		);

	return y;
}
#endif
/******************************************************************************
*                            FUNCTION DECLARATIONS                            *
******************************************************************************/

/* public API functions */
int ucmp256(struct u256* a,struct u256* b);
struct u256 build256(uint64_t a,uint64_t b,uint64_t c,uint64_t d);

/* Pure C implementation functions */
struct u256 _c_rshift256(struct u256* a, unsigned n);
struct u256 _c_lshift256(struct u256* a, unsigned n);
struct u256 _c_uadd256(struct u256* a, struct u256* b);
struct u256 _c_usub256(struct u256* a, struct u256* b);
struct u256 _c_umul256(struct u256* a, struct u256* b);
struct u256 _c_udiv256(struct u256* n, struct u256* d);
#endif //_TYPE_256_H_