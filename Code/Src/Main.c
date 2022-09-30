#define MainS
#include "Main.h"

void F_EnterHaltMode()
{
	I2CCON = 0;			//关闭I2C，否则无法关闭主时钟
	SWICON |= 0x01;		//关闭单线通信功能，否则无法关闭IRCH时钟
	CKCON = 0;			//所有时钟关闭
	PWCON &= ~0x08;		//设置LDO进入低功率模式

//------------------------------------------------------------------------
	/*在应用时还要把IO设置为省电状态，不用的IO尽量不要为悬浮状态。*/
	Sys_Clk_Set_IRCL();	//由于进入IDLE模式不会关闭主时钟，所以进入IDLE前把主时钟设为低速时钟可显著降低功耗
//---------------------------------------------------------------------	
	HaltFlag = 1;
//	PCON |= 0x02;		//进入STOP模式
	PCON |= 0x01;		//进入IDLE模式
	_nop_();
	_nop_();
	_nop_();
	PWCON |= 0x08;		//退出IDLE模式后，把LDO设回高功率模式
	Sys_Clk_Set_IRCH();	
	HaltFlag = 0;
	/* if(TOUCH_SDA_IO == 0)
	{
		//M_TESTTIME();
		//M_TESTTIME();
		//M_TESTTIME();
	} */
}

void F_McuEnterHaltCheak()
{
	GCC_CLRWDT();
	if((CntTime.Motor == _FALSE)				/* 电机驱动使用定时器1ms中断切换通电相位，电机未运行完毕，MCU不能进入HALT模式，否则STM0中断关闭，导致电机驱动出现问题 */
	  &&(Key.Pulse == _FALSE)
	  &&(Key.NowBuf == _FALSE)
	  &&(CntTime.RxTimeDown == _FALSE)			/* RF 工作完成 */
	  &&(R_MODE == D_NOR)						/* 在这个状态下保存数据 */
	  &&(Framework.McuHaltFlag.ucVal == FALSE))
	{
		//M_TESTTIME();
		switch(SaveFlag.wVal)
		{	case _FALSE: F_EnterHaltMode();		break;					
			default:	 F_SaveDataToEEprom();	break;
		}
	} 
}


void main(void)
{
	Sys_Clk_Set_XOSCL();					
	Sys_Clk_Switch(CKSEL_IRCH);
	F_INIT_XDATA_RAM();
	F_RAM_INIT();
	F_MORTO_INIT();
	F_TOUCH_KEY_INIT();
	F_RTM_INIT();
	F_RTC_INIT();
	F_ADC_INIT();
	F_TM0_INIT();
	F_TM2_INIT();
	F_WDT_INIT();
	F_LVD_INIT();
	F_LCD_INIT(LCD_3_3V);
	F_EXINT0_INIT(P33_INDEX);
//	F_EXINT1_INIT(P32_INDEX);
	P32F = INPUT;
#ifdef UART_EN
	Uart_Initial(UART_BAUTRATE);
#endif
	EMI_ENABLE();	
	F_Flash_Init_Set();
    F_ReadEEpromToRAM();
	F_ReadSlaveIDEEpromToRAM();
    F_PowerOnLcdAllCheak();
	TheVa.Param.Mode1.Bit.bit0 = D_Offline;
	R_RfFreq = RF_433MHz;
	RF_Init();
//	CMT2300A_ReadRegConfig();
//  CMT2300A_Collision_Detec();
	uart_printf ("CF = %u\n",(u16)TheVa.Param.Mode.Bit.bit0);
	uart_printf ("MODE = %u\n",(u16)TheVa.Param.Mode.ucVal);
	while (1)
    {				
		F_TimeSever(); 
		F_KeySever();
		F_KeySetMenuSever();
		F_LcdRefreshSever();
		F_RF_TRxSever();
	//	F_McuEnterHaltCheak();	
		if(T2CycleFlag1)
		{
		//	////uart_printf ("IntvBuf = %u\n",(u16)T2CycleIntvBuf);
		//	////uart_printf ("MotorCapCnt = %u\n",(u16)MotorCapCnt);
			T2CycleFlag1 = 0;
		}
	}
}
