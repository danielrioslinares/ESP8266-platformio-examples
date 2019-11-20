// src/main.c

#include "main.h"


// task_mimic_gpio()
//
//	@description : GPIO
//
typedef struct _Task_Parameters {
    unsigned int mimic_gpio_port;
	unsigned int write_gpio_port;
    xTaskHandle xHandle;
} Task_Parameters_mimic_gpio;
// Task parameters definitions
Task_Parameters_mimic_gpio task_mimic_gpio_pvParameters = {12, 2, NULL};
// Actual function
void task_mimic_gpio(void *pvParameters) {

	// Passing GPIO port as argument
    Task_Parameters_mimic_gpio *thisTask_Parameters = (Task_Parameters_mimic_gpio *) pvParameters;
	unsigned int mimic_gpio_port = thisTask_Parameters->mimic_gpio_port;
	unsigned int write_gpio_port = thisTask_Parameters->write_gpio_port;

	// Select GPIO port functions
	PIN_FUNC_SELECT(GPIO_PIN_REG(write_gpio_port), FUNC_GPIO(write_gpio_port));
	PIN_FUNC_SELECT(GPIO_PIN_REG(mimic_gpio_port), FUNC_GPIO(mimic_gpio_port));

	// Loop (blink)
    while(true) {

		if (!GPIO_INPUT_GET(GPIO_ID_PIN(mimic_gpio_port))) {
			GPIO_OUTPUT_SET(GPIO_ID_PIN(write_gpio_port), 1); // Set HIGH
		} else {
			GPIO_OUTPUT_SET(GPIO_ID_PIN(write_gpio_port), 0); // Set LOW
		}

	}

    vTaskDelete(NULL);
}
//****************************************************************************//


// user_init()
//
//	@description : initialization entry point (setup)
//
void user_init(void) {

    // Create a mimic task for GPIO port
	xTaskCreate(
		task_mimic_gpio,          // Task function identifier
		"mimic12_02",             // Name (humanized identification)
		configMINIMAL_STACK_SIZE, // Stack dedicated size
		(void*)&task_mimic_gpio_pvParameters, // Task function argument
		tskIDLE_PRIORITY + 1,     // Priority (0 to configMAX_PRIORITIES-1)
		&task_mimic_gpio_pvParameters.xHandle // Task's handle
	);

}
//****************************************************************************//
