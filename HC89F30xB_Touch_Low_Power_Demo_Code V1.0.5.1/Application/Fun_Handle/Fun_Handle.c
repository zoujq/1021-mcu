/******************* (C) COPYRIGHT 2009~2019 holychip **************************
* File Name          : Fun_Handle.c
* Author             : Touch Team
* Version            : V1.0.5.0
* Date               : 2019/10/01
********************************************************************************


*******************************************************************************/
#include "HC89F303B.h"
#include "Fun_Handle\Fun_Handle.h"
#include "TIMER\TIMER.h"
#include "HC89F30xB_GeneralKey_Touch_Lib_V1.04\HC89F30xB_GeneralKey_Touch_Lib.h"
#include "WDT\WDT.h"
#include "HC89F30xB_SYS.h"
#include <intrins.h>
#include "HC_Delay.h"

//===============================================================================
ux8 MCU_WORK_MODE = MCU_WORK_NORMAL;


//===============================================================================
extern uc8		CODE_OPENED_TK_AMOUNT;
extern ux8 	XDATA_TouchCnt[];

//===============================================================================

#define T_MCU_GO_TO_LP_MODE_DF 		5  //单位(s) 设置MCU正常模式下，无触摸多长时间后允许进入低功耗模式

//===============================================================================
void Fun_Handle()
{
	if(T0_100MS_F)
	{
		T0_100MS_F = 0;

		if((TouchKeyFlag == 0)&&(MCU_WORK_MODE==MCU_WORK_NORMAL))
		{
			//无触摸且超时后，系统允许从正常模式进入低功耗模式
			//用户可以根据实际需求增加允许进入低功耗模式的相关条件，如通常需要进入低功耗是系统关机后，则可增加是否为关机状态相应条件
			if(++T_MCU_GO_TO_LP_MODE_COUNT >= (T_MCU_GO_TO_LP_MODE_DF * 1000 / 100))
			{
				T_MCU_GO_TO_LP_MODE_COUNT = 0;
				MCU_WORK_MODE = MCU_WORK_PD; //系统允许
			}
		}
		else
		{
			T_MCU_GO_TO_LP_MODE_COUNT = 0;
		}
	}
}

//===============================================================================
void MCU_WORK_MODE_SEL(void)
{
	if(MCU_WORK_MODE == MCU_WORK_PD)
	{
		MCU_GO_TO_POWER_DOWN();
	}
	else if(MCU_WORK_MODE == MCU_WORK_IDLE)
	{
		MCU_GO_TO_IDLE();
	}
	else
	{
		;
	}
}

//===============================================================================
extern void un_init_work();
void MCU_GO_TO_POWER_DOWN(void)
{
#if 1
	u8 i = 0;

	//OFF CTK
	Scan_Pause();
	CTKCON = 0;
	TouchKeyFlag = 0;
	for(i = 0; i < CODE_OPENED_TK_AMOUNT; i++)
	{
		XDATA_TouchCnt[i] = 0;
	}

	//OFF BOR
	BORC &= ~bmBOREN;

	//OFF TIMER0
	TIMER0_DIS;
	TIMER0_COUNT_INIT;

	//下方可增加其它进入低功耗模式前需要关闭的操作


	un_init_work();



	//SET WDT WAKE UP MODE and EA&EWDT must set "1"
	WDT_INIT();

	// MCU GO f POWER DOWN
	PCON |= bmPD;
	_nop_();
	_nop_();
	_nop_();
	_nop_();

	//ON BOR
	BORC |= bmBOREN;

	//ON CTK
	CTKCON |= bmCTKON;
	Delay_us(1);
	CTKCON |= bmCTKST;

	Scan_Continue();

	MCU_WORK_MODE = MCU_WORK_IDLE; //
#endif
}

//===============================================================================
void MCU_GO_TO_IDLE(void)
{
#if 1
	// MCU GO TO IDLE
	PCON |= bmIDL;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
#endif
}

/*********************************END OF FILE************************************/
/******************* (C) COPYRIGHT 2009~2019 holychip ***************************/
