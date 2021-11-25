/* hw_timer example
 *
 *    This example code is in the Public Domain (or CC0 licensed, at your option.)
 *
 *       Unless required by applicable law or agreed to in writing, this
 *          software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 *             CONDITIONS OF ANY KIND, either express or implied.
 *             */

#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "esp_log.h"

#include "driver/gpio.h"
#include "driver/hw_timer.h"
#include "debug.h"
#include "delay.h"

static const char *TAG = "hw_timer_example";

#define GPIO_OUTPUT_IO_0    16
#define GPIO_OUTPUT_PIN_SEL  ((1ULL << GPIO_OUTPUT_IO_0))


void app_main(void)
{
	initDEBUG("", '5', 115200, "DSA - Debug example\n");
	gpio_config_t io_conf;
	io_conf.intr_type = GPIO_INTR_DISABLE;
	io_conf.mode = GPIO_MODE_OUTPUT;
	io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
	io_conf.pull_down_en = 0;
	io_conf.pull_up_en = 0;
	gpio_config(&io_conf);

	while(1)
	{
		gpio_set_level(GPIO_OUTPUT_IO_0,0);
		delay_us(200000);
		gpio_set_level(GPIO_OUTPUT_IO_0,1);
		vTaskDelay(100 / portTICK_RATE_MS);
	}
}


