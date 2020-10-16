/******************* (C) COPYRIGHT 2009~2019 holychip **************************
* File Name          : HC89F30xB_GeneralKey_Touch_Multibutton.h
* Author             : Touch Team
* Version            : V1.0.5.0    
* Date               : 2019/10/01
********************************************************************************

注：凡是HCTouchLib开头的宏定义，用户可以根据实际调试需要，修改后面的数据

*******************************************************************************/
#ifndef __HC89F30xB_GeneralKey_Touch_Multibutton_H__
#define __HC89F30xB_GeneralKey_Touch_Multibutton_H__


/****************************************************************************************************/
void TouchMultibuttonHandle(void);		//最强按键处理函数，如果大于等于两个按键同时有效，那么触摸信号最
										//强的按键判断为有效，其他按键无效。
/****************************************************************************************************/

// 设置是否使能最强按键，使能后如果大于等于两个按键同时有效，触摸信号最强的按键判断有效，其他按键无效
//			0：关闭最强按键
//			1：打开最强按键
#define HCTouchLib_MULTIBUTTON 			0

// 设置程序使能的通道
//			举例：如果打开了TK1,TK2,TK5,TK8则在下面{}中填入1,2,5,8
//			注意：此处必须严格按照使能的通道号填入，否则会导致TouchKeyFlag输出错误，如关闭了最强按键，则无需填写
#define HCTouchLib_OPENTOUCHCHANNEL		{10,11,12,13,14,15}

#endif

/******************************************************************************************************
 * Revision history:
 *
 * Revision 1.01  	2017/12/18 14:10 Taboo.Z
 * Revision 1.0.2.0	2018/07/20 16:31 Jing.L
 * Revision 1.0.3.0	2018/09/10 14:38 Jing.L
 * Revision 1.0.4.0	2019/03/06 13:59 Touch Team
 * Revision 1.0.5.0	2019/09/17 19:23 Touch Team
 * Add: 1、首次增加最强按键功能
 ******************************************************************************************************/