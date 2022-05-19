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

#include "qeep.h"


# ifdef  __cplusplus
extern "C" {
# endif

extern int q_self_test(int argc, char **argv);
extern int demo_qeep(int argc, char **argv);
extern int demo_sequr(int argc, char **argv);


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

