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

#ifdef __GNUC__
#define count_tzll(n) __builtin_ctzl(n)
#else
#define count_tzll(n) slow_count_tzll(n)
#endif
/******************************************************************************
*                              INLINE FUNCTIONS                               *
******************************************************************************/
/**
* Counts trailing zeroes using slow pure C implementation
**/
static inline int slow_count_tzll(unsigned long long n){
	int cnt;
	for(cnt = 0; !(n&(1<<cnt)); cnt++);
	return cnt;
}
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
static inline bool x86_umul_overflow(unsigned a, unsigned b, unsigned * r){
	int ret;
	__asm(
			"imul %3"
			:"=&d"(ret),"=&a"(a)
			:"1"(a),"r"(b)
			:
		);
	*r = a;
	return !!ret;
}
#endif

#endif //_SIMPLE_MATH_H