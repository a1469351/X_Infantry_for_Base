#include "application_gimbalcontrol.h"

#include "stdint.h"
#include "utilities_minmax.h"
#include "drivers_canmotor_user.h"
#include "drivers_imu_user.h"
#include "application_pidfunc.h"
#include "application_setmotor.h"

//PID_INIT(Kp, Ki, Kd, KpMax, KiMax, KdMax, OutputMax)
PID_Regulator_t yawPositionPID = PID_INIT(15.0, 0.0, 0.0, 10000.0, 10000.0, 10000.0, 10000.0);
PID_Regulator_t yawSpeedPID = PID_INIT(40.0, 0.0, 0.0, 10000.0, 10000.0, 10000.0, 4900.0);
//ÔÆÌ¨Æ«ÖÃ
int16_t YawZeroEncoderBias=1075;
int16_t PitchZeroEncoderBias=3180;

void setYawWithAngle(float targetAngle){
	if(IOPool_hasNextRead(GMYAWRxIOPool, 0)){
		//TargetAngle
		MINMAX(targetAngle, YAWDOWNLIMIT, YAWUPLIMIT);
		//RealAngle
		IOPool_getNextRead(GMYAWRxIOPool, 0); 
		float realAngle = (IOPool_pGetReadData(GMYAWRxIOPool, 0)->angle - YawZeroEncoderBias) * 360 / 8192.0;
		NORMALIZE_ANGLE180(realAngle);
		//RealSpeed
		IOPool_getNextRead(IMUIOPool, 0);
		float realSpeed = -IOPool_pGetReadData(IMUIOPool, 0)->gYroZs;
		
		setMotorWithPositionSpeedPID(GMYAW, &yawPositionPID, &yawSpeedPID, targetAngle, realAngle, realSpeed);
	}
}

PID_Regulator_t pitchPositionPID = PID_INIT(15.0, 0.00, 0.0, 10000.0, 10000.0, 10000.0, 10000.0);
PID_Regulator_t pitchSpeedPID = PID_INIT(25.0, 0.0, 0.0, 10000.0, 10000.0, 10000.0, 2000.0);


void setPitchWithAngle(float targetAngle){
	if(IOPool_hasNextRead(GMPITCHRxIOPool, 0)){
		//TargetAngle
		MINMAX(targetAngle, PITCHDOWNLIMIT, PITCHUPLIMIT);
		//RealAngle
		IOPool_getNextRead(GMPITCHRxIOPool, 0); 
		float realAngle = -(IOPool_pGetReadData(GMPITCHRxIOPool, 0)->angle - PitchZeroEncoderBias) * 360 / 8192.0;
		NORMALIZE_ANGLE180(realAngle);
		//RealSpeed
		IOPool_getNextRead(IMUIOPool, 0);
		float realSpeed = -IOPool_pGetReadData(IMUIOPool, 0)->gYroXs;
		
		setMotorWithPositionSpeedPID(GMPITCH, &pitchPositionPID, &pitchSpeedPID, targetAngle, realAngle, realSpeed);
	}
}
