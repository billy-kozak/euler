/******************************************************************************
* The four adjacent digits in the 1000-digit number that have the greatest    *
* product are 9 x 9 × 8 x 9 = 5832.                                           *
*                                                                             *
* 73167176531330624919225119674426574742355349194934                          *
* 96983520312774506326239578318016984801869478851843                          *
* 85861560789112949495459501737958331952853208805511                          *
* 12540698747158523863050715693290963295227443043557                          *
* 66896648950445244523161731856403098711121722383113                          *
* 62229893423380308135336276614282806444486645238749                          *
* 30358907296290491560440772390713810515859307960866                          *
* 70172427121883998797908792274921901699720888093776                          *
* 65727333001053367881220235421809751254540594752243                          *
* 52584907711670556013604839586446706324415722155397                          *
* 53697817977846174064955149290862569321978468622482                          *
* 83972241375657056057490261407972968652414535100474                          *
* 82166370484403199890008895243450658541227588666881                          *
* 16427171479924442928230863465674813919123162824586                          *
* 17866458359124566529476545682848912883142607690042                          *
* 24219022671055626321111109370544217506941658960408                          *
* 07198403850962455444362981230987879927244284909188                          *
* 84580156166097919133875499200524063689912560717606                          *
* 05886116467109405077541002256983155200055935729725                          *
* 71636269561882670428252483600823257530420752963450                          *
*                                                                             *
* Find the thirteen adjacent digits in the 1000-digit number that have the    *
* greatest product. What is the value of this product?                        *
******************************************************************************/

/****************************************************************************** 
*                                  INCLUDES                                   * 
******************************************************************************/ 
#include "eulerProblems.h"                                                      
#include "eulerSolvers.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#define PROBLEM_8_MAGIC 13
/******************************************************************************
*                                  CONSTANTS                                  *
******************************************************************************/
static const char* problem8_digitString=
"73167176531330624919225119674426574742355349194934"
"96983520312774506326239578318016984801869478851843"
"85861560789112949495459501737958331952853208805511"
"12540698747158523863050715693290963295227443043557"
"66896648950445244523161731856403098711121722383113"
"62229893423380308135336276614282806444486645238749"
"30358907296290491560440772390713810515859307960866"
"70172427121883998797908792274921901699720888093776"
"65727333001053367881220235421809751254540594752243"
"52584907711670556013604839586446706324415722155397"
"53697817977846174064955149290862569321978468622482"
"83972241375657056057490261407972968652414535100474"
"82166370484403199890008895243450658541227588666881"
"16427171479924442928230863465674813919123162824586"
"17866458359124566529476545682848912883142607690042"
"24219022671055626321111109370544217506941658960408"
"07198403850962455444362981230987879927244284909188"
"84580156166097919133875499200524063689912560717606"
"05886116467109405077541002256983155200055935729725"
"71636269561882670428252483600823257530420752963450";
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
static unsigned* parseDigitString(const char* digitString,size_t len);
static uint64_t biggestProdSearch(unsigned* digits,size_t nDigits,int len);
static uint64_t prodNN(unsigned** pp,unsigned* end,int len);
/****************************************************************************** 
*                            FUNCTION DEFINITIONS                             * 
******************************************************************************/
/**
* Parse string of ascii digits into array of integers
*
* Each integer is 1 digit
**/
static unsigned* parseDigitString(const char* digitString,size_t len){
	unsigned* digits = malloc(len*sizeof(unsigned));
	
	for(size_t i = 0; i < len; i++){
		digits[i] = digitString[i]-'0';
	}
	
	return digits;
}
/**
* Very specialized function which does some a vareity of very specific things
*
* Finds the product of the first consecutive string of len numbers which
* are non-zero. If the function reaches the end of the buffer before funding
* this string of digits it returns zero.
*
* If a string was succesfully found, *pp is made to point to the first
* non-zero digit which formed the start of the string. Otherwise, *pp will
* be made to point to one after then end of memory.
*
* Args:
* pp - pointer to a pointer of unsigned integers
* end - pointer to one past the end of the array of integers pointed to by
* 	*pp
* len - length of the string of non-zero digits to search for
*
* Returns:
* product of the first consecutive sequence of len non-zero integers or zero if
* no such squence if found
**/
static uint64_t prodNN(unsigned** pp,unsigned* end,int len){
	uint64_t prod = 1;
	
	unsigned* p = *pp;
	int count = 0;
	
	while(count < len){
		if(p >= end){
			*pp = end;
			return 0;
		}
		
		if(!*p){
			prod = 1;
			count = 0;
		}
		else{
			prod *= *p;
			count++;
		}
		p++;
	}
	
	//give back pointer to first non-zero digit which formed part of
	//the returned product
	*pp = (p-len);
	return prod;
}
/**
* Searches for the largest product made of consecutive numbers from the
* given array of integers.
**/
static uint64_t biggestProdSearch(unsigned* digits,size_t nDigits,int len){
	
	unsigned* pStart = digits;
	unsigned* pStop;
	unsigned* end = digits+nDigits;
	
	uint64_t prod = prodNN(&pStart,end,len);
	if(pStart >= end){
		return prod;
	}
	
	pStop = pStart + len;
	pStart += 1;
	
	uint64_t max = prod;
	
	while(pStop < end){
		
		if(*pStop){
			prod /= *(pStart-1);
			prod *= *(pStop);
			
			pStart++;
			pStop++;
		}
		else{
			pStart = pStop+1;
			prod = prodNN(&pStart,end,len);
			if(pStart >= end){
				break;
			}
			else{
				pStop = pStart + len;
				pStart += 1;
			}
		}
		
		max = (prod>max)?(prod):(max);
	}
	
	return max;
}
/**                                                                             
* Solution for problem 8                                                        
**/                                                                             
struct eulerSol euler_prob8(void){
	struct eulerSol sol = {U64};
	
	size_t dLen = strlen(problem8_digitString);
	unsigned* digits = parseDigitString(problem8_digitString,dLen);
	sol.val.u64 = biggestProdSearch(digits,dLen,PROBLEM_8_MAGIC);
	free(digits);
	
	return sol;
}
