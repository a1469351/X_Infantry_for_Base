#ifndef DRIVERS_UARTRC_USER_H
#define DRIVERS_UARTRC_USER_H

#include "utilities_iopool.h"

typedef struct{
	int16_t ch0;
	int16_t ch1;
	int16_t ch2;
	int16_t ch3;
	int8_t s1;
	int8_t s2;
}Remote_t;

typedef struct{
	int16_t x;
	int16_t y;
	int16_t z;
	uint8_t last_press_l;
	uint8_t last_press_r;
	uint8_t press_l;
	uint8_t press_r;
}Mouse_t;	

typedef struct{
	uint16_t v;
}Key_t;

typedef struct{
	Remote_t rc;
	Mouse_t mouse;
	Key_t key;
}RC_CtrlData_t; 

IOPoolDeclare(rcUartIOPool, RC_CtrlData_t);

//Bit0-----W
//Bit1-----S
//Bit2-----A
//Bit3-----D
//Bit4-----Shift
//Bit5-----Ctrl
//Bit6-----Q
//Bit7-----E
//Bit8-----R
//Bit9-----F
//Bit10-----G
//Bit11-----Z
//Bit12-----X
//Bit13-----C
//Bit14-----V
//Bit15-----B
#define KEY_W(RC_CtrlData) ((RC_CtrlData.key.v & 0x0001) >> 0)
#define KEY_S(RC_CtrlData) ((RC_CtrlData.key.v & 0x0002) >> 1)
#define KEY_A(RC_CtrlData) ((RC_CtrlData.key.v & 0x0004) >> 2)
#define KEY_D(RC_CtrlData) ((RC_CtrlData.key.v & 0x0008) >> 3)
#define KEY_SHIFT(RC_CtrlData) ((RC_CtrlData.key.v & 0x0010) >> 4)
#define KEY_CTRL(RC_CtrlData) ((RC_CtrlData.key.v & 0x0020) >> 5)
#define KEY_Q(RC_CtrlData) ((RC_CtrlData.key.v & 0x0040) >> 6)
#define KEY_E(RC_CtrlData) ((RC_CtrlData.key.v & 0x0080) >> 7)
#define KEY_R(RC_CtrlData) ((RC_CtrlData.key.v & 0x0100) >> 8)
#define KEY_F(RC_CtrlData) ((RC_CtrlData.key.v & 0x0200) >> 9)
#define KEY_G(RC_CtrlData) ((RC_CtrlData.key.v & 0x0400) >> 10)
#define KEY_Z(RC_CtrlData) ((RC_CtrlData.key.v & 0x0800) >> 11)
#define KEY_X(RC_CtrlData) ((RC_CtrlData.key.v & 0x1000) >> 12)
#define KEY_C(RC_CtrlData) ((RC_CtrlData.key.v & 0x2000) >> 13)
#define KEY_V(RC_CtrlData) ((RC_CtrlData.key.v & 0x4000) >> 14)
#define KEY_B(RC_CtrlData) ((RC_CtrlData.key.v & 0x8000) >> 15)

#endif
