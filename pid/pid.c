/**
 * @author Medeossi Erik
 * @date 14/02/2023
 * @link https://github.com/mede-erik/Stm32_Libraries
 * @version 0v1
 */

#include "pid.h"

void PID_init(PID_t *pid, float Kp, float Ki, float Kd, float setPoint)
{
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->setPoint = setPoint;
    pid->prevError = 0;
    pid->integral = 0;
}

float PID_calculate(PID_t *pid, float input)
{
    float error = pid->setPoint - input;
    pid->integral += error;

    if (pid->integral > MAX_INT)
        pid->integral = MAX_INT;
    else if (pid->integral < MIN_INT)
        pid->integral = MIN_INT;

    float derivative = error - pid->prevError;
    pid->prevError = error;

    return pid->Kp * error + pid->Ki * pid->integral + pid->Kd * derivative;
}
