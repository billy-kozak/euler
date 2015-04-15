/******************************************************************************
* Contains the euler problem solver function table                            *
******************************************************************************/

/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "eulerProblems.h"

#include <stdlib.h>
/******************************************************************************
*                                   GLOBALS                                   *
******************************************************************************/
struct eulerSol (*problemTab[NUM_EULER_PROBLEMS])(void) = {
	NULL
};