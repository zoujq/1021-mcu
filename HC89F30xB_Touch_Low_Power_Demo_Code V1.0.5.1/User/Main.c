/******************* (C) COPYRIGHT 2009~2019 holychip **************************
* File Name          : Main.c
* Author             : Touch Team
* Version            : V1.0.5.0
* Date               : 2019/10/01
********************************************************************************

��������HC89F30xB_GeneralKey_Touch_Lib_CFG_H.h�ļ������������
����ʱ����������WDT.H�ļ��и��������޸�
��������ֵ�ɲ��ձ�����ͬĿ¼��HC89F30xBϵ��_LowPower_DemoCode���Ĺ�����V1.0.0.0.xlsx�ļ�

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
	
	SystemInit();						//ʱ�ӳ�ʼ������(Ĭ��Fosc=Fcpu=16M)
	FREQ_CLK = 0x10;					//ָ����ǰϵͳʱ��
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
			TouchRawDataFilter();		//RawData�˲�����������ʹ�������˲�������HC89F30xB_GeneralKey_Touch_Filter.h�������˲���ȣ��˺�������ɾ��
			Touch_Signal_Handle();
			TouchMultibuttonHandle();	//��ǿ������������������ڵ�����������ͬʱ��Ч����ô�����ź���ǿ�İ����ж�Ϊ��Ч������������Ч
			OneCycleScanDone = 0;



			if(MCU_WORK_MODE==MCU_WORK_IDLE)
			{
				MCU_WORK_MODE = MCU_WORK_PD;

				for(i = 0; i < CODE_OPENED_TK_AMOUNT; i++)
				{
					if(XDATA_TouchCnt[i] != 0)
					{
						MCU_WORK_MODE = MCU_WORK_NORMAL;
						//ϵͳ����
						T_MCU_GO_TO_LP_MODE_COUNT = 0; //
						TIMER0_EN;
						//�·����������˳��͹���ģʽ����Ҫ�ָ��Ĳ���
						init_work();
					}
				}
			}			
		}
		
    // TouchKeyFlag Handle code
    /*
    	if(TouchKeyFlag & 0x0001)
    	{//TouchKeyFlag Ϊ���������־�Ĵ�����������鿴HC89F30xB_GeneralKey_Touch_Lib.h
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
