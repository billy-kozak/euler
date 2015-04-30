#ifndef _PRIME_GENERATION_H_
#define _PRIME_GENERATION_H_
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "w1_vect.h"
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
struct w1_vect* primeGen_sieveOfEratosthenes(unsigned bot, unsigned top);
unsigned primeN_trialDivision(unsigned n);
#endif //_PRIME_GENERATION_H_