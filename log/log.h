/**
 * @author Medeossi Erik
 * @date 06/12/2022
 *
 */

#include "main.h"
#include <string.h>
#include <stdio.h>

// labels

#define ERORR_LABEL "[ERORR]:"
#define DEBUG_LABEL "[DEBUG]:"
#define WARN_LABEL "[WARN]:"
#define INFO_LABEL "[INFO]:"
#define FAULT_LABEL "[FAULT]:"
#define MSG_LABEL "[MSG]:"

// modes

#define FAULT_MODE 0
#define ERORR_MODE 1
#define WARN_MODE 2
#define INFO_MODE 3
#define DEBUG_MODE 4

typedef struct
{
    UART_HandleTypeDef *uartHandle;
    int mode;
} LOG_HandleTypeDef;
