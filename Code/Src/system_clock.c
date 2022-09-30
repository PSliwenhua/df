#include "Main.h"

/***********************************************************************************
函数名  ：		Sys_Clk_Set_IRCH										 	
功能描述：		设置系统时钟为IRCH
输入参数：		无
返回值  ：		无
***********************************************************************************/
void Sys_Clk_Set_IRCH(void)
{
	CKCON |= IHCKE;											//IRCH时钟使能
	CKSEL = (CKSEL&0xF8) | CKSEL_IRCH;	//系统时钟切换到IRCH
}
/***********************************************************************************/



/***********************************************************************************
函数名  ：		Sys_Clk_Set_IRCL										 	
功能描述：		设置系统时钟为IRCL
输入参数：		无
返回值  ：		无
***********************************************************************************/
void Sys_Clk_Set_IRCL(void)
{
	CKCON |= ILCKE;											//IRCL时钟使能
	Delay_ms(1);												//使能IRCL后延时1ms，等待IRCL稳定
	CKSEL = (CKSEL&0xF8) | CKSEL_IRCL;	//系统时钟切换到IRCL	
}
/***********************************************************************************/

/***********************************************************************************
函数名  ：		Sys_Clk_Set_IRCL										 	
功能描述：		设置系统时钟为IRCL
输入参数：		无
返回值  ：		无
***********************************************************************************/
void Sys_Clk_Set_XOSCL(void)
{
	GPIO_Init(P52F,P52_XOSCL_OUT_SETTING);
	GPIO_Init(P53F,P53_XOSCL_IN_SETTING);
	CKCON |= XLCKE;
	//Delay_ms(2000);
	while(!(CKCON & XLSTA));
	CKSEL = (CKSEL&0xF8) | CKSEL_XOSCL;	
}
/*********************************************************************************************************************/


void Sys_Clk_Switch(u8 Clk)
{
	switch(Clk)
	{	
		case CKSEL_IRCH : 	CKSEL = (CKSEL&0xF8) | CKSEL_IRCH ;		break;
		case CKSEL_IRCL : 	CKSEL = (CKSEL&0xF8) | CKSEL_IRCL ;		break;
		case CKSEL_XOSCL: 	CKSEL = (CKSEL&0xF8) | CKSEL_XOSCL;		break;
		default: break;	
	}	

}
/*********************************************************************************************************************/


void RTC_WriteHour(unsigned char hour)  //hour=0~23
{
	RTCON |= RTCWE(1);
	RTCH = (RTCH&0xE0)|hour;
	Delay_50us(1);
	RTCON &= ~RTCWE(1); 
}
void RTC_WriteMinute(unsigned char minute) //minute=0~59
{
	RTCON |= RTCWE(1);
	RTCM = minute;
	Delay_50us(1);
	RTCON &= ~RTCWE(1); 
}
void RTC_WriteSecond(unsigned char second) //second=0~59
{
	RTCON |= RTCWE(1);
	RTCS = second;
	Delay_50us(1);
	RTCON &= ~RTCWE(1); 
}
/* 例如，设置闹钟时间为 11:30:00，时、分、秒比较全使能，程序如下： */
void F_RTM_INIT(void)
{
	RTAH = 11;  //设置闹钟小时
	RTAM = 30;  //设置闹钟分
	RTAS = 00;  //设置闹钟秒
	RTCON |= SCE(1)|MCE(1)|HCE(1);  //时、分、秒比较使能
}

/* RTC 初始化程序如下： */

void F_RTC_INIT(void)
{
	P52F = 3;
	P53F = 3;
	CKCON |= XLCKE;
	while(!(CKCON & XLSTA));
//	RTCON = RTCE(1) | MSE(1) | HSE(1); //RTC 使能，毫秒中断使能，半秒中断使能
	RTCON = RTCE(1) | MSE(1) | HSE(0); //RTC 使能，毫秒中断使能，半秒中断失能
	Delay_50us(6); //RTC 使能后必须延时 300us 再写入时间， 否则写入时间可能无效。
	RTC_WriteHour(11);  //写入小时
	RTC_WriteMinute(29); //写入分
	RTC_WriteSecond(0); //写入秒
	//F_RTM_INIT();  //设置闹钟
	RTMSS = 0;  //设置毫秒中断时间
	INT8EN = 1; //开启 RTC 中断
}

void F_RAM_INIT(void)
{
	SysTime.Day   = 19;
    SysTime.Month = 4;
    SysTime.Year  = 22;
    Temp.Display  = TEMP_INVALID;
	CntTime.TempRead = D_InitTempReadCnt-R_ID_ADD64MS;
	CntTime.LowPowerRead = D_DetecBattery-2;//读取电量
	CntTime.TestSLEEP = 13;
}

void F_TM2_INIT(void)
{
	P25F = P25_T2CP_SETTING;	 
	
	T2CON = TR2(0) | T2R(0) | T2IE(1) | UCKS(0) | T2P(0); 																				                                                     
//	T2MOD = CCFG(1) | T2M(2);				//设置为抓取模式，下降沿有效
	T2MOD = CCFG(3) | T2M(2);				//设置为抓取模式，上升沿有效
	T2CON |= TR2(1);   							//定时器2使能
	ET2 = 1;    										//定时器2中断使能
	
}

