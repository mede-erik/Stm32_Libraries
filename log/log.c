/**
 * @author Medeossi Erik
 * @date 06/12/2022
 *
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
    if (logHandle.mode <= 3)
    {
        // TODO add serial print
    }
}