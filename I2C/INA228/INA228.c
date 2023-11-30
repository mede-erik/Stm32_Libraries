/**
 * @author Medeossi Erik
 * @date 30/11/2023
 * @link https://github.com/mede-erik/Stm32_Libraries
 * @version 0v1
 */

#include "INA228.h"

HAL_StatusTypeDef INA228_Init(INA228_HandleTypeDef *hina228, I2C_HandleTypeDef *hi2c, uint16_t addr, uint16_t average, uint16_t busConvTime, uint16_t shuntConvTime, uint16_t mode, float rShuntValue, float iMax)
{
    hina228->hi2c = hi2c;
    hina228->addr = addr;
    hina228->average = average;
    hina228->busConvTime = busConvTime;
    hina228->shuntConvTime = shuntConvTime;
    hina228->mode = mode;
    hina228->rShuntValue = rShuntValue;
    hina228->iMax = iMax;

    // Calculation of calibration value
    hina228->calibrationValue = (uint16_t)(0.00512 / (hina228->rShuntValue * (1 << hina228->average)));

    if (INA228_Reset(hina228) != HAL_OK)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

HAL_StatusTypeDef INA228_Reset(INA228_HandleTypeDef *hina228)
{
    uint16_t reset = INA228_RESET;
    uint8_t data[2];

    data[0] = reset >> 8;
    data[1] = reset & 0xff;

    if (HAL_I2C_Mem_Write(hina228->hi2c, hina228->addr, CONFIG_REG, I2C_MEMADD_SIZE_16BIT, data, 2, 1000) != HAL_OK)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

HAL_StatusTypeDef INA228_Config(INA228_HandleTypeDef *hina228)
{
    uint16_t config = (hina228->average << 9) | (hina228->busConvTime << 6) | (hina228->shuntConvTime << 3) | hina228->mode;
    uint8_t data[2];

    data[0] = config >> 8;
    data[1] = config & 0xff;

    // Write config register
    if (HAL_I2C_Mem_Write(hina228->hi2c, INA228_ADDRESS, CONFIG_REG, I2C_MEMADD_SIZE_16BIT, data, 2, 1000) != HAL_OK)
    {
        return HAL_ERROR;
    }

    // Write calibration register
    data[0] = hina228->calibrationValue >> 8;
    data[1] = hina228->calibrationValue & 0xff;

    if (HAL_I2C_Mem_Write(hina228->hi2c, hina228->addr, CALIBRATION_REG, I2C_MEMADD_SIZE_16BIT, data, 2, 1000) != HAL_OK)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

HAL_StatusTypeDef INA228_ReadShuntVoltage(INA228_HandleTypeDef *hina228, float *voltage)
{
    uint16_t shuntVoltageRaw;
    uint8_t data[2];

    // Read shunt voltage register
    if (HAL_I2C_Mem_Read(hina228->hi2c, hina228->addr, SHUNT_VOLTAGE_REG, I2C_MEMADD_SIZE_16BIT, data, 2, 1000) != HAL_OK)
    {
        return HAL_ERROR;
    }

    shuntVoltageRaw = (data[0] << 8) | data[1];

    // Calculate shunt voltage in volts
    *voltage = (float)shuntVoltageRaw * hina228->shuntVoltageLSB;

    return HAL_OK;
}