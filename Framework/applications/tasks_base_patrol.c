#include "tasks_base_patrol.h"
#include "drivers_sonar_user.h"
#include "stdlib.h"
#include "utilities_tim.h"
#include "math.h"
#include "cmsis_os.h"
#include "utilities_debug.h"
#include "drivers_uartrc_user.h"
extern float FrontBackSpeedTarget,LeftRightSpeedTarget,RotateSpeedTarget;
void task_base_patrol(void const * argument)
{
	
	while(1)
	{
		continue;
		if(IOPool_hasNextRead(SonarIOPool, 0)){
			IOPool_getNextRead(SonarIOPool, 0);
			static uint32_t cnt=0;
			float disF=IOPool_pGetReadData(SonarIOPool, 0)->sonarValue[0];
			float disL=IOPool_pGetReadData(SonarIOPool, 0)->sonarValue[1];
			float disB=IOPool_pGetReadData(SonarIOPool, 0)->sonarValue[2];
			float disR=IOPool_pGetReadData(SonarIOPool, 0)->sonarValue[3];
			float disFL=IOPool_pGetReadData(SonarIOPool, 0)->sonarValue[4];
			float disFR=IOPool_pGetReadData(SonarIOPool, 0)->sonarValue[5];
			float disBL=IOPool_pGetReadData(SonarIOPool, 0)->sonarValue[6];
			float disBR=IOPool_pGetReadData(SonarIOPool, 0)->sonarValue[7];
			
			if(cnt%20==0)
			{
				uint64_t tim=fw_getTimeMicros();
				srand(tim);
				float r_rand= 2.0*rand()/RAND_MAX -1;
				RotateSpeedTarget=15000 + 6000*r_rand;
			}
			if(++cnt%40==0)
			{
				uint64_t tim=fw_getTimeMicros();
				srand(tim);
				
				float vx_rand= 2.0*rand()/RAND_MAX -1;
				float vy_rand= 2.0*rand()/RAND_MAX -1;
				
				float d=sqrt(vx_rand*vx_rand+vy_rand*vy_rand);
				
				FrontBackSpeedTarget=vx_rand/d*15000;
				LeftRightSpeedTarget=vy_rand/d*15000;
				
				//fw_printf("CNT : %d\r\n",cnt);
			}
			
				if(abs(disF)<50 && FrontBackSpeedTarget>0 && abs(disB)>50) 
				{
						FrontBackSpeedTarget=-FrontBackSpeedTarget;
				}
				else if(abs(disF)<50 && abs(disB)<50)FrontBackSpeedTarget = 0;
				
				if(abs(disB)<50 && FrontBackSpeedTarget<0 && abs(disF)>50)
				{
						FrontBackSpeedTarget=-FrontBackSpeedTarget;
				}
				else if(abs(disF)<50 && abs(disB)<50)FrontBackSpeedTarget = 0;
				
				if(abs(disL)<50 && LeftRightSpeedTarget>0 && abs(disR)>50)
				{
					LeftRightSpeedTarget=-LeftRightSpeedTarget;
				}
				else if(abs(disL)<50 && abs(disR)<50)LeftRightSpeedTarget = 0;
				
				if(abs(disR)<50 && LeftRightSpeedTarget<0 && abs(disL) > 50)
				{
					LeftRightSpeedTarget=-LeftRightSpeedTarget;
				}
				else if(abs(disL)<50 && abs(disR)<50)LeftRightSpeedTarget = 0;
				
				if(abs(disFL)<40 && LeftRightSpeedTarget>0 && abs(disBR)>40)
				{
					LeftRightSpeedTarget=-LeftRightSpeedTarget;
				}
				if(abs(disFL)<40 && FrontBackSpeedTarget>0 && abs(disBR)>40)
				{
					FrontBackSpeedTarget=-FrontBackSpeedTarget;
				}
				
				if(abs(disFR)<40 && LeftRightSpeedTarget<0 && abs(disBL)>40)
				{
					LeftRightSpeedTarget=-LeftRightSpeedTarget;
				}
				if(abs(disFR)<40 && FrontBackSpeedTarget>0 && abs(disBL)>40)
				{
					FrontBackSpeedTarget=-FrontBackSpeedTarget;
				}
				
				if(abs(disBL)<40 && LeftRightSpeedTarget>0 && abs(disFR)>40)
				{
					LeftRightSpeedTarget=-LeftRightSpeedTarget;
				}
				if(abs(disBL)<40 && FrontBackSpeedTarget<0 && abs(disFR)>40)
				{
					FrontBackSpeedTarget=-FrontBackSpeedTarget;
				}
				
				if(abs(disBR)<40 && LeftRightSpeedTarget<0 && abs(disFL)>40)
				{
					LeftRightSpeedTarget=-LeftRightSpeedTarget;
				}
				if(abs(disBR)<40 && FrontBackSpeedTarget<0 && abs(disFL)>40)
				{
					FrontBackSpeedTarget=-FrontBackSpeedTarget;
				}
				
				
		}
		osDelay(50);
	}
}