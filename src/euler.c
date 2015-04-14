/******************************************************************************
* Contains program main for project euler solver                              *
*                                                                             *
* Implements main, sets up and starts solver running                          *
******************************************************************************/

/******************************************************************************
*                                  INCLUDES                                   *
******************************************************************************/
#include "euler.h"

#include <time.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
/******************************************************************************
*                                    DATA                                     *
******************************************************************************/
const char* USAGE=" [-h] [-q] probNum";
const char* HELP= "Solves project euler programs\n"
	"\n"
	"USAGE: %s\n"
	"\n"
	"Options:\n"
	"--help,-h         Prints this help message\n"
	"\n"
	"--quiet,-q        Only prints problem solution and nothing else\n";
/******************************************************************************
*                            FUNCTION DECLARATIONS                            *
******************************************************************************/
static struct euler_progOpts get_progOpts(int argc, char** argv);
static void printHelp(const char* progName);
static int strTo_positiveInt(const char* s,long* i);
static char* usageString(const char* progName);
static void fprintUsage(FILE* fp,const char* progName);
/******************************************************************************
*                            FUNCTION DEFINITIONS                             *
******************************************************************************/
/**
* Creates a usage string in dynamic memory
*
* memory returned must be freed
**/
static char* usageString(const char* progName){
	char* u = calloc(sizeof(char),strlen(USAGE)+strlen(progName)+1);
	
	sprintf(u,"%s%s",progName,USAGE);
	
	return u;
}
/**
* Prints the program help message
**/
static void printHelp(const char* progName){
	char* u = usageString(progName);
	printf(HELP,u);
	free(u);
}
/**
* Prints the program usage message
**/
static void fprintUsage(FILE* fp,const char* progName){
	char* u = usageString(progName);
	fprintf(fp,"USAGE: %s\n",u);
	free(u);
}
/**
* Converts string to a positive integer
*
* If anything either than a positive integer representation (with optional,
* arbitrary, leading and trailing whitespace) in base 10 or hexidecimal (with
* leading 0x to denote) is given then no conversion takes place. The conversion
* will fail if the integer is out of range of the system long.
*
* Args:
* s - string to convert
* i - pointer to space for integer output. On success the converted value
* 	will be placed here. On failure this will not be changed.
* Returns:
* zero on success and 1 on falilure.
**/
static int strTo_positiveInt(const char* s,long* i){
	long temp;
	char* endptr = (char*)s;
	
	errno = 0;
	temp = strtoul(s,&endptr,0);
	
	if(errno || (temp<0) ){
		return 1;
	}
	
	while(*endptr){
		if(!isspace(*endptr)){
			return 1;
		}
	}
	
	*i = temp;
	return 0;
}
/**
* Produce program options
**/
static struct euler_progOpts get_progOpts(int argc, char** argv){
	struct euler_progOpts opts = {0};
	const char* optstring = "hq";
	struct option oTab[] = {
		{"help" ,no_argument,NULL,'h'},
		{"quiet",no_argument,NULL,'q'},
		{NULL,0,NULL,0}
	};
	int c;
	int longInd = 0;
	
	while( (c = getopt_long(argc,argv,optstring,oTab,&longInd) ) != -1){
		switch(c){
			case 'h':
				printHelp(argv[0]);
				exit(0);
				break;
			case 'q':
				opts.quiet = true;
				break;
			case '?':
				fprintUsage(stderr,argv[0]);
				exit(1);
				break;
			default:
				fprintf(stderr,"Unkown arg error\n");
				fprintUsage(stderr,argv[0]);
				exit(1);
				break;
		}
	}
	
	if(optind < (argc-1)){
		fprintf(stderr,"Error: too many arguments\n");
		fprintUsage(stderr,argv[0]);
		exit(1);
	}
	else if(optind == argc){
		fprintf(
				stderr,
				"Error: too few arguments, require problem"
				" number\n"
			);
		fprintUsage(stderr,argv[0]);
		exit(1);
	}
	
	long temp;
	if(strTo_positiveInt(argv[optind],&temp)){
		fprintf(
			stderr,
			"Error: expected positive integer, got \"%s\"\n",
			argv[optind]
		);
		fprintUsage(stderr,argv[0]);
		exit(1);
	}
	
	opts.probNum = temp;
	
	return opts; 
}
/**
* program entry
**/
int main(int argc, char** argv){
	
	const struct euler_progOpts opts = get_progOpts(argc,argv);
	struct timespec t1;
	struct timespec t2;
	
	
	if(clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&t1) ){
		perror("Error measuring time\n");	
	}
	
	if(clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&t2) ){
		perror("Error measuring time\n");	
	}
	
	if(!opts.quiet){
		double elapsed = 
			(double)(t2.tv_sec-t1.tv_sec) +
			((double)(t2.tv_nsec-t1.tv_nsec))/1000000.0;
			
		printf("Completed in %lf seconds\n",elapsed);
	}
	
	return 0;
}
