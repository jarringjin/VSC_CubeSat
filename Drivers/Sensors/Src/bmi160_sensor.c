#include "bmi160.h"
#include "bmi160_sensor.h"
#include "stm32f7xx_hal.h"  


static void init_sensor_interface(void)
{
    #if BMI160_INTERFACE_I2C == 1
    //TODO 
    #endif 

    #if BMI160_INTERFACE_SPI == 1

    // TODO
    //Set Pin configuration  without coines lib

    //CSB pin is made low for leceting SPI protocol
    /*
    coines_set_pin_config(COINES_SHUTTLE_PIN_7, COINES_PIN_DIRECTION_OUT, COINES_PIN_VALUE_LOW);
    coines_delay_msec(10);
    coines_config_spi_bus(COINES_SPI_BUS_0, COINES_SPI_SPEED_5_MHZ, COINES_SPI_MODE3);
    */
   #endif
	DWT_Delay(10); 
    // coines_set_shuttleboard_vdd_vddio_config(3300, 3300);

    #if BMI160_INTERFACE_SPI == 1
    DWT_Delay(10);
    
    //TODO

    /* CSB pin is made high for selecting SPI protocol
     * Note: CSB has to see rising after power up, to switch to SPI protocol */
    //coines_set_pin_config(COINES_SHUTTLE_PIN_7, COINES_PIN_DIRECTION_OUT, COINES_PIN_VALUE_HIGH);
    #endif
}

static void init_bmi160(void)
{
    //TODO
}

static void init_bmi160_sensor_driver_interface(void)
{
    //TODO
}

static void read_bmi160_sensor_data(void)
{
    //TODO
}