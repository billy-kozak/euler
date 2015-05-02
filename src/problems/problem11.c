/******************************************************************************
* In the 20x20 grid below, four numbers along a diagonal line have been       *
* marked in red.                                                              *
*                                                                             *
* 08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08                 *
* 49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00                 *
* 81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65                 *
* 52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91                 *
* 22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80                 *
* 24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50                 *
* 32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70                 *
* 67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21                 *
* 24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72                 *
* 21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95                 *
* 78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92                 *
* 16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57                 *
* 86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58                 *
* 19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40                 *
* 04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66                 *
* 88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69                 *
* 04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36                 *
* 20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16                 *
* 20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54                 *
* 01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48                 *
*                                                                             *
* The product of these numbers is 26 x 63 x 78 x 14 = 1788696.                *
*                                                                             *
* What is the greatest product of four adjacent numbers in the same direction *
* (up, down, left, right, or diagonally) in the 20x20 grid?                   *
******************************************************************************/
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "eulerProblems.h"                                                      
#include "eulerSolvers.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
/******************************************************************************
*                                  CONSTANTS                                  *
******************************************************************************/
static const char* problem11_digitString=
"08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08 "
"49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00 "
"81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65 "
"52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91 "
"22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80 "
"24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50 "
"32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70 "
"67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21 "
"24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72 "
"21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95 "
"78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92 "
"16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57 "
"86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58 "
"19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40 "
"04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66 "
"88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69 "
"04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36 "
"20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16 "
"20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54 "
"01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48 ";
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#define PROBLEM11_HEIGHT  20
#define PROBLEM11_WIDTH   20
#define PROBLEM11_LINELEN 4

#define MAX(a,b) ( (a<b)?(b):(a) )
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
static int** parseNumberMatrix(const char* s,int width, int height);
static void freeNumberMatrix(int** m,int width, int height);
static inline bool inBounds(int x, int y, int width, int height);
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
* parses a width*height matrix of space seperated numbers into memory
**/
static int** parseNumberMatrix(const char* s,int width, int height){
	//use calloc to make it easier to free memory on error
	int** matrix = calloc(height,sizeof(*matrix));
	
	const char* nptr = s;
	char* endptr;
	
	if(!matrix){
		goto fail0;
	}
	
	for(int i = 0; i < height; i++){
		matrix[i] = malloc(width*sizeof(*matrix[i]));
		if(!matrix[i]){
			goto fail1;
		}
		
		for(int n = 0; n < width; n++){
			matrix[i][n] = strtoul(nptr,&endptr,10);
			nptr = endptr;
		}
	}
	
	return matrix;
	
	fail1:
		freeNumberMatrix(matrix,width,height);
	fail0:
		return NULL;
}
/**
* frees dynamic memory from a number matrix
**/
static void freeNumberMatrix(int** m,int width, int height){
	for(int i = 0; i < height; i++){
		free(m[i]);
	}
	free(m);
}
/**
* Finds largest product in a lineLen line in the given 2d array of numbers
**/
static unsigned largestLineProd(int** m, int height, int width,int len){
	
	unsigned max = 0;
	
	//search horizontal lines
	for(int n = 0; n < height; n++){
		for(int i = 0; i <= (width-len); i++){
			unsigned p = m[n][i];
			for(int k = i+1; k < (len+i); k++){
				p*= m[n][k];
			}
			max = MAX(p,max);
		}
	}
	
	//search vertical lines
	for(int i = 0; i < width; i++){
		for(int n = 0; n <= (height-len); n++){
			unsigned p = m[n][i];
			for(int k = n+1; k<(len+n); k++){
				p *= m[k][i];
			}
			max = MAX(p,max);
		}
	}
	
	//search diagonal right lines
	for(int i = 0; i < width; i++){
		for(int n=0;inBounds(i+len+n,n+len,width+1,height+1);n++){
			unsigned p = m[n][i+n];
			for(int k = 1; k<len; k++){
				p*= m[n+k][i+k+n];
			}
			max = MAX(p,max);
		}
	}
	for(int n = 1; n < height; n++){
		for(int i = 0;inBounds(i+len,i+n+len,width+1,height+1);i++){
			unsigned p = m[n+i][i];
			for(int k = 1; k<len; k++){
				p*= m[n+i+k][i+k];
			}
			max = MAX(p,max);
		}
	}
	
	//search diagonal left lines
	for(int i = 0; i < width; i++){
		for(int n = 0;inBounds(i-n-len+1,n+len,width,height-1);n++){
			unsigned p = m[n][i-n];
			for(int k = 1; k<len; k++){
				p*= m[n+k][i-n-k];
			}
			max = MAX(p,max);
		}
	}
	
	int maxH = height+1;
	
	for(int n = 1; n < height; n++){
		for(int i=0;inBounds(width-i-len-2,n+i+len,width,maxH);i++){
			unsigned p = m[n+i][width-1-i];
			for(int k = 1; k<len; k++){
				p*= m[n+i+k][width-1-i-k];
			}
			max = MAX(p,max);
		}
	}
	
	return max;
}
/**
* for bounds checking on 2d arrays
**/
static inline bool inBounds(int x, int y, int width, int height){
	return (x >= 0)&&(x<width)&&(y >= 0)&&(y < height);
}
/**                                                                             
* Solution for problem 11                                                        
**/                                                                             
struct eulerSol euler_prob11(void){
	struct eulerSol sol = {UNSIGNED};
	
	int** m = parseNumberMatrix(
			problem11_digitString,PROBLEM11_HEIGHT,PROBLEM11_WIDTH
		);
	
	sol.val.u = largestLineProd(
			m,PROBLEM11_HEIGHT,PROBLEM11_WIDTH,PROBLEM11_LINELEN
		);
	
	freeNumberMatrix(m,PROBLEM11_HEIGHT,PROBLEM11_WIDTH);
	
	return sol;
}
