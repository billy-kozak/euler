#ifndef _FIBONACCI_HEAP_H_
#define _FIBONACCI_HEAP_H_
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include <stdbool.h>
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#define FIBHEAP_SUCCESS 0
#define FIBHEAP_EMPTY   1
#define FIBHEAP_ERR     2
/******************************************************************************
*                                    TYPES                                    *
******************************************************************************/
struct fib_node{
	//pointers to next and prev siblings
	//if no siblings, both point back to this object
	//if root node, points to next and prev root nodes
	struct fib_node*      next;
	struct fib_node*      prev;

	//pointers to parent (NULL for root) and list of children
	struct fib_node*    parent;
	struct fib_node*  children;

	unsigned         nChildren;
	bool                marked;

	void*                  key;
};

struct fib_heap{
	bool              (*const lt)(void*,void*);
	unsigned                              size;
	struct fib_node*                    minPtr;
};
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
void fibHeap_free(struct fib_heap* heap);
struct fib_heap* fibHeap_init(bool (*lt)(void*,void*) );
#endif //_FIBONACCI_HEAP_H_

