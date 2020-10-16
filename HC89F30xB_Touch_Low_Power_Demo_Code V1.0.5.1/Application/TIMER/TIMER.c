/******************* (C) COPYRIGHT 2009~2019 holychip **************************
* File Name          : TIMER.c
* Author             : Touch Team
* Version            : V1.0.5.0
* Date               : 2019/10/01
********************************************************************************


*******************************************************************************/
#include "HC89F303B.h"
#include "HC89F30xB_SYS.h"
#include "TIMER\TIMER.h"

//===============================================================================
u8	bdata	T0_XXS_Flag = 0;
sbit	T0_10MS_F 								= T0_XXS_Flag ^ 0;		//
sbit	T0_100MS_F		 					  = T0_XXS_Flag ^ 1;		//

ux8 T_10MS_COUNT = 0;
ux8 T_100MS_COUNT = 0;

ux8	T_MCU_GO_TO_LP_MODE_COUNT = 0;

//===============================================================================
void TIMER0_Init(void)
{
	TIMER0_DIS;
	CLR_TIMER0_TF0;
	TCON1 |= bmT0X12;				//1FP
	TMOD &= ~bmT0MODE;			//FS0
	TIMER0_COUNT_INIT;
	ET0 = 1;	
	TIMER0_EN;
}

//================================================================================
void TIMER0_ISR_Handle()
{
  if(++T_10MS_COUNT  >= T_10MS_DF)
  {
    T_10MS_COUNT = 0;
    T0_10MS_F = 1;		
  }

  if(T0_10MS_F)
  {
    T0_10MS_F = 0;

    if(++T_100MS_COUNT  >= T_100MS_DF)
    {
      T_100MS_COUNT = 0;
      T0_100MS_F = 1;
    }
  }
}



/*********************************END OF FILE************************************/
/******************* (C) COPYRIGHT 2009~2019 holychip ***************************/
