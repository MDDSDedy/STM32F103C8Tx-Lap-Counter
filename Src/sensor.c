/*
 * sensor.c
 *
 *  Created on: Nov 19, 2017
 *      Author: Dedy
 */

#include "sensor.h"
#include "device.h"
#include "stm32f1xx_hal.h"
#include "hardware_init.h"
#include "lcd.h"
#include "counter.h"
#include "timer4.h"
#include "usart1.h"
#include <string.h>

unsigned int Timeout_loop = 0;
unsigned int Timeout_value = 10000000 ;
/* Private variables ---------------------------------------------------------*/
//UART_HandleTypeDef huart2;
uint8_t lap1 = 0;
uint8_t lap2 = 0;
uint8_t lap3 = 0;


uint32_t msec = 0;
uint32_t sec = 0;
uint32_t min = 0;

void reset_Timer(void){
	if (HAL_GPIO_ReadPin(STOP_GPIO_Port, STOP_Pin) == GPIO_PIN_RESET){
		HAL_Delay (20);
		if (HAL_GPIO_ReadPin(STOP_GPIO_Port, STOP_Pin)==GPIO_PIN_RESET){
			while (HAL_GPIO_ReadPin(STOP_GPIO_Port, STOP_Pin)==GPIO_PIN_RESET);
			if(flagOn==1){
				flagOn = flagOn - 1;
				USART1_PutStr("$Reset\n\r");
				//HAL_GPIO_WritePin(Ind_Tim_GPIO_Port, Ind_Tim_Pin, GPIO_PIN_RESET);
			}
			else;
		}
		else;
	}
}

void saklarOn(void){
	uint32_t  Timeout_loop1=0;
	uint32_t  Timeout_value1=0x7FFFFF;
	uint32_t  Timeout_loop2=0;
	uint32_t  Timeout_value2=0x7FFFFF;
	if ((HAL_GPIO_ReadPin(START_GPIO_Port, START_Pin) == GPIO_PIN_RESET) && flagOn==0){
		HAL_Delay (20);
		if (HAL_GPIO_ReadPin(START_GPIO_Port, START_Pin)==GPIO_PIN_RESET){
			while (HAL_GPIO_ReadPin(START_GPIO_Port, START_Pin)==GPIO_PIN_RESET && (Timeout_loop1++<=Timeout_value1));
			if (Timeout_loop1>=Timeout_value1){
//				char *msg = "$StartTimeout\n\r";
//				HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg),10);
				USART1_PutStr("$StartTimeout\n\r");
				//HAL_GPIO_WritePin(Buz_GPIO_Port,Buz_Pin,GPIO_PIN_RESET);
				HAL_Delay(1000);
				//HAL_GPIO_WritePin(Buz_GPIO_Port,Buz_Pin,GPIO_PIN_SET);
				HAL_Delay(1000);
			}
			else{
				if(flagOn==0){
					//char *msg = "$Start\n\r";
					flagOn = flagOn + 1;
					//HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg),10);
					USART1_PutStr("$Start\n\r");
					HAL_GPIO_TogglePin(Ind_Tim_GPIO_Port,Ind_Tim_Pin);
					start_timer();

				}
				else;
			}

		}
		else;
	}
	if ((HAL_GPIO_ReadPin(START_GPIO_Port, START_Pin) == GPIO_PIN_RESET) && flagOn==1){
			HAL_Delay (20);
			if (HAL_GPIO_ReadPin(START_GPIO_Port, START_Pin)==GPIO_PIN_RESET){
				while (HAL_GPIO_ReadPin(START_GPIO_Port, START_Pin)==GPIO_PIN_RESET && (Timeout_loop2++<=Timeout_value2));
				if (Timeout_loop2>=Timeout_value2){
//					char *msg = "$StopTimeout\n\r";
//					HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg),10);
					USART1_PutStr("$StopTimeout\n\r");
					//HAL_GPIO_WritePin(Buz_GPIO_Port,Buz_Pin,GPIO_PIN_RESET);
					HAL_Delay(500);
					//HAL_GPIO_WritePin(Buz_GPIO_Port,Buz_Pin,GPIO_PIN_SET);
					HAL_Delay(500);
				}
				else{
				if(flagOn==1){
					flagOn = flagOn - 1;
//					char *msg = "$Stop\n\r";
//					HAL_UART_Transmit(&huart2, (uint8_t *)msg, strlen(msg),10);
					USART1_PutStr("$Stop\n\r");
					//HAL_GPIO_WritePin(Ind_Tim_GPIO_Port, Ind_Tim_Pin, GPIO_PIN_RESET);
					HAL_GPIO_TogglePin(Ind_Tim_GPIO_Port,Ind_Tim_Pin);
					stoptimer();
				}
				else;
				}
			}
			else;
		}
}
void getLap(){
	uint32_t  Timeout_loop=0;
	uint32_t  Timeout_value=5000000;

	if (flagOn==0){
		lap1 = 0;
		lap2 = 0;
		lap3 = 0;
	}
	if(flagOn==1){
		if (HAL_GPIO_ReadPin(S1_GPIO_Port, S1_Pin)==GPIO_PIN_SET){
			HAL_Delay(20);
			if (HAL_GPIO_ReadPin(S1_GPIO_Port, S1_Pin)==GPIO_PIN_SET){
				while((HAL_GPIO_ReadPin(S1_GPIO_Port, S1_Pin)==GPIO_PIN_SET) && (Timeout_loop++<=Timeout_value));
				if (Timeout_loop>=Timeout_value){
	//				HAL_UART_Transmit(&huart2, (uint8_t *)&"Timeout1\n\r",10,10);
					USART1_PutStr("Timeout1\n\r");
					//HAL_GPIO_WritePin(Buz_GPIO_Port,Buz_Pin,GPIO_PIN_RESET);
					HAL_Delay(500);
					//HAL_GPIO_WritePin(Buz_GPIO_Port,Buz_Pin,GPIO_PIN_SET);
					HAL_Delay(500);

				}
				else{
					HAL_GPIO_WritePin(Ind_S1_GPIO_Port,Ind_S1_Pin,GPIO_PIN_SET);
					HAL_Delay(50);
					HAL_GPIO_WritePin(Ind_S1_GPIO_Port,Ind_S1_Pin,GPIO_PIN_RESET);
					lap1 = lap1 + 1;
					lapshow(1,lap1);
				}
			}
			else;
		}
		if (HAL_GPIO_ReadPin(S2_GPIO_Port, S2_Pin)==GPIO_PIN_SET){
			HAL_Delay(20);
			if (HAL_GPIO_ReadPin(S2_GPIO_Port, S2_Pin)==GPIO_PIN_SET){
				while((HAL_GPIO_ReadPin(S2_GPIO_Port, S2_Pin)==GPIO_PIN_SET) && (Timeout_loop++<=Timeout_value));
				if (Timeout_loop>=Timeout_value){
					//HAL_UART_Transmit(&huart2, (uint8_t *)&"Timeout2\n\r",10,10);
					USART1_PutStr("Timeout2\n\r");
					for(int ss=0;ss<=1;ss++){
						//HAL_GPIO_WritePin(Buz_GPIO_Port,Buz_Pin,GPIO_PIN_RESET);
						HAL_Delay(500);
						//HAL_GPIO_WritePin(Buz_GPIO_Port,Buz_Pin,GPIO_PIN_SET);
						HAL_Delay(500);
					}

				}
				else{
					HAL_GPIO_WritePin(Ind_S2_GPIO_Port,Ind_S2_Pin,GPIO_PIN_SET);
					HAL_Delay(50);
					HAL_GPIO_WritePin(Ind_S2_GPIO_Port,Ind_S2_Pin,GPIO_PIN_RESET);
					lap2 = lap2 + 1;
					lapshow(2,lap2);
				}
			}
			else;
		}
		if (HAL_GPIO_ReadPin(S3_GPIO_Port, S3_Pin)==GPIO_PIN_SET){
			HAL_Delay(20);
			if (HAL_GPIO_ReadPin(S3_GPIO_Port, S3_Pin)==GPIO_PIN_SET){
				while((HAL_GPIO_ReadPin(S3_GPIO_Port, S3_Pin)==GPIO_PIN_SET) && (Timeout_loop++<=Timeout_value));
				if (Timeout_loop>=Timeout_value){
					//HAL_UART_Transmit(&huart2, (uint8_t *)&"Timeout3\n\r",10,10);
					USART1_PutStr("Timeout3\n\r");
					for(int ss=0;ss<=2;ss++){
						//HAL_GPIO_WritePin(Buz_GPIO_Port,Buz_Pin,GPIO_PIN_RESET);
						HAL_Delay(500);
						//HAL_GPIO_WritePin(Buz_GPIO_Port,Buz_Pin,GPIO_PIN_SET);
						HAL_Delay(500);
					}
				}
				else{
					HAL_GPIO_WritePin(Ind_S3_GPIO_Port,Ind_S3_Pin,GPIO_PIN_SET);
					HAL_Delay(50);
					HAL_GPIO_WritePin(Ind_S3_GPIO_Port,Ind_S3_Pin,GPIO_PIN_RESET);
					lap3 = lap3 + 1;
					lapshow(3,lap3);
				}
			}
			else;
		}
	}
}


void cekReset(void){
	//uint8_t FlagDetect=0;

	if(HAL_GPIO_ReadPin(STOP_GPIO_Port,STOP_Pin)== GPIO_PIN_RESET) {
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(STOP_GPIO_Port,STOP_Pin)== GPIO_PIN_RESET) {
			while(HAL_GPIO_ReadPin(STOP_GPIO_Port,STOP_Pin)== GPIO_PIN_RESET && (Timeout_loop++<=Timeout_value));
			if (Timeout_loop >= Timeout_value)
			{
				//FlagDetect=0;
				//HAL_UART_Transmit(&huart2, (uint8_t *)&"ResetTimeout\n\r",10,10);
				USART1_PutStr("ResetTimeout\n\r");
				//HAL_GPIO_WritePin(Buz_GPIO_Port,Buz_Pin,GPIO_PIN_RESET);
				//HAL_Delay(1000);
				//HAL_GPIO_WritePin(Buz_GPIO_Port,Buz_Pin,GPIO_PIN_SET);
				//HAL_Delay(1000);
			}
			else
			{
			    stoptimer();
			    flagOn=0;
			    CounterReset();
			    lcd_clear();
			    HAL_GPIO_TogglePin(Ind_RESET_GPIO_Port,Ind_RESET_Pin);

			}
		}
	}
}
