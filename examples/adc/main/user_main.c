#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/uart.h"
#include "driver/adc.h"
#include "debug.h"



void adc_task();

void app_main()
{
    initDEBUG("", '5', 115200, "DSA - Debug example");
    xTaskCreate(adc_task, "adc_task", 1024, NULL, 10, NULL);
}

void adc_task()
{
	adc_config_t adc_config;

	// Depend on menuconfig->Component config->PHY->vdd33_const value
	// When measuring system voltage(ADC_READ_VDD_MODE), vdd33_const must be set to 255.
	adc_config.mode = ADC_READ_TOUT_MODE;
	adc_config.clk_div = 8; // ADC sample collection clock = 80MHz/clk_div = 10MHz

	// ESP_ERROR_CHECK(adc_init(&adc_config));
	adc_init(&adc_config);
	uint16_t adc_data;

	while (1) 
	{
		if (ESP_OK == adc_read(&adc_data)) 
		{
			printDEBUG(DSYS, "adc read: %d\r\n", adc_data);
		}
		vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
