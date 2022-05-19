/**
 *  \file serial_stdio.h
 *  \brief stdio support for STM32HX platform 
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
  
#ifndef __SERIAL_DEBUG_H
#define __SERIAL_DEBUG_H

#include <stdio.h>

#include "main.h"
#include "stm32h7xx_hal_gpio_ex.h"

#define COM_MAX 2
#define COM1 0  // USART3  // primary 
#define COM2 1  // USART1  // auxiliary

#define COM_DEBUG_ENABLE 1
#define COM_DEBUG_PORT COM1
#define COM_AUX_PORT   COM2

#define COM1_BAUDRATE (115200*1)
#define COM2_BAUDRATE (115200*1)

// must use STDIO_FULL and 
// project options library FULL for compatibility with stdio.h 
// fputc(int, FILE*)
// fgetc(FILE*)
// fgets(char *, int, FILE*)
#define STDIO_NORMAL 0
#define STDIO_FULL   1

#if STDIO_NORMAL
  #define PUTCHAR_PROTOTYPE int fputc(int ch, void *f)
  #define GETCHAR_PROTOTYPE int fgetc(void *f)
  #define GETS_PROTOTYPE char *fgets(char *str, int num, void *f)
#endif

#if STDIO_FULL
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
  #define GETCHAR_PROTOTYPE int fgetc(FILE *f)
  #define GETS_PROTOTYPE char *fgets(char *str, int num, FILE *f)
#endif
    

//////////////////////////
// PROTOTYPES
/////////////////////////
     
int DebugComPort_Init(void);

#endif /* __SERIAL_DEBUG_H */  


