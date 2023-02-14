/**
 * @author Medeossi Erik
 * @date 14/02/2023
 * @link https://github.com/mede-erik/Stm32_Libraries
 * @version 0v1
 */

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

void PID_init(PID_t *pid, float Kp, float Ki, float Kd, float setPoint);

float PID_calculate(PID_t *pid, float input);