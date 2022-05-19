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

#ifndef _QEEP_SDK_QBC_H
#define _QEEP_SDK_QBC_H

# ifdef  __cplusplus
extern "C" {
# endif

#include <stdint.h>
#include "error.h"

#ifdef QEEP_BLOCK_CIPHER_ENABLED
/*APIs for block cipher operations */
typedef struct QEEP_Block_Cipher_Handle_   *QBC_Handle;
QEEP_RET QBC_init(QBC_Handle *pQBC, uint8_t *password, int32_t pass_len);
//QEEP_RET QBC_iv_set(QBC_Handle QBC, uint8_t *iv, int32_t iv_len);
int32_t  QBC_encrypt_length(QBC_Handle QBC, int32_t plain_len);
QEEP_RET QBC_encrypt(QBC_Handle QBC, uint8_t *iv, int32_t iv_len, uint8_t *plain, int32_t plain_len, uint8_t *cipher, int32_t *cipher_len);
int32_t  QBC_decrypt_length(QBC_Handle QBC, int32_t cipher_len);
QEEP_RET QBC_decrypt(QBC_Handle QBC, uint8_t *cipher, int32_t cipher_len, uint8_t *plain, int32_t *plain_len);
QEEP_RET QBC_close(QBC_Handle QBC);
#endif /*QEEP_BLOCK_CIPHER_ENABLED*/

# ifdef  __cplusplus
}
# endif

#endif  /*_QEEP_SDK_QBC_H */
