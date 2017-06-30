#include "tasks_motor.h"
#include "drivers_canmotor_user.h"
#include "rtos_semaphore.h"

#include "utilities_debug.h"
#include "tasks_upper.h"
#include "drivers_led_user.h"
#include "utilities_minmax.h"
#include "drivers_uartrc_user.h"
#include "drivers_sonar_user.h"
#include "drivers_imu_user.h"
#include "application_pidfunc.h"
#include "application_setmotor.h"
#include "application_gimbalcontrol.h"
#include "application_chassiscontrol.h"

#include "stdint.h"


extern float ZGyroModuleAngle;
extern float angles[3];
// 置1的时候云台才开始控制，置0不控制
uint8_t GM_RUN=0;
// 英雄的升降
int8_t flUpDown = 0, frUpDown = 0, blUpDown = 0, brUpDown = 0, allUpDown = 0;
float yawAngleTarget = 0.0;
float pitchAngleTarget = 0.0;
float FrontBackSpeedTarget = 0.0;
float LeftRightSpeedTarget = 0.0;
float RotateSpeedTarget = 0;
uint8_t sk,s;
uint16_t as;
void CMGMControlTask(void const * argument){
	while(1){
		//osSemaphoreWait(imurefreshGimbalSemaphoreHandle, osWaitForever);
		osSemaphoreWait(CMGMCanRefreshSemaphoreHandle, osWaitForever);

		
		
		if(IOPool_hasNextRead(upperIOPool, 0)){
			IOPool_getNextRead(upperIOPool, 0);
			yawAngleTarget += IOPool_pGetReadData(upperIOPool, 0)->yawAdd;
			pitchAngleTarget += IOPool_pGetReadData(upperIOPool, 0)->pitchAdd;
		}
		if(IOPool_hasNextRead(rcUartIOPool, 0)){
			IOPool_getNextRead(rcUartIOPool, 0);
			yawAngleTarget = (IOPool_pGetReadData(rcUartIOPool, 0)->rc.ch2 - 1024) / 660.0 * 45;
			pitchAngleTarget = -(IOPool_pGetReadData(rcUartIOPool, 0)->rc.ch3 - 1024) / 660.0 * 25;
			//fw_printfln("rc.ch2 %d", IOPool_pGetReadData(rcUartIOPool, 0)->rc.ch2);
			s=IOPool_pGetReadData(rcUartIOPool, 0)->rc.s2;
			as = IOPool_pGetReadData(rcUartIOPool, 0)->rc.ch3;
					
			FrontBackSpeedTarget = (IOPool_pGetReadData(rcUartIOPool, 0)->rc.ch1 - 1024) / 660.0 * 10000;
			LeftRightSpeedTarget = -(IOPool_pGetReadData(rcUartIOPool, 0)->rc.ch0 - 1024) / 660.0 * 10000;
			RotateSpeedTarget = -(IOPool_pGetReadData(rcUartIOPool,0)->rc.ch2 - 1024) / 660.0 * 10000;
		}
		if(GM_RUN)
		{
			setYawWithAngle(yawAngleTarget);
			setPitchWithAngle(pitchAngleTarget);
		}
		
			
		if(s == 1)setChassisWithSpeed(FrontBackSpeedTarget, LeftRightSpeedTarget, RotateSpeedTarget);
		
//		static int countwhile1 = 0;
//		if(countwhile1 > 300){
//			countwhile1 = 0;
//			fw_printfln("angles %f %f %f", angles[0], angles[1], angles[2]);
//		}else{
//			countwhile1++;
//		}	
		
		static int countwhile = 0;
		if(countwhile >= 300){
			countwhile = 0;
//			if(forPidDebug == 1){
//				fw_printf("yIoc = %d\t", yIoutCount);
//				fw_printf("pIoc = %d\t", pIoutCount);
//				fw_printf("count = %d\t", totalCount);
//				yIoutCount = 0, pIoutCount = 0, totalCount = 0;
				
//				fw_printf("ya = %d\t", yawAngle);
//				fw_printf("yra = %f\t", yawRealAngle);
//				fw_printf("yI = %5d\t", yawIntensity);
//				fw_printf("gYroZ = %f\t", gYroZ);
//				
//				fw_printf("pa = %d\t", pitchAngle);
//				fw_printf("pra = %f\t", pitchRealAngle);
//				fw_printf("pitI = %5d\t", pitchIntensity);
//				fw_printf("gYroY = %f \r\n", gYroY);
//			}
		}else{
			countwhile++;
		}		
		
	}
}

void AMControlTask(void const * argument){
	while(1){
		osSemaphoreWait(AMCanRefreshSemaphoreHandle, osWaitForever);
//		ZGyroReset();
//		static int countWhileZGyro = 0;
//		if(countWhileZGyro > 500){
//			countWhileZGyro = 0;
//			//fw_printfln("yawIntensity %d", yawIntensity);
//			fw_printfln("ZGyroModuleAngle %f", ZGyroModuleAngle);
//		}else{
//			countWhileZGyro++;
//		}
	}
}
