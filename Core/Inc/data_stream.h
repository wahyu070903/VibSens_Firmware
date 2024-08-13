#ifndef DATA_STREAM
	#define DATA_STREAM
	
	#include "stdio.h"
	#include "stm32f1xx_hal.h"
	#include "stm32f1xx_hal_uart.h"
	
	void stream_sendMessage(UART_HandleTypeDef* port, float data);
	char* makeJson(float data);
#endif