#include "Main.h"

void F_RF_TRxSever(void)
{	
	//if(TheVa_Last_Lock != LOCK1)	/* 主机配对申请，从机反馈 */
	//	return;							/* 配对成功后等待，温控阀保存网关主机ID到EEPROM后,再上报数据 */
	if(TheVa_State.ReciveACKTime == 0)
	{	if(TheVa_State.SendCnt)
		{	TheVa_State.SendCnt--;
			//memset(T_TxRfData,0,sizeof(T_TxRfData));
			switch(TheVa_State.CMD) 
			{
				case D_TheVa_REQPAIR 	:	R_PayloadLen = F_TheVaSendConnectRF(D_CMD_PAIR_REQ);			break;
				case D_TheVa_PairOk 	:	R_PayloadLen = F_Send_TheVa_Pv_Value_Data(D_CMD_PAIR_OK);		break;
				case D_TheVa_RemoveOk 	:	R_PayloadLen = F_TheVaSendConnectRF(D_CMD_Remove_ACK);			break;
				case D_TheVa_ACK  	 	:	R_PayloadLen = F_TheVaSendConnectRF(D_CMD_ACK);					break;
				case D_TheVa_ASK  	 	:	R_PayloadLen = F_TheVaSendConnectRF(D_CMD_ASK);					break;
				case D_TheVa_DATA 	 	:	R_PayloadLen = F_Send_TheVa_Pv_Value_Data(D_Theva_Pv_Value);	break;
				case D_TheVa_ModeParam	:	R_PayloadLen = F_Send_TheVa_Mode_Param_Data();					break;
				case D_TheVa_TIMESEG1 	:		break;
				case D_TheVa_TIMESEG2 	:		break;
				case D_TheVa_TIMESEG3 	:		break;
				default:break;
			}
			//uart_printf ("Remove = %u\n",(u16)TheVa.Param.Mode.ucVal);
			uart_printf ("pair = %u\n",(u16)TheVa.Param.Mode.Bit.bit7);
			Radio_GoTx_VariableLen();
		//	CMT2300A_SetPayloadLength(FIFO_Depth);		/* 配置有效载荷数据长度,spi速率比rf数据率高 */
			CMT2300A_GoTx();								/* 先进入tx模式，发送数据 */
		//	CMT2300A_WriteFifo(&T_TxRfData[0],R_PayloadLen);/* 边填边发 */
			CMT2300A_WriteFifo(&T_TxRfData[0],R_PayloadLen);/* 边填边发 */
			TheVa_State.ReciveACKTime = D_TheVa_WAITACK_TIME+F_GetPinvea();//左移1位
			TxTimeOut = 16;
			while((CMT2300A_ReadGpio2() == 0)&&(TxTimeOut));
			CMT2300A_WriteReg(CMT2300A_CUS_INT_CLR1, CMT2300A_MASK_TX_DONE_CLR);
			Radio_GoRx_VariableLen();
			//F_MaxTxPOWER();
		}
	}
	if(R_RXMode == TRUE)//接收中断状态
	{	if(CMT2300A_ReadGpio2())
		{	CMT2300A_GoStby();
			CMT2300A_ReadFifo(T_RxRfData, FIFO_Depth);
			CMT2300A_ClearRxFifo();
			CMT2300A_ClearInterruptFlags();
            CMT2300A_GoRx();
			F_ThermostaticValveDataAnalysis();
			
		}
	}
}

 
