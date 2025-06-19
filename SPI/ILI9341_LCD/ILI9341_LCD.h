/**
 * @author Medeossi Erik
 * @date 19/06/2024
 * @link https://github.com/mede-erik/Stm32_Libraries
 */

#include "main.h"

#define ROTATE_0 0
#define ROTATE_90 1
#define ROTATE_180 2
#define ROTATE_270 3

typedef struct
{
    SPI_HandleTypeDef *hspi;
    GPIO_TypeDef *ILI9341_DC_PORT;
    uint16_t ILI9341_DC_PIN;
    GPIO_TypeDef *ILI9341_CS_PORT;
    uint16_t ILI9341_CS_PIN;
    GPIO_TypeDef *ILI9341_RESET_PORT;
    uint16_t ILI9341_RESET_PIN;
    uint16_t LCD_width;
    uint16_t LCD_height;

} ILI9341_HandleTypeDef;

HAL_StatusTypeDef ILI9341_Init(ILI9341_HandleTypeDef *ILI9341, SPI_HandleTypeDef *hspi, GPIO_TypeDef *ILI9341_DC_PORT, uint16_t ILI9341_DC_PIN, GPIO_TypeDef *ILI9341_CS_PORT, uint16_t ILI9341_CS_PIN, GPIO_TypeDef *ILI9341_RESET_PORT, uint16_t ILI9341_RESET_PIN, uint16_t LCD_width, uint16_t LCD_height);
void ILI9341_direction(ILI9341_HandleTypeDef *ILI9341, uint8_t direction);
void ILI9341_SoftReset(ILI9341_HandleTypeDef *ILI9341);
void ILI9341_Reset(ILI9341_HandleTypeDef *ILI9341);
void ILI9341_SetWindow(ILI9341_HandleTypeDef *ILI9341, uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y);
void LCD_WR_REG(ILI9341_HandleTypeDef *ILI9341, uint8_t data);
void LCD_WR_DATA(ILI9341_HandleTypeDef *ILI9341, uint8_t data);
void ILI9341_WritePixel(ILI9341_HandleTypeDef *ILI9341, uint16_t x, uint16_t y, uint16_t color);
void ILI9341_DrawBitmap(ILI9341_HandleTypeDef *ILI9341, uint16_t w, uint16_t h, uint8_t *s);
void ILI9341_DrawRectangle(ILI9341_HandleTypeDef *ILI9341, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void ILI9341_FillScreen(ILI9341_HandleTypeDef *ILI9341, uint16_t color);
void ILI9341_DrawLine(ILI9341_HandleTypeDef *ILI9341, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
void ILI9341_DrawCircle(ILI9341_HandleTypeDef *ILI9341, uint16_t x0, uint16_t y0, uint16_t r, uint16_t color);
void ILI9341_DrawArc(ILI9341_HandleTypeDef *ILI9341, uint16_t x0, uint16_t y0, uint16_t r, uint16_t start_angle, uint16_t end_angle, uint16_t color);
void ILI9341_DrawTriangle(ILI9341_HandleTypeDef *ILI9341, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
static void ConvHL(uint8_t *s, int32_t l);

