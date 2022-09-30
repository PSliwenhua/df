#include "Main.h"

u8 F_GetYearData(u8 ucYear)
{
	u8 ucWeek;
	ucWeek = ucYear + 6; //2000/1/1 Saturday//代入00年
	ucYear = (ucYear+3)>>2;					//=1
	ucWeek += ucYear;						//=7
	while(ucWeek >= 7)
		ucWeek -= 7;	
	return ucWeek;							//=0
}

u8 F_GetMaxDay(u8 ucMonth, u8 ucYear)
{
	if(ucMonth == 2)
	{
		if(0x00 == (ucYear&0x03));
			return 29;
		//return 28;
	}
	return T_MonthDays[ucMonth];
}

u8 F_GetWeek(u8 ucDay,u8 ucMonth,u8 ucYear)
{
	u8 ucWeek1, ucWeek2;
	ucWeek1 = F_GetYearData(ucYear);
	ucWeek2 = T_MonthWeek[ucMonth];
	if(ucYear & 0x03)
		ucWeek2 &= 0x0f;		//平年取低4位
	else
		ucWeek2 >>= 4;			//闰年取高4位
	ucWeek1 += ucWeek2;	
	ucWeek1 += ucDay;			//减去天数中多加的1
	ucWeek1--;
	while(ucWeek1 >= 7)
		ucWeek1 -= 7;
	return ucWeek1;
}

u8 F_GetRtcTime()
{
	SysTime.Second++;
	if(SysTime.Second < 60)//1)
		return	D_SECOND_INC;
	SysTime.Second = 0;
	B_RefreshTime = _TRUE;
	SysTime.Minute ++;
	if(SysTime.Minute < 60)//60)测试定时打开不能调分钟
		return	D_MINUTE_INC;//分钟进位
	SysTime.Minute = 0;
	SysTime.Hour ++;	
	if(SysTime.Hour < 24)//24)测试定时打开不能调小时
		return	D_HOUR_INC;//小时进位
	SysTime.Hour = 0;
	SysTime.Week ++;
	if(SysTime.Week >= 7)
		SysTime.Week = 0;
	SysTime.Day ++;
	if(SysTime.Day <= F_GetMaxDay(SysTime.Month,SysTime.Year))
		return	D_DAY_INC;//天进位
	SysTime.Day = 1;
	SysTime.Month ++;
	if(SysTime.Month <= 12)
		return	D_MONTH_INC;//月进位
	SysTime.Month = 1;
	SysTime.Year++;
	if(SysTime.Year > 99)
		SysTime.Year = 0;
	return	D_YEAR_INC;//年进位
}

void F_SysTimeCntTask()
{	
	SysTime.State = F_GetRtcTime();
	//有天进位获取1次，星期。
	SysTime.Week = F_GetWeek(SysTime.Day,SysTime.Month,SysTime.Year);
	switch(SysTime.State)
	{	case D_YEAR_INC  :		 
		case D_MONTH_INC :  	 	
		case D_DAY_INC	 :	SysTime.Week = F_GetWeek(SysTime.Day,SysTime.Month,SysTime.Year);		 	
		case D_HOUR_INC	 : 
		case D_MINUTE_INC:  /* B_GetTemp = _TRUE; */		  //break;	
		case D_SECOND_INC:  B_RefreshTime = _TRUE;	  break;	//每秒刷新
		default:break;
	};	
}

u8 F_CntServe(u8 *temp,u8 len)
{
	u8 buf = *temp;
	buf ++;
	if(buf >= len)
	{	buf = _FALSE;
		*temp = buf;
		return _TRUE;
	}
	else
		*temp = buf;
	return _FALSE;
}

u16 F_u16CntServe(u16 *temp,u16 len)
{
	u16 buf = *temp;
	buf ++;
	if(buf >= len)
	{	buf = _FALSE;
		*temp = buf;
		return _TRUE;
	}
	else
		*temp = buf;
	return _FALSE;
}

void F_ReturnNormalModeCntTask()
{   
	if(R_MODE != D_NOR)
	{	if(F_CntServe(&CntTime.ModeReturn,D_ReturnCnt)==_TRUE)
		{
			F_RstFramework();
		}
	}
}

void F_HeatingStateOnCntDispCheak()
{   
	static u8 LastHeatingStateOn;
	if(B_MotorCtrlState == D_MotorOn)
	{	//if(CntTime.Motor == 0)
			F_CntServe(&CntTime.HeatingStateOn,5);
	}else
		CntTime.HeatingStateOn = 0;
	if(LastHeatingStateOn != CntTime.HeatingStateOn)
	{	LastHeatingStateOn = CntTime.HeatingStateOn;
		B_RefreshOnHeatingIcon = _TRUE;
	}
}

void F_NOP(u16 NOPTT)
{
	while(NOPTT--)
	{
		_nop_();
	}
}
void F_LEDON()
{
	M_LEDOUT();
	M_LEDON();
	CntTime.BackLight = D_BackLightCnt;
}

void F_LEDOFF()
{
	M_LEDOUT();
	M_LEDOFF();
	CntTime.BackLight = _FALSE;
}

void F_BackLightDispDownCntTask()
{	 
	if(CntTime.BackLight)
	{	CntTime.BackLight--;	
		if(CntTime.BackLight == _FALSE)
			F_LEDOFF();
	}	
}

void F_Rf_RxTimeDownCntSleepTask()
{	 
	if(CntTime.RxTimeDown)
	{	CntTime.RxTimeDown--;	
		if(CntTime.RxTimeDown == _FALSE)
		{	CMT2300A_GoStby();
			CMT2300A_GoSleep();
			cmt_spi3_sdio_out();
			cmt_spi3_sdio_0();/* 必须做输出0，否则耗电130uA */
			////M_TESTTIME();
			////M_TESTTIME();
		}
	}
}

void F_Rf_Connect_Cmd(u8 cmd)
{	 
	if(LOCK1 == Pairing_Wait)
	{	TheVa_State.CMD = D_TheVa_REQPAIR;
		TheVa_State.SendCnt = D_AckSendFrameNum;
	}
	else if(LOCK1 == Pairing_Succeed)
	{	TheVa_State.CMD = cmd;
		if(TheVa_State.OfflineCnt == D_OfflineCnt)
			TheVa_State.SendCnt = D_AckSendFrameNum;
		else
			TheVa_State.SendCnt = D_MaxSendFrameNum;
	}
}

void F_TempReadDownCntTask()
{	 
	F_u16CntServe(&CntTime.TempRead,D_TempReadCycle);
	switch(CntTime.TempRead)
	{
		case D_PairCmdCnt	:	F_Rf_Connect_Cmd(D_TheVa_REQPAIR);	break;
		case D_AskCmdCnt1	:	
		case D_AskCmdCnt2	:	
		case D_AskCmdCnt3	:	
		case D_AskCmdCnt4	:	
		case D_AskCmdCnt5	:	

		case D_AskCmdCnt	:	F_Rf_Connect_Cmd(D_TheVa_ASK);		break;
		//case D_TempReadCnt	:	F_Rf_Connect_Cmd(D_TheVa_DATA);B_GetTemp = _TRUE;break;
		case D_TempReadCnt	:	B_GetTemp = _TRUE;break;
		default:break;
	}
}

void F_KeyScan_Pulse_Clear_TimerOutCntTask()
{
	if(Key.TimerOut)
	{	Key.TimerOut--;
		if(Key.TimerOut == _FALSE)
		{
			if(Key.Pulse != _FALSE)/* 必须加这个判断条件，否则直接赋值，导致按键长按无效 */
			{
				Key.Pulse = _FALSE;	
				Key.Now = KEY_NULL;
				Key.NowBuf = Key.Now;
				B_Starthead = 0;
			}
		}
	}
}

void F_SetSecDotDispIcon()
{
	if(R_MODE == D_NOR)
		B_RefreshSecDot = _TRUE;
}

void F_OnPowerLcdAllDispCntTask()
{
	if(CntTime.Lcd)
	{	CntTime.Lcd--;
		if(CntTime.Lcd == _FALSE)
		{	F_LcdAll(0x00);
			R_LcdFlag.wVal = 0xFFFFu;
		}
	}
}

void F_TestlCnt()
{
	static u8 lcdtest = 0;
	if(CntTime.TestSLEEP)
		CntTime.TestSLEEP--;
	F_CntServe(&lcdtest,10);
	/* F_DisplayShuzi(T_Number1_A1,lcdtest);
	F_DisplayShuzi(T_Number2_A1,lcdtest);
	F_DisplayShuzi(T_Number3_A1,lcdtest);
	F_DisplayShuzi(T_Number4_A1,lcdtest); */
	
}

void F_SetHmiDispFlag()
{
	if(R_MODE == D_SET)
		B_RefreshSetHmi = _TRUE;
}

void F_Gateway_Offline_4hzCnt_Cheak()
{
	if(LOCK1 == Pairing_Succeed)                /* 配对成功状态下 */
	{
		if(TheVa_State.OfflineCnt < D_OfflineCnt)
		{	TheVa_State.OfflineCnt++;
			if(TheVa_State.OfflineCnt == D_OfflineCnt)
			{
				TheVa.Param.Mode1.Bit.bit0 = D_Offline;
			}
		}
	}					 
}

void F_TimeSever()
{	
	if(B_64HzFlag == _TRUE)
	{   B_64HzFlag = _FALSE;
		F_KeyValueGetScan();
	//	F_KeyValueCheak();//检测高温低温报警，打开此函数的时候，导致按键键值被清除。导致无法实现按键功能
	//	F_Buz10hzBiBiAlarmCheakCntTask();
		F_OnPowerLcdAllDispCntTask();
		F_RemoveMasterIDDelay500msClear();
		F_Rf_RxTimeDownCntSleepTask();
		F_Rf_Ack_4hzTimeOutCntTask();
		F_KeyScan_Pulse_Clear_TimerOutCntTask();
		if(B_32HzFlag == _TRUE)
		{   B_32HzFlag = _FALSE;
			B_32HzFlash ^= _TRUE;
			if(B_16HzFlag == _TRUE)
			{   B_16HzFlag = _FALSE;
				B_16HzFlash ^= _TRUE;
				if(B_8HzFlag == _TRUE)
				{   B_8HzFlag = _FALSE;
					B_8HzFlash ^= _TRUE;
					F_TempReadDownCntTask();
					if(B_4HzFlag == _TRUE)
					{   B_4HzFlag = _FALSE;
						B_4HzFlash ^= _TRUE;
						F_Gateway_Offline_4hzCnt_Cheak();
						if(B_2HzFlag == _TRUE)
						{   B_2HzFlag = _FALSE;
							B_2HzFlash ^= _TRUE;
							F_SetSecDotDispIcon();
							F_SetHmiDispFlag();
							if(B_1HzFlag == _TRUE)
							{	B_1HzFlag = _FALSE;
								B_1HzFlash ^= _TRUE;
								F_SysTimeCntTask();
								F_SetHmiFlashCheak();
							//	F_BuzAlarmOverDownCnt();
								F_GetTemperatureCheak();
								F_HeatingRadiatorOnOffCheakTask();
								F_LvdDetectBattery();
								F_ReturnNormalModeCntTask();
								F_BackLightDispDownCntTask();
								F_HeatingStateOnCntDispCheak();
								F_TestlCnt();
								//M_TESTTIME();
							}
						}
					}
				}						
			}
		}
	}
}

