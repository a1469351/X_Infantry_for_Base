#ifndef DRIVERS_IMU_USER_H
#define DRIVERS_IMU_USER_H

#include "utilities_iopool.h"
typedef struct{
	float gYroXs;
	float gYroYs;
	float gYroZs;
}IMUData_t;

IOPoolDeclare(IMUIOPool, IMUData_t);

#endif
