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
		case INT:
			printf("%d\n",sol.val.i);
			break;
		case UNSIGNED:
			printf("%u\n",sol.val.u);
			break;
		case I32:
			printf("%lld\n",(long long)sol.val.i32);
			break;
		case U32:
			printf("%llu\n",(long long unsigned)sol.val.u32);
			break;
		case I64:
			printf("%lld\n",(long long)sol.val.i64);
			break;
		case U64:
			printf("%llu\n",(long long unsigned)sol.val.u64);
			break;
		case DOUBLE:
			printf("%lf\n",sol.val.d);
			break;
		default:
			fprintf(stderr,"This should never run!\n");
			break;
	}
}