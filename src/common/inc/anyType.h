#ifndef _ANYTYPE_H_
#define _ANYTYPE_H_
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include <stdint.h>
/******************************************************************************
*                                    TYPES                                    *
******************************************************************************/
enum anyTypeID{
	RAW,
	POINTER,
	UNSIGNED,U64,U32,U16,U8,
	INTEGER,I64,I32,I16,I8,
	DOUBLE
};

union anyType{
	int        i;
	unsigned   u;
	uint32_t u32;
	int32_t  i32;
	uint64_t u64;
	int64_t  i64;
	double    d;
	void*     p;
};

union anyMem{
	void*              raw;
	
	void**             ptr;
	
	unsigned*         uSys;
	uint64_t*          u64;
	uint32_t*          u32;
	uint16_t*          u16;
	uint8_t*            u8;
	
	int*              iSys;
	int64_t*           i64;
	int32_t*           i32;
	int16_t*           i16;
	int8_t*             i8;
	
	double*              d;	
};
#endif //_ANYTYPE_H_