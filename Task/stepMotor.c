#include "stepMotor.h"


stepMotor_t stepMotor;

void stepMotorInit(void)
{
	stepMotor.dirPort = *GPIOD;
	stepMotor.dirPin = GPIO_PIN_2;
	stepMotor.htim = htim1;
	stepMotor.channel = TIM_CHANNEL_2;
}


void moveAngle(stepMotor_t *motor, int32_t angle)
{
	if(angle > 0)
		HAL_GPIO_WritePin(&motor->dirPort, motor->dirPin, GPIO_PIN_RESET);
	else
		LED1_OFF;
	
	angle = ABS(angle);
	
	if(Pulse_num >= angle*6400/360)		// 第3200次（一圈）
	{
		Pulse_num = 0;
		HAL_TIM_PWM_Stop_IT(&motor->htim, motor->channel);		// 停止输出PWM
	}
}

void moveSpeed(stepMotor_t *motor, int32_t speed)
{
	uint32_t prescaler;
	if(speed > 0)
		HAL_GPIO_WritePin(&motor->dirPort, motor->dirPin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(&motor->dirPort, motor->dirPin, GPIO_PIN_RESET);	
	
	speed = ABS(speed);
	prescaler = 45*30/speed - 0;
	
	HAL_TIM_PWM_Stop_IT(&motor->htim, motor->channel);
	
	motor->htim.Init.Prescaler = prescaler-1;
	TIM_Base_SetConfig(motor->htim.Instance, &motor->htim.Init);
	
	HAL_TIM_PWM_Start_IT(&motor->htim, motor->channel);
	__HAL_TIM_SetCompare(&motor->htim, motor->channel, 250);
	
}

int ABS(int32_t num)
{
	if((num) > 0)
		num = num;
	else
		num = -num;
	return num;
}
