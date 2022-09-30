#include "Main.h"

code u8 T_Shuzi[ Shuzi_Max ] =
{ 
  0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,//0 to 9
  0x77,0x7c,0x39,0x5E,0x79,0x71,0x76,0x06,0x38,0x37,//A b C d E F H I L N
  0x3f,0x73,0x3e,0x63,0x5c,//O,P,U 上o 下o 
  0x40,0x00,//-  NULL
  0x78,0x6D,0x50,0x7E,0x3D//T S r U
};

code u8 T_A_SegDispEn[2][7] =
{
    {COM0,COM1,COM3,COM3,COM2,COM1,COM2,},/* B */
    {COM3,COM2,COM1,COM0,COM1,COM3,COM2,},/* A */
};

code u8 T_A_SegDotAddr[2][28] =
{   
    {   SEG4, SEG5 ,SEG5 ,SEG4 ,SEG4 ,SEG4 ,SEG5 , /* T_Number_5 */   
        SEG6, SEG7 ,SEG7 ,SEG6 ,SEG6 ,SEG6 ,SEG7 , /* T_Number_4 */
        SEG8, SEG9 ,SEG9 ,SEG8 ,SEG8 ,SEG8 ,SEG9 , /* T_Number_3 */
        SEG10,SEG11,SEG11,SEG10,SEG10,SEG10,SEG11, /* T_Number_2 */
    },
    {   SEG12,SEG12,SEG12,SEG12,SEG13,SEG13,SEG13, /* T_Number_1 */
        SEG10,SEG10,SEG10,SEG10,SEG11,SEG11,SEG11, /* T_Number_2 */
        SEG8 ,SEG8 ,SEG8 ,SEG8 ,SEG9 ,SEG9 ,SEG9 , /* T_Number_3 */
        SEG6 ,SEG6 ,SEG6 ,SEG6 ,SEG7 ,SEG7 ,SEG7 , /* T_Number_4 */
    },
};                     

code u8 T_A_XdotDispEn[2][11] =
{
    {COM0,COM0,COM1,COM2,COM3,COM3,COM2,COM0,COM0,COM1,COM0,},
    {COM0,COM0,COM1,COM2,COM3,COM3,COM2,COM0,COM0,COM1,COM0,},
};

code u8 T_A_XdotAddr[2][11] =
{
    {SEG5 ,SEG15,SEG15,SEG15,SEG15,SEG2 ,SEG2 ,SEG11,SEG14,SEG14,SEG9 ,}, 
    {SEG13,SEG1 ,SEG1 ,SEG1 ,SEG1 ,SEG14,SEG14,SEG3 ,SEG2 ,SEG2 ,SEG7 ,},
};   

u8 F_Change5BCD(long num,u8 dec)
{
	if(num < 0)
	{	num = ~num + 1;
		R_Bcd[5] = Shuzi_NEG;
	}
	else
		R_Bcd[5] = Shuzi_NULL;
	R_Bcd[4] = 0;
	while(num>=10000)
	{	num -= 10000;
		R_Bcd[4] ++;
	}
	R_Bcd[3] = 0;
	while(num>=1000)
	{	num -= 1000;
		R_Bcd[3] ++;
	}
	R_Bcd[2] = 0;
	while(num>=100)
	{	num -= 100;
		R_Bcd[2] ++;
	}
	R_Bcd[1] = 0;
	while(num>=10)
	{	num -= 10;
		R_Bcd[1] ++;
	} 
	R_Bcd[0] = num;

	if(R_Bcd[4] == 0)
	{	R_Bcd[4] = R_Bcd[5];
		if(R_Bcd[3] == 0)
		{	R_Bcd[3] = R_Bcd[4];
			R_Bcd[4] = Shuzi_NULL;
			if(R_Bcd[2] == 0)
			{	R_Bcd[2] = R_Bcd[3];
				R_Bcd[3] = Shuzi_NULL;
				if(dec == _ONE)
				{	if(R_Bcd[1] == 0)
					{	R_Bcd[1] = R_Bcd[2];
						R_Bcd[2] = Shuzi_NULL;
					}//当数据为0时，屏蔽掉后显示为00， 用于分钟显示
				}
			}
		} 
	}
	return _NO_POINT;
}

void F_DisplayShuzi(u8 addr,u8 num)
{
	volatile u8 i = 0;
	volatile u8 temp = 0;
	volatile u8 val = 0;/* 需要volatile 修饰，否则显示不正常 */
	temp = T_Shuzi[num];
	for(i=0;i<7;i++)
	{
		INDEX = T_A_SegDotAddr[LcdDisp][addr];
		val = T_A_SegDispEn[LcdDisp][i];
		if(temp&0x01)
			set(LCDAT,val);
		else
			clr(LCDAT,val);
		addr ++;
		temp >>= 1;
	} 	
}

void F_DisplayDot(u8 dot,u8 Status)
{
	volatile u8 i = 0;
	volatile u8 val = 0;
	INDEX = T_A_XdotAddr[LcdDisp][dot];
	val = T_A_XdotDispEn[LcdDisp][dot];
	if(Status)
		set(LCDAT,val);
	else
		clr(LCDAT,val);
}

void F_GetBcd(u8 shuzi)
{
	R_Bcd[3] = shuzi;
	R_Bcd[2] = shuzi;
	R_Bcd[1] = shuzi;
	R_Bcd[0] = shuzi;
}

void F_RefreshRfConnectStateIcon()
{
	if(LOCK1 == Pairing_Wait) /* 这个标志位不行 */
		F_DisplayDot(Icon_RF_Connect,B_2HzFlash);/* 等待配对2hz显示RF连接图标 */
	else if(TheVa.Param.Mode1.Bit.bit0 == D_Offline)
    	F_DisplayDot(Icon_RF_Connect,B_2HzFlash);/* 离线重连2hz显示RF连接图标 */
    else
        F_DisplayDot(Icon_RF_Connect,_TRUE);	/* 显示RF连接图标 */
    
}

void F_RefreshHeatingRadiatorStateIcon()
{
	u8 i;
	if(B_RefreshOnHeatingIcon == _TRUE)
	{	B_RefreshOnHeatingIcon = _FALSE;
		for(i = Icon_OnHeating1; i <= Icon_OnHeating4; i++)
			F_DisplayDot(i,_FALSE);//掉电清除
		for(i = Icon_OnHeating1; i <= CntTime.HeatingStateOn; i++)
			F_DisplayDot(i,_TRUE);
	}
}

void F_RefreshBattery()
{	

}

void F_RefreshSysTime()
{
	if(B_RefreshSecDot == _TRUE)			
	{	B_RefreshSecDot = _FALSE;
	}
	if(B_RefreshTime == _TRUE)
	{	B_RefreshTime = _FALSE;
	}
}

void F_RefreshSetTempUnitCF(u8 Flash)
{
	if(Flash)
	{	F_DisplayDot(Icon_Temp_Dot,_TRUE);
		F_DisplayDot(Icon_Temp_monCF,_TRUE);
		F_DisplayDot(Icon_TempC,TheVa.Param.Mode.Bit.bit0 == DTEMP_C);
		F_DisplayDot(Icon_TempF,TheVa.Param.Mode.Bit.bit0 == DTEMP_F);
	}else{
		F_DisplayDot(Icon_Temp_Dot,_FALSE);
		F_DisplayDot(Icon_Temp_monCF,_FALSE);
		F_DisplayDot(Icon_TempC,_FALSE);
		F_DisplayDot(Icon_TempF,_FALSE);
	}
}

void F_RefreshTemp()
{
	static u8 LcdDispBuf;
	if(Temp.Display == TEMP_INVALID)
		F_GetBcd(Shuzi_NEGATIVE);
	else
		F_Change5BCD(Temp.Display,_DEC); 
	if(LcdDispBuf != LcdDisp)
	{
		LcdDispBuf = LcdDisp;
		F_LcdAll(0x00);
	}
	if(LOCK1 == Pairing_Succeed)
		F_DisplayShuzi(T_Number1_A1,Theva_Pv.Ch+1);
	else
		F_DisplayShuzi(T_Number1_A1,Shuzi_NULL);
	if(B_1HzFlash) 
	{	if((B_HighTempAlarm)||(B_LowTempAlarm))
		{	F_DisplayShuzi(T_Number2_A1,Shuzi_A);
			F_DisplayShuzi(T_Number4_A1,Shuzi_NULL);
			F_RefreshSetTempUnitCF(_FALSE);
			if(B_HighTempAlarm)
				F_DisplayShuzi(T_Number3_A1,Shuzi_H);
			else if(B_LowTempAlarm)
				F_DisplayShuzi(T_Number3_A1,Shuzi_L);
		}else if(B_LowBattery){
			F_RefreshSetTempUnitCF(_FALSE);
			F_DisplayShuzi(T_Number2_A1,Shuzi_L);
			F_DisplayShuzi(T_Number3_A1,Shuzi_o1);
			F_DisplayShuzi(T_Number4_A1,Shuzi_NULL);
		}
	}else
	{	F_RefreshSetTempUnitCF(_TRUE);
		F_DisplayShuzi(T_Number2_A1,R_Bcd[2]);
		F_DisplayShuzi(T_Number3_A1,R_Bcd[1]);
		F_DisplayShuzi(T_Number4_A1,R_Bcd[0]);
	}
}
     
void F_RefreshMainHmi()
{
	if(CntTime.Lcd){
		F_LcdAll(0xFF);
		return;
	}
	//////uart_printf ("RefreshTemp");
	//F_RefreshSysTime();
	F_RefreshTemp();
	//F_RefreshBattery();
    F_RefreshRfConnectStateIcon();
	F_RefreshHeatingRadiatorStateIcon();
}



void F_RefreshSetHmi()
{
	s16 ndata = 0;
	F_DisplayDot(Icon_Stop_Temp ,_FALSE);
	F_DisplayDot(Icon_Start_Temp ,_FALSE);
	switch(R_1LevelSetMENU)
	{	
		case D_1StartTemp   : ndata = TheVa.Param.StartTemp     ; F_DisplayShuzi(T_Number1_A1,Shuzi_NULL);F_DisplayDot(Icon_Start_Temp ,_TRUE);break;
		case D_1StopTemp    : ndata = TheVa.Param.StopTemp      ; F_DisplayShuzi(T_Number1_A1,Shuzi_NULL);F_DisplayDot(Icon_Stop_Temp ,_TRUE);break;
		case D_1HighTemp    : ndata = TheVa.Param.HighTempAlarm ; F_DisplayShuzi(T_Number1_A1,Shuzi_H); break;
		case D_1LowTemp     : ndata = TheVa.Param.LowTempAlarm  ; F_DisplayShuzi(T_Number1_A1,Shuzi_L); break;
		case D_1Calib	    : ndata = TheVa.Param.Calib		    ; F_DisplayShuzi(T_Number1_A1,Shuzi_C); break;
		default:	break;
	}
	if((B_2HzFlash)||(B_IncDecKeyHold))
		F_Change5BCD(ndata,_DEC); 
	else
		F_GetBcd(Shuzi_NULL);//闪烁
	F_DisplayShuzi(T_Number2_A1,R_Bcd[2]);
	F_DisplayShuzi(T_Number3_A1,R_Bcd[1]);
	F_DisplayShuzi(T_Number4_A1,R_Bcd[0]);
	F_RefreshSetTempUnitCF((B_2HzFlash)||(B_IncDecKeyHold));
}

void F_LcdRefreshSever()
{	
	if(R_LcdFlag.wVal)
	{	
		if(R_MODEBUF != R_MODE)
		{	R_MODEBUF = R_MODE;
			F_LcdAll(0x00);
		}
		switch(R_MODE)
		{	case D_NOR:	F_RefreshMainHmi();	break;	
			case D_SET:	F_RefreshSetHmi();	break;
			case D_TES:	F_RefreshTestHmi();	break;
		//	case D_OFF:	F_LcdAll(0x00);	F_LEDOFF();	break;		
			default:break;
		}
		R_LcdFlag.wVal = 0x0000u;
	}	
}	

void F_LcdSetDot(u8 Addr,u8 Data)
{
	u8* p;
	p = (u8 *)(0x0400u + Addr);
	*p = Data;
}

void F_PowerOnLcdAllCheak()
{
	F_LEDON();
	R_LcdFlag.wVal = 0xFFFFu;
	F_LcdAll(0xFF);
	CntTime.Lcd = 192;
	while(CntTime.Lcd)
	{
		//Delay_ms(1);//GCC_CLRWDT();
		B_64HzFlag = _FALSE;
		while(B_64HzFlag == _FALSE);
		CntTime.Lcd--;
		Count64Hz = 0;
	}
	F_LcdAll(0x00);
}

