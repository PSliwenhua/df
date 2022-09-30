#include "Main.h"

int F_Calib_ChangeCtoF(int temp)
{
	temp = temp*18;//度C转换度F,两位小数点、保留1位	
	// 四舍五入
	if(temp < 0)
		temp -= 5;
	else
		temp += 5;
	temp /= 10;
	return temp;
}
int F_Calib_ChangeFtoC(int temp)
{
//	temp = (temp*10-3200+9)/18;
	temp = temp*10;
	if(temp<0)
		temp -= 9;
	else
		temp += 9;
	return temp/18;
}
int F_ChangeCtoF(int temp)
{
	temp = temp*18+3200;//度C转换度F,两位小数点、保留1位	
	// 四舍五入
	if(temp < 0)
		temp -= 5;
	else
		temp += 5;
	temp /= 10;
	return temp;
}

int F_ChangeFtoC(int temp)
{
//	temp = (temp*10-3200+9)/18;
	temp = temp*10-3200;
	if(temp<0)
		temp -= 9;
	else
		temp += 9;
	return temp/18;
}

void F_GetTempCalibCheak()
{
	//////uart_printf ("CF = %u\n",(u16)TheVa.Param.Mode.Bit.bit0);
	switch(TheVa.Param.Mode.Bit.bit0)
	{	case DTEMP_C: Temp.Display = Temp.C+TheVa.Param.Calib;break;	
		case DTEMP_F: Temp.Display = Temp.F+TheVa.Param.Calib;break;/* 温度校准单位转换-320 */
		default:break;	
	}
		////uart_printf ("Temp.C = %u\n",(u16)Temp.C);
		////uart_printf ("Temp.F = %u\n",(u16)Temp.F);
		////uart_printf ("TheVa.Param.Calib = %u\n",(u16)TheVa.Param.Calib);
		////uart_printf ("Temp.Display = %u\n",(u16)Temp.Display);
	if(Temp.Display >= TheVa.Param.HighTempAlarm)
		B_HighTempAlarm = 1;
	else
		B_HighTempAlarm = 0;
	if(Temp.Display <= TheVa.Param.LowTempAlarm)
		B_LowTempAlarm = 1;
	else
		B_LowTempAlarm = 0;
	//TheVa.Param.Calib = Temp.Calib;
	B_RefreshTemp = _EN;
}

void F_GetTemperatureCheak()
{
	s16 buf;
	if(B_GetTemp == _TRUE)
	{	
		buf = F_GetADCTemperature();
		//if(abs58(buf - Temp.C) <= 3)//消抖
		//	Temp.C = Temp.C;
		//else
			Temp.C = buf;
		if(Temp.C == TEMP_INVALID)
		{	Temp.C = TEMP_INVALID;
			Temp.Display = TEMP_INVALID;
		}
		else
		{	Temp.C -= 100;
			Temp.F = F_ChangeCtoF(Temp.C);/* 待优化 */
		}
		F_GetTempCalibCheak();
		F_Rf_Connect_Cmd(D_TheVa_DATA);
	}
}

void F_HeatingRadiatorOnOffCheakTask()
{
	//UUWORD Modelast;
	if(B_GetTemp == _TRUE)
	{	B_GetTemp = _FALSE;
	//	M_TESTTIME();
	//	M_TESTTIME();
	//	M_TESTTIME();
		
		//if(TheVa.Param.Mode.Bit.bit1)
		//{
		//	/* 度假模式 */
		//}
		//if(TheVa.Param.Mode.Bit.bit4)
		//{
		//	/* 防霜冻模式 */
		//}
		//if(TheVa.Param.Mode.Bit.bit5)
		//{
		//	/* 防水垢模式 */
		//}
		//if(TheVa.Param.Mode.Bit.bit3)
		//{
		//	/* 开窗控制模式 */
		//}
	//	F_HeatingRadiatorOnOffCheak();/* 制暖判断 */
	}
}

extern void F_TestRuningTemp(u16 StopTemp,u16 Temp);
extern void F_TestTimerSEG(Theva_TimerSEG* TimerSEG1);

void F_HeatingRadiatorOnOffCheak()
{   															/* 每分钟调用1次，定时时间段自动控制温控阀制暖开关功能 */
	u8 i;
	u16 StartTimer;												/* 启动时间 */
	u16 StopTimer;												/* 停止时间 */
	u16 RunningTimer;											/* 单段时间段总运行时长 */
	u16 NowTimerLong;											/* 当前时间段运行时长 */
	u8 BasicTimerSEG = 0;										/* 基础时间段标志位 */
	volatile Theva_TimerSEG * TimerSEG;
	if(CntTime.Motor != 0)										/* 温度检测间隔大于必须大于步进电机行程运行完毕时间。 */
		return;
	NowTimerLong = SysTime.Hour*60+SysTime.Minute;				/* 将当前时间转换为分钟单位 */
	for (i = _StartTime2; i <= _StartTime11; i++)				/* 默认时间段参数，单独配置 */
	{	
		TimerSEG = &TheVa.TSEG[i];
		if(((TimerSEG->StartTimer.wVal) == 0xFFFFu)
		 ||((TimerSEG->StopTimer.wVal ) == 0xFFFFu))
			continue;
		StartTimer = TimerSEG->StartTimer.Byte.byte0*60+TimerSEG->StartTimer.Byte.byte1;/*  */
		StopTimer  = TimerSEG->StopTimer.Byte.byte0*60+TimerSEG->StopTimer.Byte.byte1;	/* 待验证字节顺序 */
		if(StopTimer >= StartTimer)
			RunningTimer = StopTimer - StartTimer;				/* 将时间段结束时间转换为运行时长 */
		else
			RunningTimer = (1440 - StartTimer) + StopTimer;		/* 单日分钟数量时长1440分钟 */
		NowTimerLong -= StartTimer;
	//	F_TestTimerSEG(&TheVa.TSEG[i]);
		if((NowTimerLong < RunningTimer))						/* 切换温度单位复位，复位时间段默认参数 */
		{   
			if((TimerSEG->StartTemp > Temp.Display)		/* 回差判断 */
			 &&(TimerSEG->StopTemp > Temp.Display))
			{	
				if(B_MotorCtrlState != D_MotorOn)				
				{	B_MotorCtrlState = D_MotorOn;
					M_A1 = 0;
					//F_TestRuningTemp(TimerSEG->StopTemp,Temp.Display);/* 影响触摸功能 */
					CntTime.Motor = D_MotorTimer;
					CntTime.MotorPWM = -2;
					TM0_ENABLE();
					////////M_TESTTIME();
					Theva_Pv.HTD_TimerLong = 0;
				}else
					Theva_Pv.HTD_TimerLong++;
			}else if(Temp.Display > TimerSEG->StopTemp)	/* 推开是关闭止水、停止加热 */ /*吸合是打开水流、开启加热。 */
			{													
				if(B_MotorCtrlState != D_MotorOff)
				{	B_MotorCtrlState = D_MotorOff;
					M_B1 = 0;
					//F_TestRuningTemp(TimerSEG->StopTemp,Temp.Display);
					CntTime.Motor = D_MotorTimer;
					CntTime.MotorPWM = -2;
					TM0_ENABLE();
					////////M_TESTTIME();
					////////M_TESTTIME();
					////////M_TESTTIME();
					Theva_Pv.HTD_TimerLong = 0;
				}
			}
			BasicTimerSEG = 1;
			break;												/* 查询到当前时间，所在的时间段被使能，并且内进行时，则退出时间段查询 */
		}														/* APP设置时间段不能重合，否则将会出现问题 */
	}
	if(BasicTimerSEG == 0)
	{
		TimerSEG = &TheVa.TSEG[_StartTime1];					/* 基础时间段确认不用判断时间 */
		if((TimerSEG->StartTemp > Temp.Display)			/* 回差判断 */
		 &&(TimerSEG->StopTemp > Temp.Display))
		{
			if(B_MotorCtrlState != D_MotorOn)				
			{	B_MotorCtrlState = D_MotorOn;
				M_A1 = 0;
				//F_TestRuningTemp(TimerSEG->StopTemp,Temp.Display);
				CntTime.Motor = D_MotorTimer;
				CntTime.MotorPWM = -2;
				TM0_ENABLE();
				////////M_TESTTIME();
				Theva_Pv.HTD_TimerLong = 0;
			}else
				Theva_Pv.HTD_TimerLong++;
		}else if(Temp.Display > TimerSEG->StopTemp)
		{				
			if(B_MotorCtrlState != D_MotorOff)
			{	B_MotorCtrlState = D_MotorOff;
				M_B1 = 0;
				//F_TestRuningTemp(TimerSEG->StopTemp,Temp.Display);
				CntTime.Motor = D_MotorTimer;
				CntTime.MotorPWM = -2;
				TM0_ENABLE();
				////////M_TESTTIME();
				////////M_TESTTIME();
				////////M_TESTTIME();
				Theva_Pv.HTD_TimerLong = 0;
			}
		}
	}
}

void F_()
{



}



void F_CutTempUnitCF()
{
	TheVa.Param.Mode.Bit.bit0 ^= _EN;
	if(TheVa.Param.Mode.Bit.bit0 == DTEMP_C)
	{	
		TheVa.Param.StartTemp	  = F_ChangeFtoC(TheVa.Param.StartTemp		);
		TheVa.Param.StopTemp	  = F_ChangeFtoC(TheVa.Param.StopTemp		);
		TheVa.Param.HighTempAlarm = F_ChangeFtoC(TheVa.Param.HighTempAlarm  );
		TheVa.Param.LowTempAlarm  = F_ChangeFtoC(TheVa.Param.LowTempAlarm   );
		////uart_printf ("Calib = %u\n",(u16)TheVa.Param.Calib);
		TheVa.Param.Calib		  = (s8)F_Calib_ChangeFtoC(TheVa.Param.Calib	);
		////uart_printf ("Calib = %u\n",(u16)TheVa.Param.Calib);
	}else{
		TheVa.Param.StartTemp	  = F_ChangeCtoF(TheVa.Param.StartTemp		);
		TheVa.Param.StopTemp	  = F_ChangeCtoF(TheVa.Param.StopTemp		);
		TheVa.Param.HighTempAlarm = F_ChangeCtoF(TheVa.Param.HighTempAlarm  );
		TheVa.Param.LowTempAlarm  = F_ChangeCtoF(TheVa.Param.LowTempAlarm   );
		////uart_printf ("Calib = %u\n",(u16)TheVa.Param.Calib);
		TheVa.Param.Calib		  = (s8)F_Calib_ChangeCtoF(TheVa.Param.Calib	);
		////uart_printf ("Calib = %u\n",(u16)TheVa.Param.Calib);
	}
	F_GetTempCalibCheak();						/* 添加后看起来没有延迟。 */
	//TheVa_State.CMD = D_TheVa_DATA;			/* 不管温度是否发生变化，都会上报温度数据 */
	TheVa_State.CMD = D_TheVa_ModeParam;		/* 不管温度是否发生变化，都会上报温度数据 */
	TheVa_State.SendCnt = D_MaxSendFrameNum;	/* 切换单位及时上报。 */
	SaveFlag.wVal |= 1;

	//uart_printf ("CF = %u\n",(u16)TheVa.Param.Mode.Bit.bit0);
	//uart_printf ("pair = %u\n",(u16)TheVa.Param.Mode.ucVal);
	//uart_printf ("Remove = %u\n",(u16)TheVa.Param.Mode.ucVal);
}

