/*
 * usart1.c
 *
 *  Created on: Nov 19, 2017
 *      Author: Dedy
 */

#include "usart1.h"
#include "hardware_init.h"
#include "timer4.h"
#include "stm32f1xx_hal.h"
UART_HandleTypeDef huart1;
//volatile char received_data=0;

//unsigned char pbStartCount = 0;
//unsigned char Car0Count = 0, Car1Count = 0, Car2Count = 0;
//unsigned int LapHour[3][4], LapMinute[3][4], LapSecond[3][4], LapCount[3][4];
//unsigned int count = 0, second = 0, minute = 0, hour = 0;
/* USART2 init function */
void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
	  return;
    //Error_Handler();
  }
}
//void USART2_IRQHandler(void)
//{
//	if(__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE)){
//		received_data = USART2->DR;
//		if (received_data == '1'){
//			if((pbStartCount++)%2 == 0){
//				//start_timer();
//			}
//			else {
//				//stoptimer();
//			}
//		}
//		else if (received_data == '2'){
////			count = 0;
////			second = 0;
////			minute = 0;
////			hour = 0;
//			Car0Count = 0;
//			Car1Count = 0;
//			Car2Count = 0;
//			for(unsigned char i = 0; i<3; i++){
//				for(unsigned char j = 0; j<4; j++){
//					LapHour[i][j] = 0;
//					LapMinute[i][j] = 0;
//					LapSecond[i][j] = 0;
//					LapCount[i][j] = 0;
//				}
//			}
//		}
//		else if(received_data == '3'){
//			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
//		}
//		else if (received_data == '4'){
//			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
//		}
//		else if (received_data == '5'){
//			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
//		}
//		else if (received_data == '6'){
//			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
//		}
//	}
//}
void USART1_PutChar(char c){
	MX_USART1_UART_Init();
	uint8_t ch;
	ch = c;
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch,1,10);
//	HAL_UART_Transmit(&huart2, (uint8_t *)&"$Start\n",8,10);
//	while(__HAL_UART_GET_FLAG(&huart2, UART_FLAG_TC) == RESET);
}
void USART1_PutStr(char *data){
	MX_USART1_UART_Init();
	int i = 0;
	int n = strlen(data);
	for(i=0; i<n; i++){
		USART1_PutChar(data[i]);
	}
}
