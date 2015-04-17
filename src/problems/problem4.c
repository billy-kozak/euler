/******************************************************************************
* A palindromic number reads the same both ways. The largest palindrome made  *
* from the product of two 2-digit numbers is 9009 = 91 x 99.                  *
*                                                                             *
* Find the largest palindrome made from the product of two 3-digit numbers.   *
******************************************************************************/

/****************************************************************************** 
*                                  INCLUDES                                   * 
******************************************************************************/ 
#include "eulerProblems.h"                                                      
#include "eulerSolvers.h"

#include <stdbool.h>
#include <limits.h>
#include <stdio.h>
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
static inline bool isPalindrome(unsigned n);
static unsigned palindrome3_brute(void);
/****************************************************************************** 
*                            FUNCTION DEFINITIONS                             * 
******************************************************************************/
/**
* Returns true if input is a palindrome
**/
static inline bool isPalindrome(unsigned n){
	unsigned mag;
	
	for(mag = 10; (n>mag); mag *= 10 );
	
	unsigned x = mag/10;
	unsigned y = 1;
	
	while(x > y){
		if( (n%(10*x) )/x != (n%(10*y) )/y ){
			return false;
		}
		x/=10;
		y*=10;
	}
	
	return true;
}
/**
* Finds largest 3 digit palindrom number by brute force
**/
static unsigned palindrome3_brute(void){
	
	unsigned largest = 0;
	unsigned c;
	
	for(unsigned n = 999; n >= 100; n--){
		for(unsigned k = 999; k >= n; k--){
			c = n*k;
			if(isPalindrome(c)){
				largest = (largest > c) ? largest : c;
			}
		}
	}
	
	return largest;
}
/**                                                                             
* Solution for problem 4                                                        
**/                                                                             
struct eulerSol euler_prob4(void){
	struct eulerSol sol = {U64};
	
	sol.val.u64 = palindrome3_brute();
	
	return sol;
}
