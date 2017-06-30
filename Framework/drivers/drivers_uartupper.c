#include "drivers_uartupper_low.h"
#include "drivers_uartupper_user.h"

#include "peripheral_define.h"

#include "usart.h"

NaiveIOPoolDefine(ctrlUartIOPool, {0});

uint8_t ctrl_data;
void zykReceiveData(uint8_t data);
void ctrlUartRxCpltCallback(){
	//osStatus osMessagePut (osMessageQId queue_id, uint32_t info, uint32_t millisec);
//	//LST
//	IOPool_getNextWrite(ctrlUartIOPool);
//	HAL_UART_Receive_DMA(&CTRL_UART, IOPool_pGetWriteData(ctrlUartIOPool)->ch, 10);
	//zyk
	zykReceiveData(ctrl_data);
	HAL_UART_Receive_IT(&CTRL_UART, &ctrl_data, 1);
}

void ctrlUartInit(){
//	//crtl DMA接收开启(一次接收10个字节)
//	if(HAL_UART_Receive_DMA(&CTRL_UART, IOPool_pGetWriteData(ctrlUartIOPool)->ch, 10) != HAL_OK){
//			Error_Handler();
//	} 
	//zyk 一次接收1字节
	if(HAL_UART_Receive_IT(&CTRL_UART, &ctrl_data, 1) != HAL_OK){
			Error_Handler();
	} 
}




uint8_t buf[REC_LEN];
uint16_t RX_STA=0;
void zykReceiveData(uint8_t data)
{
		if((RX_STA&0x8000)==0)//½ÓÊÕÎ´Íê³É
		{
			if(RX_STA&0x4000)//½ÓÊÕµ½ÁË0x0d
			{
				if(data!=0x0a)
				{
						RX_STA=0;//½ÓÊÕ´íÎó,ÖØÐÂ¿ªÊ¼
				}
				else 
				{
					RX_STA|=0x8000;	//½ÓÊÕÍê³ÉÁË
					buf[RX_LEN]='\0';    //½«Ä©Î²¸³ÖµÎª½áÊø·û
				}
			}
			else //»¹Ã»ÊÕµ½0X0D
			{	
				if(data==0x0d)RX_STA|=0x4000;
				else
				{
					buf[RX_STA&0X3FFF]=data ;
					RX_STA++;
					if(RX_STA>(REC_LEN-1))RX_STA=0;//½ÓÊÕÊý¾Ý´íÎó,ÖØÐÂ¿ªÊ¼½ÓÊÕ	  
				}		 
			}
		}
}