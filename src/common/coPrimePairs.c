/******************************************************************************
* Implements functionality relating to the generation of coprime numbers      *
*                                                                             *
* References:                                                                 *
*         http://en.wikipedia.org/wiki/Coprime_integers                       *
******************************************************************************/
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "coPrimePairs.h"

#include <string.h>
#include <stdlib.h>
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#define START_TREE_EVENODD {{2,1},NULL,NULL,NULL,NULL}
#define START_TREE_ODDODD  {{3,1},NULL,NULL,NULL,NULL}
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
* Generates "left" branch of the coPrimeTree
*
* Generated node is added to the left most node reachable from the given root
**/
struct coPrimeTree* coPrimeTree_genLeft(struct coPrimeTree * tree){
	struct coPrimeTree* leaf = tree;
	
	//now generate new node and zero it
	struct coPrimeTree* new = calloc(sizeof(struct coPrimeTree),1);
	if(!new){
		//memory error
		return NULL;
	}
	
	//first find left most leaf node
	while(leaf->left){
		leaf = leaf->left;
	}
	
	new->val.m = 2*leaf->val.m - leaf->val.n;
	new->val.n = leaf->val.m;
	
	leaf->left = new;
	new->parent = leaf;
	
	return new;
}
/**
* Generates "mid" branch of the coPrimeTree
*
* Node is added to the "mid most" node reachable from the given root (i.e.
* the node found by following the middle child of each succesive node all the
* way to a leaf node).
**/
struct coPrimeTree* coPrimeTree_genMid(struct coPrimeTree * tree){
	struct coPrimeTree* leaf = tree;
	
	//now generate new node and zero it
	struct coPrimeTree* new = calloc(sizeof(struct coPrimeTree),1);
	if(!new){
		//memory error
		return NULL;
	}
	
	//first find left most leaf node
	while(leaf->mid){
		leaf = leaf->mid;
	}
	
	new->val.m = 2*leaf->val.m + leaf->val.n;
	new->val.n = leaf->val.m;
	
	leaf->mid = new;
	new->parent = leaf;
	
	return new;
}
/**
* Generates "right" branch of the coPrimeTree
*
* Generated node is added to the right most node reachable from the given root
**/
struct coPrimeTree* coPrimeTree_genRight(struct coPrimeTree * tree){
	struct coPrimeTree* leaf = tree;
	
	//now generate new node and zero it
	struct coPrimeTree* new = calloc(sizeof(struct coPrimeTree),1);
	if(!new){
		//memory error
		return NULL;
	}
	
	//first find left most leaf node
	while(leaf->right){
		leaf = leaf->right;
	}
	
	new->val.m = leaf->val.m + 2*leaf->val.n;
	new->val.n = leaf->val.n;
	
	leaf->right = new;
	new->parent = leaf;
	
	return new;
}
/**
* Frees dynamic memory associated with each node of the tree
**/
void coPrimeTree_free(struct coPrimeTree * tree){
	if(tree->right){
		coPrimeTree_free(tree->right);
	}
	if(tree->mid){
		coPrimeTree_free(tree->mid);
	}
	if(tree->left){
		coPrimeTree_free(tree->left);
	}
	
	free(tree);
}
/**
* Initilizes a coprime tree of given type
*
* These trees can be used to enumerate all coprime numbers. The value of
* the coprime numbers strictly increases as you go down the tree. Each of
* the left, middle and right child nodes are generated using a specific
* formula; this can be exploited for some purposes.
*
* coprime trees can produce only pairs which are both odd or pairs which
* have one odd, and one even value.
**/
struct coPrimeTree* coPrimeTree_start(enum coPrimeTree_Type t){
	
	struct coPrimeTree *ret = malloc(sizeof(struct coPrimeTree));
	if(!ret){
		return NULL;
	}
	
	if(t == EVEN_ODD){
		struct coPrimeTree tmp = START_TREE_EVENODD;
		memcpy(ret,&tmp,sizeof(tmp));
	}
	else if(t == ODD_ODD){
		struct coPrimeTree tmp = START_TREE_ODDODD;
		memcpy(ret,&tmp,sizeof(tmp));
	}
	else{
		free(ret);
		return NULL;
	}
	
	return ret;
}