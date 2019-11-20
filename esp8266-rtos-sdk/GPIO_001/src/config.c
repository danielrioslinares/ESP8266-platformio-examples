// src/config.c

#include "main.h"


// user_rf_cal_sector_set()
//
//	@description : this function sets target flash sector to store RF_CAL
//		parameters. The flash sector selected can be changed in <sector>
//		variable
//
uint32 user_rf_cal_sector_set(void) {

	// Setted sector
	int sector = 5;

	// Current flash size and flash map
    flash_size_map size_map = system_get_flash_size_map();

	// RF_CAL sector initialization
    uint32 rf_cal_sec = 0;

	// RF_CAL sector selection
    switch (size_map) {
        case FLASH_SIZE_4M_MAP_256_256:
            rf_cal_sec = 128 - sector;
            break;

        case FLASH_SIZE_8M_MAP_512_512:
            rf_cal_sec = 256 - sector;
            break;

        case FLASH_SIZE_16M_MAP_512_512:
        case FLASH_SIZE_16M_MAP_1024_1024:
            rf_cal_sec = 512 - sector;
            break;

        case FLASH_SIZE_32M_MAP_512_512:
        case FLASH_SIZE_32M_MAP_1024_1024:
            rf_cal_sec = 1024 - sector;
            break;

        default:
            rf_cal_sec = 0;
            break;
    }

    return rf_cal_sec;

}
//****************************************************************************//


// UART configuration
UART_ConfigTypeDef uart_config = {
	BIT_RATE_115200,            // Baud rate
	UART_WordLength_8b,         // Word length
	USART_Parity_None,          // Parity (redundant data check: None/Even/Odd)
	USART_StopBits_1,           // Stop bits (1:1, 2:1.5 and 3:2 bits)
	USART_HardwareFlowControl_None, // Flow control
	127,                        // FIFO Rx buffer filled threshold (0 - 255)
	UART_None_Inverse           // Inverse mask
};
//****************************************************************************//
