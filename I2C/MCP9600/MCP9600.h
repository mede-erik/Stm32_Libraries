/**
 * @author Medeossi Erik
 * @date 23/06/2024
 * @version 0.1.0
 * @brief MCP9600 Temperature Sensor Driver
 * @details This driver provides functions to initialize and read temperature data from the MCP9600 sensor.
 * @link https://github.com/mede-erik/Stm32_Libraries
 */

#ifndef MCP9600_H
#define MCP9600_H

#include "main.h"

typedef struct
{
    I2C_HandleTypeDef *hi2c;
    uint16_t address;
} MCP9600_HandleTypeDef;

HAL_StatusTypeDef MCP9600_Init(MCP9600_HandleTypeDef *mcp9600, I2C_HandleTypeDef *hi2c, uint16_t address);
HAL_StatusTypeDef MCP9600_ReadTemperature(MCP9600_HandleTypeDef *mcp9600, float *temperature);

#endif /* MCP9600_H */