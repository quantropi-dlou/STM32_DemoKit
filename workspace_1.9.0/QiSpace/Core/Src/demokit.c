/**
  * @file           : demokit.c
  * @brief          : demo kit interface control and status
  */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "string.h"

#include "main.h"
#include "serial_stdio.h"

#include "demokit.h"
//#include "qeep.h"


# ifdef  __cplusplus
extern "C" {
# endif

extern int q_self_test(int argc, char **argv);
extern int demo_qeep(int argc, char **argv);
extern int demo_sequr(int argc, char **argv);

uint8_t HexChar (char c)
{
    if ('0' <= c && c <= '9') return (uint8_t)(c - '0');
    if ('A' <= c && c <= 'F') return (uint8_t)(c - 'A' + 10);
    if ('a' <= c && c <= 'f') return (uint8_t)(c - 'a' + 10);
    return 0xFF;
}

int HexToBin (const char* s, uint8_t *buff, int length)
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

/**
  * @brief  demo kit control start
  * @return 
  * 0 - OK
  * -1 error
  */
int demokit_start(void);
int demokit_start()
{
    int ret = 0;

	printf("\nDEMO KIT %s START\n", DEMO_KIT_VERSION);

	ret = q_self_test(0, NULL);
    if (ret) {
        return ret;
    }

	ret = demo_qeep(0, NULL);
    if (ret) {
        return ret;
    }

	ret = demo_sequr(0, NULL);
    if (ret) {
        return ret;
    }

    return ret;

}

# ifdef  __cplusplus
}
# endif

