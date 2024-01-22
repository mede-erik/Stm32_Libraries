/**
 * @author Medeossi Erik
 * @date 17/01/2024
 * @link https://github.com/mede-erik/Stm32_Libraries
 */

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