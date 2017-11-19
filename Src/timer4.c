#include "stm32f1xx_hal.h"
#include "timer4.h"

TIM_HandleTypeDef htim4;

void TIM4_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htim4);
	if (__HAL_TIM_GET_FLAG(&htim4, TIM_FLAG_UPDATE) != RESET)      //In case other interrupts are also running
	{
		if (__HAL_TIM_GET_IT_SOURCE(&htim4, TIM_IT_UPDATE) != RESET)
		{
			__HAL_TIM_CLEAR_FLAG(&htim4, TIM_FLAG_UPDATE);
			/*put your code here */
			CounterUpdate();

		}
	}
}

void MX_TIM4_Init(void)
{
  htim4.Init.Prescaler = 36000-1;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 20-1;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Instance = TIM4;//Same timer whose clocks we enabled
  HAL_TIM_Base_Init(&htim4);     // Init timer
 // HAL_TIM_Base_Start_IT(&htim4); // start timer interrupts
  HAL_NVIC_SetPriority(TIM4_IRQn, 0, 1);
  HAL_NVIC_EnableIRQ(TIM4_IRQn);
}
void start_timer(void){
	MX_TIM4_Init();
	HAL_TIM_Base_Start_IT(&htim4); // start timer interrupts
}
void stoptimer(void){
	MX_TIM4_Init();
	HAL_TIM_Base_Stop_IT(&htim4); // stop timer interrupts
}
