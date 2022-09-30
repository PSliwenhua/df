#ifndef _RF_H__
#define	_RF_H__

#define RF_PACKET_SIZE 		   (128)		
MyDef xdata u8 T_RxRfData[RF_PACKET_SIZE];	
MyDef xdata u8 T_TxRfData[RF_PACKET_SIZE];	


#define D_TheVa_WAITACK_TIME    16//16*64HZ = 250MS//  此处非常关键
//#define D_TheVa_WAITACK_TIME    32//16*64HZ = 250MS//  此处非常关键

typedef enum {
	D_ClrSendFrameNum = 0,
	D_AckSendFrameNum = 1,
	D_MaxSendFrameNum = 4,
}EnumRF_FrameNum;

typedef enum {
	CH1,
	CH2,
	CH3,
	CH4,
	CH5,
	CH6,
	CH7,
	CH8,
}EnumRF_Pair_MaxAmount;

typedef enum {
    RF_433MHz,
	RF_868MHz,
	RF_915MHz,
	RF_920MHz,
}EnumRF_Frequency_Type;
MyDef xdata EnumRF_Frequency_Type R_RfFreq;

typedef enum {
	Pairing_Wait		,
	Pairing_Succeed		,
}EnumRF_Pairing_Type;

typedef enum {
	D_Offline	,/* 设备离线 */
	D_Online	,/* 设备在线 */
}EnumRF_Offline_Type;


typedef enum {
	D_TheVa_NULL		,
	D_TheVa_REQPAIR		,
	D_TheVa_PairOk		,
	D_TheVa_RemoveOk	,
	D_TheVa_ASK			,
	D_TheVa_ACK			,
	D_TheVa_DATA		,
	D_TheVa_ModeParam	,
	D_TheVa_TIMESEG1	,
	D_TheVa_TIMESEG2	,
	D_TheVa_TIMESEG3	,
}EnumRF_TheVa_CMD;

typedef struct
{
    u8	INT_Index		;
    u8	Rx_Index		;
}CMT2300A_AT;
MyDef xdata CMT2300A_AT CMT2300A;

#define D_0xFF_Gaway_FamilyCode	0xFF//暖气片网关		设备机型
#define D_0xFE_TheVa_FamilyCode	0xFE//暖气片控制阀		设备机型
#define D_0xFD_Doorm_FamilyCode	0xFD//门磁检测器		设备机型
MyDef xdata u8 R_RXMode;
MyDef xdata s8 R_TheVaRssi;
MyDef xdata s8 R_GatewayRssi;
MyDef xdata u8 TxTimeOut;

void F_RF_TRxSever(void);

#endif



