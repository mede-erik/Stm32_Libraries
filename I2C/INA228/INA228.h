/**
 * @author Medeossi Erik
 * @date 30/11/2023
 * @link https://github.com/mede-erik/Stm32_Libraries
 * @version 0v1
 */

#ifdef STM32F0
#include "stm32f0xx_hal.h" /* Import HAL library */
#elif defined(STM32F1)
#include "stm32f1xx_hal.h" /* Import HAL library */
#elif defined(STM32F2)
#include "stm32f2xx_hal.h" /* Import HAL library */
#elif defined(STM32F3)
#include "stm32f3xx_hal.h" /* Import HAL library */
#elif defined(STM32F4)
#include "stm32f4xx_hal.h" /* Import HAL library */
#elif defined(STM32F7)
#include "stm32f7xx_hal.h" /* Import HAL library */
#elif defined(STM32G0)
#include "stm32g0xx_hal.h" /* Import HAL library */
#elif defined(STM32G4)
#include "stm32g4xx_hal.h" /* Import HAL library */
#elif defined(STM32H7)
#include "stm32h7xx_hal.h" /* Import HAL library */
#elif defined(STM32L0)
#include "stm32l0xx_hal.h" /* Import HAL library */
#elif defined(STM32L1)
#include "stm32l1xx_hal.h" /* Import HAL library */
#elif defined(STM32L5)
#include "stm32l5xx_hal.h" /* Import HAL library */
#elif defined(STM32L4)
#include "stm32l4xx_hal.h" /* Import HAL library */
#elif defined(STM32H7)
#include "stm32h7xx_hal.h" /* Import HAL library */
#else
#endif

#include "main.h"

#define CONFIG_REG 0x00
#define SHUNT_VOLTAGE_REG 0x01
#define BUS_VOLTAGE_REG 0x02
#define POWER_REG 0x03
#define CURRENT_REG 0x04
#define CALIBRATION_REG 0x05

#define INA228_RESET 0x8000

typedef struct
{
    I2C_HandleTypeDef *hi2c;
    uint16_t addr;
    uint16_t average;
    uint16_t busConvTime;
    uint16_t shuntConvTime;
    uint16_t mode;
    float rShuntValue;
    float iMax;
    uint16_t calibrationValue;
} INA228_HandleTypeDef;