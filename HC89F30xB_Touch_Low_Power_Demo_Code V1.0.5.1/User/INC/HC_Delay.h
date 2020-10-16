/******************* (C) COPYRIGHT 2009~2019 holychip **************************
* File Name          : HC_Delay.h
********************************************************************************


*******************************************************************************/
#ifndef __HC_DELAY_H__
#define __HC_DELAY_H__

//===============================================================================
#define DELAY_TIME_1US_FUNCTION
#define DELAY_TIME_10US_FUNCTION
#define DELAY_TIME_100US_FUNCTION
#define DELAY_TIME_1MS_FUNCTION
#define DELAY_TIME_10MS_FUNCTION

extern void Delay_us(u8 n);
extern void Delay_10us(u8 n);
extern void Delay_100us(u8 n);
extern void Delay_1ms(u8 n);
extern void Delay_10ms(u8 n);

#endif /* __HC_DELAY_H__ */

/*********************************END OF FILE************************************/
