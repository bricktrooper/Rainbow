#ifndef PWM_H
#define PWM_H

#include "types.h"

enum PWM_Channel
{
	PWM3,
	PWM4,
	PWM5
};

typedef enum PWM_Channel PWM_Channel;

void pwm_initialize(void);
void pwm_duty(PWM_Channel channel, U8 value);

#endif /* PWM_H */
