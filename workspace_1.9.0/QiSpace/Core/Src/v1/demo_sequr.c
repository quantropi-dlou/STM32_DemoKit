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

#include "qeep.h"

#include "qispace_sequr.h"

# ifdef  __cplusplus
extern "C" {
# endif

#define DEMO_QEEP_KEY_BUFFER_SIZE         1024
#define DEMO_MESSAGE_SIZE                 1024
#define DEMO_IV_SIZE                      16

int demo_sequr(int argc, char **argv)
{

UNUSED(argc);
UNUSED(argv);

QEEP_RET ret = QEEP_OK;
int i;

QSC_Handle qsc_handle_dec;


static uint8_t plaintext[DEMO_MESSAGE_SIZE];
static uint8_t qeep_key[DEMO_QEEP_KEY_BUFFER_SIZE];
uint8_t qeep_key_str[]="01e8e86830efc1c6559d315fd635bd7e59eaa5a0a95100c5d0a2431972ee7f8c0869d47df216794ecf49374b40823071e7836c8f2622";
int32_t qeep_key_len = strlen((char*)qeep_key_str)/2;

uint8_t cipher[]="SQUR demo cipher, should be generated by QiSpace Server";
int32_t cipher_length = strlen((char*)cipher)/2;
uint8_t iv[DEMO_IV_SIZE]="1234567890123456"; 

printf("%s START\n", __FUNCTION__);

qeep_key_len = strlen((char*)qeep_key_str)/2;
/* convert qeep key from hex string to binary array */
for(i = 0; i< qeep_key_len; i++) {
        sscanf((char*)&qeep_key_str[2*i], "%02x", (unsigned int *)&qeep_key[i]);
}



/** 
 * ##################################################################
*   Use QEEP key to decode cipher  
*  ##################################################################
*/

printf("Demo SQUR decode operation ....");

/**
*    Step 1, Create QSC class handle
*/
ret = QSC_init(&qsc_handle_dec);
if (ret != QEEP_OK) { printf("QSC_init fail\n"); return (-1);}

/**
 *    Step 2, Load QEEP key
 */
ret = QSC_qeep_key_load(qsc_handle_dec, qeep_key, qeep_key_len);
if (ret != QEEP_OK) { printf("QSC_qeep_key_load fail ret = %d\n", ret); return (-1);}

/**
 *    Step 3, Load IV 
 */
ret = QSC_qeep_iv_set(qsc_handle_dec, iv, DEMO_IV_SIZE);
if (ret != QEEP_OK) { printf("QSC_qeep_iv_set fail\n"); return (-1);}

/**
 *    Step 4, Decrypt operation 
 */
ret = QSC_qeep_decode(qsc_handle_dec, cipher,  cipher_length, plaintext);
if (ret != QEEP_OK) { printf("QSC_qeep_decrypt fail\n"); return (-1);}

/**
*    Step 5, Free QSC class handle
*/
ret = QSC_close(qsc_handle_dec);

printf("%s END\n", __FUNCTION__);

return 0;
}

# ifdef  __cplusplus
}
# endif
