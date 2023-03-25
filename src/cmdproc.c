/* ***************************************************** */
/* SETR 22/23, Paulo Pedreiras                           */
/* Base code for Unit Testing                            */
/*    Simple example of command processor                */
/*    Note that there are several simplifications        */
/*    E.g. Kp, Ti and Td usually are not integer values  */
/*    Code can (and should) be improved. E.g. error      */ 
/*        codes are "magic numbers" in the middle of the */
/*        code instead of being (defined) text literals  */
/* ***************************************************** */

#include <stdio.h>

#include "cmdproc.h"

/* PID parameters */
/* Note that in a real application these vars would be extern */
 char Kp, Ti, Td, CheckSum;

/* Process variables */ 
/* Note that in a real application these vars would be extern */
int setpoint, output, error; 

/* Internal variables */
static char cmdString[MAX_CMDSTRING_SIZE];
static unsigned char cmdStringLen = 0; 

/* ************************************************************ */
/* Processes the the chars received so far looking for commands */
/* Returns:                                                     */
/*   0: if a valid command was found and executed        	    */
/* 	-1: if empty string or incomplete command found             */
/* 	-2: if an invalid command was found                         */
/* 	-3: if a CS error is detected (command not executed)        */
/* 	-4: if string format is wrong                               */
/* ************************************************************ */

enum{ 	ERR_SOF = -7,
		ERR_EOF,
		STR_FULL,
		STR_FORMAT_ERR,
		CS_ERR,
		INV_COMAND,
		EMPTY_STRING,
		OK};

int cmdProcessor(void)
{
	int i, j;
	/* Detect empty cmd string */
	if(cmdStringLen == 0)
		return EMPTY_STRING; 
	
	/* Find index of SOF */
	for(i = 0; i < cmdStringLen; i++) {
		if(cmdString[i] == SOF_SYM) {
			break;
		}
	}
	
	if (i == cmdStringLen){
	 return ERR_SOF;
	}
	
	/* Find index of EOF */
	for(j = 0; j < cmdStringLen; j++) {
		if(cmdString[j] == EOF_SYM) {
			break;
		}
	}
	
	if (cmdString[j] != '!'){
	 return ERR_EOF;
	}
	
	/* If a SOF was found look for commands */
	if(i < cmdStringLen) {
		if(cmdString[i+1] == 'P') { /* P command detected */
			Kp = cmdString[i+2];
			Ti = cmdString[i+3];
			Td = cmdString[i+4];
			resetCmdString();
			return OK;
		}
		
		if(cmdString[i+1] == 'S') { /* S command detected */
			printf("Setpoint = %d, Output = %d, Error = %d", setpoint, output, error);
			resetCmdString();
			return OK;
		}		
	}
	
	/* cmd string not null and SOF not found */
	return INV_COMAND;

}

/* ******************************** */
/* Adds a char to the cmd string 	*/
/* Returns: 				        */
/*  	 0: if success 		        */
/* 		-1: if cmd string full 	    */
/* ******************************** */
int newCmdChar(unsigned char newChar)
{
	/* If cmd string not full add char to it */
	if (cmdStringLen < MAX_CMDSTRING_SIZE) {
		cmdString[cmdStringLen] = newChar;
		cmdStringLen +=1;
		return OK;		
	}
	
	/* If cmd string full return error */
	return STR_FULL;
}

/**
 * getCmdStringLen(void)
 */

/* ************************** */
/* Resets the commanbd string */  
/* ************************** */
int resetCmdString(void)
{
	cmdStringLen = 0;		
	return OK;
}
