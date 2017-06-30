#include "application_chassiscontrol.h"

#include "utilities_debug.h"

#include "utilities_minmax.h"
#include "drivers_canmotor_user.h"
#include "application_pidfunc.h"
#include "application_setmotor.h"

void setCMFLWithSpeed(float targetSpeed);
void setCMFRWithSpeed(float targetSpeed);
void setCMBLWithSpeed(float targetSpeed);
void setCMBRWithSpeed(float targetSpeed);

PID_Regulator_t CMFLPositionPID = PID_INIT(100.0, 0.0, 0.0, 1000000.0, 1000000.0, 1000000.0, 1000000.0);
PID_Regulator_t CMFRPositionPID = PID_INIT(100.0, 0.0, 0.0, 1000000.0, 1000000.0, 1000000.0, 1000000.0);
PID_Regulator_t CMBLPositionPID = PID_INIT(100.0, 0.0, 0.0, 1000000.0, 1000000.0, 1000000.0, 1000000.0);
PID_Regulator_t CMBRPositionPID = PID_INIT(100.0, 0.0, 0.0, 1000000.0, 1000000.0, 1000000.0, 1000000.0);

PID_Regulator_t CMFLSpeedPID = PID_INIT(1.0, 0.0, 0.0, 10000.0, 10000.0, 10000.0, 4900.0);
PID_Regulator_t CMFRSpeedPID = PID_INIT(1.0, 0.0, 0.0, 10000.0, 10000.0, 10000.0, 4900.0);
PID_Regulator_t CMBLSpeedPID = PID_INIT(1.0, 0.0, 0.0, 10000.0, 10000.0, 10000.0, 4900.0);
PID_Regulator_t CMBRSpeedPID = PID_INIT(1.0, 0.0, 0.0, 10000.0, 10000.0, 10000.0, 4900.0);

//FrontBackSpeed -1000~1000
//LeftRightSpeed -1000~1000
//RotateSpeed -1000~1000 顺时针为正 clockwise+
//电机转向，使车底盘顺时针旋转为正
void setChassisWithSpeed(float FrontBackSpeed, float LeftRightSpeed, float RotateSpeed){
//	FrontBackSpeed = 0;
//	LeftRightSpeed = 2000;
//	RotateSpeed = 0;
	float flSpeed = FrontBackSpeed + LeftRightSpeed + RotateSpeed;
	float frSpeed = -FrontBackSpeed + LeftRightSpeed + RotateSpeed;
	float blSpeed = FrontBackSpeed - LeftRightSpeed + RotateSpeed;
	float brSpeed = -FrontBackSpeed - LeftRightSpeed + RotateSpeed;
	setCMFLWithSpeed(-flSpeed);
	setCMFRWithSpeed(-frSpeed);
	setCMBLWithSpeed(-blSpeed);
	setCMBRWithSpeed(-brSpeed);
	
//	setCMFLWithSpeed(2000);
//	setCMFRWithSpeed(-2000);
//	setCMBLWithSpeed(2000);
//	setCMBRWithSpeed(-2000);
}

void setCMFLWithSpeed(float targetSpeed){
	if(IOPool_hasNextRead(CMFLRxIOPool, 0)){
		//TargetSpeed
		//MINMAX(targetSpeed, LIMIT, LIMIT);
		//RealSpeed
		IOPool_getNextRead(CMFLRxIOPool, 0);
		float realSpeed = (IOPool_pGetReadData(CMFLRxIOPool, 0)->RotateSpeed) * 6;//度每秒(* 360 / 60.0)
		setMotorWithSpeedPID(CMFL, &CMFLSpeedPID, targetSpeed, realSpeed);
	}
}

void setCMFRWithSpeed(float targetSpeed){
	if(IOPool_hasNextRead(CMFRRxIOPool, 0)){
		//TargetSpeed
		//MINMAX(targetSpeed, LIMIT, LIMIT);
		//RealSpeed
		IOPool_getNextRead(CMFRRxIOPool, 0);
		float realSpeed = (IOPool_pGetReadData(CMFRRxIOPool, 0)->RotateSpeed) * 6;//度每秒(* 360 / 60.0)
		setMotorWithSpeedPID(CMFR, &CMFRSpeedPID, targetSpeed, realSpeed);
	}
}

void setCMBLWithSpeed(float targetSpeed){
	if(IOPool_hasNextRead(CMBLRxIOPool, 0)){
		//TargetSpeed
		//MINMAX(targetSpeed, LIMIT, LIMIT);
		//RealSpeed
		IOPool_getNextRead(CMBLRxIOPool, 0);
		float realSpeed = (IOPool_pGetReadData(CMBLRxIOPool, 0)->RotateSpeed) * 6;//度每秒(* 360 / 60.0)
		setMotorWithSpeedPID(CMBL, &CMBLSpeedPID, targetSpeed, realSpeed);
	}
}

void setCMBRWithSpeed(float targetSpeed){
	if(IOPool_hasNextRead(CMBRRxIOPool, 0)){
		//TargetSpeed
		//MINMAX(targetSpeed, LIMIT, LIMIT);
		//RealSpeed
		IOPool_getNextRead(CMBRRxIOPool, 0);
		float realSpeed = (IOPool_pGetReadData(CMBRRxIOPool, 0)->RotateSpeed) * 6;//度每秒(* 360 / 60.0)
		setMotorWithSpeedPID(CMBR, &CMBRSpeedPID, targetSpeed, realSpeed);
	}
}
