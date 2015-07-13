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
#define count_tzll(n) __builtin_ctzll(n)
#define count_lzll(n) __builtin_clzll(n)
#else
#define count_tzll(n) slow_count_tzll(n)
#define count_lzll(n) slow_count_lzll(n)
#endif
/******************************************************************************
*                              INLINE FUNCTIONS                               *
******************************************************************************/
/**
* Return true if given n is exact power of 2
**/
static inline bool is_power_2(unsigned long long n){
	return (n-1)&n;
}
/**
* Gets the ceiling of the log2 of n
**/
static inline int log2_ceil(unsigned long long n){
	int leadingZeroes = count_lzll(n);
	int bits = sizeof(n)<<3;

	if( is_power_2(n) ){
		return bits - leadingZeroes;
	} else {
		//this is an exact power of two
		return bits - leadingZeroes - 1;
	}
}
/**
* Counts trailing zeroes using slow pure C implementation
**/
static inline int slow_count_lzll(unsigned long long n){
	int cnt;
	int max = sizeof(n)*8;
	for(cnt = 0; !(n&(1<<cnt)) || cnt == max; cnt++);
	return cnt;
}
/**
* Counts leading zeroes using slow pure C implementation
**/
static inline int slow_count_tzll(unsigned long long n){
	int cnt;
	int max = sizeof(n)*8;
	for(cnt = 0; !(n& (1<<(max-cnt)) ) || cnt==max; cnt++);
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