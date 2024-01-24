/**
 * @author Medeossi Erik
 * @date 17/12/2023
 * @link https://github.com/mede-erik/Stm32_Libraries
 */

#include "ST7735_LCD.h"
#include "Fonts.h"
#include "stdlib.h"
#include "string.h"

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
void ST7735_SendCommand(ST7735_HandleTypeDef *hst7735, uint8_t cmd)
{
    HAL_GPIO_WritePin(hst7735->ST7735_DC_PORT, hst7735->ST7735_DC_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(hst7735->ST7735_CS_PORT, hst7735->ST7735_CS_PIN, GPIO_PIN_RESET);

    HAL_SPI_Transmit(hst7735->hspi, &cmd, sizeof(&cmd), HAL_MAX_DELAY);

    HAL_GPIO_WritePin(hst7735->ST7735_CS_PORT, hst7735->ST7735_CS_PIN, GPIO_PIN_SET);
}

/**
 * @brief Write data to the ST7735 display.
 * @param data Data to be written.
 */
void ST7735_SendData(ST7735_HandleTypeDef *hst7735, uint8_t data)
{
    HAL_GPIO_WritePin(hst7735->ST7735_DC_PORT, hst7735->ST7735_DC_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(hst7735->ST7735_CS_PORT, hst7735->ST7735_CS_PIN, GPIO_PIN_RESET);

    HAL_SPI_Transmit(hst7735->hspi, &data, sizeof(&data), HAL_MAX_DELAY);

    HAL_GPIO_WritePin(hst7735->ST7735_CS_PORT, hst7735->ST7735_CS_PIN, GPIO_PIN_SET);
}

HAL_StatusTypeDef ST7735_Init(ST7735_HandleTypeDef *hst7735, SPI_HandleTypeDef *hspi, GPIO_TypeDef *ST7735_DC_PORT, uint16_t ST7735_DC_PIN, GPIO_TypeDef *ST7735_CS_PORT, uint16_t ST7735_CS_PIN, GPIO_TypeDef *ST7735_RESET_PORT, uint16_t ST7735_RESET_PIN, uint16_t LCD_width, uint16_t LCD_height)
{
    uint8_t data_FRMCTR1[] = {0x01, 0x2C, 0x2D};
    uint8_t data_FRMCTR2[] = {0x01, 0x2C, 0X2D};
    uint8_t data_FRMCTR3[] = {0x01, 0x2C, 0x2D, 0x01, 0x2C, 0x2D};
    uint8_t data_PWCTR1[] = {0xA2, 0x02, 0x84};
    uint8_t data_PWCTR3[] = {0x0A, 0x00};
    uint8_t data_PWCTR4[] = {0x8A, 0x2A};
    uint8_t data_PWCTR5[] = {0x8A, 0xEE};
    uint8_t data_RASET[] = {0x00, 0x00, 0x00, 0x7F};
    uint8_t data_CASET[] = {0x00, 0x00, 0x00, 0x7F};
    uint8_t data_GMCTRP1[] = {0x02, 0x1c, 0x07, 0x12, 0x37, 0x32, 0x29, 0x2d, 0x29, 0x25, 0x2B, 0x39, 0x00, 0x01, 0x03, 0x10};
    uint8_t data_GMCTRN1[] = {0x03, 0x1d, 0x07, 0x06, 0x2E, 0x2C, 0x29, 0x2D, 0x2E, 0x2E, 0x37, 0x3F, 0x00, 0x00, 0x02, 0x10};

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

    HAL_GPIO_WritePin(ST7735_RESET_PORT, ST7735_RESET_PIN, GPIO_PIN_RESET);
    HAL_Delay(5);
    HAL_GPIO_WritePin(ST7735_RESET_PORT, ST7735_RESET_PIN, GPIO_PIN_SET);
    HAL_Delay(10);

    status = HAL_SPI_Init(hspi);

    // Send initialization commands to the display
    ST7735_SendCommand(hst7735, ST7735_SWRESET); // Software reset
    HAL_Delay(150);

    ST7735_SendCommand(hst7735, ST7735_SLPOUT); // Sleep out
    HAL_Delay(500);

    ST7735_SendCommand(hst7735, ST7735_FRMCTR1); // Frame rate control - normal mode
    ST7735_SendData(hst7735, data_FRMCTR1);

    ST7735_SendCommand(hst7735, ST7735_FRMCTR2); // Frame rate control - idle mode
    ST7735_SendData(hst7735, data_FRMCTR2);

    ST7735_SendCommand(hst7735, ST7735_FRMCTR3); // Frame rate control - partial mode
    ST7735_SendData(hst7735, data_FRMCTR3);

    ST7735_SendCommand(hst7735, ST7735_INVCTR); // Display inversion control
    ST7735_SendData(hst7735, 0x07);

    ST7735_SendCommand(hst7735, ST7735_PWCTR1); // Power control
    ST7735_SendData(hst7735, data_PWCTR1);

    ST7735_SendCommand(hst7735, ST7735_PWCTR2); // Power control
    ST7735_SendData(hst7735, 0xC5);

    ST7735_SendCommand(hst7735, ST7735_PWCTR3); // Power control
    ST7735_SendData(hst7735, data_PWCTR3);

    ST7735_SendCommand(hst7735, ST7735_PWCTR4); // Power control
    ST7735_SendData(hst7735, data_PWCTR4);

    ST7735_SendCommand(hst7735, ST7735_PWCTR5); // Power control

    ST7735_SendData(hst7735, data_PWCTR5);

    ST7735_SendCommand(hst7735, ST7735_VMCTR1); // VCOM control
    ST7735_SendData(hst7735, 0x0E);

    ST7735_SendCommand(hst7735, ST7735_INVOFF);

    ST7735_SendCommand(hst7735, ST7735_COLMOD); // Color mode
    ST7735_SendData(hst7735, 0x05);             // 16-bit color

    ST7735_SendCommand(hst7735, ST7735_MADCTL); // Memory data access control
    ST7735_SendData(hst7735, 0xC0);             // Row address order

    ST7735_SendCommand(hst7735, ST7735_CASET); // Column address set
    ST7735_SendData(hst7735, data_CASET);

    ST7735_SendCommand(hst7735, ST7735_RASET); // Row address set
    ST7735_SendData(hst7735, data_RASET);

    ST7735_SendCommand(hst7735, ST7735_GMCTRP1); // Gamma correction
    ST7735_SendData(hst7735, data_GMCTRP1);

    ST7735_SendCommand(hst7735, ST7735_GMCTRN1); // Gamma correction
    ST7735_SendData(hst7735, data_GMCTRN1);

    ST7735_SendCommand(hst7735, ST7735_NORON); // Normal display mode
    HAL_Delay(10);

    ST7735_SendCommand(hst7735, ST7735_DISPON); // Display on
    HAL_Delay(100);

    return status;
}

/**
 * @brief Set the address window for drawing on the ST7735 display.
 * @param x0 X-coordinate of the top-left corner.
 * @param y0 Y-coordinate of the top-left corner.
 * @param x1 X-coordinate of the bottom-right corner.
 * @param y1 Y-coordinate of the bottom-right corner.
 */
HAL_StatusTypeDef ST7735_SetAddrWindow(ST7735_HandleTypeDef *hst7735, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
    if (x0 >= hst7735->LCD_width || x1 >= hst7735->LCD_width || y0 >= hst7735->LCD_height || y1 >= hst7735->LCD_height)
    {
        return 0x01;
    }
    // Set Window addr
    ST7735_SendCommand(hst7735, ST7735_CASET); // Set Column Address
    uint8_t data[] = {0x00, x0 + 2, 0x00, x1 + 2};
    ST7735_SendData(hst7735, data);

    ST7735_SendCommand(hst7735, ST7735_RASET); // Set Row Address
    data[1] = y0 + 1;
    data[3] = y1 + 1;
    ST7735_SendData(hst7735, data);
    ST7735_SendCommand(hst7735, ST7735_RAMWR); // Write to RAM

    return HAL_OK;
}

uint16_t rgb_to_color(uint8_t red, uint8_t green, uint8_t blue)
{
    return ((uint16_t)red << 11) | ((uint16_t)green << 5) | blue;
}

/**
 * @brief Fill a rectangular area on the ST7735 display with a specified color.
 * @param x X-coordinate of the top-left corner.
 * @param y Y-coordinate of the top-left corner.
 * @param width Width of the rectangle.
 * @param height Height of the rectangle.
 * @param red Red component of the color (0-255).
 * @param green Green component of the color (0-255).
 * @param blue Blue component of the color (0-255).
 */
HAL_StatusTypeDef ST7735_FillRect(ST7735_HandleTypeDef *hst7735, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t color)
{

    if (x >= hst7735->LCD_width || y >= hst7735->LCD_height || (x + width) > hst7735->LCD_width || (y + height) > hst7735->LCD_height)
    {
        return 0x01;
    }
    // Set the address window
    ST7735_SetAddrWindow(hst7735, x, y, x + width - 1, y + height - 1);

    uint8_t data[] = {color >> 8, color & 0xFF};
    // Send color to entire rectangle
    HAL_GPIO_WritePin(hst7735->ST7735_DC_PORT, hst7735->ST7735_DC_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(hst7735->ST7735_CS_PORT, hst7735->ST7735_CS_PIN, GPIO_PIN_RESET);

    for (uint32_t i = 0; i < (width * height); ++i)
    {
        HAL_SPI_Transmit(hst7735->hspi, data, sizeof(data), HAL_MAX_DELAY);
    }

    HAL_GPIO_WritePin(hst7735->ST7735_CS_PORT, hst7735->ST7735_CS_PIN, GPIO_PIN_SET);

    return HAL_OK;
}

HAL_StatusTypeDef ST7735_DrawPixel(ST7735_HandleTypeDef *hst7735, uint8_t x, uint8_t y, uint16_t color)
{
    if (x >= hst7735->LCD_width || y >= hst7735->LCD_height)
    {
        return 0x01;
    }

    // Sets the address window for the specified pixel
    ST7735_SetAddrWindow(hst7735, x, y, x, y);

    // Send the RAM Write command
    ST7735_SendCommand(hst7735, ST7735_RAMWR);

    // Send pixel data (color)
    uint8_t data[] = {color >> 8, color & 0xFF};
    ST7735_SendData(hst7735, data);

    return HAL_OK;
}
/**
 * @brief Draw a circle on the ST7735 display.
 * @param x: x coordinate of the center of the circle.
 * @param y: Y coordinate of the center of the circle.
 * @param radius: Radius of the circle.
 * @param color: Color of the circle.
 */
void ST7735_DrawCircle(ST7735_HandleTypeDef *hst7735, uint8_t x, uint8_t y, uint8_t radius, uint16_t color)
{
    int8_t f = 1 - radius;
    int8_t ddF_x = 1;
    int8_t ddF_y = -2 * radius;
    int8_t x1 = 0;
    int8_t y1 = radius;

    ST7735_DrawPixel(hst7735, x, y + radius, color);
    ST7735_DrawPixel(hst7735, x, y - radius, color);
    ST7735_DrawPixel(hst7735, x + radius, y, color);
    ST7735_DrawPixel(hst7735, x - radius, y, color);

    while (x1 < y1)
    {
        if (f >= 0)
        {
            y1--;
            ddF_y += 2;
            f += ddF_y;
        }
        x1++;
        ddF_x += 2;
        f += ddF_x + 1;

        ST7735_DrawPixel(hst7735, x + x1, y - y1, color);
        ST7735_DrawPixel(hst7735, x - x1, y - y1, color);
        ST7735_DrawPixel(hst7735, x + x1, y + y1, color);
        ST7735_DrawPixel(hst7735, x - x1, y + y1, color);

        ST7735_DrawPixel(hst7735, x + y1, y - x1, color);
        ST7735_DrawPixel(hst7735, x - y1, y - x1, color);
        ST7735_DrawPixel(hst7735, x + y1, y + x1, color);
        ST7735_DrawPixel(hst7735, x - y1, y + x1, color);
    }
}
/**
 * @brief Draw a rectangle on the ST7735 display.
 * @param x: x coordinate of the top left corner of the rectangle.
 * @param y: Y coordinate of the top left corner of the rectangle.
 * @param width: Width of the rectangle.
 * @param height: Height of the rectangle.
 * @param color: Color of the rectangle.
 */
void ST7735_DrawRectangle(ST7735_HandleTypeDef *hst7735, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t color)
{
    for (uint8_t i = 0; i < width; i++)
    {
        for (uint8_t j = 0; j < height; j++)
        {
            ST7735_DrawPixel(hst7735, x + i, y + j, color);
        }
    }
}
/**
 * @brief Draw a triangle on the ST7735 display.
 * @param x0, y0: Coordinates of the first vertex of the triangle.
 * @param x1, y1: Coordinates of the second vertex of the triangle.
 * @param x2, y2: Coordinates of the third vertex of the triangle.
 * @param color: Color of the triangle.
 */
void ST7735_DrawTriangle(ST7735_HandleTypeDef *hst7735, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t color)
{
    ST7735_DrawLine(hst7735, x0, y0, x1, y1, color);
    ST7735_DrawLine(hst7735, x1, y1, x2, y2, color);
    ST7735_DrawLine(hst7735, x2, y2, x0, y0, color);
}
/**
 * @brief Draw a graph on the ST7735 display.
 * @param data: Array of data to display in the chart.
 * @param numPoints: Number of points in the graph.
 * @param color: Color of the graph.
 */
void ST7735_DrawGraph(ST7735_HandleTypeDef *hst7735, uint8_t *data, uint8_t numPoints, uint16_t color)
{
    // Calculate the width and height of the graph
    uint8_t graphWidth = hst7735->LCD_width - 10;
    uint8_t graphHeight = hst7735->LCD_height - 20;

    // Calculate the width of each horizontal interval
    uint8_t intervalWidth = graphWidth / (numPoints - 1);

    // Find the maximum value in the data to normalize the graph
    uint8_t maxValue = 0;
    for (uint8_t i = 0; i < numPoints; i++)
    {
        if (data[i] > maxValue)
        {
            maxValue = data[i];
        }
    }

    // Draw the lines of the graph by connecting the dots
    for (uint8_t i = 0; i < numPoints - 1; i++)
    {
        uint8_t x0 = i * intervalWidth + 5;
        uint8_t y0 = graphHeight - (data[i] * graphHeight / maxValue) + 10;
        uint8_t x1 = (i + 1) * intervalWidth + 5;
        uint8_t y1 = graphHeight - (data[i + 1] * graphHeight / maxValue) + 10;

        ST7735_DrawLine(hst7735, x0, y0, x1, y1, color);
    }
}
/**
 * @brief Draw a line on the ST7735 display using Bresenham's algorithm.
 * @param x0, y0: Coordinate of the starting point of the line.
 * @param x1, y1: Coordinate of the end point of the line.
 * @param color: Color of the line.
 */
void ST7735_DrawLine(ST7735_HandleTypeDef *hst7735, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t color)
{
    int16_t dx = abs(x1 - x0);
    int16_t sx = x0 < x1 ? 1 : -1;
    int16_t dy = -abs(y1 - y0);
    int16_t sy = y0 < y1 ? 1 : -1;
    int16_t err = dx + dy; /* error value e_xy */

    while (1)
    {
        // Draw the current point
        ST7735_DrawPixel(hst7735, x0, y0, color);

        // Check if you have reached your destination
        if (x0 == x1 && y0 == y1)
        {
            break;
        }

        int16_t e2 = 2 * err;

        // Calculate the next coordinate based on the error
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }

        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void ST7735_WriteChar(ST7735_HandleTypeDef *hst7735, uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor)
{
    uint32_t i, b, j;

    ST7735_SetAddressWindow(&hst7735, x, y, x + font.width - 1, y + font.height - 1);

    for (i = 0; i < font.height; i++)
    {
        b = font.data[(ch - 32) * font.height + i];
        for (j = 0; j < font.width; j++)
        {
            if ((b << j) & 0x8000)
            {
                uint8_t data[] = {color >> 8, color & 0xFF};
                ST7735_SendData(&hst7735, data);
            }
            else
            {
                uint8_t data[] = {bgcolor >> 8, bgcolor & 0xFF};
                ST7735_SendData(&hst7735, data);
            }
        }
    }
}

void ST7735_WriteText(ST7735_HandleTypeDef *hst7735, uint16_t x, uint16_t y, const char *str, FontDef font, uint16_t color, uint16_t bgcolor)
{
    while (*str)
    {
        if (x + font.width >= hst7735->LCD_width)
        {
            x = 0;
            y += font.height;
            if (y + font.height >= hst7735->LCD_height)
            {
                break;
            }

            if (*str == ' ')
            {
                // skip spaces in the beginning of the new line
                str++;
                continue;
            }
        }

        ST7735_WriteChar(&hst7735, x, y, *str, font, color, bgcolor);
        x += font.width;
        str++;
    }
}