/******************* (C) COPYRIGHT 2009~2019 holychip **************************
* File Name          : HC89F30xB_SYS.c
********************************************************************************


*******************************************************************************/
#include	"HC89F303B.h"
#include	"HC89F30xB_SYS.h"

/****************************************************************************
* Function Name  :
* Description    :
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/
void SystemInit(void)
{
  //SYS CLOCK
  CLKSWR = (SYSCLK_SEL << 4) | SYSCLK_HSRC_DIV;

  CLKDIV = SYSCLK_FCPU_DIV;

  //BOR
#if  1
  RSTDBC = 0XFF; 			//Timer = RSTDBC*8*Tcpu + 2Tcpu
  BORC = bmBOREN | bmBOR_DBC_EN | BOR_SET_2V4 ; 		//
#else
  BORC = BORC & ~bmBOREN;
#endif
}

/*********************************END OF FILE************************************/
/******************* (C) COPYRIGHT 2009~2019 holychip ***************************/
