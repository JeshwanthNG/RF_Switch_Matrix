/*
    FreeRTOS V7.3.0 - Copyright (C) 2012 Real Time Engineers Ltd.


    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    >>>NOTE<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

/* FreeRTOS includes. */
#include "FreeRTOS.h"

/* Standard includes. */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* FreeRTOS+CLI includes. */
#include "FreeRTOS_CLI.h"
#include "task.h"

static portBASE_TYPE CliCmdGetDeviceInfo( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );
static portBASE_TYPE CliCmdSetInput( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );
static portBASE_TYPE CliCmdSetOutput( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );
static portBASE_TYPE CliCmdGetInput( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );
static portBASE_TYPE CliCmdGetOutput( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString );

static const CLI_Command_Definition_t CliCmdGetDeviceInfoDefinition =
{
	( const int8_t * const ) "getinfo", /* The command string to type. */
	( const int8_t * const ) "getinfo: \r\n Gets the device information\r\n\r\n",
	CliCmdGetDeviceInfo, /* The function to run. */
	0 /* No parameters are expected. */
};

static const CLI_Command_Definition_t CliCmdSetInputDefinition =
{
	( const int8_t * const ) "setinput", /* The command string to type. */
	( const int8_t * const ) "setinput: \r\n Connects selected input to ouput\r\n\r\n",
	CliCmdSetInput, /* The function to run. */
	2 /* No parameters are expected. */
};

static const CLI_Command_Definition_t CliCmdSetOutputDefinition =
{
	( const int8_t * const ) "setoutput", /* The command string to type. */
	( const int8_t * const ) "setoutput: \r\n Connects selected output to input\r\n\r\n",
	CliCmdSetOutput, /* The function to run. */
	2 /* No parameters are expected. */
};

static const int8_t *setmsg = ( int8_t * ) "Set\r\n";
static const int8_t *notsetmsg = ( int8_t * ) "Notset\r\n";


/*-----------------------------------------------------------*/

void vRegisterCLICommands( void )
{
	/* Register all the command line commands defined immediately above. */

	FreeRTOS_CLIRegisterCommand( &CliCmdGetDeviceInfoDefinition );
	FreeRTOS_CLIRegisterCommand( &CliCmdSetInputDefinition );
	FreeRTOS_CLIRegisterCommand( &CliCmdSetOutputDefinition );
}
/*-----------------------------------------------------------*/

/*Commands Related to switch matrix project*/
static portBASE_TYPE CliCmdGetDeviceInfo( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
	const int8_t *const infoStr = ( int8_t * ) "Switch matrix device\r\n";

	/* Remove compile time warnings about unused parameters, and check the
		write buffer is not NULL.  NOTE - for simplicity, this example assumes the
		write buffer length is adequate, so does not check for buffer overflows. */
	( void ) pcCommandString;
	( void ) xWriteBufferLen;
	configASSERT( pcWriteBuffer );

	/* Generate a table of task stats. */
	strcpy( ( char * ) pcWriteBuffer, ( char * ) infoStr );

	/* There is no more data to return after this single string, so return
		pdFALSE. */
	return pdFALSE;
}

static portBASE_TYPE CliCmdSetInput( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
#define MAX_PARAMS (2)
	int8_t *pcParameterString;
	portBASE_TYPE xParameterStringLength, xReturn;
	int32_t params[MAX_PARAMS], paramIndex=0;


	( void ) xWriteBufferLen;
	configASSERT( pcWriteBuffer );

	while(paramIndex < MAX_PARAMS)
	{
		/* Obtain the parameter string. */
		pcParameterString = ( int8_t * ) FreeRTOS_CLIGetParameter
				(
						pcCommandString,		/* The command string itself. */
						(paramIndex+1),						/* Return the first parameter. */
						&xParameterStringLength	/* Store the parameter string length. */
				);
		/* Turn the parameter into a number. */
		params[paramIndex] = ( int32_t ) atol( ( const char * ) pcParameterString );
		paramIndex++;
	}

	if(params[0] <= 4 && params[1] <= 4)
	{
		strcpy( ( char * ) pcWriteBuffer, ( const char * ) setmsg );
	}
	else
	{
		strcpy( ( char * ) pcWriteBuffer, ( const char * ) notsetmsg );
	}

	return pdFALSE;
}

static portBASE_TYPE CliCmdSetOutput( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
#define MAX_PARAMS (2)
	int8_t *pcParameterString;
	portBASE_TYPE xParameterStringLength, xReturn;
	int32_t params[MAX_PARAMS], paramIndex=0;


	( void ) xWriteBufferLen;
	configASSERT( pcWriteBuffer );

	while(paramIndex < MAX_PARAMS)
	{
		/* Obtain the parameter string. */
		pcParameterString = ( int8_t * ) FreeRTOS_CLIGetParameter
				(
						pcCommandString,		/* The command string itself. */
						(paramIndex+1),						/* Return the first parameter. */
						&xParameterStringLength	/* Store the parameter string length. */
				);
		/* Turn the parameter into a number. */
		params[paramIndex] = ( int32_t ) atol( ( const char * ) pcParameterString );
		paramIndex++;
	}

	if(params[0] <= 4 && params[1] <= 4)
	{
		strcpy( ( char * ) pcWriteBuffer, ( const char * ) setmsg );
	}
	else
	{
		strcpy( ( char * ) pcWriteBuffer, ( const char * ) notsetmsg );
	}

	return pdFALSE;
}

static portBASE_TYPE CliCmdGetInput( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
	return pdFALSE;
}

static portBASE_TYPE CliCmdGetOutput( int8_t *pcWriteBuffer, size_t xWriteBufferLen, const int8_t *pcCommandString )
{
	return pdFALSE;

}







