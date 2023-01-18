/**
 * @author Medeossi Erik
 * @date 06/12/2022
 * @link https://github.com/mede-erik/Stm32_Libraries
 * @version 0v1
 */

#include "log.h"

LOG_HandleTypeDef log_init(UART_HandleTypeDef *uartHandle, int mode)
{
    LOG_HandleTypeDef data;

    data.uartHandle = uartHandle;
    data.mode = mode;

    return data;
}

void LOG_print_info(LOG_HandleTypeDef logHandle, char msg[25])
{
    char long_msg[35];
    if (logHandle.mode >= 3)
    {
        sprintf(long_msg, "%s %s", INFO_LABEL, msg);
        HAL_UART_Transmit(logHandle.uartHandle, long_msg, sizeof(msg), 10);
    }
}

void LOG_print_warn(LOG_HandleTypeDef logHandle, char msg[25])
{
    char long_msg[35];
    if (logHandle.mode >= 2)
    {
        sprintf(long_msg, "%s %s", WARN_LABEL, msg);
        HAL_UART_Transmit(logHandle.uartHandle, long_msg, sizeof(msg), 10);
    }
}

void LOG_print_debug(LOG_HandleTypeDef logHandle, char msg[25])
{
    char long_msg[35];
    if (logHandle.mode >= 4)
    {
        sprintf(long_msg, "%s %s", DEBUG_LABEL, msg);
        HAL_UART_Transmit(logHandle.uartHandle, long_msg, sizeof(msg), 10);
    }
}

void LOG_print_error(LOG_HandleTypeDef logHandle, char msg[25])
{
    char long_msg[35];
    if (logHandle.mode >= 4)
    {
        sprintf(long_msg, "%s %s", ERROR_LABEL, msg);
        HAL_UART_Transmit(logHandle.uartHandle, long_msg, sizeof(msg), 10);
    }
}

void LOG_print_fault(LOG_HandleTypeDef logHandle, char msg[25])
{
    char long_msg[35];
    if (logHandle.mode >= 4)
    {
        sprintf(long_msg, "%s %s", FAULT_LABEL, msg);
        HAL_UART_Transmit(logHandle.uartHandle, long_msg, sizeof(msg), 10);
    }
}