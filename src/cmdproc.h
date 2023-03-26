#ifndef __CMD_PROC_H_
#define __CMD_PROC_H_

#define MAX_CMDSTRING_SIZE 10 /* Maximum size of the command string */ 
#define SOF_SYM '#'	          /* Start of Frame Symbol */
#define EOF_SYM '!'           /* End of Frame Symbol */

/* ************************************************************ */
/*			                                                    */
/*   0: if a valid command was found and executed        	    */
/* 	-1: if empty string or incomplete command found             */
/* 	-2: if an invalid command was found                         */
/* 	-3: if a CS error is detected (command not executed)        */
/* 	-4: if string format is wrong                               */
/*  -5: if string size is full and a new char is inputted 		*/
/*  -6: if the end of string char isn't found					*/
/*	-7: if the start of string char isn't found					*/
/* -8: if wrong CheckSum value 									*/
/* ************************************************************ */


enum{ 	OVF_STR = -9,
		ERR_SUM,			/* -8 */
		ERR_SOF,			/* -7 */
		ERR_EOF,			/* -6 */	
		STR_FULL,			/* -5 */
		STR_FORMAT_ERR,		/* -4 */
		CS_ERR,				/* -3 */
		INV_COMAND,			/* -2 */
		EMPTY_STRING,		/* -1 */
		OK};				/*  0 */

/* Function prototypes */
int cmdProcessor(void);

int newCmdChar(unsigned char newChar);

int resetCmdString(void);

void getCmdStringLen(void);

int newCmdStr(char* newCmd);

#endif
