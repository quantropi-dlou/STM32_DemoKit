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

#ifndef _QEEP_SDK_SHARED_H
#define _QEEP_SDK_SHARED_H

# ifdef  __cplusplus
extern "C" {
# endif

#include <stdlib.h>
#include <stdint.h>

#include <math.h>
#include "qcrypto.h"
#include "qstdlib.h"
#define QEEP_SDK_VERSION 1
#define IV_SIZE 16

#ifdef QPP_PERMUTATION_16_ON
#define QEEP_MARTIX_DIMENSION_BITS 4
#define QEEP_MARTIX_DIMENSION      16    /* = 2^QEEP_MARTIX_DIMENSION_BITS */
#define QEEP_DISPACHER_MIN_BITS    4     /* = 8 - QEEP_MARTIX_DIMENSION_BITS*/
#else
 /* for QPP_PERMUTATION_64, default is 64*/
#define QEEP_MARTIX_DIMENSION_BITS 6
#define QEEP_MARTIX_DIMENSION      64    /* = 2^QEEP_MARTIX_DIMENSION_BITS */
#define QEEP_DISPACHER_MIN_BITS    2     /* = 8 - QEEP_MARTIX_DIMENSION_BITS*/
#endif

#define QEEP_SEED_SIZE  QEEP_MARTIX_DIMENSION*256

#define QEEP_4BIT_MARTIX_DIMENSION  8
#define QEEP_4BIT_SEED_SIZE  QEEP_4BIT_MARTIX_DIMENSION*16

/*QEEK KEY Struction*/
#define QEEP_KEY_ENCRYPT 1
#define QEEP_KEY_SMOOTH  0


typedef struct _Q_PRNG_State_Interal_ *Q_PRNG_State_Interal;

typedef struct _Q_PRNG_State_ {
	int                  prng_algorithm;
	Q_PRNG_State_Interal  internal_state_p;
} Q_PRNG_State;

struct QEEP_SDK_st_
{
	unsigned char se[QEEP_MARTIX_DIMENSION][256];
	unsigned char sd[QEEP_MARTIX_DIMENSION][256];
	unsigned char iv[IV_SIZE];
	int dispatcher_d;
	int dispatcher_b;
	int last_block;   // to indicate if the partial block has been proccessed, should call steam_iv to reset IV
};

struct QEEP_SDK_4bit_st_
{
	unsigned char se[QEEP_4BIT_MARTIX_DIMENSION/2][16];
	unsigned char sd[QEEP_4BIT_MARTIX_DIMENSION/2][16];
	unsigned char iv[IV_SIZE];
	unsigned char dispatcher_d;
	unsigned char dispatcher_b;
	unsigned char last_block;   // to indicate if the partial block has been proccessed, should call steam_iv to reset IV
};


typedef struct QEEP_SDK_st_ QEEP_SDK_st;
typedef struct QEEP_SDK_4bit_st_ QEEP_SDK_4bit_st;

/* QEEP Public Key handle */
#ifdef QEEP_PUBLIC_KEY_ENABLED
struct QPK_Handle__st_
{
  
#ifdef QPK_STUB
  uint8_t pri[16];
  uint8_t pub[16];
#else
  Q_RSA_KeyPair *rsa_keypair;
  Q_RSA_KeyPair *rsa_pubkey;
#endif
  uint8_t valid;
};
typedef struct QPK_Handle__st_  QPK_Handle_st;
#endif

/*QEEP Block Cipher handle*/
#ifdef QEEP_BLOCK_CIPHER_ENABLED
struct QBC_Handle__st_
{
#ifndef QBC_STUB
 Q_AES_HANDLE aes_enc;
 Q_AES_HANDLE aes_dec;
#endif
 uint8_t key[Q_AES_KEYSIZE_BYTE];
 uint8_t iv[Q_AES_IV_SIZE];

};
typedef struct QBC_Handle__st_  QBC_Handle_st;
#endif

/* QEEP SDK Core External Handle*/
struct QSC_Handle__st_
{
 QEEP qHandle;
 int32_t index;
 int32_t q_seed_len;
 uint8_t *q_seed;
 uint8_t valid;
};
typedef struct QSC_Handle__st_  QSC_Handle_st;


struct QEEP_KEY_st_
{
	int32_t seed_len;
	uint8_t *seed;
	uint8_t iv[16];
	uint8_t head;
	uint8_t ver;
};

typedef struct QEEP_KEY_st_ QEEP_KEY_st;


struct xorshift128plus_default_state
{
  uint64_t s1, s2;
};

typedef struct xorshift128plus_default_state xs128p_default_s;


/* the interface mapping actual PRNG algorithm provider  via option of prng_algorithm at running time */
Q_PRNG_State* q_prng_init(QEEP_PRNG_ALGORITHM prng_algorithm, uint64_t *seed);
uint64_t q_prng(Q_PRNG_State* st_p);
void q_prng_free(Q_PRNG_State* st_p);



uint64_t xorshift128plus_default(xs128p_default_s *st);

int KSA(unsigned char[], unsigned char*, unsigned char*, int len);
void swap(unsigned char *, unsigned char *);

#define SDK_KEY_LENGTH  33
extern uint8_t sdk_key_array[][SDK_KEY_LENGTH];
extern int32_t SDK_KEY_NUM;



# ifdef  __cplusplus
}
# endif

#endif /*_QEEP_SDK_SHARED_H*/
