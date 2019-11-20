// src/main.h

/* Libraries */

// ESP common
#include "esp_common.h"
#include "uart.h"
#include "gpio.h"


/* Configuration */

// Set flash map (src/cfg_user_rf_cal_sector_set.c)
uint32 user_rf_cal_sector_set(void);

// UART configuration (src/config.c)
UART_ConfigTypeDef uart_config;

/* Declaration */

// gpio.h register
#define FUNC_GPIO(i) \
    (i==0) ? FUNC_GPIO0:  \
    (i==1) ? FUNC_GPIO1:  \
    (i==2) ? FUNC_GPIO2:  \
    (i==3) ? FUNC_GPIO3:  \
    (i==4) ? FUNC_GPIO4:  \
    (i==5) ? FUNC_GPIO5:  \
    (i==6) ? FUNC_GPIO6:  \
    (i==7) ? FUNC_GPIO7:  \
    (i==8) ? FUNC_GPIO8:  \
    (i==9) ? FUNC_GPIO9:  \
    (i==10)? FUNC_GPIO10: \
    (i==11)? FUNC_GPIO11: \
    (i==12)? FUNC_GPIO12: \
    (i==13)? FUNC_GPIO13: \
    (i==14)? FUNC_GPIO14: \
    FUNC_GPIO15
