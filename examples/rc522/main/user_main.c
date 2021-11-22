#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/uart.h"
#include "debug.h"

#include "mfrc522.h"

static const char* TAG = "app";

//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
//NOTE:
//
//Connection to the RFID-RC522 module
//RC522			-			NODE MCU
//SDA			-			D2
//SCK			-			D5
//MOSI			-			D6
//MISO			-			D7
//3V3			-			3V3
//GND			-			GND

static void print_task()
{
	uint32_t time = 0x00000000;
    while (1) 
	{
		if(time % 2)
		{
			/* printDEBUG(DUSER,"Hello world [%d][%x]\n",time,time); */
		}
		else
		{
			/* printDEBUG(DUSER | DWARNING,"Hello world [%d][%x]\n",time,time); */
		}
		time++;
		vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

static void rfid_task()
{
	while(1)
	{
		uint8_t CardID[5];
		if (MFRC522_Check(CardID) == MI_OK)
		{

			printDEBUG(DSYS,"Card detected\n");
			printDEBUG(DSYS,"%xb%xb%xb%xb\n",CardID[0],CardID[1],CardID[2],CardID[3],CardID[4]);
			/* os_printf("\r\nNEW CARD!\n\r"); */
			/* os_printf("0x%08x\n", CardID[0]); */
			/* os_printf("0x%08x\n", CardID[1]); */
			/* os_printf("0x%08x\n", CardID[2]); */
			/* os_printf("0x%08x\n", CardID[3]); */
			/* os_printf("0x%08x\n", CardID[4]); */
		}
		vTaskDelay(10/portTICK_PERIOD_MS);
	}
}

void app_main()
{
    initDEBUG("", '5', 115200, "DSA - Debug example");

    xTaskCreate(print_task, "uart_print_task", 1024, NULL, 10, NULL);
	MFRC522_Init();
    xTaskCreate(rfid_task, "rfid_task", 1024, NULL, 10, NULL);
}


