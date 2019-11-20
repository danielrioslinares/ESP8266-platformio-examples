// src/main.c

#include "main.h"


// uart_yield_time()
//
//	@description : print the time since booting each second
//
void uart_yield_time(void *pvParameters) {

	// Seconds counter
	int i = 0;

	// Tick settings
	const portTickType xPrintPeriod = 1000 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();

	// Loop (blink)
	while(true) {

		// Start right away and repeat every 1 second (1 Hz)
		vTaskDelayUntil(&xLastWakeTime, xPrintPeriod);

		// Print seconds from startup
		os_printf("%i seconds \n", i);

		// +1 second
		i++;

	}

	vTaskDelete(NULL);
}
//****************************************************************************//


// user_init()
//
//	@description : initialization entry point (setup)
//
void user_init(void) {

	// UART begin
	UART_ParamConfig(UART0, &uart_config); UART_SetPrintPort(UART0);

	// Create a blink task for GPIO port identified by variable gpio_port
	xTaskCreate(
		uart_yield_time,           // Task function identifier
		"uart00",                  // Name (humanized identification)
		configMINIMAL_STACK_SIZE,  // Stack dedicated size
		NULL,                      // Task function argument
		tskIDLE_PRIORITY + 1,      // Priority (0 to configMAX_PRIORITIES-1)
		NULL                       // Task's handle
	);

}
//****************************************************************************//
