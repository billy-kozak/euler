/******************************************************************************
* If the numbers 1 to 5 are written out in words: one, two, three, four,      *
* five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.          *
*                                                                             *
* If all the numbers from 1 to 1000 (one thousand) inclusive were written out *
* in words, how many letters would be used?                                   *
*                                                                             *
* NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and   *
* forty-two) contains 23 letters and 115 (one hundred and fifteen) contains   *
* 20 letters. The use of "and" when writing out numbers is in compliance with *
* British usage.                                                              *
******************************************************************************/
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "eulerProblems.h"
#include "eulerSolvers.h"
#include "englishNumbers.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#define PROBLEM_17_MAGIC_TOP 1000
#define PROBLEM_17_MAGIC_BOT 1
#define PRINT_NUMS           0
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
static unsigned countEnglishNumLetters(uint32_t bot, uint32_t top);
static unsigned countAlpha(char* s);
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
* Counts the number of alpha numeric characters in a string
**/
static unsigned countAlpha(char* s){
	unsigned count = 0;
	while(*s){
		count += !!isalpha(*s);
		s+=1;
	}

	return count;
}
/**
* Counts the number of letters in english numbers
**/
static unsigned countEnglishNumLetters(uint32_t bot, uint32_t top){

	unsigned count = 0;

	for(uint32_t i = bot; i <= top; i++){
		char* english = numToEnglish(i);

		if(PRINT_NUMS){
			printf("%s\n",english);
		}

		if(!english){
			return 0;
		}
		count += countAlpha(english);
		free(english);
	}

	return count;
}
/**
* Solution for problem 17
**/
struct eulerSol euler_prob17(void){
	struct eulerSol sol = {UNSIGNED};

	sol.val.u = countEnglishNumLetters(
		PROBLEM_17_MAGIC_BOT,
		PROBLEM_17_MAGIC_TOP
	);

	return sol;
}
