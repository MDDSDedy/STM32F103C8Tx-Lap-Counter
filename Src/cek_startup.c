/*
 * cek_startup.c
 *
 *  Created on: Nov 19, 2017
 *      Author: Dedy
 */

#include "device.h"
#include "stm32f1xx_hal.h"
#include "hardware_init.h"
#include "lcd.h"
#include "cek_startup.h"
#include <string.h>

char biff[30],kon_sen[3];
void cek_startup(void){
if (HAL_GPIO_ReadPin(S1_GPIO_Port, S1_Pin)==GPIO_PIN_RESET){
	HAL_Delay(20);
	if (HAL_GPIO_ReadPin(S1_GPIO_Port, S1_Pin)==GPIO_PIN_RESET){
		kon_sen[0]=1;
	}
	else{
		kon_sen[0]=0;
	}
}
if (HAL_GPIO_ReadPin(S2_GPIO_Port, S2_Pin)==GPIO_PIN_RESET){
	HAL_Delay(20);
	if (HAL_GPIO_ReadPin(S2_GPIO_Port, S2_Pin)==GPIO_PIN_RESET){
		kon_sen[1]=1;
	}
	else{
		kon_sen[1]=0;
	}
}
if (HAL_GPIO_ReadPin(S3_GPIO_Port, S3_Pin)==GPIO_PIN_RESET){
	HAL_Delay(20);
	if (HAL_GPIO_ReadPin(S3_GPIO_Port, S3_Pin)==GPIO_PIN_RESET){
		kon_sen[2]=1;
	}
	else{
		kon_sen[2]=0;
	}
}
}
void show_scanning(void){
	for(int i=0; i<3; i++){
	   lcd_clear();
	   lcd_gotoxy(0,0);
	   lcd_putstr("Cek Sensor");
	   lcd_gotoxy(0,1);
		int j=i+1;
		if(kon_sen[i]==1){
			sprintf(biff,"Sensor-%d Ready",j);
			lcd_putstr(biff);
		}
		else{
			sprintf(biff,"Sensor-%d Error",j);
			lcd_putstr(biff);

		}
		HAL_Delay(500);
	}
	if(kon_sen[0]==1 && kon_sen[1]==1 && kon_sen[2]==1){
	   lcd_clear();
	   lcd_gotoxy(0,0);
	   lcd_putstr("Cek Sensor");
	   lcd_gotoxy(0,1);
	   lcd_putstr("All Green");
	   HAL_Delay(500);
	}
	else{
	   int errrorr=3;
	   errrorr = errrorr-(kon_sen[0] + kon_sen[1] + kon_sen[2]);
	   lcd_clear();
	   lcd_gotoxy(0,0);
	   lcd_putstr("Sensor not Ready");
	   lcd_gotoxy(0,1);
	   sprintf(biff,"%d Sensor Error",errrorr);
	   lcd_putstr(biff);
	   HAL_Delay(1000);

	}
}
