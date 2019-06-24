/*     __  _  _  ____   __    __   ____  _  _
*    _(  )/ )( \(  _ \ /  \  /  \ (_  _)( \/ )
*   / \) \) __ ( ) _ ((  O )(  O )  )(   )  /
*   \____/\_)(_/(____/ \__/  \__/  (__) (__/
*
*
*	Bootloader für einige __AVR__ Typen
*
*/

#ifndef F_CPU
#define F_CPU	16e6
#endif

typedef void (*jump_fnc)(void); // ((jump_fnc)0x0000)();
#define JUMP_APP_ADDR	0
#define JUMP_TO_APP		((jump_fnc)JUMP_APP_ADDR())

#include <avr/io.h>
#include <avr/boot.h>
#include "inc/uart.h"


/*	Hex File
*
*	: | 10 | 0100 | 00 | 214601360121470136007EFE09D21901 | 40
*---------------------------------------------------------------
*	Start Sign , Length , Address , Record Typ , Data Field , Checksumm
*
*/
enum Parser_States
{
	_PARSER_FILE_BEGINN,	
	_PARSER_LENGTH,	
	_PARSER_ADDRESS,	
	_PARSER_TYP,	
	_PARSER_DATA,
	_PARSER_END_CRC,
	_PARSER_FAILD,
};

typedef struct  
{
	uint8_t uiFlashBuffer[SPM_PAGESIZE];
	uint8_t	uiHexBuffer[5];
	uint8_t uiRxCounter;
	uint8_t uiHexCRC;		
	
	enum Parser_States ParserState;
	
}SelfProgramming_t;


uint16_t AsciiToNumeric( const uint8_t *pData , uint8_t Lenght )
{
	uint8_t  i;
	uint16_t Result = 0;

	for ( i = 0 ; i < Lenght ; i++ )
	{
		uint8_t c = pData[i];
		
		if (c >= '0' && c <= '9')
		{
			c -= '0';
		}            
		else if (c >= 'A' && c <= 'F')
		{
			c -= 'A' - 10;
		}       
		else if (c >= 'a' && c <= 'f')       
		{
			c -= 'a' - 10;
		}
		
		Result = ( 16 * Result ) + c;
	}
	
	return Result;	
}

int main(void)
{
    SelfProgramming_t SelfProgramm;
	
	uart_init( UART_BAUD_SELECT( 9600 , F_CPU ) );
	
	// Die Interrupt Vektoren müssen noch an die "Bootloader Section" 
	// gemappt werden..
	
	
	
	//__AVR_ATx
	#if 0
	#endif
	
	
    while (1) 
    {
		uint16_t uwRxByte = uart_getc();
		
		if ( ! ( uwRxByte &  UART_NO_DATA ) )
		{
			switch( SelfProgramm.ParserState )
			{
				case _PARSER_FILE_BEGINN:
				
				if ( (uint8_t)uwRxByte == ':' ) 
				{
					SelfProgramm.ParserState = _PARSER_LENGTH;
					SelfProgramm.uiHexCRC = 0;
					SelfProgramm.uiRxCounter = 0;
				}
				
				break;
				
				case _PARSER_LENGTH:
				
				
				
				break;
				
				case _PARSER_ADDRESS:
				
				break;
				
				case _PARSER_TYP:
				
				break;
				
				case _PARSER_DATA:
				
				break;
				
				case _PARSER_END_CRC:
				
				break;
				
				case _PARSER_FAILD:
				
				break;
				
			}// switch
		}// if
		
    }// while
}// main

