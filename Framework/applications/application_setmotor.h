#ifndef APPLICATION_SETMOTOR_H
#define APPLICATION_SETMOTOR_H

#include "stdint.h"
#include "application_pidfunc.h"

typedef enum {CMFL, CMFR, CMBL, CMBR, GMYAW, GMPITCH, AM1UDFL, AM1UDFR, AM1UDBL, AM1UDBR, AM2PLATE, AM2GETBULLET} MotorId;

int16_t setMotorWithSpeedPID(
	MotorId motorId, 
	PID_Regulator_t *speedPID,
	float targetSpeed, 
	float feedbackSpeed
);
int16_t setMotorWithPositionSpeedPID(
	MotorId motorId, 
	PID_Regulator_t *positionPID,
	PID_Regulator_t *speedPID,
	float targetPostion, 
	float feedbackPostion, 
	float feedbackSpeed
);
void setMotor(MotorId motorId, int16_t Intensity);

#endif
