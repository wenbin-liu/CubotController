#include "control.h"
#include "main.h"
#include "delay.h"

int abs(int x)
{
	if(x<0)
		x=-x;
	return x;
}


/*motor init*/
 void X_MOTOR_PUL_PIN_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(X_MOTOR_PORT, X_MOTOR_PUL_PIN, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA9*/
  GPIO_InitStruct.Pin = X_MOTOR_PUL_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

 void Y_MOTOR_PUL_PIN_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Y_MOTOR_PORT, Y_MOTOR_PUL_PIN, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA10 */
  GPIO_InitStruct.Pin = Y_MOTOR_PUL_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

 void X_MOTOR_DIR_PIN_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(X_MOTOR_PORT, X_MOTOR_DIR_PIN, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA2 */
  GPIO_InitStruct.Pin = X_MOTOR_DIR_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

 void Y_MOTOR_DIR_PIN_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Y_MOTOR_PORT, Y_MOTOR_DIR_PIN, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA1 */
  GPIO_InitStruct.Pin = Y_MOTOR_DIR_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/*motor control*/
void TURN_X_MOTOR(int step)
{
	if(step >0 )
		HAL_GPIO_WritePin(X_MOTOR_PORT, X_MOTOR_DIR_PIN, GPIO_PIN_SET);
	else
	{
		HAL_GPIO_WritePin(X_MOTOR_PORT, X_MOTOR_DIR_PIN, GPIO_PIN_RESET);
		step=abs(step);
	}
	for(int count=0; count<step; count++)
	{
		HAL_GPIO_WritePin(X_MOTOR_PORT, X_MOTOR_PUL_PIN, GPIO_PIN_SET);
		//HAL_Delay(1);
		DelayUs(STEP_INTERVAL);
		HAL_GPIO_WritePin(X_MOTOR_PORT, X_MOTOR_PUL_PIN, GPIO_PIN_RESET);
		//HAL_Delay(1);
		DelayUs(STEP_INTERVAL);
	}
}
	
void TURN_Y_MOTOR(int step)
{
	if(step >0 )
		HAL_GPIO_WritePin(Y_MOTOR_PORT, Y_MOTOR_DIR_PIN, GPIO_PIN_SET);
	else
	{
		HAL_GPIO_WritePin(Y_MOTOR_PORT, Y_MOTOR_DIR_PIN, GPIO_PIN_RESET);
		step=abs(step);
	}
	for(int count=0; count<step; count++)
	{
		HAL_GPIO_WritePin(Y_MOTOR_PORT, Y_MOTOR_PUL_PIN, GPIO_PIN_SET);
	//	HAL_Delay(1);
		DelayUs(STEP_INTERVAL);
		HAL_GPIO_WritePin(Y_MOTOR_PORT, Y_MOTOR_PUL_PIN, GPIO_PIN_RESET);
		DelayUs(STEP_INTERVAL);
		//HAL_Delay(1);
	}
}
/*steer init*/
TIM_HandleTypeDef htim2;
/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
void MX_TIM2_Init(void)  
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 719;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1000;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 250;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}


/*steer control*/
void Y_STEER_OPEN(void)
{
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	__HAL_TIM_SET_COMPARE((&htim2),TIM_CHANNEL_1,CLIP_OPEN_VAL_Y);
}

void X_STEER_OPEN(void)
{
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
	__HAL_TIM_SET_COMPARE((&htim2),TIM_CHANNEL_2,CLIP_OPEN_VAL_X);
}
void X_STEER_LOOSE(void)
{
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
	__HAL_TIM_SET_COMPARE((&htim2),TIM_CHANNEL_2,CLIP_LOOSE_VAL_X);
}
void Y_STEER_LOOSE(void)
{
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	__HAL_TIM_SET_COMPARE((&htim2),TIM_CHANNEL_1,CLIP_LOOSE_VAL_Y);
}

void Y_STEER_TIGHT(void)
{
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	__HAL_TIM_SET_COMPARE((&htim2),TIM_CHANNEL_1,CLIP_TIGHT_VAL_Y);
}

void X_STEER_TIGHT(void)
{
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
	__HAL_TIM_SET_COMPARE((&htim2),TIM_CHANNEL_2,CLIP_TIGHT_VAL_X );
}

void Y_STEER_HOLD(void)
{
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	__HAL_TIM_SET_COMPARE((&htim2),TIM_CHANNEL_1,CLIP_HOLD_VAL_Y);
}

void X_STEER_HOLD(void)
{
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
	__HAL_TIM_SET_COMPARE((&htim2),TIM_CHANNEL_2,CLIP_HOLD_VAL_X );
}


/*turn control*/
void X_CLOCKWISE_90(void) //x轴-魔方整体顺时针转动90
{
	X_STEER_TIGHT();
	Y_STEER_OPEN();
	HAL_Delay(open_time);
	TURN_X_MOTOR(ANGLE90);
	HAL_Delay(turn_time);
	Y_STEER_TIGHT();
	HAL_Delay(tight_time);
	X_STEER_OPEN();
	HAL_Delay(open_time);
	TURN_X_MOTOR(-ANGLE90);
	HAL_Delay(turn_time);
	X_STEER_TIGHT();
}

void x_CLOCKWISE_90(void) //x轴-魔方面转动90
{
	X_STEER_TIGHT();
	Y_STEER_TIGHT();
	
	TURN_X_MOTOR(ANGLE90);
	HAL_Delay(turn_time);
	
	Y_STEER_TIGHT();
	X_STEER_OPEN();
	HAL_Delay(open_time);
	
	TURN_X_MOTOR(-ANGLE90);
	HAL_Delay(turn_time);
	
	X_STEER_TIGHT();
}

void X_CLOCKWISE_180(void) //x轴-魔方整体逆时针转动180
{
	X_STEER_TIGHT();
	Y_STEER_OPEN();
	HAL_Delay(open_time);
	TURN_X_MOTOR(ANGLE180);
	HAL_Delay(turn_time);
	Y_STEER_TIGHT();
}

void x_CLOCKWISE_180(void) //x轴-魔方面转动180
{
	X_STEER_TIGHT();
	Y_STEER_TIGHT();
	TURN_X_MOTOR(ANGLE180);
	Y_STEER_TIGHT();
}



void X_ANTICLOCKWISE_90(void) //x轴-魔方整体逆时针转动90
{
	X_STEER_TIGHT();
	Y_STEER_OPEN();
	HAL_Delay(open_time);
	TURN_X_MOTOR(-ANGLE90);
	HAL_Delay(turn_time);
	Y_STEER_TIGHT();
	HAL_Delay(tight_time);
	X_STEER_OPEN();
	HAL_Delay(open_time);
	TURN_X_MOTOR(ANGLE90);
	HAL_Delay(turn_time);
	X_STEER_TIGHT();
}

void x_ANTICLOCKWISE_90(void) //x轴-魔方面转动90
{
	X_STEER_TIGHT();
	Y_STEER_TIGHT();
	
	TURN_X_MOTOR(-ANGLE90);
	HAL_Delay(turn_time);
	
	Y_STEER_TIGHT();
	X_STEER_OPEN();
	HAL_Delay(open_time);
	
	TURN_X_MOTOR(ANGLE90);
	HAL_Delay(turn_time);
	
	X_STEER_TIGHT();
}

void X_ANTICLOCKWISE_180(void) //x轴-魔方整体逆时针转动180
{
	X_STEER_TIGHT();
	Y_STEER_OPEN();
	HAL_Delay(open_time);
	TURN_X_MOTOR(ANGLE180);
	HAL_Delay(turn_time);
	Y_STEER_TIGHT();
}

void x_ANTICLOCKWISE_180(void) //x轴-魔方面转动180
{
	X_STEER_TIGHT();
	Y_STEER_TIGHT();
	TURN_X_MOTOR(ANGLE180);
	Y_STEER_TIGHT();
}




void Y_CLOCKWISE_90(void) //x轴-魔方整体顺时针转动90
{
	Y_STEER_TIGHT();
	X_STEER_OPEN();
	HAL_Delay(open_time);
	TURN_Y_MOTOR(ANGLE90);
	HAL_Delay(turn_time);
	X_STEER_TIGHT();
	HAL_Delay(tight_time);
	Y_STEER_OPEN();
	HAL_Delay(open_time);
	TURN_Y_MOTOR(-ANGLE90);
	HAL_Delay(turn_time);
	Y_STEER_TIGHT();
}

void y_CLOCKWISE_90(void) //x轴-魔方面转动90
{
	Y_STEER_TIGHT();
	X_STEER_TIGHT();
	
	TURN_Y_MOTOR(ANGLE90);
	HAL_Delay(turn_time);
	
	X_STEER_TIGHT();
	Y_STEER_OPEN();
	HAL_Delay(open_time);
	
	TURN_Y_MOTOR(-ANGLE90);
	HAL_Delay(turn_time);
	
	Y_STEER_TIGHT();
}

void Y_CLOCKWISE_180(void) //x轴-魔方整体逆时针转动180
{
	Y_STEER_TIGHT();
	X_STEER_OPEN();
	HAL_Delay(open_time);
	TURN_Y_MOTOR(ANGLE180);
	HAL_Delay(turn_time);
	X_STEER_TIGHT();
}

void y_CLOCKWISE_180(void) //x轴-魔方面转动180
{
	Y_STEER_TIGHT();
	X_STEER_TIGHT();
	TURN_Y_MOTOR(ANGLE180);
	X_STEER_TIGHT();
}



void Y_ANTICLOCKWISE_90(void) //x轴-魔方整体逆时针转动90
{
	Y_STEER_TIGHT();
	X_STEER_OPEN();
	HAL_Delay(open_time);
	TURN_Y_MOTOR(-ANGLE90);
	HAL_Delay(turn_time);
	X_STEER_TIGHT();
	HAL_Delay(tight_time);
	Y_STEER_OPEN();
	HAL_Delay(open_time);
	TURN_Y_MOTOR(ANGLE90);
	HAL_Delay(turn_time);
	Y_STEER_TIGHT();
}

void y_ANTICLOCKWISE_90(void) //x轴-魔方面转动90
{
	X_STEER_TIGHT();
	Y_STEER_TIGHT();
	
	TURN_Y_MOTOR(-ANGLE90);
	HAL_Delay(turn_time);
	
	X_STEER_TIGHT();
	Y_STEER_OPEN();
	HAL_Delay(open_time);
	
	TURN_Y_MOTOR(ANGLE90);
	HAL_Delay(turn_time);
	
	Y_STEER_TIGHT();
}

void Y_ANTICLOCKWISE_180(void) //x轴-魔方整体逆时针转动180
{
	Y_STEER_TIGHT();
	X_STEER_OPEN();
	HAL_Delay(open_time);
	TURN_Y_MOTOR(ANGLE180);
	HAL_Delay(turn_time);
	X_STEER_TIGHT();
}

void y_ANTICLOCKWISE_180(void) //x轴-魔方面转动180
{
	X_STEER_TIGHT();
	Y_STEER_TIGHT();
	TURN_Y_MOTOR(ANGLE180);
	Y_STEER_TIGHT();
}


int X_TURN(char cmd)
{
	switch(cmd)
	{
		case 'X':
			X_CLOCKWISE_180();return 2;
		case '\'':
			X_ANTICLOCKWISE_90();return 2;
		default:
			X_CLOCKWISE_90();return 1;
	}
	
}

int x_TURN(char cmd)
{
	switch(cmd)
	{
		case 'x':
			x_CLOCKWISE_180();return 2;
		case '\'':
			x_ANTICLOCKWISE_90();return 2;
		default:
			x_CLOCKWISE_90();return 1;
	}
	
}

int Y_TURN(char cmd)
{
	switch(cmd)
	{
		case 'Y':
			Y_CLOCKWISE_180();return 2;
		case '\'':
			Y_ANTICLOCKWISE_90();return 2;
		default:
			Y_CLOCKWISE_90();return 1;
	}
	
}

int y_TURN(char cmd)
{
	switch(cmd)
	{
		case 'y':
			y_CLOCKWISE_180();return 2;
		case '\'':
			y_ANTICLOCKWISE_90();return 2;
		default:
			y_CLOCKWISE_90();return 1;
	}

}

void Solve(char * order)
{
	for(;*order!='\0';)
{
	if(*order=='X')
		order+=X_TURN(*(order+1));
	else if(*order=='x')
		order+=x_TURN(*(order+1));
	else if(*order=='Y')
		order+=Y_TURN(*(order+1));
	else if(*order=='y')
		order+=y_TURN(*(order+1));
//	X_STEER_LOOSE();
//	Y_STEER_LOOSE();
  HAL_Delay(1000);
} 
}
