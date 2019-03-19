#include "uart.h"
#include "main.h"
#include <stdio.h>


UART_HandleTypeDef huart3;

int fputc(int c,FILE *fp)
{
	return 0;
}

void uartInit()
{
		__HAL_RCC_GPIOB_CLK_ENABLE();
		GPIO_InitTypeDef GPIO_Str;
		GPIO_Str.Mode = GPIO_MODE_AF_PP;
		GPIO_Str.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_Str.Pin = GPIO_PIN_10;
		HAL_GPIO_Init(GPIOB,&GPIO_Str);
	
	
		GPIO_Str.Mode = GPIO_MODE_INPUT;
		GPIO_Str.Speed = GPIO_SPEED_FREQ_HIGH;
		GPIO_Str.Pin = GPIO_PIN_11;
		HAL_GPIO_Init(GPIOB,&GPIO_Str);
	
		__HAL_RCC_USART3_CLK_ENABLE();
		huart3.Instance = USART3;
		huart3.Init.BaudRate=115200;
		huart3.Init.Mode = UART_MODE_TX_RX;
		huart3.Init.WordLength = UART_WORDLENGTH_8B;
		huart3.Init.StopBits = UART_STOPBITS_1;
		huart3.Init.Parity = UART_PARITY_NONE;
		huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
		huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	
		HAL_UART_Init(&huart3);
		
	//	HAL_NVIC_EnableIRQ(USART3_IRQn);
//		
//		__HAL_UART_ENABLE_IT(&huart3,UART_IT_RXNE);
//		if(HAL_UART_Init(&huart3) != HAL_OK)
//		{
//			_Error_Handler(__FILE__,__LINE__);
//		}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uint8_t *buffer = huart->pRxBuffPtr;
	uint16_t len = huart -> RxXferSize;
	return ;
}

