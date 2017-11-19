/*
 * lcd.h
 *
 *  Created on: Nov 19, 2017
 *      Author: Dedy
 */

#ifndef LCD_H_
#define LCD_H_

#include "stm32f1xx_hal.h"

#define D7_Pin GPIO_PIN_9
#define D7_GPIO_Port GPIOB
#define D6_Pin GPIO_PIN_8
#define D6_GPIO_Port GPIOB
#define D5_Pin GPIO_PIN_7
#define D5_GPIO_Port GPIOB
#define D4_Pin GPIO_PIN_6
#define D4_GPIO_Port GPIOB
#define EN_Pin GPIO_PIN_5
#define EN_GPIO_Port GPIOB
#define RW_Pin GPIO_PIN_4
#define RW_GPIO_Port GPIOB
#define RS_Pin GPIO_PIN_3
#define RS_GPIO_Port GPIOB

#define Set_En		HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
#define Clr_En		HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
#define Set_RW		HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_SET);
#define Clr_RW		HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, GPIO_PIN_RESET);
#define Set_RS		HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET);
#define Clr_RS		HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);

void LCD_Init(void);
void lcd_string(const char *xx);
void lcd_gotoxy(unsigned char x, unsigned char y);
void wait_lcd(unsigned long int xx);
void lcd_clear(void);
#endif /* LCD_H_ */
