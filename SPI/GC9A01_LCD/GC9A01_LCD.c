/**
 * @author Medeossi Erik
 * @date 17/01/2024
 * @link https://github.com/mede-erik/Stm32_Libraries
 */

#include "GC9A01_LCD.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**
 * @brief Send data to the GC9A01 display.
 *
 * @param display Pointer to the GC9A01_Display structure.
 * @param data Pointer to the data to be sent.
 * @param size Number of bytes to be sent.
 */
void GC9A01_SendData(GC9A01_HandleTypeDef *display, uint8_t *data,size_t len)
{
    // Set DC pin to high for data mode
    HAL_GPIO_WritePin(display->GC9A01_DC_PORT, display->GC9A01_DC_PIN, GPIO_PIN_SET);

    // Set CS pin to low to enable the device
    HAL_GPIO_WritePin(display->GC9A01_CS_PORT, display->GC9A01_CS_PIN, GPIO_PIN_RESET);

    // Send data via SPI
    HAL_SPI_Transmit(display->hspi, data, len, 100);

    // Set CS pin to high to disable the device
    HAL_GPIO_WritePin(display->GC9A01_CS_PORT, display->GC9A01_CS_PIN, GPIO_PIN_SET);
}
/**
 * @brief Send a command to the GC9A01 display.
 *
 * @param display Pointer to the GC9A01_Display structure.
 * @param command Command to be sent.
 */
void GC9A01_SendCommand(GC9A01_HandleTypeDef *display, uint8_t command)
{
    // Set DC pin to low for command mode
    HAL_GPIO_WritePin(display->GC9A01_DC_PORT, display->GC9A01_DC_PIN, GPIO_PIN_RESET);

    // Set CS pin to low to enable the device
    HAL_GPIO_WritePin(display->GC9A01_CS_PORT, display->GC9A01_CS_PIN, GPIO_PIN_RESET);

    // Send command via SPI
    HAL_SPI_Transmit(display->hspi, &command, sizeof(command), 100);

    // Set CS pin to high to disable the device
    HAL_GPIO_WritePin(display->GC9A01_CS_PORT, display->GC9A01_CS_PIN, GPIO_PIN_SET);
}

static inline void GC9A01_SendByte(uint8_t val) {
    GC9A01_SendData(&val, sizeof(val));
}

/**
 * @brief Clear the GC9A01 display with a specified color.
 *
 * @param display Pointer to the GC9A01_Display structure.
 * @param color Color to fill the display with.
 */
void GC9A01_Clear(GC9A01_HandleTypeDef *display, uint16_t color)
{
    // Set column address range
    GC9A01_SendCommand(display, 0x2A);
    uint8_t column_data[] = {0x00, 0x00, (display->LCD_width >> 8) & 0xFF, display->LCD_width & 0xFF};
    GC9A01_SendData(display, column_data);

    // Set page address range
    GC9A01_SendCommand(display, 0x2B);
    uint8_t page_data[] = {0x00, 0x00, (display->LCD_height >> 8) & 0xFF, display->LCD_height & 0xFF};
    GC9A01_SendData(display, page_data);

    // Memory Write
    GC9A01_SendCommand(display, GC9A01_CMD_MEMORY_WRITE);

    // Set DC pin to high for data mode
    HAL_GPIO_WritePin(display->GC9A01_DC_PORT, display->GC9A01_DC_PIN, GPIO_PIN_SET);

    // Set CS pin to low to enable the device
    HAL_GPIO_WritePin(display->GC9A01_CS_PORT, display->GC9A01_CS_PIN, GPIO_PIN_RESET);

    // Send color data to fill the display
    for (uint32_t i = 0; i < (uint32_t)display->LCD_width * display->LCD_height; i++)
    {
        HAL_SPI_Transmit(display->hspi, (uint8_t *)&color, sizeof(color), HAL_MAX_DELAY);
    }

    // Set CS pin to high to disable the device
    HAL_GPIO_WritePin(display->GC9A01_CS_PORT, display->GC9A01_CS_PIN, GPIO_PIN_SET);
}

void GC9A01_Init(GC9A01_HandleTypeDef *display, SPI_HandleTypeDef *hspi, GPIO_TypeDef *GC9A01_DC_PORT, uint16_t GC9A01_DC_PIN, GPIO_TypeDef *GC9A01_CS_PORT, uint16_t GC9A01_CS_PIN, GPIO_TypeDef *GC9A01_RESET_PORT, uint16_t GC9A01_RESET_PIN, uint16_t LCD_width, uint16_t LCD_height,int oreientation)
{
    display->hspi = hspi;
    display->GC9A01_CS_PORT = GC9A01_CS_PORT;
    display->GC9A01_DC_PORT = GC9A01_DC_PORT;
    display->GC9A01_RESET_PORT = GC9A01_RESET_PORT;
    display->GC9A01_DC_PIN = GC9A01_DC_PIN;
    display->GC9A01_CS_PIN = GC9A01_CS_PIN;
    display->GC9A01_RESET_PIN = GC9A01_RESET_PIN;
    display->LCD_height = LCD_height;
    display->LCD_width = LCD_width;

    HAL_SPI_Init(&hspi);
    // Power On Sequence
    HAL_Delay(5); // Wait for power stabilization

    GC9A01_SendCommand(0xEF);
    
    GC9A01_SendCommand(0xEB);
    GC9A01_SendByte(0x14);
    
    GC9A01_SendCommand(0xFE);
    GC9A01_SendCommand(0xEF);
    
    GC9A01_SendCommand(0xEB);
    GC9A01_SendByte(0x14);
    
    GC9A01_SendCommand(0x84);
    GC9A01_SendByte(0x40);
    
    GC9A01_SendCommand(0x85);
    GC9A01_SendByte(0xFF);
    
    GC9A01_SendCommand(0x86);
    GC9A01_SendByte(0xFF);
    
    GC9A01_SendCommand(0x87);
    GC9A01_SendByte(0xFF);
    
    GC9A01_SendCommand(0x88);
    GC9A01_SendByte(0x0A);
    
    GC9A01_SendCommand(0x89);
    GC9A01_SendByte(0x21);
    
    GC9A01_SendCommand(0x8A);
    GC9A01_SendByte(0x00);
    
    GC9A01_SendCommand(0x8B);
    GC9A01_SendByte(0x80);
    
    GC9A01_SendCommand(0x8C);
    GC9A01_SendByte(0x01);
    
    GC9A01_SendCommand(0x8D);
    GC9A01_SendByte(0x01);
    
    GC9A01_SendCommand(0x8E);
    GC9A01_SendByte(0xFF);
    
    GC9A01_SendCommand(0x8F);
    GC9A01_SendByte(0xFF);
    
    
    GC9A01_SendCommand(0xB6);
    GC9A01_SendByte(0x00);
    GC9A01_SendByte(0x00);
    
    GC9A01_SendCommand(0x36);

    switch (orirntation)
    {
    case 0:
        GC9A01_SendByte(0x18);
        break;
    case 1:
        GC9A01_SendByte(0x28);
        break;
    case 2:
        GC9A01_SendByte(0x48);
        break;
    case 3:
        GC9A01_SendByte(0x88);
        break;
    default:
        break;
    }

    GC9A01_SendCommand(GC9A01_CMD_COLMOD);
    GC9A01_SendByte(GC9A01_CMD_COLMOD_18_BIT);
    
    GC9A01_SendCommand(0x90);
    GC9A01_SendByte(0x08);
    GC9A01_SendByte(0x08);
    GC9A01_SendByte(0x08);
    GC9A01_SendByte(0x08);
    
    GC9A01_SendCommand(0xBD);
    GC9A01_SendByte(0x06);
    
    GC9A01_SendCommand(0xBC);
    GC9A01_SendByte(0x00);
    
    GC9A01_SendCommand(0xFF);
    GC9A01_SendByte(0x60);
    GC9A01_SendByte(0x01);
    GC9A01_SendByte(0x04);
    
    GC9A01_SendCommand(0xC3);
    GC9A01_SendByte(0x13);
    GC9A01_SendCommand(0xC4);
    GC9A01_SendByte(0x13);
    
    GC9A01_SendCommand(0xC9);
    GC9A01_SendByte(0x22);
    
    GC9A01_SendCommand(0xBE);
    GC9A01_SendByte(0x11);
    
    GC9A01_SendCommand(0xE1);
    GC9A01_SendByte(0x10);
    GC9A01_SendByte(0x0E);
    
    GC9A01_SendCommand(0xDF);
    GC9A01_SendByte(0x21);
    GC9A01_SendByte(0x0c);
    GC9A01_SendByte(0x02);
    
    GC9A01_SendCommand(0xF0);
    GC9A01_SendByte(0x45);
    GC9A01_SendByte(0x09);
    GC9A01_SendByte(0x08);
    GC9A01_SendByte(0x08);
    GC9A01_SendByte(0x26);
    GC9A01_SendByte(0x2A);

    GC9A01_SendCommand(0xF1);
    GC9A01_SendByte(0x43);
    GC9A01_SendByte(0x70);
    GC9A01_SendByte(0x72);
    GC9A01_SendByte(0x36);
    GC9A01_SendByte(0x37);
    GC9A01_SendByte(0x6F);
    
    GC9A01_SendCommand(0xF2);
    GC9A01_SendByte(0x45);
    GC9A01_SendByte(0x09);
    GC9A01_SendByte(0x08);
    GC9A01_SendByte(0x08);
    GC9A01_SendByte(0x26);
    GC9A01_SendByte(0x2A);
    
    GC9A01_SendCommand(0xF3);
    GC9A01_SendByte(0x43);
    GC9A01_SendByte(0x70);
    GC9A01_SendByte(0x72);
    GC9A01_SendByte(0x36);
    GC9A01_SendByte(0x37);
    GC9A01_SendByte(0x6F);
    
    GC9A01_SendCommand(0xED);
    GC9A01_SendByte(0x1B);
    GC9A01_SendByte(0x0B);
    
    GC9A01_SendCommand(0xAE);
    GC9A01_SendByte(0x77);
    
    GC9A01_SendCommand(0xCD);
    GC9A01_SendByte(0x63);
    
    GC9A01_SendCommand(0x70);
    GC9A01_SendByte(0x07);
    GC9A01_SendByte(0x07);
    GC9A01_SendByte(0x04);
    GC9A01_SendByte(0x0E);
    GC9A01_SendByte(0x0F);
    GC9A01_SendByte(0x09);
    GC9A01_SendByte(0x07);
    GC9A01_SendByte(0x08);
    GC9A01_SendByte(0x03);
    
    GC9A01_SendCommand(0xE8);
    GC9A01_SendByte(0x34);
    
    GC9A01_SendCommand(0x62);
    GC9A01_SendByte(0x18);
    GC9A01_SendByte(0x0D);
    GC9A01_SendByte(0x71);
    GC9A01_SendByte(0xED);
    GC9A01_SendByte(0x70);
    GC9A01_SendByte(0x70);
    GC9A01_SendByte(0x18);
    GC9A01_SendByte(0x0F);
    GC9A01_SendByte(0x71);
    GC9A01_SendByte(0xEF);
    GC9A01_SendByte(0x70);
    GC9A01_SendByte(0x70);
    
    GC9A01_SendCommand(0x63);
    GC9A01_SendByte(0x18);
    GC9A01_SendByte(0x11);
    GC9A01_SendByte(0x71);
    GC9A01_SendByte(0xF1);
    GC9A01_SendByte(0x70);
    GC9A01_SendByte(0x70);
    GC9A01_SendByte(0x18);
    GC9A01_SendByte(0x13);
    GC9A01_SendByte(0x71);
    GC9A01_SendByte(0xF3);
    GC9A01_SendByte(0x70);
    GC9A01_SendByte(0x70);
    
    GC9A01_SendCommand(0x64);
    GC9A01_SendByte(0x28);
    GC9A01_SendByte(0x29);
    GC9A01_SendByte(0xF1);
    GC9A01_SendByte(0x01);
    GC9A01_SendByte(0xF1);
    GC9A01_SendByte(0x00);
    GC9A01_SendByte(0x07);
    
    GC9A01_SendCommand(0x66);
    GC9A01_SendByte(0x3C);
    GC9A01_SendByte(0x00);
    GC9A01_SendByte(0xCD);
    GC9A01_SendByte(0x67);
    GC9A01_SendByte(0x45);
    GC9A01_SendByte(0x45);
    GC9A01_SendByte(0x10);
    GC9A01_SendByte(0x00);
    GC9A01_SendByte(0x00);
    GC9A01_SendByte(0x00);
    
    GC9A01_SendCommand(0x67);
    GC9A01_SendByte(0x00);
    GC9A01_SendByte(0x3C);
    GC9A01_SendByte(0x00);
    GC9A01_SendByte(0x00);
    GC9A01_SendByte(0x00);
    GC9A01_SendByte(0x01);
    GC9A01_SendByte(0x54);
    GC9A01_SendByte(0x10);
    GC9A01_SendByte(0x32);
    GC9A01_SendByte(0x98);
    
    GC9A01_SendCommand(0x74);
    GC9A01_SendByte(0x10);
    GC9A01_SendByte(0x85);
    GC9A01_SendByte(0x80);
    GC9A01_SendByte(0x00);
    GC9A01_SendByte(0x00);
    GC9A01_SendByte(0x4E);
    GC9A01_SendByte(0x00);
    
    GC9A01_SendCommand(0x98);
    GC9A01_SendByte(0x3e);
    GC9A01_SendByte(0x07);
    
    GC9A01_SendCommand(0x35);
    GC9A01_SendCommand(0x21);
    
    GC9A01_SendCommand(0x11);
    HAL_Delay(120);
    GC9A01_SendCommand(0x29);
    HAL_Delay(20);
}

/**
 * @brief Convert RGB color to RGB565 format.
 *
 * @param red Red component (0-255).
 * @param green Green component (0-255).
 * @param blue Blue component (0-255).
 * @return Color in RGB565 format.
 */
uint16_t RGB_to_RGB565(uint8_t red, uint8_t green, uint8_t blue)
{
    // Convert 8-bit RGB components to 5-bit (red), 6-bit (green), 5-bit (blue)
    uint16_t r = (red >> 3) & 0x1F;
    uint16_t g = (green >> 2) & 0x3F;
    uint16_t b = (blue >> 3) & 0x1F;

    // Combine the components into RGB565 format
    return (r << 11) | (g << 5) | b;
}
/**
 * @brief Draw a pixel on the GC9A01 display.
 *
 * @param display Pointer to the GC9A01_Display structure.
 * @param x X coordinate of the pixel.
 * @param y Y coordinate of the pixel.
 * @param color Color of the pixel.
 */
void GC9A01_DrawPixel(GC9A01_HandleTypeDef *display, uint16_t x, uint16_t y, uint16_t color)
{
    // Set column address
    GC9A01_SendCommand(display, 0x2A);
    uint8_t column_data[] = {x >> 8, x & 0xFF, ((x + 1) >> 8) & 0xFF, (x + 1) & 0xFF};
    GC9A01_SendData(display, column_data);

    // Set page address
    GC9A01_SendCommand(display, 0x2B);
    uint8_t page_data[] = {y >> 8, y & 0xFF, ((y + 1) >> 8) & 0xFF, (y + 1) & 0xFF};
    GC9A01_SendData(display, page_data);

    // Memory Write
    GC9A01_SendCommand(display, GC9A01_CMD_MEMORY_WRITE);

    // Set DC pin to high for data mode
    HAL_GPIO_WritePin(display->GC9A01_DC_PORT, display->GC9A01_DC_PIN, GPIO_PIN_SET);

    // Set CS pin to low to enable the device
    HAL_GPIO_WritePin(display->GC9A01_CS_PORT, display->GC9A01_CS_PIN, GPIO_PIN_RESET);

    // Send color data for the pixel
    HAL_SPI_Transmit(display->hspi, (uint8_t *)&color, sizeof(color), HAL_MAX_DELAY);

    // Set CS pin to high to disable the device
    HAL_GPIO_WritePin(display->GC9A01_CS_PORT, display->GC9A01_CS_PIN, GPIO_PIN_SET);
}

/**
 * @brief Draws a line on the GC9A01 display between two points.
 *
 * This function draws a straight line between two specified points on the display.
 *
 * @param x1 The x-coordinate of the starting point.
 * @param y1 The y-coordinate of the starting point.
 * @param x2 The x-coordinate of the ending point.
 * @param y2 The y-coordinate of the ending point.
 * @param color The color of the line.
 */
void GC9A01_DrawLine(GC9A01_HandleTypeDef *display, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    int16_t dx = abs(x2 - x1);
    int16_t sx = x1 < x2 ? 1 : -1;
    int16_t dy = -abs(y2 - y1);
    int16_t sy = y1 < y2 ? 1 : -1;
    int16_t err = dx + dy; /* error value e_xy */

    while (1)
    {
        // Draw the current point
        GC9A01_DrawPixel(display, x1, y1, color);

        // Check if you have reached your destination
        if (x1 == x2 && y1 == y2)
        {
            break;
        }

        int16_t e2 = 2 * err;

        // Calculate the next coordinate based on the error
        if (e2 >= dy)
        {
            err += dy;
            x1 += sx;
        }

        if (e2 <= dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

/**
 * @brief Draw an empty rectangle on the GC9A01 display.
 *
 * @param display Pointer to the GC9A01_Display structure.
 * @param x X coordinate of the top-left corner.
 * @param y Y coordinate of the top-left corner.
 * @param width Width of the rectangle.
 * @param height Height of the rectangle.
 * @param color Color of the rectangle.
 * @return 0 if successful, -1 if the rectangle is too large for the display.
 */
int GC9A01_DrawRectangle(GC9A01_HandleTypeDef *display, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color)
{
    if ((x + width > display->LCD_width) || (y + height > display->LCD_height))
    {
        // Rectangle exceeds display boundaries
        return -1;
    }

    for (uint16_t i = 0; i < width; i++)
    {
        GC9A01_DrawPixel(display, x + i, y, color);
        GC9A01_DrawPixel(display, x + i, y + height - 1, color);
    }

    for (uint16_t i = 0; i < height; i++)
    {
        GC9A01_DrawPixel(display, x, y + i, color);
        GC9A01_DrawPixel(display, x + width - 1, y + i, color);
    }

    return 0;
}

/**
 * @brief Draw a filled rectangle on the GC9A01 display.
 *
 * @param display Pointer to the GC9A01_Display structure.
 * @param x X coordinate of the top-left corner.
 * @param y Y coordinate of the top-left corner.
 * @param width Width of the rectangle.
 * @param height Height of the rectangle.
 * @param color Color of the rectangle.
 * @return 0 if successful, -1 if the rectangle is too large for the display.
 */
int GC9A01_FillRectangle(GC9A01_HandleTypeDef *display, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color)
{
    if ((x + width > display->LCD_width) || (y + height > display->LCD_height))
    {
        // Rectangle exceeds display boundaries
        return -1;
    }

    for (uint16_t i = 0; i < width; i++)
    {
        for (uint16_t j = 0; j < height; j++)
        {
            GC9A01_DrawPixel(display, x + i, y + j, color);
        }
    }

    return 0;
}

/**
 * @brief Draw an empty circle on the GC9A01 display.
 *
 * @param display Pointer to the GC9A01_Display structure.
 * @param x X coordinate of the center.
 * @param y Y coordinate of the center.
 * @param radius Radius of the circle.
 * @param color Color of the circle.
 * @return 0 if successful, -1 if the circle is too large for the display.
 */
int GC9A01_DrawCircle(GC9A01_HandleTypeDef *display, uint16_t x, uint16_t y, uint16_t radius, uint16_t color)
{
    if ((x - radius < 0) || (x + radius >= display->LCD_width) || (y - radius < 0) || (y + radius >= display->LCD_height))
    {
        // Circle exceeds display boundaries
        return -1;
    }

    int16_t f = 1 - radius;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * radius;
    int16_t x1 = 0;
    int16_t y1 = radius;

    GC9A01_DrawPixel(display, x, y + radius, color);
    GC9A01_DrawPixel(display, x, y - radius, color);
    GC9A01_DrawPixel(display, x + radius, y, color);
    GC9A01_DrawPixel(display, x - radius, y, color);

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
        f += ddF_x;

        GC9A01_DrawPixel(display, x + x1, y + y1, color);
        GC9A01_DrawPixel(display, x - x1, y + y1, color);
        GC9A01_DrawPixel(display, x + x1, y - y1, color);
        GC9A01_DrawPixel(display, x - x1, y - y1, color);

        GC9A01_DrawPixel(display, x + y1, y + x1, color);
        GC9A01_DrawPixel(display, x - y1, y + x1, color);
        GC9A01_DrawPixel(display, x + y1, y - x1, color);
        GC9A01_DrawPixel(display, x - y1, y - x1, color);
    }

    return 0;
}

/**
 * @brief Draw a filled circle on the GC9A01 display.
 *
 * @param display Pointer to the GC9A01_Display structure.
 * @param x X coordinate of the center.
 * @param y Y coordinate of the center.
 * @param radius Radius of the circle.
 * @param color Color of the circle.
 * @return 0 if successful, -1 if the circle is too large for the display.
 */
int GC9A01_FillCircle(GC9A01_HandleTypeDef *display, uint16_t x, uint16_t y, uint16_t radius, uint16_t color)
{
    if ((x - radius < 0) || (x + radius >= display->LCD_width) || (y - radius < 0) || (y + radius >= display->LCD_height))
    {
        // Circle exceeds display boundaries
        return -1;
    }

    for (int16_t dy = 0; dy <= radius; dy++)
    {
        for (int16_t dx = 0; dx <= radius; dx++)
        {
            if (dx * dx + dy * dy <= radius * radius)
            {
                GC9A01_DrawPixel(display, x + dx, y + dy, color);
                GC9A01_DrawPixel(display, x - dx, y + dy, color);
                GC9A01_DrawPixel(display, x + dx, y - dy, color);
                GC9A01_DrawPixel(display, x - dx, y - dy, color);
            }
        }
    }

    return 0;
}

/**
 * @brief Draw text on the GC9A01 display.
 *
 * @param display Pointer to the GC9A01_Display structure.
 * @param x X coordinate of the top-left corner of the text.
 * @param y Y coordinate of the top-left corner of the text.
 * @param text String to be displayed.
 * @param font Pointer to the font bitmap data.
 * @param color Color of the text.
 * @return 0 if successful, -1 if the text is too large for the display.
 */
int GC9A01_DrawText(GC9A01_HandleTypeDef *display, uint16_t x, uint16_t y, const char *text, const uint8_t *font, uint16_t color)
{
    // Calculate the width and height of a single character in the font
    uint8_t char_width = font[0];
    uint8_t char_height = font[1];

    // Check if the entire text fits within the display
    if ((x + (strlen(text) * char_width) > display->LCD_width) || (y + char_height > display->LCD_height))
    {
        // Text exceeds display boundaries
        return -1;
    }

    // Iterate through each character in the string
    for (size_t i = 0; i < strlen(text); i++)
    {
        // Get the ASCII value of the current character
        uint8_t ascii_value = text[i];

        // Calculate the starting position of the character in the font data
        uint32_t char_offset = 2 + (ascii_value * ((char_width * char_height) / 8));

        // Draw the character on the display
        for (uint8_t row = 0; row < char_height; row++)
        {
            for (uint8_t col = 0; col < char_width; col++)
            {
                // Extract the pixel value from the font data
                uint8_t pixel = (font[char_offset + (row * (char_width / 8) + (col / 8))] >> (7 - (col % 8))) & 0x01;

                // Draw the pixel on the display
                if (pixel)
                {
                    GC9A01_DrawPixel(display, x + (i * char_width) + col, y + row, color);
                }
            }
        }
    }

    return 0;
}

/**
 * @brief Calculates the sine of the given angle in degrees.
 *
 * This function calculates the sine of the input angle using the standard math library function.
 *
 * @param angle The input angle in degrees.
 * @return The sine value in a 16-bit representation (scaled by 256).
 */
int16_t GC9A01_Sine(uint16_t angle)
{
    // Normalize the angle to [0, 359]
    angle %= 360;

    // Calculate the sine of the normalized angle
    double radians = angle * M_PI / 180.0; // Convert degrees to radians
    double sineValue = sin(radians);

    // Normalize the result and convert to a 16-bit representation
    return (int16_t)(sineValue * 256.0);
}

/**
 * @brief Calculates the cosine of the given angle in degrees.
 *
 * This function calculates the cosine of the input angle using the standard math library function.
 *
 * @param angle The input angle in degrees.
 * @return The cosine value in a 16-bit representation (scaled by 256).
 */
int16_t GC9A01_Cosine(uint16_t angle)
{
    // Normalize the angle to [0, 359]
    angle %= 360;

    // Calculate the cosine of the normalized angle
    double radians = angle * M_PI / 180.0; // Convert degrees to radians
    double cosineValue = cos(radians);

    // Normalize the result and convert to a 16-bit representation
    return (int16_t)(cosineValue * 256.0);
}

/**
 * @brief Draws a custom gauge on the display.
 *
 * This function draws a gauge with an indicator, a red zone, and textual information.
 *
 * @param gauge Pointer to the CustomGauge structure containing gauge information.
 */
void DrawCustomGauge(GC9A01_HandleTypeDef *display, Gauge *gauge)
{
    // Draw the outer circle of the gauge
    GC9A01_DrawCircle(display, gauge->x, gauge->y, gauge->radius, GC9A01_COLOR_BLACK);

    // Calculate the angle for the indicator based on the current value
    uint16_t angle = gauge->startAngle + ((gauge->currentValue - gauge->minValue) *
                                          (gauge->endAngle - gauge->startAngle)) /
                                             (gauge->maxValue - gauge->minValue);

    // Calculate the position of the indicator
    int16_t endX = gauge->x + (gauge->radius * GC9A01_Cosine(angle)) / 256;
    int16_t endY = gauge->y - (gauge->radius * GC9A01_Sine(angle)) / 256;

    // Draw the indicator line
    GC9A01_DrawLine(display, gauge->x, gauge->y, endX, endY, GC9A01_COLOR_GREEN);

    // Draw a small arrow at the end of the indicator (optional)
    GC9A01_DrawLine(display, endX, endY, endX + 5, endY + 5, GC9A01_COLOR_GREEN);
    GC9A01_DrawLine(display, endX, endY, endX - 5, endY + 5, GC9A01_COLOR_GREEN);

    // Draw the red zone if the current value exceeds the threshold
    if (gauge->currentValue >= gauge->redZone)
    {
        GC9A01_DrawCircle(display, gauge->x, gauge->y, gauge->radius, GC9A01_COLOR_RED);
    }

    // Add text with gauge information
    char valueText[20];
    snprintf(valueText, sizeof(valueText), "%d %s", gauge->currentValue, gauge->unit);
    GC9A01_DrawText(display, gauge->x - 20, gauge->y + gauge->radius + 10, valueText, font_6x8, GC9A01_COLOR_WHITE);
}

void UpdateGaugeValue(GC9A01_HandleTypeDef *display, Gauge *gauge, uint16_t newValue)
{
    // Limita il nuovo valore tra il valore minimo e massimo
    if (newValue < gauge->minValue)
    {
        gauge->currentValue = gauge->minValue;
    }
    else if (newValue > gauge->maxValue)
    {
        gauge->currentValue = gauge->maxValue;
    }
    else
    {
        gauge->currentValue = newValue;
    }

    // Disegna il gauge con il nuovo valore
    DrawCustomGauge(display, gauge);
}
