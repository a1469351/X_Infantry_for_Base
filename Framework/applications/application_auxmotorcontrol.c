#include "application_auxmotorcontrol.h"

#include "drivers_canmotor_user.h"
#include "application_pidfunc.h"
#include "application_setmotor.h"

PID_Regulator_t platePositionPID = PID_INIT(40.0, 0.0, 0.0, 1000000.0, 1000000.0, 1000000.0, 1000000.0);
PID_Regulator_t plateSpeedPID = PID_INIT(1.0, 0.0, 0.0, 10000.0, 10000.0, 10000.0, 4900.0);//0.0, 0.00003

PID_Regulator_t getBulletPositionPID = PID_INIT(6.0, 0.0, 0.0, 1000000.0, 1000000.0, 1000000.0, 1000000.0);
PID_Regulator_t getBulletSpeedPID = PID_INIT(1.0, 0.0, 0.0, 10000.0, 10000.0, 10000.0, 4900.0);//0.0, 0.00003

PID_Regulator_t UDFLPositionPID = PID_INIT(60.0, 0.0, 0.0, 1000000.0, 1000000.0, 1000000.0, 1000000.0);
PID_Regulator_t UDFLSpeedPID = PID_INIT(1.0, 0.0, 0.0, 10000.0, 10000.0, 10000.0, 8000.0);
PID_Regulator_t UDFRPositionPID = PID_INIT(60.0, 0.0, 0.0, 1000000.0, 1000000.0, 1000000.0, 1000000.0);
PID_Regulator_t UDFRSpeedPID = PID_INIT(1.0, 0.0, 0.0, 10000.0, 10000.0, 10000.0, 8000.0);
PID_Regulator_t UDBLPositionPID = PID_INIT(60.0, 0.0, 0.0, 1000000.0, 1000000.0, 1000000.0, 1000000.0);
PID_Regulator_t UDBLSpeedPID = PID_INIT(1.0, 0.0, 0.0, 10000.0, 10000.0, 10000.0, 8000.0);
PID_Regulator_t UDBRPositionPID = PID_INIT(60.0, 0.0, 0.0, 1000000.0, 1000000.0, 1000000.0, 1000000.0);
PID_Regulator_t UDBRSpeedPID = PID_INIT(1.0, 0.0, 0.0, 10000.0, 10000.0, 10000.0, 8000.0);

void setPlateWithAngle(float targetAngle){//360.0 * 12 * 2
	if(IOPool_hasNextRead(AMPLATERxIOPool, 0)){
		//TargetAngle
		//float targetAngle
		//RealAngle
		IOPool_getNextRead(AMPLATERxIOPool, 0);
		static float realAngle = 0.0;
		static float realAngleLast = 0.0;
		float realAngleCurr = (IOPool_pGetReadData(AMPLATERxIOPool, 0)->angle) * 360 / 8192.0;
		if(realAngleCurr - realAngleLast > 180){
			realAngle += realAngleCurr - 360 - realAngleLast;
		}else if(realAngleCurr - realAngleLast < -180){
			realAngle += realAngleCurr + 360 - realAngleLast;
		}else{
			realAngle += realAngleCurr - realAngleLast;
		}
		realAngle = realAngleCurr;
		//RealSpeed
		float realSpeed = (IOPool_pGetReadData(AMPLATERxIOPool, 0)->RotateSpeed) * 6;//度每秒(* 360 / 60.0)

		setMotorWithPositionSpeedPID(AM2PLATE, &platePositionPID, &plateSpeedPID, targetAngle, realAngle, realSpeed);
	}
}

void setGetBulletWithAngle(float targetAngle){//360.0 * 36 * 2;
	if(IOPool_hasNextRead(AMGETBULLETRxIOPool, 0)){
		//TargetAngle
		//float targetAngle
		//RealAngle
		IOPool_getNextRead(AMGETBULLETRxIOPool, 0);
		static float realAngle = 0.0;
		static float realAngleLast = 0.0;
		float realAngleCurr = (IOPool_pGetReadData(AMGETBULLETRxIOPool, 0)->angle) * 360 / 8192.0;
		if(realAngleCurr - realAngleLast > 180){
			realAngle += realAngleCurr - 360 - realAngleLast;
		}else if(realAngleCurr - realAngleLast < -180){
			realAngle += realAngleCurr + 360 - realAngleLast;
		}else{
			realAngle += realAngleCurr - realAngleLast;
		}
		realAngle = realAngleCurr;
		//RealSpeed
		float realSpeed = (IOPool_pGetReadData(AMGETBULLETRxIOPool, 0)->RotateSpeed) * 6;//度每秒(* 360 / 60.0)

		setMotorWithPositionSpeedPID(AM2GETBULLET, &getBulletPositionPID, &getBulletSpeedPID, targetAngle, realAngle, realSpeed);
	}
}

void setUpDownWithAngle(float UPFLTargetAngle, float UPFRTargetAngle, float UPBLTargetAngle, float UPBRTargetAngle){
	if(IOPool_hasNextRead(AMUDFLRxIOPool, 0)){
		//TargetAngle
		//float targetAngle
		//RealAngle
		IOPool_getNextRead(AMUDFLRxIOPool, 0);
		static float realAngle = 0.0;
		static float realAngleLast = 0.0;
		float realAngleCurr = (IOPool_pGetReadData(AMUDFLRxIOPool, 0)->angle) * 360 / 8192.0;
		if(realAngleCurr - realAngleLast > 180){
			realAngle += realAngleCurr - 360 - realAngleLast;
		}else if(realAngleCurr - realAngleLast < -180){
			realAngle += realAngleCurr + 360 - realAngleLast;
		}else{
			realAngle += realAngleCurr - realAngleLast;
		}
		realAngle = realAngleCurr;
		//RealSpeed
		float realSpeed = (IOPool_pGetReadData(AMUDFLRxIOPool, 0)->RotateSpeed) * 6;//度每秒(* 360 / 60.0)

		setMotorWithPositionSpeedPID(AM1UDFL, &UDFLPositionPID, &UDFLSpeedPID, UPFLTargetAngle, realAngle, realSpeed);
	}
	if(IOPool_hasNextRead(AMUDFRRxIOPool, 0)){
		//TargetAngle
		//float targetAngle
		//RealAngle
		IOPool_getNextRead(AMUDFRRxIOPool, 0);
		static float realAngle = 0.0;
		static float realAngleLast = 0.0;
		float realAngleCurr = (IOPool_pGetReadData(AMUDFRRxIOPool, 0)->angle) * 360 / 8192.0;
		if(realAngleCurr - realAngleLast > 180){
			realAngle += realAngleCurr - 360 - realAngleLast;
		}else if(realAngleCurr - realAngleLast < -180){
			realAngle += realAngleCurr + 360 - realAngleLast;
		}else{
			realAngle += realAngleCurr - realAngleLast;
		}
		realAngle = realAngleCurr;
		//RealSpeed
		float realSpeed = (IOPool_pGetReadData(AMUDFRRxIOPool, 0)->RotateSpeed) * 6;//度每秒(* 360 / 60.0)

		setMotorWithPositionSpeedPID(AM1UDFR, &UDFRPositionPID, &UDFRSpeedPID, UPFRTargetAngle, realAngle, realSpeed);
	}
	if(IOPool_hasNextRead(AMUDBLRxIOPool, 0)){
		//TargetAngle
		//float targetAngle
		//RealAngle
		IOPool_getNextRead(AMUDBLRxIOPool, 0);
		static float realAngle = 0.0;
		static float realAngleLast = 0.0;
		float realAngleCurr = (IOPool_pGetReadData(AMUDBLRxIOPool, 0)->angle) * 360 / 8192.0;
		if(realAngleCurr - realAngleLast > 180){
			realAngle += realAngleCurr - 360 - realAngleLast;
		}else if(realAngleCurr - realAngleLast < -180){
			realAngle += realAngleCurr + 360 - realAngleLast;
		}else{
			realAngle += realAngleCurr - realAngleLast;
		}
		realAngle = realAngleCurr;
		//RealSpeed
		float realSpeed = (IOPool_pGetReadData(AMUDBLRxIOPool, 0)->RotateSpeed) * 6;//度每秒(* 360 / 60.0)

		setMotorWithPositionSpeedPID(AM1UDBL, &UDBLPositionPID, &UDBLSpeedPID, UPBLTargetAngle, realAngle, realSpeed);
	}
	if(IOPool_hasNextRead(AMUDBRRxIOPool, 0)){
		//TargetAngle
		//float targetAngle
		//RealAngle
		IOPool_getNextRead(AMUDBRRxIOPool, 0);
		static float realAngle = 0.0;
		static float realAngleLast = 0.0;
		float realAngleCurr = (IOPool_pGetReadData(AMUDBRRxIOPool, 0)->angle) * 360 / 8192.0;
		if(realAngleCurr - realAngleLast > 180){
			realAngle += realAngleCurr - 360 - realAngleLast;
		}else if(realAngleCurr - realAngleLast < -180){
			realAngle += realAngleCurr + 360 - realAngleLast;
		}else{
			realAngle += realAngleCurr - realAngleLast;
		}
		realAngle = realAngleCurr;
		//RealSpeed
		float realSpeed = (IOPool_pGetReadData(AMUDBRRxIOPool, 0)->RotateSpeed) * 6;//度每秒(* 360 / 60.0)

		setMotorWithPositionSpeedPID(AM1UDBR, &UDBRPositionPID, &UDBRSpeedPID, UPBRTargetAngle, realAngle, realSpeed);
	}
}
