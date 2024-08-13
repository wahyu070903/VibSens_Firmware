#include "adxl345.h"

SPI_HandleTypeDef* handler;
ADXLInitTypedef adxlconfig;


void adxl_write(uint8_t address, uint8_t value){
	HAL_StatusTypeDef status;
	uint8_t dataframe[2];
	uint8_t timeout = 5;
	dataframe[0] = address;
	dataframe[1] = value;
	HAL_GPIO_WritePin(GPIOB, ADXL_SW, GPIO_PIN_RESET);
	status = HAL_SPI_Transmit (handler, dataframe, 2, timeout);
	HAL_GPIO_WritePin (GPIOB, ADXL_SW, GPIO_PIN_SET);
}
	
int16_t adxl_read(uint8_t address){
	HAL_StatusTypeDef TXstatus;
	HAL_StatusTypeDef RXstatus;
	address |= 0x80;  // read operation
	uint8_t result;
	uint8_t timeout = 5;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_GPIO_WritePin (GPIOB, ADXL_SW, GPIO_PIN_RESET);  // pull the pin low
	TXstatus = HAL_SPI_Transmit (handler, &address, 1, timeout);  // send address
	RXstatus = HAL_SPI_Receive (handler, &result, 6, timeout);  // receive 6 bytes data
	HAL_GPIO_WritePin (GPIOB, ADXL_SW, GPIO_PIN_SET);  // pull the pin high
	if(RXstatus == HAL_OK && TXstatus == HAL_OK){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	}
	return result;
} 

void adxl_init(SPI_HandleTypeDef* exthandler){
	handler = exthandler;
	adxlconfig.spimode = 0x00;
	adxl_write(0x31, 0x01);  // data_format range= +- 4g
	adxl_write(0x38, 0x80);
	adxl_write(0x2d, 0x00);  // reset all bits
	adxl_write(0x2d, 0x08);
}

char* adxl_getConfig(){
	int16_t data[22];
	data[0] = adxl_read(ADXL_DEVID);
	data[1] = adxl_read(ADXL_THRESH_TAP);
	data[2] = adxl_read(ADXL_OFFZ);
	data[3] = adxl_read(ADXL_DUR);
	data[4] = adxl_read(ADXL_LATENT);
	data[5] = adxl_read(ADXL_WINDOW);
	data[6] = adxl_read(ADXL_THRESH_ACT);
	data[7] = adxl_read(ADXL_THRESH_INACT);
	data[8] = adxl_read(ADXL_TIME_INAT);
	data[9] = adxl_read(ADXL_ACT_INACT_CTL);
	data[10] = adxl_read(ADXL_THRESH_FF);
	data[11] = adxl_read(ADXL_TIME_FF);
	data[12] = adxl_read(ADXL_TAP_AXES);
	data[13] = adxl_read(ADXL_TAP_STATUS);
	data[14] = adxl_read(ADXL_BW_RATE);
	data[15] = adxl_read(ADXL_POWER_CTL);
	data[16] = adxl_read(ADXL_INT_ENABLE);
	data[17] = adxl_read(ADXL_INT_MAP); 
	data[18] = adxl_read(ADXL_INT_SOURCE);
	data[19] = adxl_read(ADXL_DATA_FORMAT);
	data[20] = adxl_read(ADXL_FIFO_CTL);
	data[21] = adxl_read(ADXL_FIFO_STATUS);
	
	const char* name[22] = {
	"devId",
	"TreshTap",
	"OFFSETZ",
	"DUR",
	"Latent",
	"Window",
	"TrehAct",
	"TreshInact",
	"TimeInat",
	"InatCTL",
	"TreshFF",
	"TimeFF",
	"TapAxes",
	"TapStatus",
	"BwRate",
	"PowerCTL",
	"IntEnable",
	"IntMap",
	"IntSource",
	"DataFormat",
	"FifoCTL",
	"FifoStat" };
	
	cJSON *json = cJSON_CreateObject();
	for(int i = 0 ; i < sizeof(data) / sizeof(data[0]) ; i++){
		char hexVal[2];
		snprintf(hexVal, sizeof(hexVal), "%X", data[i]);
		cJSON_AddStringToObject(json, name[i], hexVal);
	}
	char* jsonString = cJSON_Print(json);
	cJSON_Delete(json);
	return jsonString;
}

float adxl_getAccZ(){
	int16_t data0 = adxl_read(ADXL_DATAZ0);
	int16_t data1 = adxl_read(ADXL_DATAZ1);
	int16_t z_accel = ((int16_t)data1 << 8) | data0;
 	float gforce = z_accel * 0.0039;
	return gforce;
}
