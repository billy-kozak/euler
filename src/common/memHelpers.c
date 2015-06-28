/******************************************************************************
* Implements helper functions in the vein of the mem* std library functions   *
*                                                                             *
* An example might be a function which grows a dynamically allocated array    *
* then appends to it                                                          *
******************************************************************************/
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "memHelpers.h"

#include <stdlib.h>
#include <string.h>
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
* Extend dynamic memory with another buffer
*
* This function reallocs mem1 and then copies mem2 at output address+s1 (this
* can be safely exploited to leave space between the memory in the output).
*
* mem1 must be a pointer to dynamically allocated memory
*
* Args:
* mem1 - dynamic memory to extend
* mem2 - memory to copy into the location after mem1
* s1   - mem2 will be put s1 bytes after mem1 in the output buffer
* s2   - s2 bytes are copied from mem2 to place after the data from mem1
*
* Returns:
* The address of the new dynamic memory (may be the same as mem1) or NULL
* on error
**/
void* memExtend(void* mem1,const void* mem2, size_t s1, size_t s2){
	unsigned char* newMem = realloc(mem1,s1+s2);

	if(!newMem){
		return NULL;
	}

	memcpy(newMem+s1,mem2,s2);
	return newMem;
}
/**
* Combine memory buffers into new, dynamic memory location
*
* Args:
* mem1 - first memory buffer (goes first)
* mem2 - second memory buffer (goes second)
* s1   - bytes to copy from mem1
* s2   - bytes to copy from mem2
*
* Returns:
* pointer to malloc'd memory containing the concatenation of the memory
* (or NULL on failure)
**/
void* memCombine(const void* mem1, const void* mem2, size_t s1, size_t s2){
	unsigned char* dynMem = malloc(s1+s2);
	if(!dynMem){
		return NULL;
	}

	memcpy(dynMem,mem1,s1);
	memcpy(dynMem+s1,mem2,s2);
	return dynMem;
}
/**
* Joins memory buffers with seperator
*
* Args:
* memBufs - list of memory buffers to be joined
* sep - seperator to place in bewteen every two buffers (but not at the end)
* nBufs - number of memory buffers in memBufs
*
* Returns:
* lenMem struct which points to the joined memory. The output mem is malloc'd.
* NULL is returned on error or if nBufs is zero.
**/
struct lenMem memJoin(
		const struct lenMem* memBufs,const struct lenMem* sep,int nBufs
	){
	struct lenMem output = {0};
	void* joined;
	unsigned char* writePtr;
	size_t totalMemSize = sep->len * (nBufs-1);

	if(!nBufs){
		return output;
	}

	for(int i = 0; i < nBufs; i++){
		totalMemSize += memBufs[i].len;
	}

	joined = malloc(totalMemSize);
	writePtr = joined;

	if(!joined){
		return output;
	}

	for(int i = 0; i < nBufs-1; i++){
		memcpy(writePtr,memBufs[i].mem,memBufs[i].len);
		writePtr += memBufs[i].len;
		memcpy(writePtr,sep->mem,sep->len);
		writePtr += sep->len;
	}

	memcpy(writePtr,memBufs[nBufs-1].mem,memBufs[nBufs-1].len);

	output.len = totalMemSize;
	output.mem = joined;

	return output;
}