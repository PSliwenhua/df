#include "Main.h"

void F_KeyValueGetScan()
{
	if(Key.Last != Key.NowBuf)			
	{	if(++Key.DebounceCnt > 2)
		{	B_KeyChange ^= _TRUE;
			Key.DebounceCnt = _FALSE;
		}
	}
	if(B_KeyChange)												
	{	Key.ValueBuf = Key.NowBuf ^ Key.Last;						
		Key.Down = Key.ValueBuf ^ Key.Last;     				
		Key.Up = Key.ValueBuf ^ Key.NowBuf;						
		if(Key.Down)											
		{	Key.KeepCnt++;										
			if(Key.KeepCnt == D_LongKey64Hz)	 								
				Key.Value = Key.Last<<1;
			else if(Key.KeepCnt >= D_LongKey64Hz+Key.Speed)	// 					  	   																					
			{	Key.KeepCnt = D_LongKey64Hz+1;					// 避免长按计时溢出  	   																											
				if(R_MODE == D_SET)  			  	   																													
				{	if(MEN_KEY != Key.Last)  				  	   																													
						Key.Value = Key.Last<<1;				// 长按连发功能赋键值	  
				} 																										
			} 																
		}												
		else if(Key.Up)											
		{	if(Key.KeepCnt < D_LongKey64Hz)								
			{	Key.Value = Key.ValueBuf;		
				////M_TESTTIME();
				////M_TESTTIME();
			}				
			else												
				Key.Value = KEY_NULL;							
			Key.KeepCnt = KEY_NULL;											
			Key.DebounceCnt = _FALSE;								
		}														
		Key.Last = Key.NowBuf;										
	}															
}																

void F_KeyValueCheak()
{
	if(Key.Value)
	{
		CntTime.ModeReturn = _FALSE;
		F_LEDON();
		/* if(F_KeyBreakFault())//没有蜂鸣器功能，无需打断故障蜂鸣器报警
		{
			//////uart_printf ("fault\n");
			return;			
		} */
	}
}

void F_SwLCD_Both_Sides_Now()
{
	LcdDisp ^= 1;
}

void F_KeySever()
{
	u8 KeyValueValid = 1;
	if(Key.Value)
	{	
		switch(R_MODE)
		{	case D_NOR:	
				switch(Key.Value)
				{//	case POW_KEY2S:	 F_OffPower();			 break;
					case DEC_KEY2S:   							break;	
					case INC_KEY2S:	 						 	break;	
					case MEN_KEY2S:  F_Enter_SetMode();		 	break;	
					case MEN_KEY:  	 F_CutTempUnitCF();		 	break;	
					case DEC_KEY: 	 F_SwLCD_Both_Sides_Now();	break;	
					case INC_KEY:	 F_HandFaMenCtrl();		 	break;
					case TEST_KEY2S: F_Enter_TestMode();	 	break;	
					default: KeyValueValid = 0;break;
				}break;	
			case D_SET:	
				switch(Key.Value)
				{	case MEN_KEY:	 F_MenuNext();			 	break;
				//	case MOD_KEY:	 F_SetStartTimeEnDn();	 	break;
					case INC_KEY:	 F_SetDataIncFlag();	 	break;
					case DEC_KEY:	 F_SetDataDecFlag();	 	break;	
					case INC_KEY2S:	 F_SetDataIncFlag();	 	break;
					case DEC_KEY2S:	 F_SetDataDecFlag();	 	break;
					case MEN_KEY2S:	 F_Return_NorMode();	 	break;
					default: KeyValueValid = 0;break;
				}break;	
			case D_TES:	
				switch(Key.Value)
				{	case MEN_KEY:	 F_SetShowLcdAllFlag();	 	break;
					case INC_KEY:	 F_SetShowSoftVerFlag(); 	break;
					case DEC_KEY:	 break;	
					case MEN_KEY2S:	 F_Return_NorMode();	 	break;
					default: KeyValueValid = 0;break;
				}break;
			/* case D_OFF:	
				switch(Key.Value)
				{	case POW_KEY:	 F_OnPower();			 break;
					case POW_KEY2S:	 F_OnPower();			 break;
					default:break;
				}break; */
			default: KeyValueValid = 0;break;
		}
		//F_KeyVoiceCheak(KeyValueValid);
		F_LEDON();
		R_LcdFlag.wVal = 0xFFFFu;	
		Key.Value = KEY_NULL;
	}	
}	
 
void F_Set_Temp_Param(s16* ndata,s16 min, s16 max)
{
	s16 temp = 0;/* 不能加静态修饰 */
	temp = *ndata;
	if(B_INCFLAG)
	{	if(temp < max)
			temp ++;
	}
	else if(B_DECFLAG)
	{	if(temp > min)
			temp --;
	}
	*ndata = temp;
}

void F_Set_Calib_Temp_Param(s8* ndata,s16 min, s16 max)
{
	s8 temp = 0;
	temp = *ndata;
	if(B_INCFLAG)
	{	if(temp < max)
			temp ++;
	}
	else if(B_DECFLAG)
	{	if(temp > min)
			temp --;
	}
	*ndata = temp;
}	


void F_KeySetMenuSever()
{
	if(B_INCFLAG|B_DECFLAG)
	{	if(R_MODE == D_SET){
			if(TheVa.Param.Mode.Bit.bit0){
			//if(Temp.Unit){
				switch(R_1LevelSetMENU)
				{	case D_1StartTemp : F_Set_Temp_Param((s16 *)&TheVa.Param.StartTemp	  , F_Start_Temp_Min   ,(TheVa.Param.StopTemp-1)	); break;
					case D_1StopTemp  : F_Set_Temp_Param((s16 *)&TheVa.Param.StopTemp	  , (TheVa.Param.StartTemp+1)   ,F_Stop_Temp_Max	); break;
					case D_1HighTemp  : F_Set_Temp_Param((s16 *)&TheVa.Param.HighTempAlarm, (TheVa.Param.LowTempAlarm+1),F_HighTempAlarm_Max); break;
					case D_1LowTemp   : F_Set_Temp_Param((s16 *)&TheVa.Param.LowTempAlarm , F_LowTempAlarm_Min,(TheVa.Param.HighTempAlarm-1)); break;
					case D_1Calib	  : F_Set_Calib_Temp_Param((s8 *)&TheVa.Param.Calib					 , F_Calib_Min   ,F_Calib_Max	);     break;
					default:	break;
				}
			}
			else{
				switch(R_1LevelSetMENU)
				{	case D_1StartTemp : F_Set_Temp_Param((s16 *)&TheVa.Param.StartTemp	 , C_Start_Temp_Min   ,(TheVa.Param.StopTemp-1)	);    break;
					case D_1StopTemp  : F_Set_Temp_Param((s16 *)&TheVa.Param.StopTemp	 , (TheVa.Param.StartTemp+1)   ,C_Stop_Temp_Max	);    break;
					case D_1HighTemp  : F_Set_Temp_Param((s16 *)&TheVa.Param.HighTempAlarm, (TheVa.Param.LowTempAlarm+1),C_HighTempAlarm_Max);break;
					case D_1LowTemp   : F_Set_Temp_Param((s16 *)&TheVa.Param.LowTempAlarm , C_LowTempAlarm_Min,(TheVa.Param.HighTempAlarm-1));break;
					case D_1Calib	  : F_Set_Calib_Temp_Param((s8 *)&TheVa.Param.Calib					 , C_Calib_Min   ,C_Calib_Max	);    break;
					default:	break;
				}
			}
			D_SaveThevaDATA = _TRUE;/* 清除EEPROM 网关ID 记录 */
		}
		SaveFlag.wVal = 1;
		B_INCFLAG = _FALSE;
		B_DECFLAG = _FALSE;
		TheVa_State.CMD = D_TheVa_ModeParam;		/* 不管温度是否发生变化，都会上报温度数据 */
		TheVa_State.SendCnt = D_MaxSendFrameNum;	/* 切换单位及时上报。 */
	}
		//B_ParamChange = _TRUE;	  
		//R_EepromCheakSum = F_GetCRC((u8 *)&T_MCU.DATA[0],(D_Default_DateLen));  
		//Key.Value = KEY_NULL;
}

