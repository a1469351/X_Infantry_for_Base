#ifndef TASKS_MOTOR_H
#define TASKS_MOTOR_H
#include "stdint.h"


extern uint8_t GM_RUN;

void CMGMControlTask(void const * argument);
void AMControlTask(void const * argument);

#endif
