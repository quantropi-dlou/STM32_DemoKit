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

#ifndef _QEEP_SDK_QPK_H
#define _QEEP_SDK_QPK_H

# ifdef  __cplusplus
extern "C" {
# endif

#include <stdint.h>
#include "error.h"

#ifdef QEEP_PUBLIC_KEY_ENABLED
/* APIs for public key operations */
typedef struct QEEP_Public_Key_Handle_  *QPK_Handle;
QEEP_RET QPK_init(QPK_Handle *pQPK); 
 /* rec_pub_ky: receiver's public key, private key is not exposable*/
int32_t QPK_pub_key_length();
QEEP_RET QPK_rec_pub_key_create(QPK_Handle QPK, uint8_t *qe, int32_t qe_len, uint8_t *rec_pub_key, int32_t *pub_key_len);  
int32_t QPK_encrypt_length(int32_t plain_len);
QEEP_RET QPK_encrypt(QPK_Handle QPK, uint8_t *rec_pub_key, int32_t pub_key_len, uint8_t *plain, int32_t plain_len, uint8_t *cipher, int32_t *cipher_len);
int32_t QPK_decrypt_length(int32_t cipher_len);
QEEP_RET QPK_decrypt(QPK_Handle QPK, uint8_t *cipher, int32_t cipher_len, uint8_t *plain, int32_t *plain_len);
QEEP_RET QPK_close(QPK_Handle QPK);
#endif  /*QEEP_PUBLIC_KEY_ENABLED*/

# ifdef  __cplusplus
}
# endif

#endif  /*_QEEP_SDK_QPK_H */
