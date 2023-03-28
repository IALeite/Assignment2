#ifndef __CMD_PROC_H_
#define __CMD_PROC_H_

#define MAX_CMDSTRING_SIZE 10 /* Maximum size of the command string */ 
#define SOF_SYM '#'	          /* Start of Frame Symbol */
#define EOF_SYM '!'           /* End of Frame Symbol */

/**\file cmdProc
 *
 * */


/** \brief Enum with error codes
 * 
 *  0: Executed function with success		                                                          	    
 * -1: empty string          
 * -2: an invalid command was found                         
 * -3: a CS error is detected (command not executed)        
 * -4: string format is wrong                               
 * -5: string size is full and a new char is inputted 						
 * -6: wrong CheckSum value 	
 * -7: String to long to be command
 * 							*/
 
enum{ 	OVF_STR = -7,
		ERR_SUM,			/* -6 */	
		STR_FULL,			/* -5 */
		STR_FORMAT_ERR,		/* -4 */
		CS_ERR,				/* -3 */
		INV_COMAND,			/* -2 */
		EMPTY_STRING,		/* -1 */
		OK};				/*  0 */
		

/* Function prototypes */
/**
 * \brief function responsible for processing the command string
 * \returns 0: OK -1:Empty String -2:Invalid Cmd -3:Cmd with errors -4: String format wrong -6: Error Checksum 
 */
int cmdProcessor(void);

/**
 * \brief function responsible for insert a new char in command string
 * \returns 0: OK -5: string full
 */
int newCmdChar(unsigned char newChar);

/**
 * \brief function responsible for reset command string
 * \returns 0: OK
 */
int resetCmdString(void);

/**
 * \brief function responsible for insert a string in command string
 * \returns 0: OK -7: string too big 
 */
int newCmdStr(char* newCmd);

#endif
