// src/main.c

#include "main.h"


// task_blink_gpio()
//
//	@description : blink GPIO
//
typedef struct _Task_Parameters {
    unsigned int gpio_port;
    xTaskHandle xHandle;
} Task_Parameters_blink_gpio;
// Task parameters definitions
Task_Parameters_blink_gpio task_blink_gpio_pvParameters[16] = {
	{ 0, NULL},{ 1, NULL},{ 2, NULL},{ 3, NULL},{ 4, NULL},{ 5, NULL},
	{ 6, NULL},{ 7, NULL},{ 8, NULL},{ 9, NULL},{10, NULL},{11, NULL},
	{12, NULL},{13, NULL},{14, NULL},{15, NULL}
	};
// Actual function
void task_blink_gpio(void *pvParameters) {

	// Passing GPIO port as argument
    Task_Parameters_blink_gpio *thisTask_Parameters = (Task_Parameters_blink_gpio *) pvParameters;
	unsigned int gpio_port = thisTask_Parameters->gpio_port;

	// Select GPIO port as output
	PIN_FUNC_SELECT(GPIO_PIN_REG(gpio_port), FUNC_GPIO(gpio_port));

	// Loop (blink)
    while(true) {

		GPIO_OUTPUT_SET(GPIO_ID_PIN(gpio_port), 1); // Set HIGH
		vTaskDelay( 500 / portTICK_RATE_MS );
		GPIO_OUTPUT_SET(GPIO_ID_PIN(gpio_port), 0); // Set LOW
		vTaskDelay( 500 / portTICK_RATE_MS );

	}

    vTaskDelete(NULL);
}
//****************************************************************************//


// user_init()
//
//	@description : initialization entry point (setup)
//
void user_init(void) {

    // Create a blink task for GPIO port identified by variable gpio_port
	xTaskCreate(
		task_blink_gpio,          // Task function identifier
		"blink02",                // Name (humanized identification)
		configMINIMAL_STACK_SIZE, // Stack dedicated size
		(void*)&task_blink_gpio_pvParameters[ 2], // Task function argument
		tskIDLE_PRIORITY + 1,     // Priority (0 to configMAX_PRIORITIES-1)
		&task_blink_gpio_pvParameters[ 2].xHandle // Task's handle
	);

}
//****************************************************************************//
