/******************************************************************************
* Implements converting numbers to english string                             *
*                                                                             *
* i.e. 21 is twenty-one                                                       *
******************************************************************************/
/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "englishNumbers.h"
#include "memHelpers.h"

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
/******************************************************************************
*                                   DEFINES                                   *
******************************************************************************/
#define NULL_CAST(type)	((type*)NULL)
#define MAXU32_DIGITS   10
/******************************************************************************
*                                    TYPES                                    *
******************************************************************************/
struct decDigits{
	uint8_t  digits[MAXU32_DIGITS];
	unsigned len;
};
/******************************************************************************
*                                    DATA                                     *
******************************************************************************/
static const char* english_ones[]={
	"zero","one","two","three","four","five","six","seven","eight","nine"
};
static const char* english_teens[]={
	"ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen",
	"seventeen","eighteen","nineteen"
};
static const char* english_tens[]={
	"zero","ten","twenty","thirty","forty","fifty","sixty","seventy",
	"eighty","ninety"
};

static const char* english_hundreds  ="hundred";

static const char* english_powerWords[] = {
	"","thousand","million","billion"
};
/******************************************************************************
*                             FUNCTION PROTOTYPES                             *
******************************************************************************/
static struct decDigits* toRevDigits(uint32_t n);
static char* sayHundreds(unsigned digit,size_t* len);
static char* say0To9(unsigned digit,size_t* len);
static char* say0To99(unsigned dig2, unsigned dig1,size_t* len);
static char* say10To19(unsigned digit,size_t* len);
static char* say20To99(unsigned dig2, unsigned dig1,size_t* len);
static uint8_t getDigit(struct decDigits* digStruct,int digit);
char* buildPowerStatement(struct decDigits* digStruct,int pow,size_t* len);
static char* englishWordsFromDigits(struct decDigits* digStruct);
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
* Converts given number to sequence of digits (with one's first, tens next...)
*
* Outputs a pointer to malloc allocated memory (NULL on memory error)
**/
static struct decDigits* toRevDigits(uint32_t n){

	struct decDigits* digStruct = malloc(sizeof(*digStruct));

	if(!digStruct){
		return NULL;
	}

	digStruct->len = 0;

	if(!n){
		digStruct->digits[0] = 0;
		digStruct->len = 1;

		return digStruct;
	}

	do{
		uint32_t r = n%10;
		n = n/10;

		assert(digStruct->len <= MAXU32_DIGITS);

		digStruct->digits[digStruct->len] = r;
		digStruct->len += 1;
	}while(n);

	return digStruct;
}
/**
* Get digit from digit struct, return 0 for all digits outside the struct
**/
static uint8_t getDigit(struct decDigits* digStruct,int digit){
	return (digit < digStruct->len)?(digStruct->digits[digit]):(0);
}
/**
* Output a digit as digit*100 as an english string (ex 2 -> "two hundred")
*
* Also stores length of output string (minus trailing null) in *len
**/
static char* sayHundreds(unsigned digit,size_t* len){

	const char* word1 = english_ones[digit];
	const char* word2 = english_hundreds;
	size_t word1Len   = strlen(word1);
	size_t word2Len   = strlen(word2);
	size_t outLen     = word1Len+word2Len+2;

	char*  outStr     = malloc(outLen*sizeof(char));
	if(!outStr){
		return NULL;
	}

	memcpy(outStr,word1,word1Len);
	outStr[word1Len] = ' ';
	memcpy(outStr+word1Len+1,word2,word2Len);
	outStr[outLen-1] = '\0';

	*len = outLen-1;
	return outStr;
}
/**
* Output number from zero to nine as an english string (ex. 7 -> "seven")
*
* Also stores length of output string (minus trailing null) in *len
**/
static char* say0To9(unsigned digit,size_t* len){
	const char* word = english_ones[digit];
	size_t wordLen   = strlen(word)+1;

	char* outStr = malloc(wordLen*sizeof(char));
	if(!outStr){
		return NULL;
	}

	memcpy(outStr,word,wordLen);
	*len = wordLen-1;
	return outStr;
}
/**
* Output digit as 10+digit as an english string (ex. 7 -> "seventeen")
*
* Only numbers 0 to 9 are allowedn as inputs
*
* Also stores length of output string (minus trailing null) in *len
**/
static char* say10To19(unsigned digit,size_t* len){
	const char* word = english_teens[digit];
	size_t wordLen   = strlen(word)+1;

	char* outStr = malloc(wordLen*sizeof(char));
	if(!outStr){
		return NULL;
	}

	memcpy(outStr,word,wordLen);
	*len = wordLen-1;
	return outStr;
}
/**
* Outputs english string of 10*dig2+dig1 (ex. 21 -> "twenty-one")
*
* dig2 can only be [2,9], dig1 can only be [0,9]
*
* Also stores length of output string (minus trailing null) in *len
**/
static char* say20To99(unsigned dig2, unsigned dig1,size_t* len){
	const char* word1 = english_tens[dig2];
	const char* word2 = (dig1)?(english_ones[dig1]):("");
	size_t word1Len   = strlen(word1);
	size_t word2Len   = strlen(word2);
	size_t outLen     = word1Len+word2Len+1+(!!word2Len);

	char*  outStr     = malloc(outLen*sizeof(char));
	if(!outStr){
		return NULL;
	}

	if(!word2Len){
		memcpy(outStr,word1,outLen);
	}
	else{
		memcpy(outStr,word1,word1Len);
		outStr[word1Len] = '-';
		memcpy(outStr+word1Len+1,word2,word2Len);
		outStr[outLen-1] = '\0';
	}

	*len = outLen-1;
	return outStr;
}
/**
* Outputs number dig2*10+dig1 as an english string (ex. 21 -> "twenty-one")
*
* dig2 can only be [0,9], dig1 can only be [0,9]
*
* Also stores length of output string (minus trailing null) in *len
**/
static char* say0To99(unsigned dig2, unsigned dig1,size_t* len){
	if(!dig2){
		return say0To9(dig1,len);
	}
	else if(dig2 == 1){
		return say10To19(dig1,len);
	}
	else{
		return say20To99(dig2,dig1,len);
	}
}
/**
* Outputs number dig3*100+dig2*10+dig1 as an english string
*
* dig1 dig2 and dig3 can only be [0,9]
*
* Also stores length of output string (minus trailing null) in *len
**/
static char* say0To999(unsigned dig3,unsigned dig2, unsigned dig1, size_t*len){
	size_t word1Len = 0;
	size_t word2Len = 0;

	bool  noWord2   = dig3&&(!dig2 && !dig1);

	char* word1 = (dig3)?(sayHundreds(dig3,&word1Len)):("");
	char* word2 = (!noWord2)?(say0To99(dig2,dig1,&word2Len)):("");

	const char* sep = (word1Len&&word2Len)?(" and "):("");
	size_t sepLen   = strlen(sep);

	size_t outLen = word1Len+word2Len+sepLen+1;

	char*  outStr     = malloc(outLen*sizeof(char));

	if(!word1 || !word2 || !outStr){

		if(word1Len){
			free(word1);
		}
		if(word2Len){
			free(word2);
		}
		free(outStr);
		return NULL;
	}

	assert(word1Len || word2Len);

	if(!word2Len){
		memcpy(outStr,word1,outLen);

		free(word1);
	}
	else if(!word1Len){
		memcpy(outStr,word2,outLen);

		free(word2);
	}
	else{
		memcpy(outStr,word1,word1Len);
		memcpy(outStr+word1Len,sep,sepLen);
		memcpy(outStr+word1Len+sepLen,word2,word2Len);
		outStr[outLen-1] = '\0';

		free(word1);
		free(word2);
	}

	*len = outLen-1;
	return outStr;
}
/**
* Build an english statement that describes some number * 1000^n
*
* Output is empty is the numbers in digStruct are 0 for the particular power
* of 1000
**/
char* buildPowerStatement(struct decDigits* digStruct,int pow,size_t* len){
	const char* powerWord = english_powerWords[pow];
	size_t powerWordLen   = strlen(powerWord);

	uint8_t dig3 = getDigit(digStruct,3*pow+2);
	uint8_t dig2 = getDigit(digStruct,3*pow+1);
	uint8_t dig1 = getDigit(digStruct,3*pow+0);

	char* numWord = NULL;
	size_t numWordLen = 0;

	char* output = NULL;

	if( !dig3 && !dig2 && !dig1 ){
		// return empty string if all digits are zero
		*len = 0;
		return calloc(1,sizeof(char));
	}

	numWord = say0To999(dig3,dig2,dig1,&numWordLen);
	if(!numWord){
		return NULL;
	}

	if(!powerWordLen){
		//for zero len power word, we just return the numWord
		*len = numWordLen;
		return numWord;
	}

	*len = numWordLen+1+powerWordLen;

	//extend memory but leave one space for ' ' after numWord
	//also, copy the trailing NULL byte on the powerWord
	output = memExtend(
		numWord,powerWord,
		numWordLen+1,powerWordLen+1
	);

	if(!output){
		free(numWord);
		return NULL;
	}

	output[numWordLen] = ' ';

	return output;
}
/**
* Prints english words for numbers from list of digits
*
* Number represented must not be zero
**/
static char* englishWordsFromDigits(struct decDigits* digStruct){

	char* sepWord = " ";
	size_t sepLen = strlen(sepWord);
	struct lenMem sep = {sepWord,sepLen};

	int wordCount = (digStruct->len/3)+!!(digStruct->len%3);

	struct lenMem* words = calloc(wordCount,sizeof(*words));

	char* output = NULL;

	int wInd = 0;

	if(!words){
		goto fail0;
	}

	for(int i = (wordCount-1); i >= 0; i--){

		words[wInd].mem = buildPowerStatement(
			digStruct,i,&(words[wInd].len)
		);

		if(!words[wInd].mem){
			goto fail1;
		}

		if(words[wInd].len){
			wInd += 1;
		}
		else{
			free(words[wInd].mem);
		}
	}
	//include trailing null on this word
	words[wInd-1].len += 1;

	output = memJoin(words,&sep,wInd).mem;

	if(!output){
		goto fail1;
	}
	for(int i = 0; i < wInd; i++){
		free(words[i].mem);
	}
	free(words);

	return output;
fail1:
	for(int i = 0; i < wordCount; i++){
		free(words[i].mem);
	}
fail0:
	free(words);
	return NULL;
}
/**
* Outputs 32 bit number as an english string
**/
char* numToEnglish(uint32_t num){

	struct decDigits* digStruct = toRevDigits(num);

	char* output = NULL;

	if(!digStruct){
		return NULL;
	}
	if(!num){
		size_t dummy;
		output = say0To999(0,0,0,&dummy);
	}
	else{
		output = englishWordsFromDigits(digStruct);
	}

	free(digStruct);
	return output;
}