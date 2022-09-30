#ifndef _ThermostaticValve_H__
#define	_ThermostaticValve_H__


#define	D_TheVa_FamilyCode	  	(0)
#define	D_TheVa_SetPayloadLen 	(1)
#define	D_TheVa_MODE 			(7)


#define	D_CMD_CacheNull			('N')
#define	D_CMD_PAIR_REQ			('R')
#define	D_CMD_PAIR_OK			('O')
#define	D_CMD_Remove_ACK		('M')
#define	D_CMD_ACK				('A')
#define	D_CMD_ASK				('S')
#define	D_CMD_WIFI_TIME			('W')
#define	D_Theva_Pv_Value		('V')
#define	D_CMD_Theva_Mode		('D')

typedef enum {
/* 	D_CMD_CacheNull			,
	D_CMD_PAIR_REQ			,
	D_CMD_PAIR_OK			,
	D_CMD_Remove_ACK		,
	D_CMD_ACK				,
	D_CMD_ASK				,
	D_CMD_WIFI_TIME			,
	D_Theva_Pv_Value		,//模式、状态、。。。
	D_CMD_Theva_Mode		,//模式、状态、。。。 */
	D_Timer1				,
	D_Timer2				,
	D_Timer3				,
	D_Timer4				,
	D_Timer5				,
	D_Timer6				,
	D_Timer7				,
	D_Timer8				,
	D_Timer9				,
	D_Timer10				,
	D_Timer11				,
	D_Timer12				,
	D_ALLRFDPID				,
}Enum_Thermostatic_RF_DPID;
typedef struct
{
	UWORD StartTimer		;
	UWORD StopTimer 		;
	s16 StartTemp			;
	s16 StopTemp			;
//	u8	crc					;
}Theva_TimerSEG;

typedef struct
{
	u8 		FamilyCode		;
	u8 		SetPayloadLen	;
	u8 		Master_ID_HSB	;
	u8 		Master_ID_LSB	;
	u8 		Slave_ID_HSB	;
	u8 		Slave_ID_LSB	;
	u8 		DPID			;
	u8	 	Ch				;
	s16 	TempC			;
	s16 	TempF			;
	u16 	HTD_TimerLong	;
	UBYTE  	State			;
	u8 Crc					;
	u8 Sum					;
}Theva_Pv_Value;
MyDef Theva_Pv_Value Theva_Pv;
/* 网关主控为小端结构 */
	#define B_MotorCtrlState    	Theva_Pv.State.Bit.bit7/* 阀门加热状态，    	   0->关闭；1->打开  */
	#define B_LowBattery    		Theva_Pv.State.Bit.bit6/* 电池低电压报警，	       0->未报警；1->报警*/
	#define B_WindowAlarm    		Theva_Pv.State.Bit.bit5/* 开窗报警，			   0->未报警；1->报警*/
	#define B_HighTempAlarm    		Theva_Pv.State.Bit.bit4/* 高温报警，			   0->未报警；1->报警*/
	#define B_LowTempAlarm    		Theva_Pv.State.Bit.bit3/* 低温报警，			   0->未报警；1->报警*/
	#define B_NtcAlarm    			Theva_Pv.State.Bit.bit2/* NTC电阻开短路异常报警，	0->未报警；1->报警*/
//	#define B_LowBattery    		Theva_Pv.State.Bit.bit1/* 			*/
	#define B_Rf_Connect_State    	Theva_Pv.State.Bit.bit0/* RF连接状态 			   0->离线、1->在线  */

typedef struct
{
	u8 FamilyCode			;
	u8 SetPayloadLen		;
	u8 Master_ID_HSB		;
	u8 Master_ID_LSB		;
	u8 Slave_ID_HSB			;
	u8 Slave_ID_LSB			;
	u8 DPID					;
	u8 Ch   				;/* Ch  */
	UBYTE Mode  			;/* 模式0  			*/
	UBYTE Mode1  			;/* 模式1  			*/
	s16 StartTemp   		;/* 默认启动温度   	*/
	s16 StopTemp   			;/* 默认停止温度   	*/
	s16 HighTempAlarm   	;/* 高温报警值   	*/
	s16 LowTempAlarm   		;/* 低温报警值   	*/
	s8 Calib				;/* 温度校准值 		*/
	u8 TimingOnOff			;/* 温度校准值 		*/
	u8 TimingSeg   			;/* 用与存储eeprom长度  */
	u8 Crc					;
	u8 Sum					;
}Theva_TempMode;

typedef struct
{
	u8 FamilyCode			;
	u8 SetPayloadLen		;
	u8 Master_ID_HSB		;
	u8 Master_ID_LSB		;
	u8 Slave_ID_HSB			;
	u8 Slave_ID_LSB			;
	u8 DPID					;
	u8 Ch   				;/* Ch  */
	UWORD StartTimer		;
	UWORD StopTimer 		;
	s16 StartTemp			;
	s16 StopTemp			;
//	Theva_TimerSEG TSEG		;
	u8 Crc					;
	u8 Sum					;
}Theva_RF_DATA_DPID_TIME_SEG;

typedef struct
{
	u8 FamilyCode			;
	u8 SetPayloadLen		;
	u8 Master_ID_HSB		;
	u8 Master_ID_LSB		;
	u8 Slave_ID_HSB			;
	u8 Slave_ID_LSB			;
	u8 DPID					;
	u8 Ch					;
	u8 Year   				;
	u8 Month  				;
	u8 Day    				;
	u8 Hour   				;
	u8 Minute 				;
	u8 Second 				;
	u8 Crc					;
	u8 Sum					;
}Theva_RF_DATA_DPID_WIFI_TIME;

typedef struct {
   	Theva_TempMode  Param;
	Theva_TimerSEG  TSEG[11];
	u8 Sum					;
}_Thermostatic_Valve_;
MyDef xdata _Thermostatic_Valve_ TheVa;/* 暖气片温控阀从机参数表存储 */

MyDef xdata u8 Save_Cmd_Iqe_Index;

/* 

	Param.Mode.Bit.bit7    配对模式		0->移除；1->添加 
	Param.Mode.Bit.bit6    夏令时模式	0->关闭；1->开启
	Param.Mode.Bit.bit5    霜冻模式		0->关闭；1->开启
	Param.Mode.Bit.bit4    水垢模式		0->关闭；1->开启
	Param.Mode.Bit.bit3    度假模式		0->关闭；1->开启
	Param.Mode.Bit.bit2    开窗控制		0->关闭；1->开启
	Param.Mode.Bit.bit1    儿童锁		0->关闭；1->开启
	Param.Mode.Bit.bit0    温度单位		0->摄氏度；1->华氏度
												
	Param.Mode1.Bit.bit7    设备开关机	0->关机；1->开机； 	
	Param.Mode1.Bit.bit6    恢复出厂设置模式参数//状态变化有效
	Param.Mode1.Bit.bit5    查询设备所有参数//状态变化有效
	Param.Mode1.Bit.bit4    
	Param.Mode1.Bit.bit3    
	Param.Mode1.Bit.bit2    电机状态自检 0->关闭；1->开启
	Param.Mode1.Bit.bit1    配对状态，0->已经配对，1->未配对
	Param.Mode1.Bit.bit0    RF连接状态 ，0->离线、1->在线
 */




/* ***************************************************************** */
/* ***************************************************************** */

enum{
    _StartTime1,
    _StartTime2,
    _StartTime3,
    _StartTime4,
    _StartTime5,
    _StartTime6,
    _StartTime7,
    _StartTime8,
    _StartTime9,
    _StartTime10,
    _StartTime11,
};



MyDef xdata u8 R_PayloadLen;
#define FIFO_Depth	(32)/* 包长 */

#define D_OfflineCnt (50*4)	/* 快速测试 50秒内没有更新数据，离线显示 */
//#define D_OfflineCnt (5*60*4) /* 5分钟 */

typedef struct {
    u8 Ch;				
	u8 OfflineCnt;		
	u8 R_RfLearnTime;	
	u16 RfTimeCnt;		
	u8 SendCnt;			
	u8 ReciveACKTime;   
	u8 ACK_CMD;   
	u8 CMD;  				//上报查询命令标志位 
	u16 RemoveIdDelay;  	/*  bit0 250ms 没有重发，说明接收成功网关ID清除延时 */ 	
	UBYTE  Flag;
}_Thermostatic_Valve_State_;
MyDef  _Thermostatic_Valve_State_ TheVa_State;
	#define B_TheVa_Cache_Cmd       TheVa_State.Flag.Bit.bit0/* 查询至缓存命令为空标志位 */
	#define TheVa_RemoveIdDelay     TheVa_State.Flag.Bit.bit1/* 250ms 没有重发，说明接收成功网关ID清除延时 */
MyDef u8 LOCK1;
typedef enum {
	D_Cache_Have,
	D_Cache_Null,
}Enum_Cache_Cmd;

enum {
    D_TheVa_Remove                ,//结束  
    D_TheVa_PairingEn             , 
};
typedef struct 
{
	UBYTE Flag;
	u8 Diffe;
	s8 Calib;
	s16 C;
	s16 F;
	s16 Display;
	s16 Cnt;
}T_Temp;
MyDef  T_Temp volatile Temp;
	#define B_GetTemp       	Temp.Flag.Bit.bit0

void F_Rf_Ack_4hzTimeOutCntTask(void);
void F_ThermostaticValveDataAnalysis(void);
u8 F_GetPinvea(void);
void F_ThermostaticValveACK(void);
u8 F_TheVaSendConnectRF(u8 cmd);
void F_Receive_Wifi_Timer_Cmd();
void F_RemoveMasterIDDelay500msClear(void);



u8 F_Send_TheVa_Pv_Value_Data(u8 cmd);
u8 F_Send_TheVa_Mode_Param_Data(void);
/* ***************************************************************** */
/* ***************************************************************** */


#endif



