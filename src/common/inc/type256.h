#ifndef _TYPE_256_H_
#define _TYPE_256_H_
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include <stdint.h>
/******************************************************************************
*                                    TYPES                                    *
******************************************************************************/
struct unsigned256{
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
#define uadd256   _c_uadd256
#define usub256   _c_usub256
#define umul256   _c_umul256
#define udiv256   _c_udiv256
#define lshift256 _c_lshift256
#define rshift256 _c_rshift256
/******************************************************************************
*                              INLINE FUNCTIONS                               *
******************************************************************************/
#ifdef _GNU_X86_64_
static inline struct unsigned256 _x64_uadd256(
		struct unsigned256* a, struct unsigned256* b
	){
	struct unsigned256 y;

	y.words.w64[0] = a->words.w64[0];
	y.words.w64[1] = a->words.w64[1];
	y.words.w64[2] = a->words.w64[2];
	y.words.w64[3] = a->words.w64[3];

	__asm(
			"add %0 %4\n\t"
			"adc %1 %5\n\t"
			"adc %2 %6\n\t"
			"adc %3 %7\n\t"

			: /*        0                    1        */
			  "=r"(y.words.w64[0]),"=r"(y.words.w64[1]),
			  /*        2                    3        */
			  "=r"(y.words.w64[2]),"=r"(y.words.w64[3])

			: /*        4                    5        */
			  "g"(b->words.w64[0]),"g"(b->words.w64[1]),
			  /*        6                    7        */
			  "g"(b->words.w64[2]),"g"(b->words.w64[3]),

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
int ucmp256(struct unsigned256* a,struct unsigned256* b);

/* Pure C implementation functions */
struct unsigned256 _c_rshift256(struct unsigned256* a, unsigned n);
struct unsigned256 _c_lshift256(struct unsigned256* a, unsigned n);
struct unsigned256 _c_uadd256(struct unsigned256* a, struct unsigned256* b);
struct unsigned256 _c_usub256(struct unsigned256* a, struct unsigned256* b);
struct unsigned256 _c_umul256(struct unsigned256* a, struct unsigned256* b);
struct unsigned256 _c_udiv256(struct unsigned256* n, struct unsigned256* d);
#endif //_TYPE_256_H_