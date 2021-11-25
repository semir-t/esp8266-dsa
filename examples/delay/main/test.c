#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/uart.h"
#include "driver/gpio.h"
#include "driver/hw_timer.h"
#include "debug.h"

#define GPIO_LED										16

static void print_task()
{
	uint32_t time = 0x00000000;
	while (1) 
	{
		if(time % 2)
		{
			printDEBUG(DUSER,"Hello world [%d][%x]\n",time,time);
		}
		else
		{
			printDEBUG(DUSER | DWARNING,"Hello world [%d][%x]\n",time,time);
		}
		time++;
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}
}
void hw_timer_callback1(void *arg)
{
	static int state = 0;
	/* gpio_set_level(GPIO_OUTPUT_IO_0, (state ++) % 2); */
	gpio_set_level(GPIO_LED,(state ++) % 2);
	printDEBUG(DSYS,"TIMER\n");

}

void delay_ms(uint32_t ms)
{
	printDEBUG(DSYS,"-> Initialize TIM\n");
	printDEBUG(DSYS,"-> Set alarm\n");
	/* hw_timer_alarm_us(100,true); */
	/* hw_timer_set_clkdiv(TIMER_CLKDIV_1); */
	vTaskDelay(10 / portTICK_RATE_MS);
	printDEBUG(DSYS,"Timer[%d]\n",hw_timer_get_count_data);
	printDEBUG(DSYS,"-> Deinit\n");
	/* hw_timer_deinit(); */

	/* while(1) */
	/* { */

	/* 	vTaskDelay(100 / portTICK_RATE_MS); */
	/* } */

}
void app_main()
{
	initDEBUG("", '5', 115200, "DSA - Debug example");
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

	xTaskCreate(print_task, "uart_print_task", 1024, NULL, 10, NULL);
	hw_timer_init(hw_timer_callback1, NULL);
	hw_timer_enable(true);
	while (1) 

	{
		delay_ms(100);
		vTaskDelay(100 / portTICK_RATE_MS);
		/* gpio_set_level(GPIO_LED, 0); */
		/* vTaskDelay(100 / portTICK_RATE_MS); */
		/* gpio_set_level(GPIO_LED, 1); */
	}

}


