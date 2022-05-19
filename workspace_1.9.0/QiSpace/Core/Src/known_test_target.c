#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include "demokit.h"
#include "qeep.h"

# ifdef  __cplusplus
extern "C" {
# endif

#define TEST_VECTOR_NUM  2

typedef struct {
   uint8_t seed[257];
   int32_t seed_len;
   uint8_t iv[17] ;
   int32_t iv_len;
   uint8_t message[129];
   int32_t message_len;
   uint8_t cipher[129];
   int32_t cipher_len;
} known_tv_st;

typedef struct {
   char seed[513];
   char iv[33] ;
   char message[256];
   char cipher[256];
} known_tv_st_hex;


known_tv_st_hex know_tests_hex[TEST_VECTOR_NUM] = {
    {   "083DBD40215519778B2347323B952CD2",
        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
        "00000000000000000000000000000000",
        "EDA980B4AD7A40FAC1C38050CD9049FA"
    },
    {"A5C14FE1950C1C643C387C67602DC45A9E1609BF08EFD1207921DD5A5B1ACA848DCDABB0576BF26965F2C7C4599655F4353275306AD1DE0A46D241669A8246B10B3A75301370E45E20680347511B0E56B8747F0BA3BC43861CADA1CA7E2F55CDA3D1E980CCD115C3E8272640C58DEC13CC2C5B339E677BBA951FD9DC76A515FC",
    "ACCFDA4AD4B054DA3BA7E14855D15F30",
    "415B2E5F1FB29DFCB493F4E855E80119602CEF47EE6792F2853B7603DDBB812DE7CEAECDB48B221D8777E44ECB831A7D",
    "62F7D7AAE8B1E8091A2FA5CF1F78639C637F907B2AB20D287B84C016FBDA3A5629B1990107A1B6A31F99CCBD6735EE60"
    },
};

void printf_buf(char *title, uint8_t *buf, int len ) {
    printf("\n%s(%d) : ", title, len);
    for (int i =0; i < len; i++) {
     printf("%02X", (buf[i]&0xff));
    }
    printf("\n");
}

#if 0
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
#endif


static int test_encoding(known_tv_st *tv, int idx) {
    QEEP q;
    QEEP_RET ret;
    int i;
    int results = 0;
    uint8_t *cipher = NULL;
    
    // printf("iv %d, seed %d, msg %d \n", tv->iv_len, tv->seed_len, tv->message_len);

    ret = qeep_init(tv->seed, tv->seed_len, &q);
    if (ret != QEEP_OK) {
        printf("qeep_init fail for %d \n", ret);
        return -1;
    }
    cipher = malloc(tv->message_len);
    if (cipher == NULL)  {
        printf("allocate mem for cipher fail \n");
        results = -1;
        goto encoding_exit;
    }
    ret = qeep_encode(q, tv->iv, tv->iv_len, tv->message, tv->message_len, cipher);
    if (ret != QEEP_OK) {
        printf("qeep_encode fail for %d \n", ret);
        results = -1;
        goto encoding_exit;
    }

    if (memcmp((tv->cipher), cipher, tv->message_len) == 0 ) {
        // printf("encoding test pass \n");
        results = 0;
    } else {
        printf("cipher not match  at idx = %d \n", idx);
        printf("iv %ld, seed %ld, msg %ld \n", tv->iv_len, tv->seed_len, tv->message_len);
        printf_buf("seed  ", tv->seed, 16 );
        printf_buf("iv    ", tv->iv,tv->iv_len );
        printf_buf("msg   ", tv->message,tv->message_len );
        printf_buf("Expect", tv->cipher,tv->message_len );
        printf_buf("Output", cipher,tv->message_len );
        results = -1;
    }
    /* Test stream_encode */
    if (tv->message_len > 16) {
        ret = qeep_stream_iv(q, tv->iv, tv->iv_len);
        if (ret != QEEP_OK) {
            printf("qeep_stream_iv fail for %d \n", ret);
            results = -1;
            goto encoding_exit;
            }
        for(i=0; i < tv->message_len-16; i=i+16 ) {
            ret = qeep_stream_encode(q, &(tv->message[i]), 16, &cipher[i]);
        }

        ret = qeep_stream_encode(q, &(tv->message[i]), tv->message_len-i, &cipher[i]);
        if (ret != QEEP_OK) {
            printf("qeep_stream_encode fail for %d \n", ret);
            results = -1;
            goto encoding_exit;
        }
        if (memcmp((tv->cipher), cipher, tv->message_len) == 0 ) {
            results = 0;
        } else {
            printf("stream_encode match not match at idx = %d \n", idx);
            printf("iv %ld, seed %ld, msg %ld \n", tv->iv_len, tv->seed_len, tv->message_len);
            printf_buf("seed  ", tv->seed, 16 );
            printf_buf("iv    ", tv->iv,tv->iv_len );
            printf_buf("msg   ", tv->message,tv->message_len );
            printf_buf("Expect", tv->cipher,tv->message_len );
            printf_buf("Output", cipher,tv->message_len );
            results = -1;
        }
    }
encoding_exit:
    free(cipher);
    qeep_close(q);
    return (results);
}

static int test_decoding(known_tv_st *tv, int idx) {
    QEEP q;
    QEEP_RET ret;
    int i;
    int results = 0;
    uint8_t *message = NULL;
    ret = qeep_init(tv->seed, tv->seed_len, &q);
    if (ret != QEEP_OK) {
        printf("qeep_init fail for %d \n", ret);
        return -1;
    }
    message = malloc(tv->message_len);
    if (message == NULL)  {
        printf("allocate mem for message fail \n");
        results = -1;
        goto decoding_exit;
    }
    ret = qeep_decode(q, tv->iv, tv->iv_len, tv->cipher, tv->message_len, message);
    if (ret != QEEP_OK) {
        printf("qeep_decode fail for %d \n", ret);
        results = -1;
        goto decoding_exit;
    }

    if (memcmp((tv->message), message, tv->message_len) == 0 ) {
        // printf("decoding test pass \n");
        results = 0;
    } else {
        printf("message not match at idx = %d \n", idx);
        printf("iv %ld, seed %ld, msg %ld \n", tv->iv_len, tv->seed_len, tv->message_len);
        printf_buf("seed  ", tv->seed, 16 );
        printf_buf("iv    ", tv->iv,tv->iv_len );
        printf_buf("cipher", tv->cipher,tv->cipher_len );
        printf_buf("Expect", tv->message,tv->message_len );
        printf_buf("ouput ", message,tv->message_len );
        results = -1;
    }
    
    /* Test stream_decode */
    if (tv->message_len > 16) {
        ret = qeep_stream_iv(q, tv->iv, tv->iv_len);
        if (ret != QEEP_OK) {
            printf("qeep_stream_iv fail for %d \n", ret);
            results = -1;
            goto decoding_exit;
            }
        for(i=0; i < tv->message_len-16; i=i+16 ) {
            ret = qeep_stream_decode(q, &(tv->cipher[i]), 16, &message[i]);
        }

        ret = qeep_stream_decode(q, &(tv->cipher[i]), tv->message_len-i, &message[i]);
        if (ret != QEEP_OK) {
            printf("qeep_stream_decode fail for %d \n", ret);
            results = -1;
        goto decoding_exit;
        }
        if (memcmp((tv->message), message, tv->message_len) == 0 ) {
            results = 0;
        } else {
            printf("stream_decode message not match at idx = %d \n", idx);
            printf("iv %ld, seed %ld, msg %ld \n", tv->iv_len, tv->seed_len, tv->message_len);
            printf_buf("seed  ", tv->seed, 16 );
            printf_buf("iv    ", tv->iv,tv->iv_len );
            printf_buf("cipher", tv->cipher,tv->cipher_len );
            printf_buf("Expect", tv->message,tv->message_len );
            printf_buf("ouput ", message,tv->message_len );
            results = -1;
        }
    }

decoding_exit:
    free(message);
    qeep_close(q);
    return (results);
}




int q_self_test(int argc, char **argv)
{   
	UNUSED(argc);
	UNUSED(argv);

    known_tv_st tv;

    printf("%s START\n", __FUNCTION__);

    for (int i =0; i < TEST_VECTOR_NUM; i++) {
        //convert hex string test vector to binary
        tv.seed_len = strlen((char*)know_tests_hex[i].seed )/2;
        if (HexToBin(know_tests_hex[i].seed, tv.seed , tv.seed_len) == -1 ) 
            {printf("HexToBin fail \n"); return -1;}
        tv.iv_len = strlen((char*)know_tests_hex[i].iv )/2;
        if (HexToBin(know_tests_hex[i].iv, tv.iv , tv.iv_len) == -1 ) 
            {printf("HexToBin fail \n"); return -1;}
        tv.message_len = strlen((char*)know_tests_hex[i].message )/2;
        if (HexToBin(know_tests_hex[i].message, tv.message , tv.message_len ) == -1 ) 
            {printf("HexToBin fail \n"); return -1;}
        tv.cipher_len = strlen((char*)know_tests_hex[i].cipher )/2;
        if (HexToBin(know_tests_hex[i].cipher, tv.cipher , tv.cipher_len) == -1 ) 
            {printf("HexToBin fail \n"); return -1;}

        // test decoding
        if (test_decoding(&tv, i) != 0 ) return -1;


        // test encoding
        if (test_encoding(&tv, i) != 0) return -1;
    }

    printf("%s END and PASS\n", __FUNCTION__);

    return 0;

}

# ifdef  __cplusplus
}
# endif

