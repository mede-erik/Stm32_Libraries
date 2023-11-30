/**
 * @author Medeossi Erik
 * @date 06/12/2022
 * @link https://github.com/mede-erik/Stm32_Libraries
 * @version 0v1
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

#include "main.h"
#include <string.h>
#include <stdio.h>

// labels

#define ERROR_LABEL "[ERROR]:"
#define DEBUG_LABEL "[DEBUG]:"
#define WARN_LABEL "[WARN]:"
#define INFO_LABEL "[INFO]:"
#define FAULT_LABEL "[FAULT]:"
#define MSG_LABEL "[MSG]:"

// modes

#define FAULT_MODE 0
#define ERROR_MODE 1
#define WARN_MODE 2
#define INFO_MODE 3
#define DEBUG_MODE 4

typedef struct
{
    UART_HandleTypeDef *uartHandle;
    int mode;
} LOG_HandleTypeDef;

LOG_HandleTypeDef log_init(UART_HandleTypeDef *uartHandle, int mode);

void LOG_print_info(LOG_HandleTypeDef logHandle, char msg[25]);

void LOG_print_warn(LOG_HandleTypeDef logHandle, char msg[25]);

void LOG_print_debug(LOG_HandleTypeDef logHandle, char msg[25]);

void LOG_print_error(LOG_HandleTypeDef logHandle, char msg[25]);

void LOG_print_fault(LOG_HandleTypeDef logHandle, char msg[25]);