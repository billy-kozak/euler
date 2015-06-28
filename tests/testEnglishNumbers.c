/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "common/englishNumbers.c"
#include "common/memHelpers.c"

//all other includes should come after the source file include!
#include "mySimpleTestFramework.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
static bool testEnglishConversion(uint32_t n,char* exp);
/******************************************************************************
*                                    TESTS                                    *
******************************************************************************/
/**
* Test conversion of number to english string
**/
static bool testEnglishConversion(uint32_t n,char* exp){

	char* english = numToEnglish(n);
	size_t expLen = strlen(exp);
	size_t engLen = strnlen(english,expLen+1);
	bool ret = false;

	if(expLen == engLen){
		ret = !strncmp(english,exp,expLen+1);
	}

	free(english);
	return ret;
}
/**
* Test entry point
**/
int main(int argc, char** argv){
	 MSTF_START();
	 	MSTF_RUN(
	 			"failed english '1'",
	 			testEnglishConversion(1,"one")
	 		);
	 	MSTF_RUN(
	 			"failed english '123'",
	 			testEnglishConversion(
	 				123,"one hundred and twenty-three"
	 			)
	 		);
	 	MSTF_RUN(
	 			"failed english '300'",
	 			testEnglishConversion(
	 				300,"three hundred"
	 			)
	 		);
	 	MSTF_RUN(
	 			"failed english '1000'",
	 			testEnglishConversion(
	 				1000,"one thousand"
	 			)
	 		);
	 	MSTF_RUN(
	 			"failed english '2,800,564,945'",
	 			testEnglishConversion(
	 				2800564945,
	 				"two billion "
	 				"eight hundred million "
	 				"five hundred and sixty-four thousand "
	 				"nine hundred and forty-five"
	 			)
	 		);
	 MSTF_END();

	 return 0;
}