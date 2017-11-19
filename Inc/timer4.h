/*
 * timer4.h
 *
 *  Created on: Nov 19, 2017
 *      Author: Dedy
 */

#ifndef TIMER4_H_
#define TIMER4_H_
#include "device.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"
#include "counter.h"
void TIM4_IRQHandler(void);
void MX_TIM4_Init();
void start_timer(void);
void stoptimer(void);
extern TIM_HandleTypeDef htim4;
#endif /* TIMER4_H_ */
