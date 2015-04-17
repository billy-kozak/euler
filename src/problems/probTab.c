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
	euler_prob1, euler_prob2, euler_prob3, euler_prob4
};
//END STUBPROB GENERATION//