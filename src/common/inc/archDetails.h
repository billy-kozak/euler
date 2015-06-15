/******************************************************************************
* This header provides convience macros for detecting architecture specific   *
* details                                                                     *
******************************************************************************/
#ifndef _ARCH_DETAILS_H_
#define _ARCH_DETAILS_H_

/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#if ( defined(__GNUC__) && defined(__x86_64__) )
#define ARCH_GNU_X86_64 1
#endif

#if ( defined(__GNUC__) && defined(__i386__) )
#define ARCH_GNU_X86_32 1
#endif

#if defined(__BYTE_ORDER__)&&(__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define ARCH_BIG_ENDIAN 1
#elif defined(__BYTE_ORDER__)&&(__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#define ARCH_LITTLE_ENDIAN 1
#endif


#ifndef ARCH_BIG_ENDIAN
#define ARCH_BIG_ENDIAN 0
#endif

#ifndef ARCH_LITTLE_ENDIAN
#define ARCH_LITTLE_ENDIAN 0
#endif

#endif //_ARCH_DETAILS_H_