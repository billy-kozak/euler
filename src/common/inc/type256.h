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
/* public API functions */
#define uadd256   _c_uadd256
#define usub256   _c_usub256
#define umul256   _c_umul256
#define udiv256   _c_udiv256
#define lshift256 _c_lshift256
#define rshift256 _c_rshift256
/******************************************************************************
*                            FUNCTION DECLARATIONS                            *
******************************************************************************/

/* public API functions */
int type256cmp(struct unsigned256* a,struct unsigned256* b);

/* Pure C implementation functions */
struct unsigned256 _c_rshift256(struct unsigned256* a, unsigned n);
struct unsigned256 _c_lshift256(struct unsigned256* a, unsigned n);
struct unsigned256 _c_uadd256(struct unsigned256* a, struct unsigned256* b);
struct unsigned256 _c_usub256(struct unsigned256* a, struct unsigned256* b);
struct unsigned256 _c_umul256(struct unsigned256* a, struct unsigned256* b);
struct unsigned256 _c_udiv256(struct unsigned256* n, struct unsigned256* d);
#endif //_TYPE_256_H_