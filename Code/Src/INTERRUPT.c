#include "Main.h"

void TIMER0_ISR (void) interrupt 1 		 //每1ms产生中断
{
	TH0 = TH_VAL;
	TL0 = TL_VAL;
    if(CntTime.Motor)
    {
        CntTime.MotorPWM++;
        if(CntTime.MotorPWM==4)
            CntTime.MotorPWM = 0;
        switch(B_MotorCtrlState)
        {	
            case D_MotorOn: 
                switch(CntTime.MotorPWM)
                {	case -1: M_EN = 1;	break;
                    case 0: M_A1 ^= 1;	break;
                    case 2: M_B1 ^= 1;	break;
                    default: break;	
                }	
                break;
            case D_MotorOff: 
                switch(CntTime.MotorPWM)
                {	case -1:M_EN = 1;	break;
                    case 0: M_B1 ^= 1;	break;
                    case 2: M_A1 ^= 1;	break;
                    default: break;	
                }	
                break;
            default: break;	
        }	
        CntTime.Motor--;
        if(CntTime.Motor == _FALSE)
        {	M_EN = 0;
			TM0_DISABLE();
			MotorCapCnt = 0;
        //    STM0_DISABLE();
            D_SaveThevaDATA = 1;
            TheVa.Param.Mode1.Bit.bit2 = B_MotorCtrlState;
        }
		if(T2CapValueBuf != T2CapValue)
		{
			T2CapValueBuf = T2CapValue;
			T2CycleIntvBuf = T2CycleIntv;
			T2CycleIntv = 0;
			T2CycleFlag1 = 1;
			if(CntTime.Motor<(D_MotorTimer-10))
			{	if(T2CycleIntvBuf<8)
				{
					M_EN = 0;
					TM0_DISABLE();
					MotorCapCnt = 0;
					CntTime.Motor = 0;
					D_SaveThevaDATA = 1;
					TheVa.Param.Mode1.Bit.bit2 = B_MotorCtrlState;
				}else
					MotorCapCnt++;
			}
		}
		T2CycleIntv++;
    }
}

void TIMER2_ISR (void) interrupt 5 
{
	if(T2MOD & TF2)		  //定时器2溢出中断
	{
		T2MOD = (T2MOD&0x1F) | TF2;
		////M_TESTTIME();
	}
	if(T2MOD & CF2)		  //定时器2抓取中断
	{
		T2MOD = (T2MOD&0x1F) | CF2;
		T2CapValue = T2CH*256 + T2CL;		//读取定时器抓取值
		////M_TESTTIME();
	}
}


void INT0_ISR (void) interrupt 0
{
	CKSEL = (CKSEL&0xF8) | CKSEL_IRCH;	//系统时钟切换到IRCH
	TOUCH_SDA_IN; 
	if(B_Starthead == 0)
	{	B_Starthead = 1;
		//CKSEL = (CKSEL&0xF8) | CKSEL_IRCH;
		++Key.Pulse;
		return;
	}
	Key.TimerOut = D_KeyTimerOut;
	if(++Key.Pulse <= 9)
	{
		Key.Now<<=1;
		if(TOUCH_SDA_IO)
		{	Key.Now |= 0x01;
			//M_TESTTIME();
		}
		else
		{	Key.Now &= ~0x01;
			//M_TESTTIME();//M_TESTTIME();
		}
	}
	else if(Key.Pulse >= 10)
	{
		Key.Pulse = 0;
		if(Key.Now == TOUCH_KEYUP_VALUE)//按键释放
			Key.Now = KEY_NULL;
		Key.NowBuf = Key.Now;
		B_Starthead = 0;
		TOUCH_SDA_OUT; 
		TOUCH_SDA_OUT1; 
	}
}

void INT1_ISR (void) interrupt 2
{
   // if(HaltFlag == 1)

}

void INT2_ISR (void) interrupt 7
{
	if(EPIF & 0x01)
	{
		EPIF = 0x01;
	}
}

void INT4_ISR (void) interrupt 9	//LVD中断服务程序
{
	if(LVDCON & LVDF)
	{
		LVDCON |= LVDF;			    //清除LVD中断标志
		B_LowBattery = _TRUE;
		/* 立即上报 */
	}		
}

void RTC_ISR (void) interrupt 13
{
	if(RTCIF & RTC_MF)  //毫秒中断
	{
		RTCIF = RTC_MF; //毫秒中断服务程序
        Framework.Count256Hz++;
        GCC_CLRWDT();
        if(!(Framework.Count256Hz&0x01))
        {     {B_128HzFlag  = _TRUE;}
            if(!(Framework.Count256Hz&0x03))
            {    {B_64HzFlag  = _TRUE;}
                if(!(Framework.Count256Hz&0x07))
                {    {B_32HzFlag  = _TRUE;}
                    if(!(Framework.Count256Hz&0x0F))
                    {    {B_16HzFlag  = _TRUE;}
                        if(!(Framework.Count256Hz&0x1F))
                        {    {B_8HzFlag  = _TRUE;}
                            if(!(Framework.Count256Hz&0x3F))
                            {    {B_4HzFlag  = _TRUE;}
                                if(!(Framework.Count256Hz&0x7F))
                                {    {B_2HzFlag  = _TRUE;}
                                    if(Framework.Count256Hz==0)
                                        {B_1HzFlag  = _TRUE;}
                                }
                            }
                        }
                    }						
                }
            }
        }
		/* 开启半秒中断后，对，256Hz中断计时有影响，故：关闭2hz中断 */
		/* 现象:  在2hz中断翻转时候，256hz也翻转。看时序 */
	}
	if(RTCIF & RTC_HF)  //半秒中断
	{
		RTCIF = RTC_HF;
		SysTime.Second = RTCS;
		SysTime.Minute = RTCM;
		SysTime.Hour = RTCH;
		//半秒中断服务程序
	} 
	if(RTCIF & RTC_AF)  //闹钟中断
	{
		RTCIF = RTC_AF; 
		//闹钟中断服务程序
	}
} 