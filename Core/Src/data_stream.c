#include "data_stream.h"

void stream_sendMessage(UART_HandleTypeDef* port, float data){
	char buffer[8] = {0};
	snprintf(buffer, sizeof(buffer), "%.5f", data);
	buffer[sizeof(buffer)-1] = 0x0A;
	HAL_UART_Transmit(port, (uint8_t*)buffer, sizeof(buffer), HAL_MAX_DELAY);
}