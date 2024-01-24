/**
 * @author Medeossi Erik
 * @date 17/12/2023
 * @link https://github.com/mede-erik/Stm32_Libraries
 */
#ifndef INC_ST7735_LCD_H_
#define INC_ST7735_LCD_H_

#include "main.h"
#include "Fonts.h"

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

#define ST7735_SWRESET 0x01
#define ST7735_SLPOUT 0x11
#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR 0xB4
#define ST7735_PWCTR1 0xC0
#define ST7735_PWCTR2 0xC1
#define ST7735_PWCTR3 0xC2
#define ST7735_PWCTR4 0xC3
#define ST7735_PWCTR5 0xC4
#define ST7735_VMCTR1 0xC5
#define ST7735_COLMOD 0x3A
#define ST7735_MADCTL 0x36
#define ST7735_INVOFF 0x20
#define ST7735_CASET 0x2A
#define ST7735_RASET 0x2B
#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1
#define ST7735_NORON 0x13
#define ST7735_DISPON 0x29
#define ST7735_RAMWR 0x2C

#define ST7735_COLOR_BLACK 0x0000
#define ST7735_COLOR_WHITE 0xFFFF
#define ST7735_COLOR_BLUE 0xF800
#define ST7735_COLOR_GREEN 0x07E0
#define ST7735_COLOR_RED 0x001F
#define ST7735_COLOR_YELLOW 0x07FF
#define ST7735_COLOR_MAGENTA 0xF81F
#define ST7735_COLOR_CYAN 0xFFE0
#define ST7735_COLOR_LIGHTBLUE 0xFC00
#define ST7735_COLOR_PURPLE 0x8010
#define ST7735_COLOR_PINK 0xF81F
#define ST7735_COLOR_GRAY 0x8410
#define ST7735_COLOR_LIGHTGRAY 0xC618

typedef struct
{
    SPI_HandleTypeDef *hspi;
    GPIO_TypeDef *ST7735_DC_PORT;
    uint16_t ST7735_DC_PIN;
    GPIO_TypeDef *ST7735_CS_PORT;
    uint16_t ST7735_CS_PIN;
    GPIO_TypeDef *ST7735_RESET_PORT;
    uint16_t ST7735_RESET_PIN;
    uint16_t LCD_width;
    uint16_t LCD_height;

} ST7735_HandleTypeDef;

HAL_StatusTypeDef ST7735_Init(ST7735_HandleTypeDef *hst7735, SPI_HandleTypeDef *hspi, GPIO_TypeDef *ST7735_DC_PORT, uint16_t ST7735_DC_PIN, GPIO_TypeDef *ST7735_CS_PORT, uint16_t ST7735_CS_PIN, GPIO_TypeDef *ST7735_RESET_PORT, uint16_t ST7735_RESET_PIN, uint16_t LCD_width, uint16_t LCD_height);
void ST7735_Reset(ST7735_HandleTypeDef *hst7735);
void ST7735_SendCommand(ST7735_HandleTypeDef *hst7735, uint8_t cmd);
void ST7735_SendData(ST7735_HandleTypeDef *hst7735, uint8_t data);
HAL_StatusTypeDef ST7735_SetAddrWindow(ST7735_HandleTypeDef *hst7735, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
HAL_StatusTypeDef ST7735_FillRect(ST7735_HandleTypeDef *hst7735, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t color);
HAL_StatusTypeDef ST7735_DrawPixel(ST7735_HandleTypeDef *hst7735, uint8_t x, uint8_t y, uint16_t color);
void ST7735_DrawCircle(ST7735_HandleTypeDef *hst7735, uint8_t x, uint8_t y, uint8_t radius, uint16_t color);
void ST7735_DrawRectangle(ST7735_HandleTypeDef *hst7735, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t color);
void ST7735_DrawTriangle(ST7735_HandleTypeDef *hst7735, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t color);
void ST7735_DrawGraph(ST7735_HandleTypeDef *hst7735, uint8_t *data, uint8_t numPoints, uint16_t color);
void ST7735_DrawLine(ST7735_HandleTypeDef *hst7735, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t color);
uint16_t rgb_to_color(uint8_t red, uint8_t green, uint8_t blue);
void ST7735_WriteText(ST7735_HandleTypeDef *hst7735, uint16_t x, uint16_t y, const char *str, FontDef font, uint16_t color, uint16_t bgcolor);
void ST7735_WriteChar(ST7735_HandleTypeDef *hst7735, uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor);
#endif /* INC_ST7735_LCD_H_ */