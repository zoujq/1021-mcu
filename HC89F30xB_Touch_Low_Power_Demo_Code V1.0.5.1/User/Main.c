/******************* (C) COPYRIGHT 2009~2019 holychip **************************
* File Name          : Main.c
* Author             : Touch Team
* Version            : V1.0.5.0
* Date               : 2019/10/01
********************************************************************************

触摸请在HC89F30xB_GeneralKey_Touch_Lib_CFG_H.h文件进行相关配置
唤醒时间设置请在WDT.H文件中根据需求修改
具体评估值可参照本工程同目录下HC89F30xB系列_LowPower_DemoCode功耗估算器V1.0.0.0.xlsx文件

********************************************************************************/

//================================================================================
#define  ALLOCATE_EXTERN
#include "HC89F303B.h"
#include "HC89F30xB_SYS.h"
#include "HC89F30xB_IO_INIT.h"
#include "WDT\WDT.h"
#include "HC_Delay.h"
#include "TIMER\TIMER.h"
#include "Fun_Handle\Fun_Handle.h"
#include "HC89F30xB_GeneralKey_Touch_Lib_V1.04\HC89F30xB_GeneralKey_Touch_Lib.h"
#include "HC89F30xB_GeneralKey_Touch_Lib_V1.04\HC89F30xB_GeneralKey_Touch_Filter.h"
#include "HC89F30xB_GeneralKey_Touch_Lib_V1.04\HC89F30xB_GeneralKey_Touch_Multibutton.h"
#include "HC89F30xB_TouchUartDebug_Lib_V1.00\HC89F30xB_TouchUartDebug_Lib_CFG.h"
#include "HC89F30xB_TouchUartDebug_Lib_V1.00\HC89F30xB_TouchUartDebug_Lib.h"
//================================================================================
extern uc8		CODE_OPENED_TK_AMOUNT;
extern ux8	 	XDATA_TouchCnt[];
//================================================================================
extern void init_printf();
extern void init_work();
extern void un_init_work();
extern void display_all();
void main()
{
	u8 i = 0;	
	
	SystemInit();						//时钟初始化函数(默认Fosc=Fcpu=16M)
	FREQ_CLK = 0x10;					//指明当前系统时钟
	IO_Init();
	TIMER0_Init();
	WDT_Clock_Freq_Cal();	
	
	EA = 1;
	CTK_Init();

	init_work();
	while(1)
	{
		if(OneCycleScanDone)
		{
			TouchRawDataFilter();		//RawData滤波函数，如需使能数据滤波，需在HC89F30xB_GeneralKey_Touch_Filter.h中设置滤波深度，此函数不可删除
			Touch_Signal_Handle();
			TouchMultibuttonHandle();	//最强按键处理函数，如果大于等于两个按键同时有效，那么触摸信号最强的按键判断为有效，其他按键无效
			OneCycleScanDone = 0;



			if(MCU_WORK_MODE==MCU_WORK_IDLE)
			{
				MCU_WORK_MODE = MCU_WORK_PD;

				for(i = 0; i < CODE_OPENED_TK_AMOUNT; i++)
				{
					if(XDATA_TouchCnt[i] != 0)
					{
						MCU_WORK_MODE = MCU_WORK_NORMAL;
						//系统唤醒
						T_MCU_GO_TO_LP_MODE_COUNT = 0; //
						TIMER0_EN;
						//下方增加其它退出低功耗模式后需要恢复的操作
						init_work();
					}
				}
			}			
		}
		
    // TouchKeyFlag Handle code
    /*
    	if(TouchKeyFlag & 0x0001)
    	{//TouchKeyFlag 为触摸输出标志寄存器，具体请查看HC89F30xB_GeneralKey_Touch_Lib.h
    		;
    	}
    */		

		// Other Functions Handle code
		display_all();
		Fun_Handle();
		MCU_WORK_MODE_SEL();
	}
}

/*********************************END OF FILE************************************/
/******************* (C) COPYRIGHT 2009~2019 holychip ***************************/
