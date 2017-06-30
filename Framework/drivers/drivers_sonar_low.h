#ifndef DRIVERS_SONAR_LOW_H
#define DRIVERS_SONAR_LOW_H
#include "stdint.h"

void SonarCallbask(uint16_t GPIO_Pin);
void sonarTask(void const * argument);

#endif
