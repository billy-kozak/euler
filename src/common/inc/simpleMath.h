#ifndef _SIMPLE_MATH_H_
#define _SIMPLE_MATH_H_
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include <math.h>
#include <stdbool.h>
#include <assert.h>
/******************************************************************************
*                                   MACROS                                    *
******************************************************************************/
#if ( defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__) ) )
#define umul_overflow(a,b,res) x86_umul_overflow(a,b,res)
#else
#define umul_overflow(a,b,res) slow_umul_overflow(a,b,res)
#endif
/******************************************************************************
*                              INLINE FUNCTIONS                               *
******************************************************************************/
/**
* Returns a number which is greater than or equal to sqrt of n
*
* Tries to be close to the actual sqrt
**/
static inline unsigned gteSquareRoot(unsigned n){
	unsigned root = (unsigned)ceil(sqrt((double)n));

	while( (root*root) < n){
		root += 1;
	}

	return root;
}
/**
* Slow method of detecting multiply overflow
**/
static inline bool slow_umul_overflow(unsigned a, unsigned b,unsigned* res){
	*res = a*b;
	return (a != 0 && *res / a != b);
}


#if ( defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__) ) )
/**
* Fast inline asm version for 32bit x86
**/
static inline bool _x86_32_umul_overflow(unsigned a, unsigned b, unsigned * r){
	int ret;
	__asm(
			"imull %3"
			:"=&d"(ret),"=&a"(a)
			:"1"(a),"r"(b)
			:
		);
	*r = a;
	return !!ret;
}
#ifdef __x86_64__
static inline bool _x86_64_umul_overflow(unsigned a, unsigned b, unsigned * r){
	int ret;
	__asm(
			"imulq %3"
			:"=&d"(ret),"=&a"(a)
			:"1"(a),"r"(b)
			:
		);
	*r = a;
	return !!ret;
}
#else
//should never actually be used!
#define _x86_64_umul_overflow(a,b,r) ({assert(0);while(1);})
#endif
/**
* Assembly optimized multiply with overflow detection for x86
**/
static inline bool x86_umul_overflow(unsigned a, unsigned b, unsigned * r){
	if(sizeof(a) == 4){
		return _x86_32_umul_overflow(a,b,r);
	}else if(sizeof(a) == 8){
		return _x86_64_umul_overflow(a,b,r);
	}else{
		return slow_umul_overflow(a,b,r);
	}
}
#endif

#endif //_SIMPLE_MATH_H