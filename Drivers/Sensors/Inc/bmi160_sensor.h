#define BMI160_INTERFACE_I2C  1
#define BMI160_INTERFACE_SPI  0

#if (!((BMI160_INTERFACE_I2C == 1) && (BMI160_INTERFACE_SPI == 0)) && \
    (!((BMI160_INTERFACE_I2C == 0) && (BMI160_INTERFACE_SPI == 1))))
#error "Invalid value given for the macros BMI160_INTERFACE_I2C / BMI160_INTERFACE_SPI"
#endif

/*! bmi160 shuttle id */
#define BMI160_SHUTTLE_ID     0x38

/*! bmi160 Device address */
// #define BMI160_DEV_ADDR       BMI160_I2C_ADDR  // for this project we will bmi160 in SPI mode

struct bmi160_dev bmi160dev;
struct bmi160_sensor_data bmi160_accel;
struct bmi160_sensor_data bmi160_gyro;

//Functional definations
/*!
 * @brief   internal API is used to initialize the sensor interface
 */
static void init_sensor_interface(void);

/*!
 * @brief   This internal API is used to initialize the bmi160 sensor with default
 */
static void init_bmi160(void);

/*!
 * @brief   This internal API is used to initialize the sensor driver interface
 */
static void init_bmi160_sensor_driver_interface(void);

/*!
 * @brief   This internal API is used to read the sensor driver interface
 */

static void init_bmi160(void)
