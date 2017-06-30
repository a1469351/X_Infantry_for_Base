#include "application_setmotor.h"

#include "can.h"
#include "drivers_canmotor_user.h"
#include "rtos_semaphore.h"
#include "utilities_debug.h"

#include "config_motor.h"

int16_t setMotorWithSpeedPID(
	MotorId motorId, 
	PID_Regulator_t *speedPID,
	float targetSpeed, 
	float feedbackSpeed
){
	speedPID->target = targetSpeed;
	speedPID->feedback = feedbackSpeed;
	speedPID->Calc(speedPID);
	setMotor(motorId, (int16_t)speedPID->output);
	return (int16_t)speedPID->output;
}

int16_t setMotorWithPositionSpeedPID(
	MotorId motorId, 
	PID_Regulator_t *positionPID,
	PID_Regulator_t *speedPID,
	float targetPostion, 
	float feedbackPostion, 
	float feedbackSpeed
){
	positionPID->target = targetPostion;
	positionPID->feedback = feedbackPostion;	
	positionPID->Calc(positionPID);

	speedPID->target = positionPID->output;
	speedPID->feedback = feedbackSpeed;
	speedPID->Calc(speedPID);
		
	setMotor(motorId, (int16_t)speedPID->output);
	return (int16_t)speedPID->output;
}

void setMotor(MotorId motorId, int16_t Intensity){
	static int16_t CMFLIntensity = 0, CMFRIntensity = 0, CMBLIntensity = 0, CMBRIntensity = 0;
	static int8_t CMReady = 0;
	
	static int16_t GMYAWIntensity = 0, GMPITCHIntensity = 0;
	static int8_t GMReady = 0;
	
	static int16_t AM1UDFLIntensity = 0, AM1UDFRIntensity = 0, AM1UDBLIntensity = 0, AM1UDBRIntensity = 0;
	static int8_t AM1Ready = 0;
	
	static int16_t AM2PLATEIntensity = 0, AM2GETBULLETIntensity = 0;
	static int8_t AM2Ready = 0;
	
	switch(motorId){
		case CMFL:
			if(CMReady & 0x1){CMReady = 0xF;}else{CMReady |= 0x1;}
			CMFLIntensity = CMFL_DIR * Intensity;break;
		case CMFR:
			if(CMReady & 0x2){CMReady = 0xF;}else{CMReady |= 0x2;}
			CMFRIntensity = CMFR_DIR * Intensity;break;
		case CMBL:
			if(CMReady & 0x4){CMReady = 0xF;}else{CMReady |= 0x4;}
			CMBLIntensity = CMBL_DIR * Intensity;break;
		case CMBR:
			if(CMReady & 0x8){CMReady = 0xF;}else{CMReady |= 0x8;}
			CMBRIntensity = CMBR_DIR * Intensity;break;
		
		case GMYAW:
			if(GMReady & 0x1){GMReady = 0x3;}else{GMReady |= 0x1;}
			GMYAWIntensity = GMYAW_DIR * Intensity;break;
		case GMPITCH:
			if(GMReady & 0x2){GMReady = 0x3;}else{GMReady |= 0x2;}
			GMPITCHIntensity = GMPITCH_DIR * Intensity;break;
			
		case AM1UDFL:
			if(AM1Ready & 0x1){AM1Ready = 0xF;}else{AM1Ready |= 0x1;}
			AM1UDFLIntensity = AMUDFL_DIR * Intensity;break;
		case AM1UDFR:
			if(AM1Ready & 0x2){AM1Ready = 0xF;}else{AM1Ready |= 0x2;}
			AM1UDFRIntensity = AMUDFR_DIR * Intensity;break;
		case AM1UDBL:
			if(AM1Ready & 0x4){AM1Ready = 0xF;}else{AM1Ready |= 0x4;}
			AM1UDBLIntensity = AMUDBL_DIR * Intensity;break;
		case AM1UDBR:
			if(AM1Ready & 0x8){AM1Ready = 0xF;}else{AM1Ready |= 0x8;}
			AM1UDBRIntensity = AMUDBR_DIR * Intensity;break;
			
		case AM2PLATE:
			if(AM2Ready & 0x1){AM2Ready = 0x3;}else{AM2Ready |= 0x1;}
			AM2PLATEIntensity = AMPLATE_DIR * Intensity;break;
		case AM2GETBULLET:
			if(AM2Ready & 0x2){AM2Ready = 0x3;}else{AM2Ready |= 0x2;}
			AM2GETBULLETIntensity = AMGETBULLET_DIR * Intensity;break;
		default:
			fw_Error_Handler();
	}
	
	if(CMReady == 0xF){
		CanTxMsgTypeDef *pData = IOPool_pGetWriteData(CMTxIOPool);
		//pData->StdId = CM_TXID;
		pData->Data[0] = (uint8_t)(CMFRIntensity >> 8);//CMFLIntensity
		pData->Data[1] = (uint8_t)CMFRIntensity;//CMFLIntensity
		pData->Data[2] = (uint8_t)(CMFLIntensity >> 8);//CMFRIntensity
		pData->Data[3] = (uint8_t)CMFLIntensity;//CMFRIntensity
		pData->Data[4] = (uint8_t)(CMBLIntensity >> 8);
		pData->Data[5] = (uint8_t)CMBLIntensity;
		pData->Data[6] = (uint8_t)(CMBRIntensity >> 8);
		pData->Data[7] = (uint8_t)CMBRIntensity;
		IOPool_getNextWrite(CMTxIOPool);
		CMReady = 0;
		CMFLIntensity = CMFRIntensity = CMBLIntensity = CMBRIntensity = 0;
		if(osSemaphoreRelease(CMGMCanHaveTransmitSemaphoreHandle) == osErrorOS){
			fw_Warning();
		}
	}
	
	if(GMReady == 0x3){
		CanTxMsgTypeDef *pData = IOPool_pGetWriteData(GMTxIOPool);
		//pData->StdId = GM_TXID;
		pData->Data[0] = (uint8_t)(GMYAWIntensity >> 8);
		pData->Data[1] = (uint8_t)GMYAWIntensity;
		pData->Data[2] = (uint8_t)(GMPITCHIntensity >> 8);
		pData->Data[3] = (uint8_t)GMPITCHIntensity;
		pData->Data[4] = 0;
		pData->Data[5] = 0;
		pData->Data[6] = 0;
		pData->Data[7] = 0;
		IOPool_getNextWrite(GMTxIOPool);
		GMReady = 0;
		GMYAWIntensity = GMPITCHIntensity = 0;
		if(osSemaphoreRelease(CMGMCanHaveTransmitSemaphoreHandle) == osErrorOS){
			fw_Warning();
		}
	}
	
	if(AM1Ready == 0xF){
		CanTxMsgTypeDef *pData = IOPool_pGetWriteData(AM1TxIOPool);
		//pData->StdId = AM1_TXID;
		pData->Data[0] = (uint8_t)(AM1UDFLIntensity >> 8);
		pData->Data[1] = (uint8_t)AM1UDFLIntensity;
		pData->Data[2] = (uint8_t)(AM1UDFRIntensity >> 8);
		pData->Data[3] = (uint8_t)AM1UDFRIntensity;
		pData->Data[4] = (uint8_t)(AM1UDBLIntensity >> 8);
		pData->Data[5] = (uint8_t)AM1UDBLIntensity;
		pData->Data[6] = (uint8_t)(AM1UDBRIntensity >> 8);
		pData->Data[7] = (uint8_t)AM1UDBRIntensity;
		IOPool_getNextWrite(AM1TxIOPool);
		AM1Ready = 0;
		AM1UDFLIntensity = AM1UDFRIntensity = AM1UDBLIntensity = AM1UDBRIntensity = 0;
		if(osSemaphoreRelease(AMCanHaveTransmitSemaphoreHandle) == osErrorOS){
			fw_Warning();
		}
	}
	
	if(AM2Ready == 0x3){
		CanTxMsgTypeDef *pData = IOPool_pGetWriteData(AM2TxIOPool);
		//pData->StdId = AM2_TXID;
		pData->Data[0] = (uint8_t)(AM2PLATEIntensity >> 8);
		pData->Data[1] = (uint8_t)AM2PLATEIntensity;
		pData->Data[2] = (uint8_t)(AM2GETBULLETIntensity >> 8);
		pData->Data[3] = (uint8_t)AM2GETBULLETIntensity;
		pData->Data[4] = 0;
		pData->Data[5] = 0;
		pData->Data[6] = 0;
		pData->Data[7] = 0;
		IOPool_getNextWrite(AM2TxIOPool);
		AM2Ready = 0;
		AM2PLATEIntensity = AM2GETBULLETIntensity = 0;
		if(osSemaphoreRelease(AMCanHaveTransmitSemaphoreHandle) == osErrorOS){}
	}
	
}
