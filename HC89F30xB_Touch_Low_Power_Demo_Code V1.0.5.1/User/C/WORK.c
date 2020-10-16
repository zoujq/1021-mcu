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

void init_printf();
void init_work();
void un_init_work();
void display_all();

void init_ntc_adc();
void init_leds();


static char init_state=0;
void init_work()
{
	if(init_state==0)
	{
		init_state=1;
		init_ntc_adc();
		init_leds();
	}
}
void un_init_work()
{
	if(init_state==1)
	{
		init_state=0;
		
		//NTC
		P0M2=GPIO_In_AN;//OFF NTC 
		P2M0=GPIO_In_AN;//OFF NTC POWER
		//LED
		P1M3=GPIO_In_AN;
		P2M1=GPIO_In_AN;
		P3M5=GPIO_In_AN;
		P2M4=GPIO_In_AN;
		P2M2=GPIO_In_AN;
		P1M5=GPIO_In_AN;
		P3M4=GPIO_In_AN;
		P1M6=GPIO_In_AN;
		P2M3=GPIO_In_AN;
		P1M4=GPIO_In_AN;
		
		ADCC0=0x03;
		ADCC1=0;
		ADCC2=0;
		ADCR=0;

		
	}

}


/*************************************ADC************************************************/
u16 code Temp_Table[100]={
3815,3788,3761,3734,3707,3680,3653,3626,3599,3572,3545,3518,3491,3464,3437,3410,3383,3356,
	3329,3302,3275,3248,3221,3194,3167,3140,3113,3086,3059,3032,3005,2978,2951,2924,2897,2870,
	2843,2816,2789,2762,2735,2708,2681,2654,2627,2600,2573,2546,2519,2492,2465,2438,2411,2384,
	2357,2330,2303,2276,2249,2222,2195,2168,2141,2114,2087,2060,2033,2006,1979,1952,1925,1898,
	1871,1844,1817,1790,1763,1736,1709,1682,1655,1628,1601,1574,1547,1520,1493,1466,1439,1412,
	1385,1358,1331,1304,1277,1250,1223,1196,1169,1142
};

void init_ntc_adc()
{
	
	P0M2 = 0x01;				        //P02设置为模拟输入
	ADCC0 = 0x80;						//打开ADC转换电源
	Delay_10us(5);						//延时50us，确保ADC系统稳定
	ADCC1 = 2;						//选择外部通道2
	ADCC2 = 0x4B;						//转换结果12位数据，数据右对齐，ADC时钟16分频

	//NTC POWER
	P2M0=GPIO_Out_PP;	
	P2_0=1;
	
	
}
unsigned int get_ntc_adc()
{
		ADCC0 |= 0x40;					//启动ADC转换
		while(!(ADCC0&0x20));			//等待ADC转换结束
		ADCC0 &=~ 0x20;					//清除标志位
		return ADCR;
}

u16 get_temp()
{
	u16 n=0;
	u16 ntc_adc=get_ntc_adc();
	
	for(n=0;n<100;n++)
	{
		if(Temp_Table[n]<ntc_adc)
		{
			break;
		}
	}
	return n;

}


/************************************数码管***************************************/
//阳极
#define LED1 P1_3
#define LED2 P2_1
#define LED3 P3_5
#define LED4 P2_4
#define LED5 P2_2
#define LED7 P1_5
#define LED9 P3_4
//阴极
#define LED6 P1_6
#define LED8 P2_3
#define LED10 P1_4
void init_leds()
{
	P1M3=GPIO_Out_PP;
	P2M1=GPIO_Out_PP;
	P3M5=GPIO_Out_PP;
	P2M4=GPIO_Out_PP;
	P2M2=GPIO_Out_PP;
	P1M5=GPIO_Out_PP;
	P3M4=GPIO_Out_PP;
	P1M6=GPIO_Out_PP;
	P2M3=GPIO_Out_PP;
	P1M4=GPIO_Out_PP;
	LED6=1;
	LED8=1;
	LED10=1;

}

void display(char position,char value)
{
	LED6=1;
	LED8=1;
	LED10=1;
		
	switch(value)
	{
		case 0:
			LED1=0;	LED2=1;LED3=1;LED4=1;LED5=1;LED7=1;LED9=1;
	
			break;
		case 1:
			LED1=0;	LED2=1;LED3=0;LED4=0;LED5=1;LED7=0;LED9=0;
			break;
		case 2:
			LED1=1;	LED2=1;LED3=1;LED4=0;LED5=0;LED7=1;LED9=1;
			break;
		case 3:
			LED1=1;	LED2=1;LED3=1;LED4=0;LED5=1;LED7=0;LED9=1;
			break;
		case 4:
			LED1=1;	LED2=1;LED3=0;LED4=1;LED5=1;LED7=0;LED9=0;
			break;
		case 5:
			LED1=1;	LED2=0;LED3=1;LED4=1;LED5=1;LED7=0;LED9=1;
			break;
		case 6:
			LED1=1;	LED2=0;LED3=1;LED4=1;LED5=1;LED7=1;LED9=1;
			break;
		case 7:
			LED1=0;	LED2=1;LED3=1;LED4=0;LED5=1;LED7=0;LED9=0;
			break;
		case 8:
			LED1=1;	LED2=1;LED3=1;LED4=1;LED5=1;LED7=1;LED9=1;
			break;
		case 9:
			LED1=1;	LED2=1;LED3=1;LED4=1;LED5=1;LED7=0;LED9=1;
			break;
		case 'c':
			LED1=1;	LED2=0;LED3=1;LED4=1;LED5=0;LED7=0;LED9=0;
			break;		
		case '-':
			LED1=0;	LED2=1;LED3=1;LED4=1;LED5=1;LED7=1;LED9=1;
			break;
		case '+':
			LED1=0;	LED2=0;LED3=0;LED4=0;LED5=0;LED7=0;LED9=0;
			break;
		default:
			
			break;
	
	}
	if(position==1)
	{		
		LED6=1;
		LED8=1;
		LED10=0;
	}
	else if(position==2) 
	{
		LED6=1;
		LED8=0;
		LED10=1;
	}
	else
	{
		LED6=0;
		LED8=1;
		LED10=1;
	}
}
void display_temp(u16 temp)
{
	char b_1=0;
	char b_2=0;
	if(temp>99)
	{
		temp=99;
	}
	b_1=temp/10;
	b_2=temp%10;
	
	if(b_1==0)
	{
		b_1='+';
	}
	display(1,b_1);
	Delay_1ms(2);
	display(2,b_2);
	Delay_1ms(2);
	display(3,'c');
	Delay_1ms(2);

}
void display_all()
{
	static u16 last_temp=0;
	if(init_state==1)
	{
		u16 real_temp=get_temp();
		
		if(real_temp>last_temp)
		{
			if(real_temp-last_temp>=2)
			{
				last_temp=real_temp-1;
			}
		}
		else if(real_temp<last_temp)
		{
			if(last_temp-real_temp>=2)
			{
				last_temp=real_temp+1;
			}
		}	
		if(real_temp==99)
		{
			last_temp=99;
		}
		if(real_temp==0)
		{
			last_temp=0;
		}
		
		display_temp(last_temp);
	}
	
}

/********************************************printf****************************************/

#define PRINTF_BAUDRATE  		9600   
void init_printf()
{
	P2M0 = 0xC1;				        //设置P20推完输出
	
	TXD_MAP = 0x20;						//TXD
	
	T4CON = 0x06;						//T4，波特率发生器

	SCON2 = 0x02;   // uart mode 1
	
	T4 = 65536.5 - (SYSCLK_FOSC / 16 / PRINTF_BAUDRATE); //


}

char putchar (char c)
{
	SBUF = c;

	while(!TI);

	TI = 0;
  return 0;
}






















