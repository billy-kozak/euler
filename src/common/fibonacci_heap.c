/******************************************************************************
* Implments a fibonacci heap                                                  *
******************************************************************************/
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "fibonacci_heap.h"

#include <string.h>
#include <stdlib.h>

#include <assert.h>
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
static struct fib_node* minNode(
		struct fib_node* n1, struct fib_node* n2,struct fib_heap* heap
	);
static void treeList_merge(struct fib_node* l1, struct fib_node* l2);
static void delete_parent(struct fib_node* children);
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
*
**/
static void treeList_merge(struct fib_node* l1, struct fib_node* l2){

	struct fib_node* l1First = l1;
	struct fib_node* l1Last  = l1->prev;
	struct fib_node* l2First = l2;
	struct fib_node* l2Last  = l2->prev;

	l1First->prev = l2Last;
	l1Last->next  = l2First;

	l2Last->next  = l1First;
	l2First->prev = l1Last;
}
/**
*
**/
static void delete_parent(struct fib_node* children){
	struct fib_node* c = children;

	if(!c){
		return;
	}

	do{
		c->parent = NULL;
		c = c->next;

	}while( c != children );
}
/**
*
**/
static void remove_root(struct fib_node* rootPtr){
	struct fib_node* prev = rootPtr->prev;
	struct fib_node* next = rootPtr->next;

	prev->next = next;
	next->prev = prev;
}
/**
*
**/
static struct fib_node* minNode(
		struct fib_node* n1, struct fib_node* n2,struct fib_heap* heap
	){
	if(n1 == NULL){
		return n2;
	}
	else if(n2 == NULL){
		return n1;
	}

	return ( heap->lt(n1->key,n2->key) )?(n1):(n2);
}
/**
*
**/
int fibHeap_extractMin(struct fib_heap* heap,void** ret){
	struct fib_node* min     = heap->minPtr;

	if(!min){
		return FIBHEAP_EMPTY;
	}

	*ret = min->key;

	delete_parent(min->children);
	remove_root(min);

	/* TODO - Perform the Balancing act */
	/* TODO - free unused memory */

	return FIBHEAP_SUCCESS;
}
/**
* Insert element into the heap
**/
int fibHeap_insert(struct fib_heap* heap, void* k){

	struct fib_node* root = calloc(1,sizeof(*root));

	if(!root){
		goto fail;
	}

	root->key  = k;

	if( !heap->minPtr ){
		heap->minPtr = root;
		root->prev = root;
		root->next = root;
	}
	else{
		root->prev = heap->minPtr->prev;
		root->next = heap->minPtr;

		root->prev->next = root;
		root->next->prev = root;

		if( heap->lt(root->key,heap->minPtr->key) ){
			heap->minPtr = root;
		}
	}

	return FIBHEAP_SUCCESS;
fail:
	free(root);
	return FIBHEAP_ERR;
}
/**
* Merges together two fibonacci heaps
**/
struct fib_heap* fibHeap_merge(struct fib_heap* h1, struct fib_heap* h2){

	assert(h1->lt == h2->lt);

	if( !h2->minPtr ){
		fibHeap_free(h2);
		return h1;
	}
	else if( !h1->minPtr ){
		fibHeap_free(h1);
		return h2;
	}

	treeList_merge(h1->minPtr,h2->minPtr);

	h1->minPtr = minNode(h1->minPtr,h2->minPtr,h1);
	h2->minPtr = NULL;

	fibHeap_free(h2);
	return h1;
}
/**
* Returns value of minimum object
**/
int fibHeap_findMinimum(struct fib_heap* heap,void** ret){
	if(!heap->minPtr){
		return FIBHEAP_EMPTY;
	}

	*ret = &(heap->minPtr->key);
	return FIBHEAP_SUCCESS;
}
/**
* Free all dynamic memory associated with the heap
**/
void fibHeap_free(struct fib_heap* heap){
	free(heap);

	/* TODO free all dynamic memory assocated with all nodes; this will
	require a full tree traversal implementation */
}
/**
* Initilizes a fib heap object
**/
struct fib_heap* fibHeap_init( bool (*lt)(void*,void*) ){
	struct fib_heap tmp     = {lt,NULL};
	struct fib_heap* output = malloc(sizeof(*output));

	if(!output){
		return NULL;
	}

	memcpy(output,&tmp,sizeof(tmp));
	return output;
}
