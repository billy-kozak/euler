/******************************************************************************
* Implements generic functionality relating to running problem solvers        *
******************************************************************************/

/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "eulerProblems.h"

#include <stdint.h>
#include <stdio.h>
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
* Prints the solution out to stdout
**/
void printEulerSol(struct eulerSol sol){
	switch(sol.type){
		case I32:
			printf("%d\n",sol.val.i32);
			break;
		case U32:
			printf("%u\n",sol.val.u32);
			break;
		case I64:
			printf("%ld\n",sol.val.i64);
			break;
		case U64:
			printf("%lu\n",sol.val.u64);
		case DOUBLE:
			printf("%lf\n",sol.val.d);
			break;
		default:
			fprintf(stderr,"This should never run!\n");
			break;
	}
}