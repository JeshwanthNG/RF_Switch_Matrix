/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */


#include "../Middlewares/Third_Party/LwIP/src/include/lwip/opt.h"

#if LWIP_NETCONN

#include "../Middlewares/Third_Party/LwIP/src/include/lwip/sys.h"
#include "../Middlewares/Third_Party/LwIP/src/include/lwip/api.h"

#define TCPECHO_THREAD_PRIO  ( tskIDLE_PRIORITY + 4 )

#include <string.h>
#include "FreeRTOS_CLI.h"

#if 1
static void tcpecho_thread(void *arg)
{
#define cmdMAX_INPUT_SIZE	60
#define cmdMAX_OUTPUT_SIZE	1250
  struct netconn *conn, *newconn;
  err_t err, accept_err;
  struct netbuf *buf;
  void *data;
  u16_t len;
  static char cInputString[ cmdMAX_INPUT_SIZE ];
  static char cOutputString[ cmdMAX_OUTPUT_SIZE ];
  static char localbuf[ cmdMAX_OUTPUT_SIZE ];
  char cInChar = 0;
  uint8_t cInputIndex = 0;
  uint8_t rcvdlen = 0;
  BaseType_t xMoreDataToFollow;

  LWIP_UNUSED_ARG(arg);

  /* Create a new connection identifier. */
  conn = netconn_new(NETCONN_TCP);

  if (conn!=NULL)
  {
    /* Bind connection to well known port number 7. */
    err = netconn_bind(conn, NULL, 7);

    if (err == ERR_OK)
    {
      /* Tell connection to go into listening mode. */
      netconn_listen(conn);

      while (1)
      {
        /* Grab new connection. */
         accept_err = netconn_accept(conn, &newconn);

        /* Process the new connection. */
        if (accept_err == ERR_OK)
        {

          while (netconn_recv(newconn, &buf) == ERR_OK)
          {
        	rcvdlen = 0;
            do
            {
              netbuf_data(buf, &data, &len);
              while(rcvdlen < len)
              {
            	  localbuf[rcvdlen] = (*(char*)data);
            	  rcvdlen++;
            	  data++;
              }
            }
            while (netbuf_next(buf) >= 0);
            rcvdlen = 0;

            netbuf_delete(buf);
            /*Parse the string*/
            while(rcvdlen < len)
            {
            	cInChar = localbuf[rcvdlen];
            	rcvdlen++;

            	if( cInChar == '\n' )
            	{
            		do
            		{
            			/* Pass the string to FreeRTOS+CLI. */
            			xMoreDataToFollow = FreeRTOS_CLIProcessCommand( cInputString, cOutputString, cmdMAX_OUTPUT_SIZE );

            			netconn_write(newconn, cOutputString, strlen( cOutputString ), NETCONN_COPY);

            		} while( xMoreDataToFollow != pdFALSE ); /* Until the command does not generate any more output. */

            		cInputIndex = 0;
            		memset( cInputString, 0x00, cmdMAX_INPUT_SIZE );
            	}
            	else
            	{
            		if( cInChar == '\r' )
            		{
            			/* Ignore the character.  Newlines are used to
            		            	  							detect the end of the input string. */
            		}
            		else if( cInChar == '\b' )
            		{
            			/* Backspace was pressed.  Erase the last character
            		            	  							in the string - if any. */
            			if( cInputIndex > 0 )
            			{
            				cInputIndex--;
            				cInputString[ cInputIndex ] = '\0';
            			}
            		}
            		else
            		{
            			/* A character was entered.  Add it to the string
            		            	  							entered so far.  When a \n is entered the complete
            		            	  							string will be passed to the command interpreter. */
            			if( cInputIndex < cmdMAX_INPUT_SIZE )
            			{
            				cInputString[ cInputIndex ] = cInChar;
            				cInputIndex++;
            			}
            		}
            	}
            }
          }

          /* Close connection and discard connection identifier. */
          netconn_close(newconn);
          netconn_delete(newconn);
        }
      }
    }
    else
    {
      netconn_delete(newconn);
    }
  }
}
#endif

/*-----------------------------------------------------------------------------------*/

void tcpecho_init(void)
{
  sys_thread_new("tcpecho_thread", tcpecho_thread, NULL, DEFAULT_THREAD_STACKSIZE, TCPECHO_THREAD_PRIO);
}
/*-----------------------------------------------------------------------------------*/
#endif /* LWIP_NETCONN */
