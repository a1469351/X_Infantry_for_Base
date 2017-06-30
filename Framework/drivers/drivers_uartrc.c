#include "drivers_uartrc_user.h"
#include "drivers_uartrc_low.h"
#include "drivers_led_user.h"
#include "usart.h"

#include "peripheral_define.h"

NaiveIOPoolDefine(rcUartIOPool, {0});

uint8_t RC_Data_ch[18];

void rcInit(){
	//遥控器DMA接收开启(一次接收18个字节)
	if(HAL_UART_Receive_DMA(&RC_UART, RC_Data_ch, 18) != HAL_OK){
			Error_Handler();
	} 
}

void rcUartRxCpltCallback(){
	//osStatus osMessagePut (osMessageQId queue_id, uint32_t info, uint32_t millisec);
	RC_CtrlData_t *pRC_CtrlData = IOPool_pGetWriteData(rcUartIOPool);
	
	pRC_CtrlData->rc.ch0 = ((int16_t)RC_Data_ch[0] | ((int16_t)RC_Data_ch[1] << 8)) & 0x07FF; 
	pRC_CtrlData->rc.ch1 = (((int16_t)RC_Data_ch[1] >> 3) | ((int16_t)RC_Data_ch[2] << 5)) & 0x07FF;
	pRC_CtrlData->rc.ch2 = (((int16_t)RC_Data_ch[2] >> 6) | ((int16_t)RC_Data_ch[3] << 2) |
											 ((int16_t)RC_Data_ch[4] << 10)) & 0x07FF;
	pRC_CtrlData->rc.ch3 = (((int16_t)RC_Data_ch[4] >> 1) | ((int16_t)RC_Data_ch[5]<<7)) & 0x07FF;
	
	pRC_CtrlData->rc.s1 = ((RC_Data_ch[5] >> 4) & 0x000C) >> 2;
	pRC_CtrlData->rc.s2 = ((RC_Data_ch[5] >> 4) & 0x0003);

	pRC_CtrlData->mouse.x = ((int16_t)RC_Data_ch[6]) | ((int16_t)RC_Data_ch[7] << 8);
	pRC_CtrlData->mouse.y = ((int16_t)RC_Data_ch[8]) | ((int16_t)RC_Data_ch[9] << 8);
	pRC_CtrlData->mouse.z = ((int16_t)RC_Data_ch[10]) | ((int16_t)RC_Data_ch[11] << 8);    

	pRC_CtrlData->mouse.press_l = RC_Data_ch[12];
	pRC_CtrlData->mouse.press_r = RC_Data_ch[13];

	pRC_CtrlData->key.v = ((int16_t)RC_Data_ch[14]);// | ((int16_t)pData[15] << 8);
	IOPool_getNextWrite(rcUartIOPool);
	HAL_UART_Receive_DMA(&RC_UART, RC_Data_ch, 18);
}

//typedef union
//{
//  struct
//  { 
//    struct
//    { 
//      uint16_t ch0:11;
//      uint16_t ch1:11;
//      uint16_t ch2:11;
//      uint16_t ch3:11;
//      uint8_t  s1:2;
//      uint8_t  s2:2;
//    }rc;
//    struct
//    {
//      int16_t x;
//      int16_t y;
//      int16_t z;
//      uint8_t press_l;
//      uint8_t press_r;
//    }mouse;
//    struct
//    {
//      uint16_t v;
//    }key;
//  };
//  uint8_t buf[18];
//}RC_Ctl_t;
