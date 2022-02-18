/**
 * This File define sensors definetions* 
*/

#include <stdint.h>

#define LOW 0
#define HIGH 1
/*DS18B20 Definations*/
#define DS18B20_PORT GPIOE
#define DS18B20_PIN GPIO_PIN_13

/*DS18B20 Functions Definations*/
uint8_t DS18B20_Start (void);
void DS18B20_Write (uint8_t data);
uint8_t DS18B20_Read (void);
float ds18b20_output(void);