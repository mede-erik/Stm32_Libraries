/**
 * @author Medeossi Erik
 * @date 10/01/2024
 * @link https://github.com/mede-erik/Stm32_Libraries
 */

#ifndef INC_MAX6675_H_
#define INC_MAX6675_H_

#include "main.h"

typedef struct
{
    SPI_HandleTypeDef *hspi;
    GPIO_TypeDef *CS_PORT;
    uint16_t CS_PIN;
} MAX6675_HandleTypeDef;

HAL_StatusTypeDef MAX6675_Init(MAX6675_HandleTypeDef *hmax6675, GPIO_TypeDef *ST7735_CS_PORT, uint16_t ST7735_CS_PIN);
double MAX6675_ReadTemperature(MAX6675_HandleTypeDef *hmax6675);
#endif
