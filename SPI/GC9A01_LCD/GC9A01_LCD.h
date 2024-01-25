/**
 * @author Medeossi Erik
 * @date 17/01/2024
 * @link https://github.com/mede-erik/Stm32_Libraries
 */

#ifndef INC_GC9A01_LCD_H_
#define INC_GC9A01_LCD_H_

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

#define GC9A01_CMD_SLEEP_OUT 0x11
#define GC9A01_CMD_DISPLAY_ON 0x29
#define GC9A01_CMD_MEMORY_WRITE 0x2C
#define GC9A01_CMD_MAC 0x36
#define GC9A01_CMD_PIXEL_FORMAT 0x3A
#define GC9A01_CMD_MEMORY_ACCESS_CTL 0x36
#define GC9A01_CMD_COLMOD 0x3A
#define GC9A01_COLOR_RED 0xF800
#define GC9A01_COLOR_GREEN 0x07E0
#define GC9A01_COLOR_BLUE 0x001Fa
#define GC9A01_COLOR_CYAN 0x07FFa
#define GC9A01_COLOR_MAGENTA 0xF81F
#define GC9A01_COLOR_YELLOW 0xFFE0
#define GC9A01_COLOR_ORANGE 0xFC00
#define GC9A01_COLOR_PURPLE 0x8010
#define GC9A01_COLOR_PINK 0xF81F
#define GC9A01_COLOR_WHITE 0xFFFF
#define GC9A01_COLOR_BLACK 0x0000

typedef struct
{
    SPI_HandleTypeDef *hspi;
    GPIO_TypeDef *GC9A01_DC_PORT;
    uint16_t GC9A01_DC_PIN;
    GPIO_TypeDef *GC9A01_CS_PORT;
    uint16_t GC9A01_CS_PIN;
    GPIO_TypeDef *GC9A01_RESET_PORT;
    uint16_t GC9A01_RESET_PIN;
    uint16_t LCD_width;
    uint16_t LCD_height;
} GC9A01_HandleTypeDef;

const uint8_t font_6x8[] = {
    6, 8, // Width, Height

    // ASCII 32-127
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // (space)
    0x00, 0x00, 0x5F, 0x00, 0x00, 0x00, // !
    0x00, 0x03, 0x00, 0x03, 0x00, 0x00, // "
    0x14, 0x7F, 0x14, 0x7F, 0x14, 0x00, // #
    0x24, 0x2A, 0x7F, 0x2A, 0x12, 0x00, // $
    0x23, 0x13, 0x08, 0x64, 0x62, 0x00, // %
    0x36, 0x49, 0x55, 0x22, 0x50, 0x00, // &
    0x00, 0x05, 0x03, 0x00, 0x00, 0x00, // '
    0x00, 0x1C, 0x22, 0x41, 0x00, 0x00, // (
    0x00, 0x41, 0x22, 0x1C, 0x00, 0x00, // )
    0x08, 0x2A, 0x1C, 0x2A, 0x08, 0x00, // *
    0x08, 0x08, 0x3E, 0x08, 0x08, 0x00, // +
    0x00, 0x50, 0x30, 0x00, 0x00, 0x00, // ,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x00, // -
    0x00, 0x60, 0x60, 0x00, 0x00, 0x00, // .
    0x20, 0x10, 0x08, 0x04, 0x02, 0x00, // /
    0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00, // 0
    0x00, 0x04, 0x02, 0x7F, 0x00, 0x00, // 1
    0x42, 0x61, 0x51, 0x49, 0x46, 0x00, // 2
    0x22, 0x41, 0x49, 0x49, 0x36, 0x00, // 3
    0x18, 0x14, 0x12, 0x7F, 0x10, 0x00, // 4
    0x2F, 0x49, 0x49, 0x49, 0x31, 0x00, // 5
    0x3C, 0x4A, 0x49, 0x49, 0x30, 0x00, // 6
    0x01, 0x71, 0x09, 0x05, 0x03, 0x00, // 7
    0x36, 0x49, 0x49, 0x49, 0x36, 0x00, // 8
    0x06, 0x49, 0x49, 0x29, 0x1E, 0x00, // 9
    0x00, 0x36, 0x36, 0x00, 0x00, 0x00, // :
    0x00, 0x56, 0x36, 0x00, 0x00, 0x00, // ;
    0x08, 0x14, 0x22, 0x41, 0x00, 0x00, // <
    0x14, 0x14, 0x14, 0x14, 0x14, 0x00, // =
    0x00, 0x41, 0x22, 0x14, 0x08, 0x00, // >
    0x02, 0x01, 0x51, 0x09, 0x06, 0x00, // ?
    0x3E, 0x41, 0x49, 0x55, 0x5E, 0x00, // @
    0x7E, 0x11, 0x11, 0x11, 0x7E, 0x00, // A
    0x7F, 0x49, 0x49, 0x49, 0x36, 0x00, // B
    0x3E, 0x41, 0x41, 0x41, 0x22, 0x00, // C
    0x7F, 0x41, 0x41, 0x41, 0x3E, 0x00, // D
    0x7F, 0x49, 0x49, 0x49, 0x41, 0x00, // E
    0x7F, 0x09, 0x09, 0x09, 0x01, 0x00, // F
    0x3E, 0x41, 0x41, 0x49, 0x3A, 0x00, // G
    0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00, // H
    0x00, 0x41, 0x7F, 0x41, 0x00, 0x00, // I
    0x20, 0x40, 0x41, 0x3F, 0x01, 0x00, // J
    0x7F, 0x08, 0x14, 0x22, 0x41, 0x00, // K
    0x7F, 0x40, 0x40, 0x40, 0x40, 0x00, // L
    0x7F, 0x02, 0x0C, 0x02, 0x7F, 0x00, // M
    0x7F, 0x04, 0x08, 0x10, 0x7F, 0x00, // N
    0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00, // O
    0x7F, 0x09, 0x09, 0x09, 0x06, 0x00, // P
    0x3E, 0x41, 0x51, 0x21, 0x5E, 0x00, // Q
    0x7F, 0x09, 0x19, 0x29, 0x46, 0x00, // R
    0x26, 0x49, 0x49, 0x49, 0x32, 0x00, // S
    0x01, 0x01, 0x7F, 0x01, 0x01, 0x00, // T
    0x3F, 0x40, 0x40, 0x40, 0x3F, 0x00, // U
    0x0F, 0x30, 0x40, 0x30, 0x0F, 0x00, // V
    0x7F, 0x20, 0x10, 0x20, 0x7F, 0x00, // W
    0x63, 0x14, 0x08, 0x14, 0x63, 0x00, // X
    0x03, 0x04, 0x78, 0x04, 0x03, 0x00, // Y
    0x61, 0x51, 0x49, 0x45, 0x43, 0x00, // Z
    0x7F, 0x41, 0x41, 0x00, 0x00, 0x00, // [
    0x02, 0x04, 0x08, 0x10, 0x20, 0x00, //
    0x41, 0x41, 0x7F, 0x00, 0x00, 0x00, // ]
    0x04, 0x02, 0x01, 0x02, 0x04, 0x00, // ^
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, // _
    0x00, 0x01, 0x02, 0x04, 0x00, 0x00, // `
    0x20, 0x54, 0x54, 0x54, 0x78, 0x00, // a
    0x7F, 0x48, 0x44, 0x44, 0x38, 0x00, // b
    0x38, 0x44, 0x44, 0x44, 0x20, 0x00, // c
    0x38, 0x44, 0x44, 0x48, 0x7F, 0x00, // d
    0x38, 0x54, 0x54, 0x54, 0x18, 0x00, // e
    0x08, 0x7E, 0x09, 0x01, 0x02, 0x00, // f
    0x18, 0xA4, 0xA4, 0xA4, 0x7C, 0x00, // g
    0x7F, 0x08, 0x04, 0x04, 0x78, 0x00, // h
    0x00, 0x44, 0x7D, 0x40, 0x00, 0x00, // i
    0x40, 0x80, 0x84, 0x7D, 0x00, 0x00, // j
    0x7F, 0x10, 0x28, 0x44, 0x00, 0x00, // k
    0x00, 0x41, 0x7F, 0x40, 0x00, 0x00, // l
    0x7C, 0x04, 0x18, 0x04, 0x78, 0x00, // m
    0x7C, 0x08, 0x04, 0x04, 0x78, 0x00, // n
    0x38, 0x44, 0x44, 0x44, 0x38, 0x00, // o
    0xFC, 0x24, 0x24, 0x24, 0x18, 0x00, // p
    0x18, 0x24, 0x24, 0x18, 0xFC, 0x00, // q
    0x7C, 0x08, 0x04, 0x04, 0x08, 0x00, // r
    0x48, 0x54, 0x54, 0x54, 0x24, 0x00, // s
    0x04, 0x3F, 0x44, 0x40, 0x20, 0x00, // t
    0x3C, 0x40, 0x40, 0x20, 0x7C, 0x00, // u
    0x1C, 0x20, 0x40, 0x20, 0x1C, 0x00, // v
    0x3C, 0x40, 0x30, 0x40, 0x3C, 0x00, // w
    0x44, 0x28, 0x10, 0x28, 0x44, 0x00, // x
    0x1C, 0xA0, 0xA0, 0xA0, 0x7C, 0x00, // y
    0x44, 0x64, 0x54, 0x4C, 0x44, 0x00, // z
    0x00, 0x08, 0x36, 0x41, 0x00, 0x00, // {
    0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, // |
    0x00, 0x41, 0x36, 0x08, 0x00, 0x00, // }
    0x08, 0x08, 0x2A, 0x1C, 0x08, 0x00  // ~
};

typedef struct
{
    int16_t x;             // Posizione x del centro del gauge
    int16_t y;             // Posizione y del centro del gauge
    uint16_t radius;       // Raggio del gauge
    uint16_t startAngle;   // Angolo di inizio del gauge (in gradi)
    uint16_t endAngle;     // Angolo di fine del gauge (in gradi)
    uint16_t minValue;     // Valore minimo del gauge
    uint16_t maxValue;     // Valore massimo del gauge
    uint16_t currentValue; // Valore da indicare con la freccia
    uint16_t redZone;      // Valore per la zona rossa
    const char *unit;      // Unità di misura
} Gauge;

void GC9A01_SendData(GC9A01_HandleTypeDef *display, uint8_t *data);
void GC9A01_SendCommand(GC9A01_HandleTypeDef *display, uint8_t command);
void GC9A01_Clear(GC9A01_HandleTypeDef *display, uint16_t color);
void GC9A01_Init(GC9A01_HandleTypeDef *display, SPI_HandleTypeDef *hspi, GPIO_TypeDef *GC9A01_DC_PORT, uint16_t GC9A01_DC_PIN, GPIO_TypeDef *GC9A01_CS_PORT, uint16_t GC9A01_CS_PIN, GPIO_TypeDef *GC9A01_RESET_PORT, uint16_t GC9A01_RESET_PIN, uint16_t LCD_width, uint16_t LCD_height);
uint16_t RGB_to_RGB565(uint8_t red, uint8_t green, uint8_t blue);
void GC9A01_DrawPixel(GC9A01_HandleTypeDef *display, uint16_t x, uint16_t y, uint16_t color);
int GC9A01_DrawRectangle(GC9A01_HandleTypeDef *display, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
int GC9A01_FillRectangle(GC9A01_HandleTypeDef *display, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
int GC9A01_DrawCircle(GC9A01_HandleTypeDef *display, uint16_t x, uint16_t y, uint16_t radius, uint16_t color);
int GC9A01_FillCircle(GC9A01_HandleTypeDef *display, uint16_t x, uint16_t y, uint16_t radius, uint16_t color);
int GC9A01_DrawText(GC9A01_HandleTypeDef *display, uint16_t x, uint16_t y, const char *text, const uint8_t *font, uint16_t color);
int16_t GC9A01_Cosine(uint16_t angle);
int16_t GC9A01_Sine(uint16_t angle);
void DrawCustomGauge(GC9A01_HandleTypeDef *display, Gauge *gauge);
void UpdateGaugeValue(GC9A01_HandleTypeDef *display, Gauge *gauge, uint16_t newValue);

#endif /* INC_GC9A01_LCD_H_ */