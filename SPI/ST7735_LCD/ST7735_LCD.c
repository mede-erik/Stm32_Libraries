/**
 * @author Medeossi Erik
 * @date 17/12/2023
 * @link https://github.com/mede-erik/Stm32_Libraries
 */

#include "ST7735_LCD.h"

/**
 * @brief Reset the ST7735 display.
 */
void ST7735_Reset(ST7735_HandleTypeDef *hst7735)
{
    HAL_GPIO_WritePin(hst7735->ST7735_RESET_PORT, hst7735->ST7735_RESET_PIN, GPIO_PIN_RESET);
    HAL_Delay(5);
    HAL_GPIO_WritePin(hst7735->ST7735_RESET_PORT, hst7735->ST7735_RESET_PIN, GPIO_PIN_SET);
    HAL_Delay(10);
}

/**
 * @brief Write a command to the ST7735 display.
 * @param cmd Command to be written.
 */
void ST7735_WriteCommand(ST7735_HandleTypeDef *hst7735, uint8_t cmd)
{
    HAL_GPIO_WritePin(hst7735->ST7735_DC_PORT, hst7735->ST7735_DC_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(hst7735->ST7735_CS_PORT, hst7735->ST7735_CS_PIN, GPIO_PIN_RESET);

    HAL_SPI_Transmit(hst7735->hspi, &cmd, 1, HAL_MAX_DELAY);

    HAL_GPIO_WritePin(hst7735->ST7735_CS_PORT, hst7735->ST7735_CS_PIN, GPIO_PIN_SET);
}

/**
 * @brief Write data to the ST7735 display.
 * @param data Data to be written.
 */
void ST7735_WriteData(ST7735_HandleTypeDef *hst7735, uint8_t data)
{
    HAL_GPIO_WritePin(hst7735->ST7735_DC_PORT, hst7735->ST7735_DC_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(hst7735->ST7735_CS_PORT, hst7735->ST7735_CS_PIN, GPIO_PIN_RESET);

    HAL_SPI_Transmit(hst7735->hspi, &data, 1, HAL_MAX_DELAY);

    HAL_GPIO_WritePin(hst7735->ST7735_CS_PORT, hst7735->ST7735_CS_PIN, GPIO_PIN_SET);
}

HAL_StatusTypeDef ST7735_Init(ST7735_HandleTypeDef *hst7735, SPI_HandleTypeDef *hspi, GPIO_TypeDef *ST7735_DC_PORT, uint16_t ST7735_DC_PIN, GPIO_TypeDef *ST7735_CS_PORT, uint16_t ST7735_CS_PIN, GPIO_TypeDef *ST7735_RESET_PORT, uint16_t ST7735_RESET_PIN, unit16_t LCD_width, uint16_t LCD_height)
{
    HAL_StatusTypeDef status = 0x01;

    hst7735->hspi = hspi;
    hst7735->ST7735_CS_PIN = ST7735_CS_PIN;
    hst7735->ST7735_DC_PIN = ST7735_DC_PIN;
    hst7735->ST7735_RESET_PIN = ST7735_RESET_PIN;
    hst7735->ST7735_CS_PORT = ST7735_CS_PORT;
    hst7735->ST7735_DC_PORT = ST7735_DC_PORT;
    hst7735->ST7735_RESET_PORT = ST7735_RESET_PORT;
    hst7735->LCD_width = LCD_width;
    hst7735->LCD_height = LCD_height;

    // Configura il pin di reset
    HAL_GPIO_WritePin(ST7735_RESET_PORT, ST7735_RESET_PIN, GPIO_PIN_RESET);
    HAL_Delay(5);
    HAL_GPIO_WritePin(ST7735_RESET_PORT, ST7735_RESET_PIN, GPIO_PIN_SET);
    HAL_Delay(10);

    status = HAL_SPI_Init(&hspi);

    // Invia comandi di inizializzazione al display
    ST7735_SendCommand(ST7735_SWRESET); // Software reset
    HAL_Delay(150);

    ST7735_SendCommand(ST7735_SLPOUT); // Sleep out
    HAL_Delay(500);

    ST7735_SendCommand(ST7735_FRMCTR1); // Frame rate control - normal mode
    ST7735_SendData(0x01);
    ST7735_SendData(0x2C);
    ST7735_SendData(0x2D);

    ST7735_SendCommand(ST7735_FRMCTR2); // Frame rate control - idle mode
    ST7735_SendData(0x01);
    ST7735_SendData(0x2C);
    ST7735_SendData(0x2D);

    ST7735_SendCommand(ST7735_FRMCTR3); // Frame rate control - partial mode
    ST7735_SendData(0x01);
    ST7735_SendData(0x2C);
    ST7735_SendData(0x2D);
    ST7735_SendData(0x01);
    ST7735_SendData(0x2C);
    ST7735_SendData(0x2D);

    ST7735_SendCommand(ST7735_INVCTR); // Display inversion control
    ST7735_SendData(0x07);

    ST7735_SendCommand(ST7735_PWCTR1); // Power control
    ST7735_SendData(0xA2);
    ST7735_SendData(0x02);
    ST7735_SendData(0x84);

    ST7735_SendCommand(ST7735_PWCTR2); // Power control
    ST7735_SendData(0xC5);

    ST7735_SendCommand(ST7735_PWCTR3); // Power control
    ST7735_SendData(0x0A);
    ST7735_SendData(0x00);

    ST7735_SendCommand(ST7735_PWCTR4); // Power control
    ST7735_SendData(0x8A);
    ST7735_SendData(0x2A);

    ST7735_SendCommand(ST7735_PWCTR5); // Power control
    ST7735_SendData(0x8A);
    ST7735_SendData(0xEE);

    ST7735_SendCommand(ST7735_VMCTR1); // VCOM control
    ST7735_SendData(0x0E);

    ST7735_SendCommand(ST7735_COLMOD); // Color mode
    ST7735_SendData(0x05);             // 16-bit color

    ST7735_SendCommand(ST7735_MADCTL); // Memory data access control
    ST7735_SendData(0xC8);             // Row address order

    ST7735_SendCommand(ST7735_CASET); // Column address set
    ST7735_SendData(0x00);
    ST7735_SendData(0x00);
    ST7735_SendData(0x00);
    ST7735_SendData(0x7F);

    ST7735_SendCommand(ST7735_RASET); // Row address set
    ST7735_SendData(0x00);
    ST7735_SendData(0x00);
    ST7735_SendData(0x00);
    ST7735_SendData(0x9F);

    ST7735_SendCommand(ST7735_GMCTRP1); // Gamma correction
    ST7735_SendData(0x02);
    ST7735_SendData(0x1C);
    ST7735_SendData(0x07);
    ST7735_SendData(0x12);
    ST7735_SendData(0x37);
    ST7735_SendData(0x32);
    ST7735_SendData(0x29);
    ST7735_SendData(0x2D);
    ST7735_SendData(0x29);
    ST7735_SendData(0x25);
    ST7735_SendData(0x2B);
    ST7735_SendData(0x39);
    ST7735_SendData(0x00);
    ST7735_SendData(0x01);
    ST7735_SendData(0x03);
    ST7735_SendData(0x10);

    ST7735_SendCommand(ST7735_GMCTRN1); // Gamma correction
    ST7735_SendData(0x03);
    ST7735_SendData(0x1D);
    ST7735_SendData(0x07);
    ST7735_SendData(0x06);
    ST7735_SendData(0x2E);
    ST7735_SendData(0x2C);
    ST7735_SendData(0x29);
    ST7735_SendData(0x2D);
    ST7735_SendData(0x2E);
    ST7735_SendData(0x2E);
    ST7735_SendData(0x37);
    ST7735_SendData(0x3F);
    ST7735_SendData(0x00);
    ST7735_SendData(0x00);
    ST7735_SendData(0x02);
    ST7735_SendData(0x10);

    ST7735_SendCommand(ST7735_NORON); // Normal display mode
    HAL_Delay(10);

    ST7735_SendCommand(ST7735_DISPON); // Display on
    HAL_Delay(100);

    return status;
}