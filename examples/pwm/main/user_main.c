#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/uart.h"
#include "driver/pwm.h"
#include "debug.h"

#define PWM_CNT_ARRAY_SIZE			17

#define GPIO_LED					5
#define PWM_PERIOD					(1000)			// * [us]

uint16_t pwm[PWM_CNT_ARRAY_SIZE] = {0,2,5,11,23,50,109,235,509,999,509,235,109,50,23,11,5,2};
uint8_t pwm_cnt = 0;

const uint32_t pin_num[1] = 
{
	GPIO_LED,
};

// duties table, real_duty = duties	[x]/PERIOD
uint32_t duties[1] = 
{
	128 
};

// phase table, delay = (phase[x]/360)*PERIOD
float phase[1] = 
{
	0, 
};

void pwm_task();

void app_main()
{
    initDEBUG("", '5', 921600, "DSA - Debug example");
    xTaskCreate(pwm_task, "pwm_task", 1024, NULL, 10, NULL);
}

void pwm_task()
{

	pwm_init(PWM_PERIOD, duties, 1, pin_num);
	pwm_set_phases(phase);
	pwm_start();

	while (1) 
	{
		pwm_stop(0);
		pwm_set_duty(0,1000 - pwm[pwm_cnt]);
		pwm_start();
		pwm_cnt++;
		if(pwm_cnt == (PWM_CNT_ARRAY_SIZE))
		{
			pwm_cnt = 0;
		}
		vTaskDelay(200/portTICK_PERIOD_MS);
    }
}
