#ifndef _EULER_PROBLEMS_H_
#define _EULER_PROBLEMS_H_
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include <stdint.h>
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#define NUM_EULER_PROBLEMS 501
/******************************************************************************
*                                    TYPES                                    *
******************************************************************************/
struct eulerSol{
	enum{
		INT,UNSIGNED,
		I32,U32,
		I64,U64,
		DOUBLE
	}type;
	
	union{
		int        i;
		unsigned  u;
		uint32_t u32;
		int32_t  i32;
		uint64_t u64;
		int64_t  i64;
		double    d;
	}val;
};
/******************************************************************************
*                                   GLOBALS                                   *
******************************************************************************/
extern struct eulerSol (*problemTab[NUM_EULER_PROBLEMS])(void);
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
void printEulerSol(struct eulerSol sol);
#endif //_EULER_PROBLEMS_H_