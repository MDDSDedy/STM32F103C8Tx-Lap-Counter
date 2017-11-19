#include "timer4.h"
#include "device.h"
#include "stm32f1xx_hal.h"
#include "lcd.h"
#include "hardware_init.h"
#include "sensor.h"
#include "counter.h"
#include "usart1.h"
#include "cek_startup.h"
int main(void)
{

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART1_UART_Init();

  LCD_Init();
  lcd_clear();
  lcd_gotoxy(0,1);
  lcd_putstr("Embedded System");
  HAL_Delay(3000);
//  cek_startup();
//  show_scanning();
  lcd_clear();
  while (1)
  {
	  HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	  HAL_Delay(100);
	  saklarOn();
	  counterShow();
	  getLap();
	  cekReset();

  }
}
