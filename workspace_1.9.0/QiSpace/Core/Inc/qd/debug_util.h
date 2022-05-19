/******************************************************************************
 *
 * Quantropi CONFIDENTIAL
 * ----------------------
 *
 * This file is proprietary code and subject to the terms and conditions
 * defined in the file 'LICENSE', which is part of this source code package.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Quantropi Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to Quantropi Incorporated and its suppliers and
 * may be covered by Canadian, U.S. and Foreign Patents,
 * patents in process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Quantropi Incorporated.
 *
 *****************************************************************************/

#ifndef _QEEP_DEBUG_UTIL_H
#define _QEEP_DEBUG_UTIL_H

#ifdef  __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#ifdef QEEP_DEBUG_ON

void  _qeep_debug_start(char *func_name);
void  _qeep_debug_end(char *func_name);
void  _qeep_debug_print_buffer_uint8(char *  text, uint8_t *buff, int len);
void  _qeep_debug_print_value_uint8(char *  text,  uint8_t value);

#define QEEP_DEBUG_START(function_name) _qeep_debug_start(function_name)
#define QEEP_DEBUG_END(function_name) _qeep_debug_end(function_name)
#define QEEP_DEBUG_PRINT_UINT8_BUFFER(text, buff, len) _qeep_debug_print_buffer_uint8(text, buff, len)
#define QEEP_DEBUG_PRINT_UINT8_VALUE(text, value) _qeep_debug_print_value_uint8(text, value)
#define QEEP_DEBUG_PRINT_STR(text, buff) printf("%s:\n%s\n", text, buff) 
#define QEEP_DEBUG_PRINT_INT32_VALUE(text, value) printf("%s: %d\n", text, value) 


#else

#define QEEP_DEBUG_START(func_name) 
#define QEEP_DEBUG_END(func_name) 
#define QEEP_DEBUG_PRINT_UINT8_BUFFER(text, buff, len)
#define QEEP_DEBUG_PRINT_STR(text, buff)
#define QEEP_DEBUG_PRINT_UINT8_VALUE(text, value)
#define QEEP_DEBUG_PRINT_INT32_VALUE(text, value)
#endif



#ifdef  __cplusplus
}
#endif

#endif /*_QEEP_DEBUG_UTIL_H*/