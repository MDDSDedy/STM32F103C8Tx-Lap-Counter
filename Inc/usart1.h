/*
 * usart1.h
 *
 *  Created on: Nov 19, 2017
 *      Author: Dedy
 */

#ifndef USART1_H_
#define USART1_H_
#include <string.h>
#include "stm32f1xx_hal.h"
#include "timer4.h"

GPIO_InitTypeDef GPIO_InitStruct;
extern UART_HandleTypeDef huart1;

extern volatile char received_data;
extern unsigned char pbStartCount;
extern unsigned char Car0Count, Car1Count, Car2Count;
extern unsigned int LapHour[3][4], LapMinute[3][4], LapSecond[3][4], LapCount[3][4];

void USART1_IRQHandler(void);
void MX_USART1_UART_Init(void);
extern void USART1_PutChar(char c);
extern void USART1_PutStr(char *data);
#endif /* USART1_H_ */
