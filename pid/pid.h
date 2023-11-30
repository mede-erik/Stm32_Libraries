/**
 * @author Medeossi Erik
 * @date 14/02/2023
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

#define MAX_INT 16777216
#define MIN_INT -16777216

typedef struct
{
    float Kp;
    float Ki;
    float Kd;
    float setPoint;
    float prevError;
    float integral;
} PID_t;
/**
 * @brief The PID_init function initializes the values of a PID_t structure to keep the PID coefficients and the values needed for calculating the PID algorithm
 *
 * @param pid pointer to the PID_t structure to be initialized
 * @param Kp proportional coefficient of the PID. This value affects how the system responds to the current error.
 * @param Ki integral coefficient of the PID. This value affects how the system responds to cumulative error over time.
 * @param Kd derivative coefficient of the PID. This value affects how the system responds to error variation over time.
 * @param setPoint set point, i.e. the reference value that the system tries to reach.
 */

void PID_init(PID_t *pid, float Kp, float Ki, float Kd, float setPoint);

float PID_calculate(PID_t *pid, float input);