#include "delay.h"

void hw_timer_callback1(void *arg)
{
	static int state = 0;

	uint8_t * flag = (uint8_t * )arg;
	*flag = 0;
}


void delay_us(uint32_t us)
{
	if(us < 11)
	{
        uint8_t k = 0;
        for(k = 0; k < (us * 12); k++)
        {
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
            __asm__("nop");
        }
        return;
	}

    uint8_t flag = 1;
    void * arg = & flag;
    hw_timer_init(hw_timer_callback1, arg);
    hw_timer_alarm_us(us, TIMER_ONE_SHOT);
    while(flag)
    {

    }
    hw_timer_deinit();
    return;
}

