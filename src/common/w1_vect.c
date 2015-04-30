/******************************************************************************
* Implements an efficient write once memory structure                         *
*                                                                             *
* The write once vector supports fast insertions and traveral with small      *
* memory overhead.                                                            *
*                                                                             *
* This data structure is useful when an unkown amount of data has to be       *
* written to memory and does not need to be modifed after writing. The idea   *
* is to minimize the number of memory allocations while still keeping memory  *
* overhead low and eliminating the need to copy data around when growing      *
* memory.                                                                     *
*                                                                             *
* The vector also can keep an optional index to make accessing elements by    *
* index very fast. This comes at the cost of memory reallocations (i.e.       *
* calling realloc on memory) if the vector grows too big for the index. The   *
* index can, instead, be created after writing is finished.                   *
******************************************************************************/
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "w1_vect.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
/**
* Creates functions for appending various data types to a w1 vector
*
* Returns:
* zero on success and one on failure (memory error).
**/
#define W1APPEND_FUNC(f,w1Type,w1Name,dType) \
int f (struct w1_vect* v, dType x){ \
	assert(v->type == w1Type ); \
	v->writePtr->memory.w1Name[v->writePtr->len] = x; \
	return w1incrMem(v); \
}
/**
* Creates functions to return a value at a given index into the vector
*
* Functions to do not check for out of bounds accesses. To gaurantee proper
* operation, make sure that the given index is less than the vectors "len"
**/
#define W1GETIND_FUNC(f,w1Type,w1Name,dType) \
dType f (struct w1_vect* v,int i){ \
	int nodeNum = (i/v->nodeSize); \
	int memInd  = (i%v->nodeSize); \
	assert(v->type == w1Type ); \
	assert(i <= v->len); \
	struct _w1Node* p = w1vect_getNode(v,nodeNum); \
	assert(p); \
	return p->memory.w1Name[memInd]; \
}
/**
* Creates functions to return next value on iterator
*
* Returns:
* NULL if (currently) at end of vector and pointer to next value otherwise
**/
#define W1NEXT_FUNC(f,w1Type,w1Name,dType) \
dType* f (struct w1_iter* i){ \
	dType* ret = NULL; \
	assert(i->v->type == w1Type ); \
	assert(i->memInd <= i->node->len); \
	if(i->memInd == i->v->nodeSize && i->node->next){ \
		i->node = i->node->next; \
		i->memInd = 0; \
		i->nodeNum += 1; \
	} \
	if(i->memInd < i->node->len){ \
		ret = i->node->memory.w1Name + i->memInd; \
		i->memInd += 1; \
	} \
	return ret; \
}
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
static size_t w1TypeSize(enum anyTypeID t);
static int w1incrMem(struct w1_vect* v);
static int w1Alloc(struct w1_vect* v);
static struct _w1Node* w1vect_getNode(struct w1_vect* v,int i);
/******************************************************************************
*                       PREPROCESSOR CREATED FUNCTIONS                        *
******************************************************************************/
W1APPEND_FUNC(w1vect_appendPtr,POINTER,ptr,void*);

W1APPEND_FUNC(w1vect_appendUnsigned,UNSIGNED,uSys,unsigned);
W1APPEND_FUNC(w1vect_appendU64,U64,u64,uint64_t);
W1APPEND_FUNC(w1vect_appendU32,U32,u32,uint32_t);
W1APPEND_FUNC(w1vect_appendU16,U16,u16,uint16_t);
W1APPEND_FUNC(w1vect_appendU8,U8,u8,uint8_t);

W1APPEND_FUNC(w1vect_appendInteger,INTEGER,iSys,int);
W1APPEND_FUNC(w1vect_appendI64,I64,i64,int64_t);
W1APPEND_FUNC(w1vect_appendI32,I32,i32,int32_t);
W1APPEND_FUNC(w1vect_appendI16,I16,i16,int16_t);
W1APPEND_FUNC(w1vect_appendI8,I8,i8,int8_t);

W1APPEND_FUNC(w1vect_appendDouble,DOUBLE,d,double);
/**-------------------------------------------------------------------------**/
W1GETIND_FUNC(w1vect_getIndPtr,POINTER,ptr,void*);

W1GETIND_FUNC(w1vect_getIndUnsigned,UNSIGNED,uSys,unsigned);
W1GETIND_FUNC(w1vect_getIndU64,U64,u64,uint64_t);
W1GETIND_FUNC(w1vect_getIndU32,U32,u32,uint32_t);
W1GETIND_FUNC(w1vect_getIndU16,U16,u16,uint16_t);
W1GETIND_FUNC(w1vect_getIndU8,U8,u8,uint8_t);

W1GETIND_FUNC(w1vect_getIndInteger,INTEGER,iSys,int);
W1GETIND_FUNC(w1vect_getIndI64,I64,i64,int64_t);
W1GETIND_FUNC(w1vect_getIndI32,I32,i32,int32_t);
W1GETIND_FUNC(w1vect_getIndI16,I16,i16,int16_t);
W1GETIND_FUNC(w1vect_getIndI8,I8,i8,int8_t);

W1GETIND_FUNC(w1vect_getIndDouble,DOUBLE,d,double);
/**-------------------------------------------------------------------------**/
W1NEXT_FUNC(w1vect_nextPtr,POINTER,ptr,void*);

W1NEXT_FUNC(w1vect_nextUnsigned,UNSIGNED,uSys,unsigned);
W1NEXT_FUNC(w1vect_nextU64,U64,u64,uint64_t);
W1NEXT_FUNC(w1vect_nextU32,U32,u32,uint32_t);
W1NEXT_FUNC(w1vect_nextU16,U16,u16,uint16_t);
W1NEXT_FUNC(w1vect_nextU8,U8,u8,uint8_t);

W1NEXT_FUNC(w1vect_nextInteger,INTEGER,iSys,int);
W1NEXT_FUNC(w1vect_nextI64,I64,i64,int64_t);
W1NEXT_FUNC(w1vect_nextI32,I32,i32,int32_t);
W1NEXT_FUNC(w1vect_nextI16,I16,i16,int16_t);
W1NEXT_FUNC(w1vect_nextI8,I8,i8,int8_t);

W1NEXT_FUNC(w1vect_nextDouble,DOUBLE,d,double);
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
* Returns the element size for given w1 vector type
**/
static size_t w1TypeSize(enum anyTypeID t){
	switch(t){
		case RAW:
			return 1;
			break;
		case POINTER:
			return sizeof(void*);
			break;
		case UNSIGNED:
		case INTEGER:
			return sizeof(int);
			break;
		case U64:
		case I64:
			return sizeof(uint64_t);
			break;
		case U32:
		case I32:
			return sizeof(uint32_t);
			break;
		case U16:
		case I16:
			return sizeof(uint16_t);
			break;
		case U8:
		case I8:
			return sizeof(uint8_t);
			break;
		case DOUBLE:
			return sizeof(double);
			break;
		default:
			return 0;
			break;
	}
	
	return 0;
}
/**
* Increment vector memory by one element.
*
* may try (and possibly fail) to allocate more memory
*
* Returns:
* zero on success 1 on failure (memory error)
**/
static int w1incrMem(struct w1_vect* v){
	v->writePtr->len += 1;
	v->len           += 1;
	
	if(v->writePtr->len == v->nodeSize){
		//attempt to allocate more memory
		return w1Alloc(v);
	}
	
	return 0;
}
/**
* Allocates a new node at the end of the write pointer.
*
* Should only be used if all other nodes are full
*
* Returns:
* zero on success 1 on failure (memory error)
**/
static int w1Alloc(struct w1_vect* v){
	struct _w1Node* wp = v->writePtr;

	wp->next = calloc(sizeof(struct _w1Node),1);
	if(!wp->next){
		goto fail0;
	}
	
	wp->next->memory.raw = malloc(v->elSize*v->nodeSize);
	if(!wp->next->memory.raw){
		goto fail1;
	}
	
	wp->next->prev = wp;
	v->writePtr = wp->next;
	
	if(v->indOn==AUTO){
		assert(v->indLen <= v->indSize);
		
		//store node to the index if index is turned on!
		if(v->indSize == v->indLen){
			size_t nextSize = v->indSize+INDEX_START_SIZE;
			void* tmp = realloc(
					v->index,
					nextSize*sizeof(struct _w1Node*)
				);
			if(!tmp){
				//failed to allocate more memory for the index
				goto fail1;
			}
			
			v->index = tmp;
			v->indSize += INDEX_START_SIZE;
		}
		
		v->index[v->indLen] = wp->next;
		v->indLen += 1;
	}
	
	return 0;
	
	fail1:
		free(wp->next);
	fail0:
		return 1;
}
/**
* Returns a given numbered node (indexed from zero) from the vector
*
* Will return NULL if the index is too large.
**/
static struct _w1Node* w1vect_getNode(struct w1_vect* v,int i){

	struct _w1Node* p = &(v->nodeZero);
	int count = 0;
	
	if(v->indOn){
		
		if( (v->indOn == AUTO) || (i<v->indLen) ){
			assert(i < v->indLen);
			return v->index[i];
		}
		else if(v->indLen){
			p = v->index[v->indLen-1];
			count = (v->indLen-1)*v->nodeSize;
		}
	}
	
	while( count < i){
		count ++;
		p = p->next;
	}

	return p;
}

/**
* Append raw bytes of memory to the vector.
*
* This function cab be used regardless of the vector's "type" so long as
* the given length is a multiple of the vector's element size
**/
int w1vect_appendRaw(struct w1_vect* v,void* src,size_t len){
	
	size_t nodeBytes = v->writePtr->len * v->elSize;
	void* dest = v->writePtr->memory.u8 + nodeBytes;
	
	//length must be multiple of the element size
	assert(!(len%v->elSize));
	
	do{
		struct _w1Node* wp = v->writePtr;
		
		//remaining write space in bytes
		size_t wSpace = (v->nodeSize-wp->len)*v->elSize;
		size_t wSize  = (len<wSpace)?len:wSpace;
		
		memcpy(dest,src,wSize);
		
		len-=wSize;
		wp->len += wSize;
		v->len  += wSize;
		
		if(len){
			if(w1Alloc(v)){
				//error allocating memory
				return 1;
			}
		}
	}while(len);
	
	return 0;
}
/**
* Reads raw memory from the vector
*
* The read from the vector begins at index i
*
* Behaviour is undefined if there is not enough memory available in the
* vector after the index; this function will not check for that condition.
**/
void w1vect_getRaw(struct w1_vect* v,void* dest,size_t len,int i){
	int nodeNum = (i/v->nodeSize);
	int memInd  = (i%v->nodeSize);
	struct _w1Node* p = w1vect_getNode(v,nodeNum);
	
	assert(v->len >= (i+(len/v->elSize)) );
	
	while(len){
		assert(p);
		
		size_t nodeRemain = v->nodeSize-memInd;
		size_t rLen = (len < nodeRemain)?(len):(nodeRemain);
		
		memcpy(dest,(p->memory.u8+memInd),rLen);
		
		len -= rLen;
		dest = (void*) (((uint8_t*)dest)+rLen);
		memInd = 0;
		p = p->next;
	}
}
/**
* Updates the vector's index.
*
* Returns:
* zero on success and one on failure (memory error)
**/
int w1vect_updateIndex(struct w1_vect* v){
	
	size_t nodeCount = v->len/v->nodeSize;
	struct _w1Node* p;
	
	if(nodeCount >= v->indSize){
		size_t newSize = nodeCount;

		v->index = realloc(v->index,newSize*sizeof(struct _w1Node*));
		if(!(v->index)){
			//memory error
			return 1;
		}
		
		v->indSize = newSize;
	}
	
	if(v->indLen){
		p = v->index[v->indLen-1];
	}
	else{
		p = &(v->nodeZero);
	}
	
	while(nodeCount > v->indLen){
		assert(v->indLen < v->indSize);
		
		v->index[v->indLen] = p;
		p = p->next;
		v->indLen += 1;
		
		assert(p);
	}
	
	return 0;
}
/**
* Frees a dynamically allocated w1 vector
*
* Ignores NULL pointers
**/
void w1vect_free(struct w1_vect* v){
	
	if(!v){
		return;
	}
	
	struct _w1Node* p = v->nodeZero.next;
	
	if(v->indOn){
		free(v->index);
	}
	
	free(v->nodeZero.memory.raw);
	
	while(p){
		struct _w1Node* next = p->next;
		free(p->memory.raw);
		free(p);
		
		p = next;
	}
	
	free(v);
}
/**
* Frees iterator dynamic memory
*
* Ignores NULL pointers
**/
void w1vect_freeIter(struct w1_iter* i){
	free(i);
}
/**
* Initilize an iterator for the given w1 vector
*
* Can fail (with memory allocation error) and will return NULL;
**/
struct w1_iter* w1vect_initIter(struct w1_vect* v){
	struct w1_iter* itr = calloc(sizeof(struct w1_iter),1);
	
	if(!itr){
		//memory error
		return NULL;
	}
	
	itr->node = &(v->nodeZero);
	itr->v = v;
	
	return itr;
}
/**
* Resets the iterator so that it points to the first element again
**/
void w1vect_resetIter(struct w1_iter* i){
	i->node = &(i->v->nodeZero);
	i->nodeNum = 0;
	i->memInd = 0;
}
/**
* Initilizes a w1 vector on the heap.
*
* Can fail on memory error, in which case NULL will be returned.
**/
struct w1_vect* w1vect_init(enum w1_indexMode im,size_t ns,enum anyTypeID t){
	
	size_t elSize = w1TypeSize(t);
	struct w1_vect tmp = {
			t,elSize,(ns)?(ns):NODE_SIZE_DEFAULT,
			im
		};
	struct w1_vect* ret = malloc(sizeof(struct w1_vect));
	if(!ret){
		goto fail2;
	}

	//work around initilization of constant variables
	memcpy(ret,&tmp,sizeof(struct w1_vect));
		
	if(!elSize){
		//invalid type
		return NULL;
	}
	
	//initilize first node
	ret->nodeZero.memory.raw = malloc(ret->elSize*ret->nodeSize);
	if(!ret->nodeZero.memory.raw){
		goto fail0;
	}
	ret->writePtr = &(ret->nodeZero);
	
	if(im==AUTO){
		ret->indSize = INDEX_START_SIZE;
		ret->index = malloc(ret->indSize*sizeof(struct w1_vect*));
		
		if(!ret->index){
			goto fail1;
		}
		ret->index[ret->indLen] = ret->writePtr;
		ret->indLen += 1;
	}
	
	return ret;
	
	fail2:
		free(ret->nodeZero.memory.raw);
	fail1:
		//note that it is ok to call free on NULL
		free(ret->index);
	fail0:
		return NULL;
}