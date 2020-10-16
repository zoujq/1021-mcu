/******************* (C) COPYRIGHT 2009~2019 holychip **************************
* File Name          : Fun_Handle.H
* Author             : Touch Team¤Z
* Version            : V1.0.5.0
* Date               : 2019/10/01
********************************************************************************


*******************************************************************************/
#ifndef __Fun_Handle_H__
#define __Fun_Handle_H__

//===============================================================================
extern ux8 MCU_WORK_MODE;

extern void Fun_Handle();
extern void MCU_WORK_MODE_SEL(void);
extern void MCU_GO_TO_POWER_DOWN();
extern void MCU_GO_TO_IDLE();

#define MCU_WORK_NORMAL      0
#define MCU_WORK_PD          1
#define MCU_WORK_IDLE        2


#endif /* __Fun_Handle_H__ */
