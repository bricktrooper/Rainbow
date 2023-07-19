#ifndef PWM_H
#define PWM_H

#include "types.h"

#define PWM_MAX   UINT8_MAX

typedef enum PWM_Channel PWM_Channel;

enum PWM_Channel
{
	PWM3,
	PWM4,
	PWM5
};

void pwm_initialize(void);                      // initialize PWM
void pwm_duty(PWM_Channel channel, U8 value);   // set duty cycle of PWM channel

#endif /* PWM_H */
