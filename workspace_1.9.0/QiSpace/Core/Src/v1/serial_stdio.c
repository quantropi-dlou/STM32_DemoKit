/**
 *  \file serial_stdio.c
 *  \brief stdio redirect for STM32HX platform 
 *
 *  \if license
 *  Copyright (c) 2009-2022 Cypherbridge Systems, LLC.
 *  www.cypherbridge.com
 *
 *  Portions of this work may be based on third party contributions.
 *  Cypherbridge Systems LLC reserves copyrights to this work whose
 *  license terms are defined under a separate Software License
 *  Agreement (SLA).  Re-distribution of any or all of this work,
 *  in source or binary form, is prohibited unless authorized by
 *  Cypherbridge Systems, LLC under SLA.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 *  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *  \endif
 *
 *  \if credits
 *  COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
 *  @file    UART/UART_Printf/Inc/main.h
 *  @author  MCD Application Team
 *  @version V1.0.2
 *  @date    30-December-2016
 *  @brief   Header for main.c module
 *  \endif
 *
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "main.h"
#include "serial_stdio.h"

// enables stdio self test
#define USE_STDIO_TEST 0

#if USE_STDIO_TEST
static void stdio_test(void);
#endif

static UART_HandleTypeDef UartHandle;

/**
  * @brief  Initialize COM1 interface for serial debug
  * @note   COM1 interface is defined in stm3210g_eval.h file 
  * (under Utilities\STM32_EVAL\STM324xG_EVAL)  
  * @param  None
  * @retval 
  * 0 - init OK
  * -1 init failed
  */
int DebugComPort_Init(void)
{
  int rc;
  int baudrate;
  
  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
  /* UART configured as follows:
      - 430.8K N81
      - BaudRate    = 115.2K or multiplier to 430800
      - Parity      = NO parity
      - Word Length = 8
      - Stop Bit    = One Stop bit
      - Hardware flow control disabled (RTS and CTS signals) */

  if (COM_DEBUG_PORT == COM1) {
    UartHandle.Instance = USART3;
    baudrate = COM1_BAUDRATE;
  }
  else if (COM_DEBUG_PORT == COM2) {
    UartHandle.Instance = USART1;
    baudrate = COM2_BAUDRATE;
  }
  else 
    return -1;

  UartHandle.Init.BaudRate   = baudrate;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits   = UART_STOPBITS_1;
  UartHandle.Init.Parity     = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode       = UART_MODE_TX_RX;
  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
  
  rc = HAL_UART_Init(&UartHandle);
      
  if (rc != HAL_OK) {
      return -1;
  }

  // build option stdio test
  #if USE_STDIO_TEST
  stdio_test();
  #endif

  return 0;

}

#define MAXBUF 250
static char dbg[MAXBUF+4];
int printf(const char *format, ...)
{
	char *c;
	int len;
	va_list args;

    va_start(args, format);
    vsnprintf(dbg, MAXBUF, format, args);
    va_end(args);

    // line endings

    c = strchr(dbg, '\n');
    if (NULL == c) strcat(dbg, "\n");
    c = strchr(dbg, '\r');
    if (NULL == c) strcat(dbg, "\r");

    // write to output

    c = dbg;
    len = strlen(dbg);
    while (len--) {
    	putchar((int) *c++);
    }

    return 0;

}

// low level retargeting
struct __FILE {};

/**
  * @brief  Retargets the C library fputc function to the USART.
  * @param  None
  * @retval None
  */
FILE __stdout;
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}

int putchar(int ch)
{
	int c = ch;

	HAL_UART_Transmit(&UartHandle, (uint8_t *)&c, 1, 0xFFFF);

	return ch;
}

/**
  * @brief  Retargets the C library fgetc function to the USART.
  * @param  None
  * @retval None
  */
FILE __stdin;
int fgetc(FILE *f)
{
  uint8_t ch = 0;

  // polling loop
  while (1) {
    HAL_UART_Receive(&UartHandle, (uint8_t *)&ch, 1, 0);
    if (ch != 0) {
        break;
    }
  }
   
  #if 0
  // timeout 0xFFFF stalls when running in Region 2 0x08020000
  // use polling loop above instead
  HAL_UART_Receive(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF);
  #endif
  
  #if 0
  // echo character
  HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF);
  #endif
  
  return ch;
}
/**
  * @brief  Retargets the C library fgets function to the USART.
  * @param  None
  * @retval None
  */
char *fgets(char *str, int num, FILE *f)
{
  uint8_t ch;
  char *p = str;
  while (num > 1) {
      ch = fgetc(f);
      if ('\r' == ch) ch = '\n';
      *str++ = ch;
      if ('\n' == ch) break;
      num--;
  }

  // FIXME newline USART_SendData(STDIO_PORT, '\n');
  
  *str = 0;
  return p;
}

#if USE_STDIO_TEST
/** 
 * \brief test stdio
 * \return void
 */
static void stdio_test()
{
  char buf[32];
  char *p;
  char c;
    
  printf("fgetc test.  enter character: ");
  c = fgetc(stdin);
  printf("got %c (0x%02x)\n", c, c);
  printf("fgets test. enter string: ");
  p = fgets(buf,sizeof(buf)-1, stdin);
  printf("got %s\n", p);
  
}
#endif


