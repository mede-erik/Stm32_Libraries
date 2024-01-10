/**
 * @author Medeossi Erik
 * @date 10/01/2024
 * @link https://github.com/mede-erik/Stm32_Libraries
 */

HAL_StatusTypeDef MAX6675_Init(MAX6675_HandleTypeDef *hmax6675, SPI_HandleTypeDef *hspi, GPIO_TypeDef *CS_PORT, uint16_t CS_PIN)
{
    hmax6675->hspi = hspi;
    hmax6675->CS_GPIO_Port = CS_PORT;
    hmax6675->CS_GPIO_Pin = CS_PIN;
    return HAL_SPI_Init(&hspi);
}
/**
 * @brief Return the temperature of the thermocouple
 *
 * @param hmax6675
 * @return double
 */
double MAX6675_ReadTemperature(MAX6675_HandleTypeDef *hmax6675)
{
    int16_t data = 0;

    // Select MAX6675
    HAL_GPIO_WritePin(hmax6675->CS_GPIO_Port, hmax6675->CS_GPIO_Pin, GPIO_PIN_RESET);

    // Read data from MAX6675
    if (HAL_SPI_Receive(hmax6675->hspi, (uint8_t *)&data, sizeof(data), 1000) != HAL_OK)
    {
        // Error reading data
        return HAL_ERROR;
    }

    // Deselect MAX6675
    HAL_GPIO_WritePin(hmax6675->CS_GPIO_Port, hmax6675->CS_GPIO_Pin, GPIO_PIN_SET);

    // Check for error flags
    if (data & 0x4)
    {
        // Error reading temperature
        return HAL_ERROR;
    }

    // Calculate temperature
    double temperature = data * 0.25;

    return temperature;
}