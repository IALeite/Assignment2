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
/*  -5: if string size is full and a new char is inputted 		*/
/*  -6: if the end of string char isn't found					*/
/*	-7: if the start of string char isn't found					*/
/*	-8: if missing Kp value 									*/
/*	-9: if missing Ti value										*/
/* -10: if missing Td value 									*/
/* -11: if wrong or missing CheckSum value 						*/
/* ************************************************************ */

enum{ 	ERR_SUM=-11,
		ERR_Td,				/*-10 */
		ERR_Ti,				/* -9 */
		ERR_Kp,				/* -8 */
		ERR_SOF,			/* -7 */
		ERR_EOF,			/* -6 */	
		STR_FULL,			/* -5 */
		STR_FORMAT_ERR,		/* -4 */
		CS_ERR,				/* -3 */
		INV_COMAND,			/* -2 */
		EMPTY_STRING,		/* -1 */
		OK};				/* 0  */

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
	
	/* Send error in case SOF isn't found */
	if (i == cmdStringLen){
	 return ERR_SOF;
	}
	
	/* Find index of EOF */
	for(j = 0; j < cmdStringLen; j++) {
		if(cmdString[j] == EOF_SYM) {
			break;
		}
	}
	
	/* Send error in case EOF isn't found */
	if (cmdString[j] != '!'){
	 return ERR_EOF;
	}
	
	/* If a SOF was found look for commands */
	if(i < cmdStringLen) {

		/* In case of the P command is detected */
		if(cmdString[i+1] == 'P') { 
			
			/* If there is no value for Kp returns error */
			if(cmdString[i+2]=='!')
				return ERR_Kp;
			Kp = cmdString[i+2];
			
			/* If there is no value for Ti returns error */
			if(cmdString[i+3]=='!')
				return ERR_Ti;
			Ti = cmdString[i+3];

			/* If there is no value for Td returns error */
			if(cmdString[i+4]=='!')
				return ERR_Td;
			Td = cmdString[i+4];
			
			/* Wrong SumCheck on string return error */
			if((char)(cmdString[i+1]+Kp+Ti+Td)!=cmdString[i+5])
				return ERR_SUM;

			resetCmdString();
			return OK;
		}

		/* In case of the S command is detected */
		if(cmdString[i+1] == 'S') {
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

/* ******************************** */
/* Displays string length		 	*/
/* ******************************** */
 void getCmdStringLen(void)
{
	printf("String length:%u",cmdStringLen);
}


/* ************************** */
/* Resets the commanbd string */  
/* ************************** */
int resetCmdString(void)
{
	cmdStringLen = 0;		
	return OK;
}
