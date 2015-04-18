/******************************************************************************
* A Pythagorean triplet is a set of three natural numbers, a < b < c, for     *
* which,                                                                      *
* a2 + b2 = c2                                                                *
*                                                                             *
* For example, 32 + 42 = 9 + 16 = 25 = 52.                                    *
*                                                                             *
* There exists exactly one Pythagorean triplet for which a + b + c = 1000.    *
* Find the product abc.                                                       *
******************************************************************************/
/****************************************************************************** 
*                                  INCLUDES                                   * 
******************************************************************************/ 
#include "eulerProblems.h"                                                      
#include "eulerSolvers.h"

#include "pythagorean_tripple.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#define OUTPUT_MODE_PRINT_TRIPPLE 0
#define MAX_INTEGER_PRINT        45 //max digits in 64 bit integer plus sign
#define PROBLEM_9_MAGIC        1000
/******************************************************************************
*                                  CONSTANTS                                  *
******************************************************************************/
/****************************************************************************** 
*                            FUNCTION DEFINITIONS                             * 
******************************************************************************/
/**                                                                             
* Solution for problem 9                                                        
**/                                                                             
struct eulerSol euler_prob9(void){
	struct eulerSol sol;
	
	struct pythago_tripple trip;
	trip = pythagoTripple_findSumN_Euclid(PROBLEM_9_MAGIC);
	
	if(OUTPUT_MODE_PRINT_TRIPPLE){
		const char* trippleFormat = "a=%d b=%d c=%d\n";
		size_t sLenMax = strlen(trippleFormat)+3*MAX_INTEGER_PRINT;
		
		sol.type = STRING;
		
		sol.val.s = calloc(sLenMax,sizeof(char));
		snprintf(
				sol.val.s,sLenMax,trippleFormat,trip.a,
				trip.b,trip.c
			);
	}
	else{
		sol.type = UNSIGNED;
		sol.val.u = trip.a*trip.b*trip.c;
	}
	return sol;
}
