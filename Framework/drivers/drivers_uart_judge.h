#ifndef DRIVERS_UART_JUDGE_H
#define DRIVERS_UART_JUDGE_H
#include "stdint.h"


typedef __packed struct 
{
    uint8_t flag;
    float x;
    float y;
    float z;
    float compass;
}tLocData;

typedef __packed struct 
{
    uint32_t remainTime;
    uint16_t remainLifeValue;
    float realChassisOutV;
    float realChassisOutA;
    tLocData locData;
    float remainPower;
}tGameInfo;

void judgeUartRxCpltCallback();
void judgeUartInit();
void judge_process_data(uint8_t data);
#endif
