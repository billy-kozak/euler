/******************************************************************************
* Starting in the top left corner of a 2x2 grid, and only being able to move  *
* to the right and down, there are exactly 6 routes to the bottom right       *
* corner.                                                                     *
*                                                                             *
* How many such routes are there through a 20x20 grid?                        *
******************************************************************************/
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "eulerProblems.h"
#include "eulerSolvers.h"
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#define PROBLEM15_MAGIC_X 20
#define PROBLEM15_MAGIC_Y 20
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
static unsigned countLatticePaths(unsigned xLen,unsigned yLen);
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
* Counts the number of possible lattice paths
**/
static unsigned countLatticePaths(unsigned xLen,unsigned yLen){

	return 0;
}
/**
* Solution for problem 15
**/
struct eulerSol euler_prob15(void){
	struct eulerSol sol = {UNSIGNED};
	sol.val.u = countLatticePaths(PROBLEM15_MAGIC_X,PROBLEM15_MAGIC_Y);

	return sol;
}
