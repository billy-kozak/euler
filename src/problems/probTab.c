/******************************************************************************
* Contains the euler problem solver function table                            *
******************************************************************************/

/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "eulerProblems.h"
#include "eulerSolvers.h"

#include <stdlib.h>
/******************************************************************************
*                                   GLOBALS                                   *
******************************************************************************/
//This table is managed by the stubProb program.
//be careful when editting the code

//OPEN STUBPROB GENERATION//
struct eulerSol (*problemTab[NUM_EULER_PROBLEMS])(void) = {
	 euler_prob1, euler_prob2, euler_prob3, euler_prob4, euler_prob5
	,euler_prob6, euler_prob7, euler_prob8, euler_prob9, euler_prob10
	,euler_prob11, euler_prob12, euler_prob13, euler_prob14, euler_prob15
	,euler_prob16, euler_prob17, euler_prob18
};
//END STUBPROB GENERATION//
