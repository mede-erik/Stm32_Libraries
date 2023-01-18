/**
 * @author Medeossi Erik
 * @date 06/12/2022
 * @link https://github.com/mede-erik/Stm32_Libraries
 * @version 0v1
 */

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