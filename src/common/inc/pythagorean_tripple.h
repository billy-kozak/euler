#ifndef _PYTHAGOREAN_TRIPPLE_H_
#define _PYTHAGOREAN_TRIPPLE_H_
/******************************************************************************
*                                    TYPES                                    *
******************************************************************************/
struct pythago_tripple{
	unsigned a;
	unsigned b;
	unsigned c;
};
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
struct pythago_tripple pythagoTripple_findSumN_Euclid(unsigned x);
#endif //_PYTHAGOREAN_TRIPPLE_H_
