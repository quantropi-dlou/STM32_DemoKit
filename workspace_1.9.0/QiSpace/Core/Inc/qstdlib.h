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

#ifndef _Q_STDLIB_SDK_H
#define _Q_STDLIB_SDK_H

# ifdef  __cplusplus
extern "C" {
# endif


#ifdef Q_STDLIB_PROVIDED

extern void* Q_malloc (size_t size);
extern void Q_free (void* ptr);
extern void * Q_memcpy ( void * destination, const void * source, size_t num );
extern int Q_memcmp ( const void * ptr1, const void * ptr2, size_t num );
extern void * Q_memset ( void * ptr, int value, size_t num );

#else


#include <stdlib.h>
#include <string.h>

#define Q_malloc(size)             malloc(size)
#define Q_free(ptr)                free(ptr)
#define Q_memcpy(ptr1, ptr2, size) memcpy(ptr1, ptr2,size)
#define Q_memset(ptr, value, num)  memset(ptr, value, num)
#define Q_memcmp(ptr1, ptr2, size) memcmp(ptr1, ptr2, size)

#endif

# ifdef  __cplusplus
}
# endif
#endif  /*_Q_STDLIB_SDK_H*/
