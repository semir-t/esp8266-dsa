
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "driver/gpio.h"
#include "driver/uart.h"

#define BUF_SIZE (1024)

#define GPIO_LED										16
static void task_print();
static void task_blink();

void app_main(void)
{
	xTaskCreate(task_blink, "gpio_blink_task", 1024, NULL, 10, NULL);
	xTaskCreate(task_print, "uart_print_task", 1024, NULL, 10, NULL);
}

void task_blink()
{
	gpio_config_t io_conf;
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO15/16
    io_conf.pin_bit_mask =  (1 << GPIO_LED);
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);


    while (1) 
	{
		gpio_set_level(GPIO_LED, 1);
        vTaskDelay(100 / portTICK_RATE_MS);
        gpio_set_level(GPIO_LED, 0);
        vTaskDelay(100 / portTICK_RATE_MS);
    }
	
		
}
void task_print()
{
    // Configure parameters of an UART driver,
    // communication pins and install the driver
    uart_config_t uart_config =
	{
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_NUM_0, &uart_config);
    uart_driver_install(UART_NUM_0, BUF_SIZE * 2, 0, 0, NULL, 0);

    // Configure a temporary buffer for the incoming data

    while (1) 
    {
		vTaskDelay(1000/portTICK_PERIOD_MS);
		uint8_t str[] = {"Hello world\r\n"};
		uint8_t k = 0;
		while(str[k] != '\0')
		{
			uart_write_bytes(UART_NUM_0,(const char*) & str[k], 1);
			k++;
		}
    }
}

