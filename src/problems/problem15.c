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

#include "2dmatrix.h"

#include <stdio.h>
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#define PROBLEM15_MAGIC_X 20
#define PROBLEM15_MAGIC_Y 20
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
static uint64_t countLatticePaths(uint64_t xLen,uint64_t yLen);
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
* Counts the number of possible lattice paths
**/
static uint64_t countLatticePaths(uint64_t xLen,uint64_t yLen){
	uint64_t** matrix = alloc2dMatrix(xLen+1,yLen+1,sizeof(**matrix));
	uint64_t count = 0;

	if(!matrix){
		return 0;
	}

	for(int y = 0; y <= yLen; y++){
		matrix[xLen][y] = 1;
	}
	for(int x = 0; x <= xLen; x++){
		matrix[x][yLen] = 1;
	}

	for(int y = yLen-1; y >= 0 ; y--){
		for(int x = xLen-1; x >= 0; x--){
			uint64_t right = matrix[x+1][y];
			uint64_t down  = matrix[x][y+1];

			matrix[x][y] = right+down;
		}
	}

	count = matrix[0][0];
	free2dMatrix(matrix);

	return count;
}
/**
* Solution for problem 15
**/
struct eulerSol euler_prob15(void){
	struct eulerSol sol = {U64};
	sol.val.u64 = countLatticePaths(PROBLEM15_MAGIC_X,PROBLEM15_MAGIC_Y);

	return sol;
}
