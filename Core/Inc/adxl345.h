#ifndef ADXL345
	#define ADXL345
	#include <stdint.h>
	#include "stdio.h"
	#include "stm32f1xx_hal.h"
	#include "stm32f1xx_hal_spi.h"
	#include "cJSON.h"
	
	#define ADXL_SW GPIO_PIN_0
	
	//Registers
	#define ADXL_DEVID					0x0
	#define ADXL_THRESH_TAP			0x1D
	#define ADXL_OFFX						0x1E
	#define ADXL_OFFY						0x1F
	#define ADXL_OFFZ						0x20
	#define ADXL_DUR						0x21
	#define ADXL_LATENT					0x22
	#define ADXL_WINDOW					0x23
	#define ADXL_THRESH_ACT			0x24
	#define ADXL_THRESH_INACT		0x25
	#define ADXL_TIME_INAT			0x26
	#define ADXL_ACT_INACT_CTL	0x27
	#define ADXL_THRESH_FF 			0x28
	#define ADXL_TIME_FF				0x29
	#define ADXL_TAP_AXES				0x2A
	#define ADXL_TAP_STATUS			0x2B
	#define ADXL_BW_RATE				0x2C 
	#define ADXL_POWER_CTL 			0x2D
	#define ADXL_INT_ENABLE			0x2E
	#define ADXL_INT_MAP				0x2F
	#define ADXL_INT_SOURCE			0x30
	#define ADXL_DATA_FORMAT 		0x31
	#define ADXL_DATAZ0					0X36
	#define ADXL_DATAZ1					0x37
	#define ADXL_FIFO_CTL 			0x38
	#define ADXL_FIFO_STATUS		0x39
	
	typedef struct{
		uint8_t spimode;
	} ADXLInitTypedef;
		
	void adxl_write(uint8_t address, uint8_t value);
	int16_t adxl_read(uint8_t address);
	void adxl_init(SPI_HandleTypeDef *handler);
	char* adxl_getConfig();
	float adxl_getAccZ();
#endif