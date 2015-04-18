/******************************************************************************
* Implements functionality relating to pythagorean tripples                   *
*                                                                             *
* References:                                                                 *
*         http://en.wikipedia.org/wiki/Pythagorean_triple                     *
******************************************************************************/
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "pythagorean_tripple.h"
#include "coPrimePairs.h"

#include <stdio.h>
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
* Finds a pythagorean tripples whos terms together add to n
*
* Uses Euclid's formula for generating pythagorean tripples as its basis
*
* This formula is as follows:
* a = k(m^2-n^2), b = k*(2mn), c = k(m^2+n^2)
* where m > n, (m-n) is odd, and m,n are coprime.
* n,m and k are all positive integers
*
* All pythagorean tripples follow this pattern
* See: http://en.wikipedia.org/wiki/Pythagorean_triple#Generating_a_triple
*
* This gives us:
* a+b+c=X => 2k(m^2+m*n)=X
**/
struct pythago_tripple pythagoTripple_findSumN_Euclid(unsigned x){
	//start a coPrime tree which will generate all co-primes with one
	//even and one odd term
	struct coPrimeTree* tree = coPrimeTree_start(EVEN_ODD);
	struct coPrimeTree* node = tree;
	struct pythago_tripple ret = {0,0,0};
	
	if(!!(x%2)){
		//a+b+c will always be even, it is not possible to find
		//a,b,c to sastisfy this x
		return ret;
	}
	
	//Note that this algorithm will have us checking many nodes twice
	//TODO: fix checking nodes more than once
	while(node){
		unsigned m = node->val.m;
		unsigned n = node->val.n;
		
		if( (m*m+m*n) >= 1000){
			//m and n are strictly increaasing as we move down the
			//tree.
			//Therefore, m*m+m*n will only increase down the tree
			//we can only go back up!
			node = node->parent;
			continue;
		}
		else if(  !( x % (2*(m*m+m*n) )) ){
			//we have found a solution
			unsigned k = x/(2*(m*m+m*n));
			
			ret.a = k*(m*m-n*n);
			ret.b = k*2*m*n;
			ret.c = k*(m*m+n*n);
			break;
		}
		
		if( node->left ){
			//we've already checked the left path
			
			if(node->mid){
				//we've already checked the mid path
				if(node->right){
					//we've already checked the right path
					
					//we can only go up
					node = node->parent;
					continue;
				}
				else{
					node = coPrimeTree_genRight(node);
				}
			}
			else{
				node = coPrimeTree_genMid(node);
			}
		}
		else{
			node = coPrimeTree_genLeft(node);
		}
	}
	
	coPrimeTree_free(tree);
	
	return ret;
}