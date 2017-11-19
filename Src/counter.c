/*
 * counter.c
 *
 *  Created on: Nov 19, 2017
 *      Author: Dedy
 */

#include "counter.h"
#include "stm32f1xx_hal.h"
#include "lcd.h"
#include "usart1.h"
#include <string.h>

uint16_t count=0,detik=0,menit=0,jam=0;
char lcd_buff[20];
char lcd_time[20];
char kir[50];
char time[50];
void timeshow(void);
void CounterUpdate(void){
	++count;
	if(count==100)
	{
		detik++;
		count=0;
	}
	if(detik==60){
		menit++;
		detik=0;
	}
	if(menit==60){
		jam++;
		menit=0;
	}
}
void CounterReset(void){
	count=0;
	detik=0;
	menit=0;
	jam=0;
}
void counterShow(void){
	//lcd_clear();
	lcd_gotoxy(0,0);
	sprintf(lcd_buff, "Time %d:%d:%d:%d", jam,menit,detik,count);
	lcd_putstr(lcd_buff);
	timeshow();
}
void timeshow(void){
	sprintf(time, "$time,%d,%d,%d,%d\n\r", jam,menit,detik,count);
	//HAL_UART_Transmit(&huart2, (uint8_t *)time, strlen(time),20);
	USART1_PutStr(time);
}

void lapshow(unsigned char car,unsigned char lap){
	uint16_t getcount,getdetik,getmenit,getjam;
	getcount=count;
	getdetik=detik;
	getmenit=menit;
	getjam=jam;
	lcd_clear();
	if(lap>3){
		lcd_gotoxy(0,1);
		sprintf(lcd_time, "Car%dEnd=%d:%d:%d", car,getmenit,getdetik,getcount);
		lcd_putstr(lcd_time);
		sprintf(kir, "$data,%d,Finish,%d,%d,%d,%d\n\r", car,getjam,getmenit,getdetik,getcount);
		//HAL_UART_Transmit(&huart2, (uint8_t *)kir, strlen(kir),20);
		USART1_PutStr(kir);


	}
	else{
		lcd_gotoxy(0,1);
		sprintf(lcd_time, "Car%dL%d=%d:%d:%d:%d", car,lap,getjam,getmenit,getdetik,getcount);
		lcd_putstr(lcd_time);
		sprintf(kir, "$data,%d,%d,%d,%d,%d,%d\n\r", car,lap,getjam,getmenit,getdetik,getcount);
		//HAL_UART_Transmit(&huart2, (uint8_t *)kir, strlen(kir),20);
		USART1_PutStr(kir);
	}
}
