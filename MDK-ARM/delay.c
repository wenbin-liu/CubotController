#include "main.h"

TIM_HandleTypeDef htim3;
void Delay_Timer_Init(void)
{
	__HAL_RCC_TIM3_CLK_ENABLE();
	htim3.Init.Prescaler = 71;
	htim3.Instance = TIM3;
	HAL_TIM_Base_Init(&htim3);
//    HAL_TimeBase TIM_TimeBaseInitStruct;
//    
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
//    
//    TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
//    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
//    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Down;
//    TIM_TimeBaseInitStruct.TIM_Period = 100-1;
//    TIM_TimeBaseInitStruct.TIM_Prescaler = (84-1);
//    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
//    
//    while((TIM3->SR & TIM_FLAG_Update)!=SET);
//    TIM3->SR = (uint16_t)~TIM_FLAG_Update;
}

void DelayUs(uint16_t ticks)
{
	__HAL_TIM_SET_AUTORELOAD(&htim3,ticks);
	HAL_TIM_Base_Start(&htim3);
	__HAL_TIM_CLEAR_FLAG(&htim3,TIM_FLAG_UPDATE);
	while(__HAL_TIM_GET_FLAG(&htim3,TIM_FLAG_UPDATE) ==0 )
			;
	HAL_TIM_Base_Stop(&htim3);
}