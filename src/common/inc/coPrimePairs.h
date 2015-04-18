#ifndef _CO_PRIME_PAIRS_H_
#define _CO_PRIME_PAIRS_H_
/******************************************************************************
*                                    TYPES                                    *
******************************************************************************/
//coprime pair, m is greater than n
struct coPrimePair{
	unsigned m;
	unsigned n;
};

enum coPrimeTree_Type{
	EVEN_ODD,ODD_ODD
};

struct coPrimeTree{
	struct coPrimePair val;
	
	struct coPrimeTree* left;
	struct coPrimeTree* mid;
	struct coPrimeTree* right;
	
	struct coPrimeTree* parent;
};
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
struct coPrimeTree* coPrimeTree_start(enum coPrimeTree_Type t);
struct coPrimeTree* coPrimeTree_genLeft(struct coPrimeTree * tree);
struct coPrimeTree* coPrimeTree_genMid(struct coPrimeTree * tree);
struct coPrimeTree* coPrimeTree_genRight(struct coPrimeTree * tree);
struct coPrimeTree* coPrimeTree_start(enum coPrimeTree_Type t);
void coPrimeTree_free(struct coPrimeTree * tree);
#endif //_CO_PRIME_PAIRS_H_