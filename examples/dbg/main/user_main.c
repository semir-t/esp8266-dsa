#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/uart.h"
#include "debug.h"


static void print_task()
{
    while (1) 
	{
        printDEBUG(DERROR,"Hello world\n");
		vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void app_main()
{
    initDEBUG("", '5', 115200, "DSA - Debug example");
    xTaskCreate(print_task, "uart_print_task", 1024, NULL, 10, NULL);
}
