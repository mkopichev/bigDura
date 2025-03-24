#ifndef PWM_H_
#define PWM_H_

#include "common.h"

// radiosignal from radio receiver transfer into motors pwm

#define DEAD_ZONE_UPPER_LEVEL 3
#define DEAD_ZONE_LOWER_LEVEL -3
#define SCALE_COEF            2.5F

#define LEFT_WHEEL_FORWARD   OCR1B
#define LEFT_WHEEL_BACKWARD  OCR1A
#define RIGHT_WHEEL_FORWARD  OCR0B
#define RIGHT_WHEEL_BACKWARD OCR0A

void pwmInit(void);
void pwmGo(void);

#endif