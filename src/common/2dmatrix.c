/******************************************************************************
* Implements a simple 2d matrix type                                          *
*                                                                             *
* The matrix uses pointers of pointers in order to allow for easy indexing    *
******************************************************************************/
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "micro-optimizations.h"
#include "2dmatrix.h"

#include <stdlib.h>
#include <stdint.h>
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
* Allocates a 2d matrix
**/
void* alloc2dMatrix(size_t x, size_t y,size_t elSize){
	void**   matrix = malloc(x*sizeof(void*));
	uint8_t*  data   = calloc(x*y,elSize);

	if(unlikely(!matrix || !data)){
		free(matrix);
		free(data);
		return NULL;
	}

	for(int i = 0; i < x; i++){
		matrix[i] = data+(i*y*elSize);
	}

	return matrix;
}
/**
* Frees a 2d matrix
**/
void free2dMatrix(void* m){
	void** matrix = m;
	void*  data   = matrix[0];

	free(matrix);
	free(data);
}