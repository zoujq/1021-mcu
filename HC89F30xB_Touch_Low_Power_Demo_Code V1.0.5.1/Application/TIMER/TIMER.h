/******************* (C) COPYRIGHT 2009~2019 holychip **************************
* File Name          : TIMER.h
* Author             : Touch Team
* Version            : V1.0.5.0
* Date               : 2019/10/01
********************************************************************************


*******************************************************************************/
#ifndef __TIMER_H__
#define __TIMER_H__

//===============================================================================
//1MS
#define	T0_MS                1  //ms max 2.048ms
#define	T0_XMS			        (u16)(65536-(SYSCLK_FOSC/1000*T0_MS))

#define TH0_DF         			(T0_XMS/256)
#define TL0_DF         			(T0_XMS%256)
#define	TIMER0_COUNT_INIT		TH0=TH0_DF ; TL0=TL0_DF

#define TIMER0_EN       	(TR0 = 1)
#define TIMER0_DIS 		 		(TR0 = 0)
#define CLR_TIMER0_TF0 		(TF0 = 0)

#define SET_TIMER0_SWI		(TCON |= (bmTR0 |bmTF0))	//立即进入Timer0 中断

#define T_10MS_DF 				      10    //10*1ms
#define T_100MS_DF 				      10	  //8*25ms



extern	u8	bdata	T0_XXS_Flag;
extern	bit	bdata	T0_10MS_F;
extern	bit	bdata	T0_100MS_F;


extern ux8 T_10MS_COUNT;
extern ux8 T_100MS_COUNT;
extern ux8 T_500MS_COUNT;
extern ux8 T_5S_COUNT;


extern ux8 T_MCU_GO_TO_LP_MODE_COUNT ;


extern void TIMER0_Init(void);
extern void TIMER0_ISR_Handle(void);

#endif /* __TIMER_H__ */
