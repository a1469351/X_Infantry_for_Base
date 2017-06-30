#ifndef DRIVERS_UARTUPPER_USER_H
#define DRIVERS_UARTUPPER_USER_H

#include "utilities_iopool.h"

IOPoolDeclare(ctrlUartIOPool, struct{uint8_t ch[10];});


#define REC_LEN            1024
#define RX_DONE           (RX_STA&0x8000)
#define RX_LEN	  			   (RX_STA&0x3f)

extern uint8_t buf[REC_LEN];
extern uint16_t RX_STA;
#endif
