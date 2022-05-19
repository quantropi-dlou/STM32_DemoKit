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

/* 
This header file is used for Server size
*/
#ifndef _QEEP_SDK_H
#define _QEEP_SDK_H

# ifdef  __cplusplus
extern "C" {
# endif

#include <stdint.h>
#include "error.h"
#include "qsc.h"
/*
 *
#include "qbc.h"
#include "qpk.h"
 */

/* Define QEEP SDK API Return Code */
typedef enum {
	QEEP_DEFAULT          = 0, 
	QEEP_PCG64            = 1,
	QEEP_PCG32            = 2,
} QEEP_PRNG_ALGORITHM;


/* QEEP SDK Struct*/
typedef struct QEEP_st_ *QEEP;

QEEP_RET qeep_init_prng(const uint8_t * seed, int32_t seed_len, QEEP  *Q, QEEP_PRNG_ALGORITHM prng);

QEEP_RET qeep_init(const uint8_t * seed, int32_t seed_len, QEEP  *Q);

QEEP_RET qeep_close(QEEP Q);

QEEP_RET qeep_encode(QEEP Q, const uint8_t *iv, int32_t iv_len, const uint8_t *in, int32_t in_len, uint8_t *out);

QEEP_RET qeep_decode(QEEP Q, const uint8_t *iv, int32_t iv_len, const uint8_t *in, int32_t in_len, uint8_t *out);

/* To back compatible with qeep_encode/qeep_decode functions, 
   qeep_stream functions process 16 bytes block by block.

   The input buffer length must be dividable by 16 except for the last call
   after each qeep_stream_iv call.
   Any 16-non-dividable input indicates this is the last block of stream operations for this IV. 
   To call qeep_stream_encode or qeep_stream_decore again, one must call qeep_stream_iv
*/
QEEP_RET qeep_stream_iv(QEEP Q, const uint8_t *iv, int32_t iv_len);
QEEP_RET qeep_stream_encode(QEEP Q, const uint8_t *in, int32_t in_len, uint8_t *out);
QEEP_RET qeep_stream_decode(QEEP Q, const uint8_t *in, int32_t in_len, uint8_t *out);

/*High level APIs for both private key and subscriber key protections */
/* Named QEEP SDK Core  =  QSC*/
QEEP_RET QSC_index(QSC_Handle QSC, uint8_t *index, int32_t len);
/*
    Return the length of QEEP Key
    Input parameters:
        - qkFlag: 0 or 1; 1 means QEEP key protection enabled
        - req_qk_len: 1 ~ 4096; the length of QEEP key requested in bytes
*/
int32_t  QSC_qeep_key_length(int32_t qkFlag, int32_t req_qk_len);

/*
    Given quantum entropy source, generate QEEP key with QEEP, protected or not
    Input parameters:
        - QSC: qsc_handle created by QSC_init
        - qe: quantum entropy, which should be retrieved from QiSpace platform via REST APIs
        - qe_len: the length of qe in bytes, which must be greater than (req_qk_len + 16)
        - qkFlag: 0 or 1; 1 means QEEP key protection enabled
        - req_qk_len: 1 ~ 4096; the length of QEEP key requested in bytes
        - qk_out: the buffer to store the generated QEEP key, the buffer should be pre-allocated (the buffer size can be caculated by calling "QSC_qeep_key_length")
        - qk_out_len: the returned QEEP key length if successful, otherwise it is 0
    return QEEP_OK if successful
*/
QEEP_RET QSC_qeep_key_create(QSC_Handle QSC, uint8_t *qe, int32_t qe_len, int32_t qkFlag, int32_t req_qk_len, uint8_t *qk_out, int32_t *qk_out_len);
QEEP_RET QSC_qk_to_qk(QSC_Handle QSC, uint8_t *qk_in, int32_t qk_len, uint8_t *qk_new, uint8_t *iv, uint8_t *exp);

/* 
    QK helper functions
        QSC_qk_to_crypto_key: convert qeep key to a crypto key, such as AES
        QSC_qk_valid: check if QK is valid
    QEEP_RET QSC_qk_to_crypto_key(QSC_Handle QSC, uint8_t *qk, int32_t qk_len, uint8_t *key, int32_t *key_len);
    QEEP_RET QSC_qk_valid(QSC_Handle QSC, uint8_t *qk_in, int32_t qk_len);
*/

# ifdef  __cplusplus
}
# endif

#endif  /*_QEEP_SDK_H */
