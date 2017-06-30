#include "tasks_upper.h"
#include "drivers_uartupper_user.h"

#include "drivers_flash.h"

#include "utilities_debug.h"

#include "drivers_uartupper_user.h"

#include "string.h"

#include "UserProtocal.h"

#include "drivers_canmotor_user.h"
NaiveIOPoolDefine(upperIOPool, {0});

extern uint16_t yawAngle, pitchAngle;
int forPidDebug = 0;

extern int8_t flUpDown, frUpDown, blUpDown, brUpDown, allUpDown;
//extern float yawAngleTarget, pitchAngleTarget;
void getCtrlUartTask(void const * argument){
	uint8_t data[10];
	while(1){
		//////////////////////LST//////////////////////////////
//		if(IOPool_hasNextRead(ctrlUartIOPool, 0)){
//			IOPool_getNextRead(ctrlUartIOPool, 0);
//			fw_printf("received!\r\n");
//			uint8_t *pData = IOPool_pGetReadData(ctrlUartIOPool, 0)->ch;
//		
//			for(uint8_t i = 0; i != 10; ++i){
//				data[i] = pData[i];
//			}			
//			
//			IOPool_pGetWriteData(upperIOPool)->yawAdd = 0;
//			IOPool_pGetWriteData(upperIOPool)->pitchAdd = 0;
//			if(data[0] == 'L'){
//				fw_printfln("L");
//				IOPool_pGetWriteData(upperIOPool)->yawAdd = + 1.0f * ((int)data[1] - '0');
//				//yawAngleTarget = yawRealAngle + 1.0f * ((int)data[1] - 48);
//			}else if(data[0] == 'R'){
//				IOPool_pGetWriteData(upperIOPool)->yawAdd = - 1.0f * ((int)data[1] - '0');
//				//yawAngleTarget = yawRealAngle - 1.0f * ((int)data[1] - 48);
//			}else if(data[0] == 'U'){
//				IOPool_pGetWriteData(upperIOPool)->pitchAdd = + 8.0f * ((int)data[1] - '0');
//				//pitchAngleTarget += 8.0f;
//			}else if(data[0] == 'D'){
//				IOPool_pGetWriteData(upperIOPool)->pitchAdd = - 8.0f * ((int)data[1] - '0');
//				//pitchAngleTarget -= 8.0f;
//			}else if(data[0] == 'T'){
//				fw_printfln("received T: %d", data[1]);
//			}else if(data[0] == '1'){
//				if(data[1] == 'U'){
//					flUpDown = 5;
//				}else if(data[1] == 'D'){
//					flUpDown = -5;
//				}else if(data[1] == 'S'){
//					flUpDown = 0;
//				}
//			}else if(data[0] == '2'){
//				if(data[1] == 'U'){
//					frUpDown = 5;
//				}else if(data[1] == 'D'){
//					frUpDown = -5;
//				}else if(data[1] == 'S'){
//					frUpDown = 0;
//				}
//			}else if(data[0] == '3'){
//				if(data[1] == 'U'){
//					blUpDown = 5;
//				}else if(data[1] == 'D'){
//					blUpDown = -5;
//				}else if(data[1] == 'S'){
//					blUpDown = 0;
//				}
//			}else if(data[0] == '4'){
//				if(data[1] == 'U'){
//					brUpDown = 5;
//				}else if(data[1] == 'D'){
//					brUpDown = -5;
//				}else if(data[1] == 'S'){
//					brUpDown = 0;
//				}
//			}else if(data[0] == '5'){
//				if(data[1] == 'U'){
//					flUpDown = 50;
//					frUpDown = 50;
//					blUpDown = 50;
//					brUpDown = 50;
//				}else if(data[1] == 'D'){
//					flUpDown = -50;
//					frUpDown = -50;
//					blUpDown = -50;
//					brUpDown = -50;
//				}else if(data[1] == 'S'){
//					flUpDown = 0;
//					frUpDown = 0;
//					blUpDown = 0;
//					brUpDown = 0;
//				}
//			}else if(data[0] == '6'){
//				if(data[1] == 'U'){
//					flUpDown = 50;
//					frUpDown = 50;
//				}else if(data[1] == 'D'){
//					flUpDown = -50;
//					frUpDown = -50;
//				}
//			}else if(data[0] == '7'){
//				if(data[1] == 'U'){
//					blUpDown = 50;
//					brUpDown = 50;
//				}else if(data[1] == 'D'){
//					blUpDown = -50;
//					brUpDown = -50;
//				}
//			}else if(data[0] == '?'){
//				forPidDebug = 1;
//			}else if(data[0] == '!'){
//				forPidDebug = 0;
//			}
//			
//			IOPool_getNextWrite(upperIOPool);
			
//			else if(data[0] == 'F'){
//				uint32_t temp;
//				if(data[1] == '1'){
//					temp = 1;
//				}else if(data[1] == '0'){
//					temp = 0;
//				}else{
//					temp = 99;
//				}
//				STMFLASH_Write(PARAM_SAVED_START_ADDRESS, &temp, 1);
//				fw_printfln("F: %d", temp);
//			}else if(data[0] == 'X'){
//				uint32_t temp;
//				STMFLASH_Read(PARAM_SAVED_START_ADDRESS, &temp, 1);
//				fw_printfln("Read: %d", temp);
//			}				
			
//			fw_printf("d:");
//			fw_printf("%c|", data[0]);
//			fw_printf("%c|", data[1]);
//			fw_printf("%c|", data[2]);
//			fw_printf("%c|", data[3]);
//			fw_printf("%c|", data[4]);
//			fw_printf("%c|", data[5]);
//			fw_printf("%c|", data[6]);
//			fw_printf("%c|", data[7]);
//			fw_printf("%c|", data[8]);
//			fw_printf("%c\r\n", data[9]);
//			fw_printf("===========\r\n");
//
//		}
	zykProcessData();
	}
}


extern float yawAngleTarget, pitchAngleTarget,LeftRightSpeedTarget,FrontBackSpeedTarget,RotateSpeedTarget;
extern uint8_t GM_RUN;
extern uint8_t SonarPrint;
void zykProcessData(void)
{
	if(RX_DONE)
	{
		char data[10][15];
		//fw_printf(buf);
		/////////////GM Start and stop//////////////
		if(strcmp(buf,"GM")==0)
		{
			if(GM_RUN)
			{
				GM_RUN=0;
				fw_printf("STOP GM!\r\n");
			}
			else
			{
				GM_RUN=1;
				fw_printf("START GM!\r\n");
			}
		}
		/////////////GM ADD////////////////
		else if(strcmp(buf,"L")==0)
		{
			fw_printf("Left\r\n");
			IOPool_pGetWriteData(upperIOPool)->yawAdd = + 5.0f;
		}
		else if(strcmp(buf,"R")==0)
		{
			fw_printf("Right\r\n");
			IOPool_pGetWriteData(upperIOPool)->yawAdd = - 5.0f;
		}
		else if(strcmp(buf,"U")==0)
		{
			fw_printf("Right\r\n");
			IOPool_pGetWriteData(upperIOPool)->pitchAdd = + 5.0f;
		}
		else if(strcmp(buf,"D")==0)
		{
			fw_printf("Right\r\n");
			IOPool_pGetWriteData(upperIOPool)->pitchAdd = - 5.0f;
		}
		/////////////GM SET////////////////
		else if(ComProtocal(buf,"#GM","$","@",data))
		{
			float ang1=atof(data[0]);
			float ang2=atof(data[1]);
			MINMAX(ang1, YAWDOWNLIMIT, YAWUPLIMIT);
			MINMAX(ang2, PITCHDOWNLIMIT, PITCHUPLIMIT);
			yawAngleTarget=ang1;
			pitchAngleTarget=ang2;
		}
		/////////// CM SET ////////////////
		else if(strcmp(buf,"CL")==0)
		{
			//fw_printf("CL");
			LeftRightSpeedTarget=5000;
		}
		else if(strcmp(buf,"CR")==0)
		{
			LeftRightSpeedTarget=-5000;
		}
		else if(strcmp(buf,"CF")==0)
		{
			FrontBackSpeedTarget=5000;
		}
		else if(strcmp(buf,"CB")==0)
		{
			FrontBackSpeedTarget=-5000;
		}
		else if(strcmp(buf,"CRL")==0)
		{
			RotateSpeedTarget=5000;
		}
		else if(strcmp(buf,"CRR")==0)
		{
			RotateSpeedTarget=-5000;
		}
		else if(strcmp(buf,"STOP")==0)
		{
			FrontBackSpeedTarget=0;
			LeftRightSpeedTarget=0;
			RotateSpeedTarget=0;
		}
		//////// GET GM ZERO
		else if(strcmp(buf,"GME")==0)
		{
			int16_t yz= IOPool_pGetReadData(GMYAWRxIOPool, 0)->angle;
			int16_t pz= IOPool_pGetReadData(GMPITCHRxIOPool, 0)->angle;
			fw_printf("Yaw encoder now is %d\r\n",yz);
			fw_printf("Pitch encoder now is %d\r\n",pz);
			IOPool_getNextRead(GMYAWRxIOPool, 0); 
			IOPool_getNextRead(GMPITCHRxIOPool, 0); 
		}
		else if(strcmp(buf,"GMZ")==0)
		{
			IOPool_getNextRead(GMYAWRxIOPool, 0); 
			IOPool_getNextRead(GMPITCHRxIOPool, 0); 
			int16_t yz= IOPool_pGetReadData(GMYAWRxIOPool, 0)->angle;
			int16_t pz= IOPool_pGetReadData(GMPITCHRxIOPool, 0)->angle;
			fw_printf("Yaw encoder now is %d\r\n",yz);
			fw_printf("Pitch encoder now is %d\r\n",pz);
			fw_printf("Yaw encoder bias now is %d\r\n",YawZeroEncoderBias);
			fw_printf("Pitch encoder bias now is %d\r\n",PitchZeroEncoderBias);
			YawZeroEncoderBias=yz;
			PitchZeroEncoderBias=pz;
			fw_printf("Encoder zero changed to %d  %d  \r\n", yz, pz);
		}
		////////////////SONAR ////////////////
		if(strcmp(buf,"SONAR")==0)
		{
			fw_printf("received\r\n");
			if(SonarPrint)
			{
				SonarPrint=0;
				//fw_printf("STOP GM!\r\n");
			}
			else
			{
				SonarPrint=1;
				//fw_printf("START GM!\r\n");
			}
		}
		IOPool_getNextWrite(upperIOPool);

		strcpy(buf,"\0");
		RX_STA=0;
	}
}