#ifndef _MY_SIMPLE_TEST_FRAMEWORK_H_
#define _MY_SIMPLE_TEST_FRAMEWORK_H_
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#define _STRINGIFY(x) #x
#define _TOSTRING(x) _STRINGIFY(x)

/**
* Print message to indicate that testing is done
**/
#define MSTF_MSGDONE(f,t) \
	if(f) printf("\n"); \
	printf("TESTS COMPLETED WITH %d failures out of %d total tests!\n",f,t)

/**
* Format test failure error message
**/
#define MSTF_FORMAT_ERR(m) \
	("Test Failure at line " _TOSTRING(__LINE__) ": " m "\n")

/**
* Place in function to start block of tests to run
**/
#define MSTF_START() \
	do{ struct mstfData _data = {0};
/**
* Declare between MSTF_START and MSTF_END to run a test. If the boolean value
* of the test is false then the test has failed.
**/
#define MSTF_RUN(message,test) \
		_data.ret = (test)?(NULL):(MSTF_FORMAT_ERR(message)); \
		if(!_data.ret){;_data.pass++;} \
		else{fputs(_data.ret,stderr);_data.fail++;}

/**
* Place in function after MSTF_START() and all tests to close test block
**/
#define MSTF_END() \
		MSTF_MSGDONE(_data.fail,_data.fail+_data.pass);}while(0);
/******************************************************************************
*                                    TYPES                                    *
******************************************************************************/	
struct mstfData{
	char* ret;
	int fail;
	int pass;
};
#endif //_MY_SIMPLE_TEST_FRAMEWORK_H_