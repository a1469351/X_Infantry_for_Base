#include "drivers_plate_motor.h"
#include "stdint.h"
#include "gpio.h"
#include "cmsis_os.h"
#include "utilities_tim.h"
#include "utilities_debug.h"

#define plate_motor_encoder_pin   GPIO_PIN_0
#define plate_motor_encoder_gpio   GPIOF

////---------------拨盘电机的脉冲反馈程序
uint32_t encoder_cnt=0;
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//	if(GPIO_Pin==plate_motor_encoder_pin)
//	{
//		if(HAL_GPIO_ReadPin(plate_motor_encoder_gpio,plate_motor_encoder_pin)==GPIO_PIN_SET)
//		{
//			++encoder_cnt;
//		}
//	}
//}

//------------------Task
void plate_motor_task()
{
	while(1)
	{
		osDelay(250);
	}
}