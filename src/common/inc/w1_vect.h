#ifndef _W1_VECT_H_
#define _W1_VECT_H_
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "anyType.h"
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#define NODE_SIZE_EXP      12
#define NODE_SIZE          (1UL<<NODE_SIZE_EXP)
#define INDEX_START_SIZE   128
/******************************************************************************
*                                    TYPES                                    *
******************************************************************************/
struct _w1Node{
	struct _w1Node*  next;
	struct _w1Node*  prev;
	size_t            len;
	union anyMem    memory;
};

enum w1_indexMode{
	OFF=0,AUTO=1,MANUAL=2
};

struct w1_vect{
	const enum anyTypeID        type;
	const size_t             elSize;
	const enum w1_indexMode  indOn;

	size_t                      len;

	struct _w1Node        nodeZero;
	struct _w1Node*       writePtr;

	size_t                  indSize;
	size_t                   indLen;
	struct _w1Node**         index;

	struct _w1Node*          _pool;
};

struct w1_iter{
	int nodeNum;
	int memInd;

	struct _w1Node* node;
	struct w1_vect* v;
};
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
int w1vect_appendPtr(struct w1_vect* v, void* x);
int w1vect_appendUnsigned(struct w1_vect* v, unsigned x);
int w1vect_appendU64(struct w1_vect* v, uint64_t x);
int w1vect_appendU32(struct w1_vect* v, uint32_t x);
int w1vect_appendU16(struct w1_vect* v, uint16_t x);
int w1vect_appendU8(struct w1_vect* v, uint8_t x);
int w1vect_appendInteger(struct w1_vect* v, int x);
int w1vect_appendI64(struct w1_vect* v, int64_t x);
int w1vect_appendI32(struct w1_vect* v, int32_t x);
int w1vect_appendI16(struct w1_vect* v, int16_t x);
int w1vect_appendI8(struct w1_vect* v, int8_t x);
int w1vect_appendDouble(struct w1_vect* v, double x);

void* w1vect_getIndPtr(struct w1_vect* v,int i);
unsigned w1vect_getIndUnsigned(struct w1_vect* v,int i);
uint64_t w1vect_getIndU64(struct w1_vect* v,int i);
uint32_t w1vect_getIndU32(struct w1_vect* v,int i);
uint16_t w1vect_getIndU16(struct w1_vect* v,int i);
uint8_t w1vect_getIndU8(struct w1_vect* v,int i);
int w1vect_getIndInteger(struct w1_vect* v,int i);
int64_t w1vect_getIndI64(struct w1_vect* v,int i);
int32_t w1vect_getIndI32(struct w1_vect* v,int i);
int16_t w1vect_getIndI16(struct w1_vect* v,int i);
int8_t w1vect_getIndI8(struct w1_vect* v,int i);
double w1vect_getIndDouble(struct w1_vect* v,int i);

void** w1vect_nextPtr(struct w1_iter* i);
unsigned* w1vect_nextUnsigned(struct w1_iter* i);
uint64_t* w1vect_nextU64(struct w1_iter* i);
uint32_t* w1vect_nextU32(struct w1_iter* i);
uint16_t* w1vect_nextU16(struct w1_iter* i);
uint8_t* w1vect_nextU8(struct w1_iter* i);
int* w1vect_nextInteger(struct w1_iter* i);
int64_t* w1vect_nextI64(struct w1_iter* i);
int32_t* w1vect_nextI32(struct w1_iter* i);
int16_t* w1vect_nextI16(struct w1_iter* i);
int8_t* w1vect_nextI8(struct w1_iter* i);
double* w1vect_nextDouble(struct w1_iter* i);

void w1vect_freeIter(struct w1_iter* i);
struct w1_iter* w1vect_initIter(struct w1_vect* v);
void w1vect_resetIter(struct w1_iter* i);
int w1vect_updateIndex(struct w1_vect* v);
void w1vect_getRaw(struct w1_vect* v,void* dest,size_t len,int i);
int w1vect_appendRaw(struct w1_vect* v,void* src,size_t len);
void w1vect_free(struct w1_vect* v);
void w1vect_reset(struct w1_vect* v);
struct w1_vect* w1vect_init(enum w1_indexMode im,enum anyTypeID t);
#endif //_W1_VECT_H_