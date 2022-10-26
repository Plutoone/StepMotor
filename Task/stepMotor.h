#ifndef _STEPMOTOR_H
#define _STEPMOTOR_H

#include "main.h"
#include "tim.h"

#define PULSE			6400

typedef struct _stepMotor
{
	GPIO_TypeDef dirPort;
	uint16_t dirPin;
	TIM_HandleTypeDef htim;
	uint32_t channel;
}stepMotor_t;


extern stepMotor_t stepMotor;

void stepMotorInit(void);
void moveAngle(stepMotor_t *motor, int32_t angle);
void moveSpeed(stepMotor_t *motor, int32_t speed);
int ABS(int32_t num);

#endif

