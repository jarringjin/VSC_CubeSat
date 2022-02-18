/*
*
*
*/
#include "stm32f7xx_hal.h"  
#include "ds18b20.h"
#include "dwt_delay.h"

/************DS18b20 Definations*******************/
uint8_t Presence = 0;
uint8_t Temp_byte1, Temp_byte2;
float Temperature = 0;
float Temperature_2 = 0;
uint16_t TEMP;
/************End*******************/

void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}
void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

uint8_t DS18B20_Start (void)
{
	uint8_t Response = 0;
	Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);   // set the pin as output
	HAL_GPIO_WritePin (DS18B20_PORT, DS18B20_PIN, LOW);  // pull the pin low
	DWT_Delay(480);   // delay according to datasheet
	Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);    // set the pin as input
	DWT_Delay(80);    // delay according to datasheet

	if (!(HAL_GPIO_ReadPin (DS18B20_PORT, DS18B20_PIN))) Response = 1;    // if the pin is low i.e the presence pulse is detected
	else Response = -1;

	DWT_Delay(400); // 480 us delay totally.

	return Response;
}

void DS18B20_Write (uint8_t data)
{
	Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);  // set as output

	for (int i=0; i<8; i++)
	{

		if ((data & (1<<i))!=0)  // if the bit is high
		{
			// write 1

			Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);  // set as output
			HAL_GPIO_WritePin (DS18B20_PORT, DS18B20_PIN, LOW);  // pull the pin LOW
			DWT_Delay(1);  // wait for 1 us

			Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);  // set as input
			DWT_Delay(60);  // wait for 60 us
		}

		else  // if the bit is low
		{
			// write 0

			Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);
			HAL_GPIO_WritePin (DS18B20_PORT, DS18B20_PIN, LOW);  // pull the pin LOW
			DWT_Delay(60);  // wait for 60 us

			Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);
		}
	}
}

uint8_t DS18B20_Read (void)
{
	uint8_t value=0;
	Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);

	for (int i=0;i<8;i++)
	{
		Set_Pin_Output(DS18B20_PORT, DS18B20_PIN);   // set as output

		HAL_GPIO_WritePin (DS18B20_PORT, DS18B20_PIN, LOW);  // pull the data pin LOW
		DWT_Delay(2);  // wait for > 1us

		Set_Pin_Input(DS18B20_PORT, DS18B20_PIN);  // set as input
		if (HAL_GPIO_ReadPin (DS18B20_PORT, DS18B20_PIN))  // if the pin is HIGH
		{
			value |= 1<<i;  // read = 1
		}
		DWT_Delay(60);  // wait for 60 us
	}
	return value;
}
/********** End of DS18b20 Functions **************/

/********** DS18b20 App Code **************/

float ds18b20_output(void){
Presence = DS18B20_Start ();
HAL_Delay (1);
DS18B20_Write (0xCC);  // skip ROM
DS18B20_Write (0x44);  // convert t
HAL_Delay(800);

Presence = DS18B20_Start ();
DS18B20_Write (0xCC);  // skip ROM
DS18B20_Write (0xBE);  // Read Scratch-pad

Temp_byte1 = DS18B20_Read();
Temp_byte2 = DS18B20_Read();
TEMP = (Temp_byte2<<8)|Temp_byte1;
Temperature = (float)TEMP/2;
return(Temperature);
}
