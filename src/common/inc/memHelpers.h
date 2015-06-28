#ifndef _MEM_HELPERS_H_
#define _MEM_HELPERS_H_
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include <stdlib.h>
/******************************************************************************
*                                    TYPES                                    *
******************************************************************************/
struct lenMem{
	void*  mem;
	size_t len;
};
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
void* memExtend(void* mem1,const void* mem2, size_t s1, size_t s2);
void* memCombine(const void* mem1, const void* mem2, size_t s1, size_t s2);
struct lenMem memJoin(
		const struct lenMem* memBufs,const struct lenMem* sep,int nBufs
	);
#endif // _MEM_HELPERS_H_