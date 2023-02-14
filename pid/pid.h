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