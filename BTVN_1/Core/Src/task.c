/*
 * task.c
 *
 *  Created on: Mar 24, 2024
 *      Author: DELL
 */
#include "task.h"
#include "main.h"

static	led_state_t	led_state;
uint32_t	led_timer_count = 0;


void led_control(bool state)
{
	if(state)	LL_GPIO_SetOutputPin(LED_GPIO_Port, LED_Pin);
	else LL_GPIO_ResetOutputPin(LED_GPIO_Port, LED_Pin);
}

bool is_btn_press()
{
	if(LL_GPIO_IsInputPinSet(Btn_GPIO_Port, Btn_Pin))	return false;
	else return true;
}

void led_set_timer(uint32_t	ms)
{
	led_timer_count = ms;
}

bool led_timer_over()
{
	if(led_timer_count == 0)	return true;
	else return false;
}

void led_init_state()
{
	led_state = LED_OFF;
	led_control(false);
}

void led_state_update()
 {
	 switch (led_state)
	 {
	 case LED_OFF:
		 if(is_btn_press())
		 {
			 led_state = LED_WAIT_ON;
			 led_set_timer(3000);
		 }
		 break;

	 case LED_WAIT_ON:
		 if (!is_btn_press())
		 {
			 led_state = LED_OFF;
		 }
		 else if (led_timer_over())
		 {
			 led_state = LED_ON;
			 led_control(true);
		 }
		 break;

	 case LED_ON:
		 if (is_btn_press())
		 {
			 led_state = LED_WAIT_OFF;
			 led_set_timer(6000);
		 }
		 break;

	 case LED_WAIT_OFF:
		 if (!is_btn_press())
		 {
			 led_state = LED_ON;
		 }
		 else if (led_timer_over())
		 {
			 led_state = LED_OFF;
			 led_control(false);
		 }
		 break;
	 }
 }

