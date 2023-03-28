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
	 return STR_FORMAT_ERR;
	}
	
	/* Find index of EOF */
	for(j = 0; j < cmdStringLen; j++) {
		if(cmdString[j] == EOF_SYM) {
			break;
		}
	}
	
	/* Send error in case EOF isn't found */
	if (cmdString[j] != '!'){
	 return STR_FORMAT_ERR;
	}
	
	/* If a SOF was found look for commands */
	if(i < cmdStringLen) {
		switch(cmdString[i+1]){
			/* In case of the P command is detected */
			case 'P': 
				/* If there is not enough values */
				if(j - i != 6){
					resetCmdString();
					return CS_ERR;
				}
					
				Kp = cmdString[i+2];
				Ti = cmdString[i+3];
				Td = cmdString[i+4];
				
				/* Wrong SumCheck on string return error */
				if((char)(cmdString[i+1]+Kp+Ti+Td)!=cmdString[i+5]){
					printf("%u",cmdString[i+5]);
					resetCmdString();
					return ERR_SUM;
					}
				break;
			
			/* In case of the S command is detected */
			case 'S':
				if(j - i != 2){
					resetCmdString();
					return CS_ERR;
				}
				printf("Setpoint = %d, Output = %d, Error = %d\n", setpoint, output, error);
				resetCmdString();
				break;
			case 'R':
				if(j - i != 2){
					resetCmdString();
					return CS_ERR;
				}
				Kp = 0;
				Ti = 0;
				Td = 0;
				resetCmdString();
				break;
			default:
				return INV_COMAND;
		}
	}
			return OK;

}

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

int newCmdStr(char* newCmd)
{
	int cnt = 0;
	int i,checksum = 0;
	
	/*String size*/
	for(i = 0; newCmd[i] != '\0'; i++)
	{
		cnt++;
	}
	
	/*String size error ( -1 to add checksum)*/
	if(cnt > (MAX_CMDSTRING_SIZE - 3))
	{
		return OVF_STR;
	}
	
	
	cmdString[0] = '#';
	
	/*checksum*/
	if (cnt > 1)
	{
		for(i = 0; i < cnt + 1; i++)
		{
			checksum = checksum + newCmd[i];
			cmdString[i+1] = newCmd[i];
		}
		cmdString[cnt+1] = (unsigned char)(checksum);
		cmdString[cnt+2] = '!';
		cmdStringLen = cnt + 3;	
	}
	else
	{
		for(i = 0; i < cnt + 1; i++)
		{
			cmdString[i+1] = newCmd[i];
		}
		cmdString[cnt+1] = '!';
		cmdStringLen = cnt + 2;	
	}
	

	
	return OK;
}


int resetCmdString(void)
{
	cmdStringLen = 0;		
	return OK;
}
