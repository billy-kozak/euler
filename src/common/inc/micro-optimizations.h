/******************************************************************************
* Contains functionality for performing micro-optimizations                   *
*                                                                             *
* Usually, functionality is compiler specific                                 *
******************************************************************************/
#ifndef _MICRO_OPTIMIZATIONS_H_
#define _MICRO_OPTIMIZATIONS_H_

#if __GNUC__
#define likely(x)      __builtin_expect(!!(x), 1)
#define unlikely(x)    __builtin_expect(!!(x), 0)
#else
#define likely(x)     (x)
#define unlikely(x)   (x)
#endif

#endif  //_MICRO_OPTIMIZATIONS_H_