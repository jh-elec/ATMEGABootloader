/*     __  _  _  ____   __    __   ____  _  _
*    _(  )/ )( \(  _ \ /  \  /  \ (_  _)( \/ )
*   / \) \) __ ( ) _ ((  O )(  O )  )(   )  /
*   \____/\_)(_/(____/ \__/  \__/  (__) (__/
*
*
*	Bootloader für einige __AVR__ Typen
*
*/

#define _DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const uint8_t * HexDump =
{
   ":100000000C942A000C943C000C943C000C943C0092\
	:100010000C943C000C943C000C943C000C943C0070\
	:100020000C943C000C943C000C943C000C943C0060\
	:100030000C943C000C9445000C9471000C943C0012\
	:100040000C943C000C943C000C943C000C943C0040\
	:100050000C943C0011241FBECFE5D8E0DEBFCDBF1D\
	:1000600020E0A0E6B0E001C01D92A53AB207E1F79A\
	:100070000E943E000C94C3000C94000087E690E0C0\
	:100080000E9496000E94AA00FDCF1F920F920FB609\
	:100090000F9211242F938F939F93EF93FF938BB124\
	:1000A0002CB18871E0916200EF5FEF719091610077\
	:1000B000E91739F0E0936200F0E0EB59FF4F20833D\
	:1000C00001C082E090916000892B80936000FF91D5\
	:1000D000EF919F918F912F910F900FBE0F901F90D6\
	:1000E00018951F920F920FB60F9211248F939F9322\
	:1000F000EF93FF939091640080916300981761F0F3\
	:10010000E0916300EF5FEF71E0936300F0E0EB5785\
	:10011000FF4F80818CB901C05598FF91EF919F915D\
	:100120008F910F900FBE0F901F9018951092640042\
	:1001300010926300109262001092610099231CF4E7\
	:1001400022E02BB99F7790BD89B988E98AB986E802\
	:1001500080BD08959091620080916100981781F0B0\
	:10016000E0916100EF5FEF71E0936100F0E0EB5927\
	:10017000FF4F8081909160001092600090E00895A0\
	:0A01800080E091E00895F894FFCFAD\
	:00000001FF"	
};

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
	uint8_t uiFlashBuffer[128];
	uint8_t uiFlashBufferCnt;
	
	uint8_t	uiHexBuffer[5];
	uint8_t uiHexBufferCnt;
	
	struct
	{
		uint8_t uiLength;
		uint8_t uiType;
		uint8_t uiChecksumm;
		uint16_t uwAddress;
	}HexInfo;
	
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

#define UART_NO_DATA 0


int main(int argc, char *argv[]) 
{
	SelfProgramming_t SelfProgramm;
	
	do
	{
		uint8_t uiRxByte = 0;
		
		if ( ! ( (uint8_t)uiRxByte & UART_NO_DATA ) )
		{
			if ( (uint8_t)uiRxByte == ':' )
			{
				SelfProgramm.ParserState = _PARSER_LENGTH;
			} 			
		}			
		
		
		
	}while( SelfProgramm.ParserState != _PARSER_END_CRC );


	return 0;
}
