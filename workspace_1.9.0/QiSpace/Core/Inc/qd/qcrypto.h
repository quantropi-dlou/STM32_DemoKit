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

#ifndef _Q_CRYPTO_SDK_H
#define _Q_CRYPTO_SDK_H

# ifdef  __cplusplus
extern "C" {
# endif

#include <stdint.h>

#ifndef OPENSSL_DISABLED
#include <openssl/aes.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

#define Q_AES_KEYSIZE_BITS 256
#define Q_AES_KEYSIZE_BYTE (Q_AES_KEYSIZE_BITS/8)
#define Q_AES_IV_SIZE 16

#define Q_AES_HANDLE AES_KEY
#define Q_AES_SET_ENC_KEY(key, KeySizeBits, aesHandle) AES_set_encrypt_key((key), (KeySizeBits), (aesHandle))
#define Q_AES_SET_DEC_KEY(key, KeySizeBits, aesHandle) AES_set_decrypt_key((key), (KeySizeBits), (aesHandle))
#define Q_AES_CBC_ENC(iv, plain, cipher, plainSize, aesHandle) AES_cbc_encrypt((plain), (cipher), (plainSize), (aesHandle), (iv), AES_ENCRYPT)
#define Q_AES_CBC_DEC(iv, cipher, plain, cipherSize, aesHandle) AES_cbc_encrypt((cipher), (plain), (cipherSize), (aesHandle), (iv), AES_DECRYPT)
#define Q_AES_ECB_ENC( plain, cipher,  aesHandle) AES_ecb_encrypt((plain), (cipher),  (aesHandle),  AES_ENCRYPT)
#define Q_AES_ECB_DEC( cipher, plain,  aesHandle) AES_ecb_encrypt((cipher), (plain),  (aesHandle),  AES_DECRYPT)


#define Q_PUBLIC_EXPONENT 17
#define Q_RSA_KEY_LENGTH 2048
#define Q_RSA_PADDING_SIZE 42
#define Q_RSA_PLAIN_BLOCK_SIZE ((Q_RSA_KEY_LENGTH/8)-Q_RSA_PADDING_SIZE)
#define Q_RSA_CIPHER_BLOCK_SIZE (Q_RSA_KEY_LENGTH/8)

#define Q_RSA_KeyPair RSA
#define Q_RSA_KeyPair_New() RSA_new()
#define Q_RSA_KeyPair_Fee(pKeyPair) RSA_free(pKeyPair)
#define Q_RSA_Generate_KeyPair(pKeyPair, KEY_LENGTH )  \
               { \
                BIGNUM * _bne = BN_new(); \
                if ( BN_set_word(_bne, Q_PUBLIC_EXPONENT) == 1 ) { \
                    RSA_generate_key_ex(pKeyPair, KEY_LENGTH, _bne, NULL); \
                  } \
                BN_free(_bne); \
                }

#define Q_RSA_Get_PubKey_PemLen(pRsaKeyPair, len) \
    { \
    BIO *_bio = BIO_new(BIO_s_mem()); \
    len = -1; \
    if (NULL != _bio) { \
        if (0 != PEM_write_bio_RSAPublicKey(_bio, pRsaKeyPair)) { \
            len = BIO_pending(_bio)+1; \
        } \
    } \
    BIO_free(_bio);\
   }

#define Q_RSA_Get_PubKey_PEM(pRsaKeyPair, pRsaPubKeyPemStr, klen) \
    { \
    BIO *_bio = BIO_new(BIO_s_mem()); \
    if (NULL != _bio) { \
        if (0 != PEM_write_bio_RSAPublicKey(_bio, pRsaKeyPair)) { \
            klen = BIO_pending(_bio) +1; \
            memset(pRsaPubKeyPemStr, 0, klen); \
            BIO_read(_bio, pRsaPubKeyPemStr, klen); \
        } \
    } \
    BIO_free(_bio);\
   }

#define Q_RSA_Load_PubKey_PEM(pRsaPubKeyPemStr, pem_len,  pRsaPubKey) \
    { \
    BIO *_bio = BIO_new_mem_buf(pRsaPubKeyPemStr, pem_len); \
    if (NULL != _bio) { \
        pRsaPubKey = PEM_read_bio_RSAPublicKey(_bio, NULL, NULL, NULL); \
    } \
    BIO_free(_bio); \
    }

#define Q_RSA_Buff_Size(key) RSA_size(key)

#define Q_RSA_Pub_Encrypt(mLen, msg, cipher, pubKey) RSA_public_encrypt(mLen, msg, cipher, pubKey, RSA_PKCS1_OAEP_PADDING)
#define Q_RSA_Pri_Decrypt(cLen, cipher, msg, priKey) RSA_private_decrypt(cLen, cipher, msg, priKey, RSA_PKCS1_OAEP_PADDING)

#else
/* turn off QCrypto APIs*/
#define Q_AES_KEYSIZE_BITS 256
#define Q_AES_KEYSIZE_BYTE (Q_AES_KEYSIZE_BITS/8)
#define Q_AES_IV_SIZE 16
#define Q_AES_HANDLE 
#define Q_AES_SET_ENC_KEY(key, KeySizeBits, aesHandle) 
#define Q_AES_SET_DEC_KEY(key, KeySizeBits, aesHandle) 
#define Q_AES_CBC_ENC(iv, plain, cipher, plainSize, aesHandle) 
#define Q_AES_CBC_DEC(iv, cipher, plain, cipherSize, aesHandle) 

#define Q_PUBLIC_EXPONENT 17
#define Q_RSA_KeyPair 
#define Q_RSA_KeyPair_New() 
#define Q_RSA_KeyPair_Fee(pKeyPair) 
#define Q_RSA_Generate_KeyPair(pKeyPair, KEY_LENGTH ) {

#define Q_RSA_Get_PubKey_PEM(pRsaKeyPair, pRsaPubKeyPemStr) 

#define Q_RSA_Load_PubKey_PEM(pRsaPubKeyPemStr, pRsaPubKey) 

#define Q_RSA_Buff_Size(key) 

#define Q_RSA_Pub_Encrypt(mLen, msg, cipher, pubKey) 
#define Q_RSA_Pri_Decrypt(cLen, cipher, msg, priKey) 


#endif

# ifdef  __cplusplus
}
# endif
#endif  /*_Q_CRYPTO_SDK_H*/
