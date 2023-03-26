/* ***************************************************** */
/* SETR 22/23, Paulo Pedreiras                           */
/* Base code for Unit Testing                            */
/*   A few tests to the cmdProcessor                     */
/*      just to illustrate how it works                  */
/*   Shoud be improved (e.g. test more cases)            */
/*                                                       */
/* Compile with: gcc cmdproc.c main.c -o main            */
/*                                                       */
/* ***************************************************** */
#include <stdio.h>
#include "cmdproc.h"
#include "../unity/unity.h"

extern char Kp, Ti, Td, CheckSum;


void test_cmdProcessor_should_res_KP_Ti_Td(void)
{
	char CheckSum = (unsigned char)('P'+'1'+'2'+'3');
	resetCmdString();
	newCmdChar('#');
	newCmdChar('P');
	newCmdChar('1');
	newCmdChar('2');
	newCmdChar('3');
	newCmdChar(CheckSum);
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT(0,cmdProcessor());
	TEST_ASSERT_EQUAL_INT('1', Kp);
	TEST_ASSERT_EQUAL_INT('2', Ti);
	TEST_ASSERT_EQUAL_INT('3', Td);	
}


void test_EmptyString_should_0(void)
{
	resetCmdString();
	TEST_ASSERT_EQUAL_INT(-1,cmdProcessor());
}

void test_FullString(void)
{
	resetCmdString();
	/* Fills the string max size(10) with SOF */
	int i;
	for(i=0;i<10;i++){
		newCmdChar('#');
	}
	TEST_ASSERT_EQUAL_INT(-5,newCmdChar('#'));
	
}

void test_InvalidCmd(void)
{
	resetCmdString();
	newCmdChar('#');
	newCmdChar('D');	/*check invalid command D */
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT(-2,cmdProcessor());
}

void test_InvalidSOF(void)
{	
	resetCmdString();
	newCmdChar('+');	/* check invalid SOF */
	newCmdChar('S');
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT(-7,cmdProcessor());
}

void test_InvalidEOF(void)
{	
	resetCmdString();
	newCmdChar('#');
	newCmdChar('S');
	newCmdChar('-');
	TEST_ASSERT_EQUAL_INT_MESSAGE(-6,cmdProcessor(),"wrong char passed!");
	newCmdChar('#'); 	/* check invalid EOF */
	newCmdChar('S');
	TEST_ASSERT_EQUAL_INT_MESSAGE(-6,cmdProcessor(),"Nothing passed");
}


void test_invalid_Kp(void)
{
	/*check Kp error */
	resetCmdString();
	newCmdChar('#');
	newCmdChar('P');
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT_MESSAGE(-8,cmdProcessor(),"missing value Kp");
}

void test_invalid_Ti(void)
{
	/*check Ti error */
	resetCmdString();
	newCmdChar('#');
	newCmdChar('P');
	newCmdChar('1');
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT_MESSAGE(-9,cmdProcessor(),"missing value Ti");
}

void test_invalid_Td(void)
{
	/* check Td error */
	resetCmdString();
	newCmdChar('#');
	newCmdChar('P');
	newCmdChar('1');
	newCmdChar('2');
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT_MESSAGE(-10,cmdProcessor(),"missing value Td");
}

void test_invalid_sumCheck(void)
{
	/* check SumCheck error */
	resetCmdString();
	newCmdChar('#');
	newCmdChar('P');
	newCmdChar('1');
	newCmdChar('2');
	newCmdChar('3');
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT_MESSAGE(-11,cmdProcessor(),"missing or wrong SumCheck");
}

void test_cmdProcessor_S(void){
	resetCmdString();
	newCmdChar('#');
	newCmdChar('S');
	newCmdChar('!');
	TEST_ASSERT_EQUAL_INT(0,cmdProcessor());
}

int main(void) 
{
	UNITY_BEGIN();
	RUN_TEST(test_cmdProcessor_should_res_KP_Ti_Td);
	RUN_TEST(test_EmptyString_should_0);
	RUN_TEST(test_FullString);
	RUN_TEST(test_InvalidCmd);
	RUN_TEST(test_InvalidSOF);
	RUN_TEST(test_InvalidEOF);
	RUN_TEST(test_invalid_Kp);
	RUN_TEST(test_invalid_Ti);
	RUN_TEST(test_invalid_Td);
	RUN_TEST(test_invalid_sumCheck);
	RUN_TEST(test_cmdProcessor_S);
	return UNITY_END();
}
