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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../lib/qispace_qeep.h"



#define DEMO_QEEP_KEY_BUFFER_SIZE         256
#define DEMO_IV_SIZE                      16
#define DEMO_MESSAGE_SIZE                 1024


static uint8_t HexChar (char c)
{
    if ('0' <= c && c <= '9') return (uint8_t)(c - '0');
    if ('A' <= c && c <= 'F') return (uint8_t)(c - 'A' + 10);
    if ('a' <= c && c <= 'f') return (uint8_t)(c - 'a' + 10);
    return 0xFF;
}

static int HexToBin (const char* s, uint8_t *buff, int length)
{
    int result;
    if (!s || !buff || length <= 0) return -1;

    for (result = 0; *s; ++result)
    {
        uint8_t msn = HexChar(*s++);
        if (msn == 0xFF) return -1;
        uint8_t lsn = HexChar(*s++);
        if (lsn == 0xFF) return -1;
        uint8_t bin = (msn << 4) + lsn;

        if (length-- <= 0) return -1;
        *buff++ = bin;
    }
    return result;
}

static char qeep_key_str[]="01e8e86830efc1c6559d315fd635bd7e59eaa5a0a95100c5d0a2431972ee7f8c0869d47df216794ecf49374b40823071e7836c8f2622";

int main(int argc, char **argv)
{

QEEP_RET ret = QEEP_OK;
int i;

QP_Handle qp_handle_enc;
QP_Handle qp_handle_dec;


uint8_t iv[DEMO_IV_SIZE]; 
uint8_t message[DEMO_MESSAGE_SIZE];
int32_t message_length = DEMO_MESSAGE_SIZE;
uint8_t cipher[DEMO_MESSAGE_SIZE], plaintext[DEMO_MESSAGE_SIZE];
int32_t cipher_length = 0;

uint8_t qeep_key[DEMO_QEEP_KEY_BUFFER_SIZE];
int32_t qeep_key_len = 0;



srand(time(0));

qeep_key_len = strlen(qeep_key_str)/2;
/* convert qeep key from hex string to binary array */
if (HexToBin(qeep_key_str,qeep_key, qeep_key_len ) != qeep_key_len) {
        printf("Convert QK hex string to binary array fail \n");
        return (1);
}
/* generate test IV */
for(i = 0; i< DEMO_IV_SIZE; i++)
        iv[i] = rand()&0xff;

/* Create message for test purpose */
for(i = 0; i< message_length; i++)
        message[i] = rand()&0xff;



/** 
 * ##################################################################
*   Use QEEP key to encode message 
*  ##################################################################
*/

printf("Demo QiSpace QEEP operation ....");
/**
*    Step 1, Create QEEP handle
*/
ret = QP_init(&qp_handle_enc);
if (ret != QEEP_OK) { printf("QP_init fail\n"); return (-1);}

/**
 *    Step 2, Load QEEP key
 */
ret = QP_qeep_key_load(qp_handle_enc, qeep_key, qeep_key_len);
if (ret != QEEP_OK) { printf("QP_qeep_key_load fail ret = %d\n", ret); return (-1);}

/**
 *    Step 3, Load IV 
 */
ret = QP_iv_set(qp_handle_enc, iv, DEMO_IV_SIZE);
if (ret != QEEP_OK) { printf("fail at QP_iv_set \n"); return (-1);}

/**
 *    Step 4, Encrypt operation 
 */
ret = QP_encrypt(qp_handle_enc, message,  message_length, cipher);
if (ret != QEEP_OK) { printf("fail at QP_encode \n"); return (-1);}
cipher_length = message_length;
/**
*    Step 5, Free QEEP handle
*/
ret = QP_close(qp_handle_enc);
printf("Done \n");



/** 
 * ##################################################################
*   Use QEEP key to decode cipher 
*  ##################################################################
*/

printf("Demo QEEP decode operation ....");
/**
*    Step 1, Create QEEP handle
*/
ret = QP_init(&qp_handle_dec);
if (ret != QEEP_OK) { printf("QP_init fail\n"); return (-1);}

/**
 *    Step 2, Load QEEP key
 */
ret = QP_qeep_key_load(qp_handle_dec, qeep_key, qeep_key_len);
if (ret != QEEP_OK) { printf("QP_qeep_key_load fail ret = %d\n", ret); return (-1);}

/**
 *    Step 3, Load IV 
 */
ret = QP_iv_set(qp_handle_dec, iv, DEMO_IV_SIZE);
if (ret != QEEP_OK) { printf("QP_iv_set fail\n"); return (-1);}

/**
 *    Step 4, Decrypt operation 
 */
ret = QP_decrypt(qp_handle_dec, cipher,  cipher_length, plaintext);
if (ret != QEEP_OK) { printf("QP_decrypt fail\n"); return (-1);}

/**
*    Step 5, Free QEEP handle
*/
ret = QP_close(qp_handle_dec);
printf("Done \n");



/**
 *  Verify encrypt and decrypt resuls for test purpose
 */
ret =memcmp(message, plaintext, message_length);
printf("Compare message and plaintext ....");
if ( ret == 0 ) {
    printf("Match, Demo exit ! \n");
    return 0;
} else {
    printf("NOT match (ret= %d), Demo exit! \n", ret);
    return 1;
}
return 0;
}