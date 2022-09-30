#include "Main.h"

void F_Rf_Ack_4hzTimeOutCntTask(void)
{
	if(TheVa_State.ReciveACKTime)
		TheVa_State.ReciveACKTime--;
}



void F_RemoveMasterIDDelay500msClear(void)
{
	if(TheVa_State.RemoveIdDelay)
	{	TheVa_State.RemoveIdDelay--;
		if(TheVa_State.RemoveIdDelay == 0)
		{
			if(TheVa_RemoveIdDelay == _TRUE)
			{	TheVa_RemoveIdDelay = _FALSE;
				TheVa.Param.Master_ID_HSB = 0;
				TheVa.Param.Master_ID_LSB = 0;
				LOCK1 = Pairing_Wait;/* 清除已配对成功标志位 */
				D_SaveThevaDATA = _TRUE;/* 清除EEPROM 网关ID 记录 */
				////M_TESTTIME();
				////M_TESTTIME();
			}
		}
	}
}


void F_Receive_TheVa_Mode_Param_Cmd()
{	
	volatile _Thermostatic_Valve_ *RxDate = (_Thermostatic_Valve_*)T_RxRfData;
	if(RxDate->Param.Mode.Bit.bit7 != TheVa.Param.Mode.Bit.bit7) 
	{
		if(RxDate->Param.Mode.Bit.bit7 == D_TheVa_Remove)/* 移除设备 命令 */ 
		{	//TheVa_State.RemoveIdDelay = D_TheVa_WAITACK_TIME<<1; /*设置500MS 如果移除的瞬间刚好关机，那么是收不到网关回复的ACK  */
			//TheVa_RemoveIdDelay = _TRUE;
			TheVa_State.CMD = D_TheVa_RemoveOk;/* 只能放在这里，返回移除设备RemoveOk ACK命令 */
		}									  /* 其它返回 ACK命令 */
		TheVa_State.SendCnt = D_MaxSendFrameNum;
	}
	memcpy((u8 *)&(TheVa.Param.Mode.ucVal),(u8 *)&(RxDate->Param.Mode.ucVal),13);
	B_RefreshTemp = _EN;/* 切换温度单位及时刷新 */
	//F_GetTempCalibCheak();
	switch(TheVa.Param.Mode.Bit.bit0)
	{	case DTEMP_C: Temp.Display = Temp.C+TheVa.Param.Calib;break;	
		case DTEMP_F: Temp.Display = Temp.F+TheVa.Param.Calib;break;
		default:break;	
	}
	TheVa_State.SendCnt = D_MaxSendFrameNum;
}

void F_Receive_Wifi_Timer_Cmd()
{
	memcpy((u8 *)&(SysTime.Year),(u8 *)&T_RxRfData,6);
	TheVa_State.SendCnt = D_MaxSendFrameNum;
}

Theva_TimerSEG F_GetTheva_TimerSEG()
{
	Theva_TimerSEG Theva_TimerSEG;
	volatile Theva_RF_DATA_DPID_TIME_SEG *RxDate = (Theva_RF_DATA_DPID_TIME_SEG*)T_RxRfData;
	//memcpy((u8 *)&(Theva_TimerSEG.StartTimer.wVal),(u8 *)&(RxDate.TSEG[0].StartTimer.wVal),8);
	Theva_TimerSEG.StartTimer.wVal	= RxDate->StartTimer.wVal ;     
	Theva_TimerSEG.StopTimer.wVal 	= RxDate->StopTimer.wVal  ;   
	Theva_TimerSEG.StartTemp  	= RxDate->StartTemp  ;     
	Theva_TimerSEG.StopTemp    = RxDate->StopTemp   ;  
	TheVa_State.SendCnt = D_MaxSendFrameNum; /* 查询所有数据命令 */
	return Theva_TimerSEG;
}

void F_Receive_Remove_ACK()
{	
	TheVa_State.RemoveIdDelay = D_TheVa_WAITACK_TIME>>1; /*设置125MS 保存至EEPROM , 来不及保存信息，就立马断电关机会出问题 */
	TheVa_RemoveIdDelay = _TRUE;
	//TheVa_State.CMD = D_TheVa_RemoveOk;
	TheVa_State.SendCnt = D_ClrSendFrameNum;
	CntTime.RxTimeDown = 0;
	CMT2300A_GoStby();
	CMT2300A_GoSleep();
}
void F_Receive_ACK(u8 dpid)
{	
	CntTime.RxTimeDown = 0;
	TheVa_State.SendCnt = D_ClrSendFrameNum;
	CMT2300A_GoStby();
	CMT2300A_GoSleep();
	if(dpid == D_CMD_Remove_ACK)
		B_TheVa_Cache_Cmd = D_Cache_Null;
}

void F_Receive_Pairing_Succeed_ACK()
{	
	volatile _Thermostatic_Valve_ *RxDate = (_Thermostatic_Valve_*)T_RxRfData;
	TheVa.Param.Ch  = RxDate->Param.Ch;
	TheVa_State.CMD = D_TheVa_PairOk;		
	TheVa_State.SendCnt = D_MaxSendFrameNum;
}

void F_ThermostaticValveDataAnalysis(void)
{
	volatile _Thermostatic_Valve_ *RxDate = (_Thermostatic_Valve_*)T_RxRfData;
	CMT2300A.INT_Index = T_RxRfData[D_TheVa_SetPayloadLen];
	if(RxDate->Param.FamilyCode != D_0xFF_Gaway_FamilyCode)	return;	
	if(T_RxRfData[CMT2300A.INT_Index-2] != GetCrc(&T_RxRfData[0],(CMT2300A.INT_Index-2),0x00))	return;
	if(T_RxRfData[CMT2300A.INT_Index-1] != GetSum(&T_RxRfData[0],(CMT2300A.INT_Index-1)))		return;
	if(LOCK1 == Pairing_Succeed)
	{	if((TheVa.Param.Master_ID_HSB != RxDate->Param.Master_ID_HSB)
		 ||(TheVa.Param.Master_ID_LSB != RxDate->Param.Master_ID_LSB)
		 ||(TheVa.Param.Slave_ID_HSB  != RxDate->Param.Slave_ID_HSB)
		 ||(TheVa.Param.Slave_ID_LSB  != RxDate->Param.Slave_ID_LSB))
			return;
	}else{
		if((TheVa.Param.Slave_ID_HSB != RxDate->Param.Slave_ID_HSB)
		 ||(TheVa.Param.Slave_ID_LSB != RxDate->Param.Slave_ID_LSB))
		{	
			return;
		}
		TheVa.Param.Master_ID_HSB = RxDate->Param.Master_ID_HSB;
		TheVa.Param.Master_ID_LSB = RxDate->Param.Master_ID_LSB;
		LOCK1 = Pairing_Succeed;		/* 设置配对成功标志位 */
		TheVa.Param.Mode1.Bit.bit1 = Pairing_Succeed;
		D_SaveThevaDATA = _TRUE;	/* 保存网关ID到EEPROM */	/* 导致功耗高 */
		M_TESTTIME();
		M_TESTTIME();
		M_TESTTIME();
	//	R_PayloadLen = F_Send_TheVa_Pv_Value_Data(D_CMD_PAIR_OK);
		TheVa.Param.Ch  = RxDate->Param.Ch;
		Theva_Pv.Ch = RxDate->Param.Ch;
		TheVa_State.CMD = D_TheVa_PairOk;		
		TheVa_State.SendCnt = D_MaxSendFrameNum;
		TheVa_State.ReciveACKTime = 0;
		//F_Receive_Pairing_Succeed_ACK();
		return;
	}												
	switch(RxDate->Param.DPID)
	{						
		case D_CMD_Remove_ACK : F_Receive_Remove_ACK();								   		      	return;
		case D_CMD_CacheNull : F_Receive_ACK(RxDate->Param.DPID);							   	return;
		case D_CMD_ACK		 : F_Receive_ACK(RxDate->Param.DPID);							   	return;
	//	case D_CMD_PAIR_OK	 : F_Receive_Pairing_Succeed_ACK();							   		 return;
		
		case D_CMD_WIFI_TIME : F_Receive_Wifi_Timer_Cmd(); 					  	   		         break;
		case D_CMD_Theva_Mode: F_Receive_TheVa_Mode_Param_Cmd(); 		D_SaveThevaDATA = _TRUE; break;
		case D_Timer1		 : TheVa.TSEG[0 ] = F_GetTheva_TimerSEG();	D_SaveTimerSEG1 = _TRUE; break;
		case D_Timer2		 : TheVa.TSEG[1 ] = F_GetTheva_TimerSEG();	D_SaveTimerSEG2 = _TRUE; break;
		case D_Timer3		 : TheVa.TSEG[2 ] = F_GetTheva_TimerSEG();	D_SaveTimerSEG3 = _TRUE; break;
		case D_Timer4		 : TheVa.TSEG[3 ] = F_GetTheva_TimerSEG();	D_SaveTimerSEG4 = _TRUE; break;
		case D_Timer5		 : TheVa.TSEG[4 ] = F_GetTheva_TimerSEG();	D_SaveTimerSEG5 = _TRUE; break;
		case D_Timer6		 : TheVa.TSEG[5 ] = F_GetTheva_TimerSEG();	D_SaveTimerSEG6 = _TRUE; break;
		case D_Timer7		 : TheVa.TSEG[6 ] = F_GetTheva_TimerSEG();	D_SaveTimerSEG7 = _TRUE; break;
		case D_Timer8		 : TheVa.TSEG[7 ] = F_GetTheva_TimerSEG();	D_SaveTimerSEG8 = _TRUE; break;
		case D_Timer9		 : TheVa.TSEG[8 ] = F_GetTheva_TimerSEG();	D_SaveTimerSEG9 = _TRUE; break;
		case D_Timer10		 : TheVa.TSEG[9 ] = F_GetTheva_TimerSEG();	D_SaveTimerSEGA = _TRUE; break;
		case D_Timer11		 : TheVa.TSEG[10] = F_GetTheva_TimerSEG();	D_SaveTimerSEGB = _TRUE; break;
		default: break;	
	}
	B_TheVa_Cache_Cmd = D_Cache_Have;
//	TheVa_State.CMD = D_TheVa_ACK;	/* 返回ACK */
	R_PayloadLen = F_TheVaSendConnectRF(D_CMD_ACK);
//	TheVa_State.SendCnt = D_AckSendFrameNum;

	TheVa.Param.Mode1.Bit.bit0 = D_Online;
//	TheVa_State.ReciveACKTime = 0;/* 省电操作 */
	TheVa_State.ReciveACKTime = D_TheVa_WAITACK_TIME;//+F_GetPinvea();
	TheVa_State.R_RfLearnTime = 0;
	TheVa_State.RfTimeCnt = 0;
	TheVa_State.OfflineCnt = 0;
	//	CMT2300A.Rx_Succeed = _TRUE;	/* 返回ACK */
	//if(CMT2300A.Rx_Succeed == _TRUE)
	//{	CMT2300A.Rx_Succeed = _FALSE;
		Radio_GoTx_VariableLen();//有效载荷长度配置
		CMT2300A_GoTx();
		CMT2300A_WriteFifo(&T_TxRfData,R_PayloadLen);
		TxTimeOut = 16;
		while((CMT2300A_ReadGpio2() == 0)&&(TxTimeOut));
		CMT2300A_WriteReg(CMT2300A_CUS_INT_CLR1, CMT2300A_MASK_TX_DONE_CLR);
		Radio_GoRx_VariableLen();
	//}else{
	//	Radio_GoRx_VariableLen();//校验失败情况下
	//}
	return;
}

u8 F_GetPinvea(void)
{
	static u8 lief;
	u8 resulst = 0;
	F_CntServe(&lief,7);
	switch(lief)
	{
		case 0: resulst = R_ID_ADD64MS & 0x01u;break;
		case 1: resulst = R_ID_ADD64MS & 0x02u;break;
		case 2: resulst = R_ID_ADD64MS & 0x04u;break;
		case 3: resulst = R_ID_ADD64MS & 0x08u;break;
		case 4: resulst = R_ID_ADD64MS & 0x10u;break;
		case 5: resulst = R_ID_ADD64MS & 0x20u;break;
		case 6: resulst = R_ID_ADD64MS & 0x40u;break;
		case 7: resulst = R_ID_ADD64MS & 0x80u;break;
		default:break;	
	}
	if(resulst)
		return TRUE;
	return _FALSE;
}

s16 F_BIG_ENDIAN_SWAP_LITTLE_ENDIAN(s16 ndata)
{
	SWORD Swap;
	SWORD SwapBuf;
	SwapBuf.wVal = ndata;
	Swap.Byte.byte0 = SwapBuf.Byte.byte1;
	Swap.Byte.byte1 = SwapBuf.Byte.byte0;
	return Swap.wVal;
}

u8 F_Send_TheVa_Pv_Value_Data(u8 cmd)
{

	volatile Theva_Pv_Value *TxDate = (Theva_Pv_Value*)T_TxRfData;
	u8 len = sizeof(Theva_Pv);
	TxDate->FamilyCode		= TheVa.Param.FamilyCode	  ;
	TxDate->SetPayloadLen	= len						  ;
	TxDate->Master_ID_HSB	= TheVa.Param.Master_ID_HSB	  ;
	TxDate->Master_ID_LSB	= TheVa.Param.Master_ID_LSB	  ;
	TxDate->Slave_ID_HSB	= TheVa.Param.Slave_ID_HSB 	  ;
	TxDate->Slave_ID_LSB	= TheVa.Param.Slave_ID_LSB 	  ;
	TxDate->DPID			= cmd			  			  ;
	TxDate->Ch				= TheVa.Param.Ch  			  ;
	switch(TheVa.Param.Mode.Bit.bit0)
	{	case DTEMP_C: 
				TxDate->TempC = F_BIG_ENDIAN_SWAP_LITTLE_ENDIAN(Temp.Display);
				TxDate->TempF = F_BIG_ENDIAN_SWAP_LITTLE_ENDIAN(F_ChangeCtoF(Temp.Display));
			break;	
		case DTEMP_F: 
				TxDate->TempF = F_BIG_ENDIAN_SWAP_LITTLE_ENDIAN(Temp.Display);
				TxDate->TempC = F_BIG_ENDIAN_SWAP_LITTLE_ENDIAN(F_ChangeCtoF(Temp.Display));
			break;
		default:break;	
	}
	TxDate->HTD_TimerLong	= Theva_Pv.HTD_TimerLong;
	TxDate->State			= Theva_Pv.State;

	//T_TxRfData[len-2]	  = GetCrc(&T_TxRfData[0],(len-2),0x00);
	//T_TxRfData[len-1]	  = GetSum(&T_TxRfData[0],(len-1) );
	TxDate->Crc	  = GetCrc(&T_TxRfData[0],(len-2),0x00);
	TxDate->Sum	  = GetSum(&T_TxRfData[0],(len-1) );
	CntTime.RxTimeDown = D_RxTimeOutSleep;
	return TxDate->SetPayloadLen;	
}

u8 F_Send_TheVa_Mode_Param_Data(void)
{
	u8 len = 2+sizeof(TheVa.Param);
	volatile Theva_TempMode *TxDate = (Theva_TempMode*)T_TxRfData;
	memcpy((u8 *)&(TxDate->FamilyCode),(u8 *)&(TheVa.Param.FamilyCode),len);
	TxDate->FamilyCode	   = TheVa.Param.FamilyCode	  ;
	TxDate->SetPayloadLen = len						  	  ;
	TxDate->DPID		  = D_CMD_Theva_Mode			  ;
	TxDate->Ch			= TheVa.Param.Ch  			  ;
	T_TxRfData[len-2]	  = GetCrc(&T_TxRfData[0],(len-2),0x00);
	T_TxRfData[len-1]	  = GetSum(&T_TxRfData[0],(len-1) );
	CntTime.RxTimeDown = D_RxTimeOutSleep;
	return TxDate->SetPayloadLen;	
}

u8 F_TheVaSendConnectRF(u8 cmd)
{	
	volatile _Thermostatic_Valve_ *TxDate = (_Thermostatic_Valve_*)T_TxRfData;
	u8 len = 10;
	//memcpy((u8 *)&(T_TxRfData),(u8 *)&(TheVa.Param.FamilyCode),len);
	TxDate->Param.FamilyCode    = TheVa.Param.FamilyCode;
	TxDate->Param.SetPayloadLen = len;
	TxDate->Param.Master_ID_HSB = TheVa.Param.Master_ID_HSB;
	TxDate->Param.Master_ID_LSB = TheVa.Param.Master_ID_LSB;
	TxDate->Param.Slave_ID_HSB	= TheVa.Param.Slave_ID_HSB; 
	TxDate->Param.Slave_ID_LSB	= TheVa.Param.Slave_ID_LSB; 
	TxDate->Param.Ch			= TheVa.Param.Ch; 
	TxDate->Param.DPID			= cmd;
	T_TxRfData[len-2] = GetCrc(&T_TxRfData[0],(len-2),0x00);
	T_TxRfData[len-1] = GetSum(&T_TxRfData[0],(len-1) );
	CntTime.RxTimeDown = D_RxTimeOutSleep;
	return len;
}
