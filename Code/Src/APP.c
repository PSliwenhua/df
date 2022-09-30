#include "Main.h"

code u8 crc_table[256] = 
{
	0x00, 0x31, 0x62, 0x53, 0xc4, 0xf5, 0xa6, 0x97,
	0xb9, 0x88, 0xdb, 0xea, 0x7d, 0x4c, 0x1f, 0x2e,
	0x43, 0x72, 0x21, 0x10, 0x87, 0xb6, 0xe5, 0xd4,
	0xfa, 0xcb, 0x98, 0xa9, 0x3e, 0x0f, 0x5c, 0x6d,
	0x86, 0xb7, 0xe4, 0xd5, 0x42, 0x73, 0x20, 0x11,
	0x3f, 0x0e, 0x5d, 0x6c, 0xfb, 0xca, 0x99, 0xa8,
	0xc5, 0xf4, 0xa7, 0x96, 0x01, 0x30, 0x63, 0x52,
	0x7c, 0x4d, 0x1e, 0x2f, 0xb8, 0x89, 0xda, 0xeb,
	0x3d, 0x0c, 0x5f, 0x6e, 0xf9, 0xc8, 0x9b, 0xaa,
	0x84, 0xb5, 0xe6, 0xd7, 0x40, 0x71, 0x22, 0x13,
	0x7e, 0x4f, 0x1c, 0x2d, 0xba, 0x8b, 0xd8, 0xe9,
	0xc7, 0xf6, 0xa5, 0x94, 0x03, 0x32, 0x61, 0x50,
	0xbb, 0x8a, 0xd9, 0xe8, 0x7f, 0x4e, 0x1d, 0x2c,
	0x02, 0x33, 0x60, 0x51, 0xc6, 0xf7, 0xa4, 0x95,
	0xf8, 0xc9, 0x9a, 0xab, 0x3c, 0x0d, 0x5e, 0x6f,
	0x41, 0x70, 0x23, 0x12, 0x85, 0xb4, 0xe7, 0xd6,
	0x7a, 0x4b, 0x18, 0x29, 0xbe, 0x8f, 0xdc, 0xed,
	0xc3, 0xf2, 0xa1, 0x90, 0x07, 0x36, 0x65, 0x54,
	0x39, 0x08, 0x5b, 0x6a, 0xfd, 0xcc, 0x9f, 0xae,
	0x80, 0xb1, 0xe2, 0xd3, 0x44, 0x75, 0x26, 0x17,
	0xfc, 0xcd, 0x9e, 0xaf, 0x38, 0x09, 0x5a, 0x6b,
	0x45, 0x74, 0x27, 0x16, 0x81, 0xb0, 0xe3, 0xd2,
	0xbf, 0x8e, 0xdd, 0xec, 0x7b, 0x4a, 0x19, 0x28,
	0x06, 0x37, 0x64, 0x55, 0xc2, 0xf3, 0xa0, 0x91,
	0x47, 0x76, 0x25, 0x14, 0x83, 0xb2, 0xe1, 0xd0,
	0xfe, 0xcf, 0x9c, 0xad, 0x3a, 0x0b, 0x58, 0x69,
	0x04, 0x35, 0x66, 0x57, 0xc0, 0xf1, 0xa2, 0x93,
	0xbd, 0x8c, 0xdf, 0xee, 0x79, 0x48, 0x1b, 0x2a,
	0xc1, 0xf0, 0xa3, 0x92, 0x05, 0x34, 0x67, 0x56,
	0x78, 0x49, 0x1a, 0x2b, 0xbc, 0x8d, 0xde, 0xef,
	0x82, 0xb3, 0xe0, 0xd1, 0x46, 0x77, 0x24, 0x15,
	0x3b, 0x0a, 0x59, 0x68, 0xff, 0xce, 0x9d, 0xac
};

u8 GetCrc(u8 * lpBuff, u8 ucLen,u8 intcrc)
{
	u8 crc;
	crc = intcrc;
	while(ucLen)
	{
		ucLen--;
		crc = crc_table[*lpBuff ^ crc];
		lpBuff++;
	}
	return crc;
}

u8 GetSum(u8 * lpBuff, u8 ucLen)
{
	u8 checksum;
	checksum = 0;
	while (ucLen)
	{
		ucLen--;
		checksum += *lpBuff;
		lpBuff++;
	}
	return checksum;
}

u8 F_GetSum(u8 *addr, u8 length)
{
	u8 i;
	u8 sum = 0;
	for(i=0; i<length; i++)
		sum += *addr++;
	return sum;
}

u8 F_GetCRC(u8 *pBuff, u8 ucLen)
{
	u8 crc, i, ucTemp1, ucTemp2;
	crc = 0xFF;
	while(ucLen--)
	{
		ucTemp1 = *pBuff++;
		for (i=0; i<8; i++)
		{
			ucTemp2 = crc ^ ucTemp1;
			crc = crc << 1;
			if(ucTemp2 & 0x80)
			{
				crc |= 0x01;
				crc = crc ^ 0x30;
			}
			ucTemp1 = ucTemp1 << 1;
		}
	}	
	return crc;
}

void F_SwapBigEnd(u8* a , u8* b) 
{
	u8 t = *a;
	*a = *b;
	*b = t;
}

u8 Mystrcpy(char *strDest, const char *strSrc)
{
	u8 Len = 0;
    while( *(strSrc+Len) != '\0')
	{
		*(strDest+Len) = *(strSrc+Len);
		Len++;
	}
    return  Len; 
}





void F_OnPower()
{
	//B_PowerMode = D_PowerOn;
	B_PowerModeLast = D_PowerOn;
	R_MODE = D_NOR;
	//FRAME_MODE = _TRUE;	
	CntTime.Lcd = 192;//64*3;

}
void F_OffPower()
{
	//B_PowerMode = D_PowerOff;
	B_PowerModeLast = D_PowerOff;
	R_MODE = D_OFF;

}


void F_Enter_TestMode()
{
	R_MODE = D_TES;
}

void F_SetShowSoftVerFlag()
{
	F_LcdAll(0x00);
	R_TEST = D_SHOWVER;
}
void F_SetShowLcdAllFlag()
{
	F_LcdAll(0x00);
	R_TEST = D_SHOWALL;
}

void F_SetOnOffMotorFlag()
{
	R_TEST = D_MOTORONOFF;
}

void F_Return_NorMode()
{
	//Key.Speed = _FALSE;
	R_TEST = D_SHOWALL;
	CntTime.ModeReturn = _FALSE;//保存设置参数到EEPROM。
	F_RstFramework();
}
void F_SetHmiFlashCheak()
{
	if(Key.Up == KEY_NULL)
	{	if(R_MODE == D_SET) 	
			B_IncDecKeyHold = _FALSE;	
	}
}

/* ***************************************************************** */
/* ***************************************************************** */

void F_ShowSoftVer()
{	
	F_DisplayShuzi(T_Number2_A1,Shuzi_V);
	F_DisplayShuzi(T_Number3_A1,VERSION0);
	F_DisplayShuzi(T_Number4_A1,VERSION1);
}	
void F_ShowLcdAll()
{	
	F_LcdAll(0xFF);
}	

void F_OnOffMotor()
{
	return;
}

void F_RefreshTestHmi()
{
	switch(R_TEST)
	{	case D_SHOWVER:		F_ShowSoftVer();	break;		
		case D_SHOWALL:		F_ShowLcdAll();		break;			
		case D_MOTORONOFF:	F_OnOffMotor();		break;
		default:break;
	}	
}

/* ***************************************************************** */
/* ***************************************************************** */
void F_SetStartTimer(u16* Timer)
{
	u8 buf;
	UWORD Time;
	s8 Minue;
	s8 Hour;
	Time.wVal = *Timer;
	Minue = Time.sByte.sbyte0;//小时有符号
	Hour  = Time.sByte.sbyte1;//分钟有符号
	buf = 24;
	if(B_INCFLAG)
	{	Minue += 1;//10;进位
		if(Minue >= 60)
		{	Minue = 0;
			Hour += 1;
			if(Hour >= buf)
				Hour = 0;
		}
	}
	else if(B_DECFLAG)
	{	Minue -= 1;
		if(Minue < 0)
		{	Minue = 60-1;
			Hour -= 1;
			if(Hour < 0)
				Hour = buf-1;
		}
	}
	Time.sByte.sbyte0 = Minue;//小时有符号
	Time.sByte.sbyte1 = Hour ;//分钟有符号
	*Timer = Time.wVal;
}

void F_SetSvTemp(u16* SvTemp)
{
	u16 MaxTemp;
	u16 MinTemp;
	switch(TheVa.Param.Mode.Bit.bit0)
	{	case DTEMP_C: MaxTemp = 350; MinTemp = 100;break;	
		case DTEMP_F: MaxTemp = 950; MinTemp = 50; break;
		default:break;	
	}
	if(B_INCFLAG)
	{	if((*SvTemp) < MaxTemp)
			(*SvTemp)++;
	}
	else if(B_DECFLAG)
	{	if((*SvTemp) > MinTemp)
			(*SvTemp)--;
	}
	//温度 单位换算  //切换单位复位默认参数。
}

void F_Enter_SetMode()
{
	R_MODE = D_SET;
	R_MENU = 0;
	R_1LevelSetMENU = 0;
	B_SET_NOR = _TRUE;
	////M_TESTTIME();
}

void F_MenuNext()
{
	F_CntServe((u8 *)&R_1LevelSetMENU,D_1MENULEN);
	switch(R_1LevelSetMENU)
	{	
		case D_1StartTemp      : Key.Speed = 0;break;
		case D_1StopTemp       : break;
		case D_1HighTemp       : break;
		case D_1LowTemp        : break;
		case D_1Calib	       : break;
		default:	break;
	}	
}




void F_SetDataIncFlag()
{
	B_INCFLAG = _TRUE;
	B_IncDecKeyHold = _TRUE;
}

void F_SetDataDecFlag()
{
	B_DECFLAG = _TRUE;
	B_IncDecKeyHold = _TRUE;
}

void F_RstFramework()
{
    //DP_FLAG.wVal = 0xFFFFu;     
//    FRAME_CanPair = 0; 
//    FRAME_VerDev  = 0;
	R_MENU = 0;
	R_MODE = D_NOR; 
	R_LcdFlag.wVal = 0xFFFFu;
}

void F_HandFaMenCtrl()
{
	if(CntTime.Motor != 0)
		return;
	B_MotorCtrlState ^= _EN;
	switch(B_MotorCtrlState)
	{	
		case D_MotorOn:  M_A1 = 0;	break;
		case D_MotorOff: M_B1 = 0;	break;
		default: break;	
	}	
	CntTime.Motor = D_MotorTimer;
	CntTime.MotorPWM = -2;
	TM0_ENABLE();
}

