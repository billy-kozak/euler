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
#include <stdbool.h>
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#define PROBLEM15_MAGIC_X 20
#define PROBLEM15_MAGIC_Y 20

#define COUNT_USING_GRID  0
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
static uint64_t countLatticePaths(unsigned xLen,unsigned yLen);
static uint64_t computeSquareLatticePaths(unsigned w);
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
* Compute lattice path count by exploting relation to pascal's triangle
*
* It turns out that, pascal's triangle can be used to compute the path count
* and that, the path count is equal to 2*w choose w the countLatticePaths
* solution can help to visualize this by printing out the values written
* to the matrix.
*
* Note that, this function has a much higher change of producing incorrect
* behaviour due to integer overflow but that, steps have been taken to help
* minimize this somewhat.
*
* Note that, 2*w choose w reduces to (2w!)/(2 * w!) which reduces to
* (w+1*w+2*w+3...+2w)/(w!)
**/
static uint64_t computeSquareLatticePaths(unsigned w){

	uint64_t top = 1;
	uint64_t bot = 1;

	if(!w){
		return 0;
	}

	//half of the factors in w+1*w+2*w+3...+2w are divisble by half of the
	//factors in w! the quoitient of these divisions is 2

	//We exploit this by multiplying together only those terms in the
	//demoniator which do not share this property
	for(uint64_t i = 2; i <= (w/2); i++){
		bot *= i;
	}

	//similiarily, we take only those terms in the numetator which cannot
	//be expressed as 2*some term in the denominator
	for(uint64_t i = w/2; i < w; i++){
		top *= (2*i)+1;
	}

	//we then multiply back in all of the 2's that we created by ignoring
	//some of the terms in the numerator and denominator above
	top = top<<(w/2+w%2);

	return top/bot;
}
/**
* Counts the number of possible lattice paths
**/
static uint64_t countLatticePaths(unsigned xLen,unsigned yLen){
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
	bool square = (PROBLEM15_MAGIC_X==PROBLEM15_MAGIC_Y);

	if(COUNT_USING_GRID || !square){
		sol.val.u64 = countLatticePaths(
				PROBLEM15_MAGIC_X,PROBLEM15_MAGIC_Y
			);
	}
	else{
		sol.val.u64 = computeSquareLatticePaths(PROBLEM15_MAGIC_X);
	}

	return sol;
}
