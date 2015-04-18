#ifndef _PRIME_FACTORS_H_
#define _PRIME_FACTORS_H_
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
uint64_t primeFactorLargest_trialDivision(uint64_t target);
bool isPrime_trialDivision(unsigned n);
#endif //_PRIME_FACTORS_H_