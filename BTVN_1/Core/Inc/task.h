/*
 * task.h
 *
 *  Created on: Mar 24, 2024
 *      Author: DELL
 */

#ifndef INC_TASK_H_
#define INC_TASK_H_

#include <stdbool.h>
#include <stdint.h>
typedef enum{LED_OFF, LED_WAIT_ON, LED_ON, LED_WAIT_OFF}	led_state_t;
extern	uint32_t	led_timer_count;

void	led_init_state();
void	led_state_update();

#endif /* INC_TASK_H_ */
