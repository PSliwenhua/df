#ifndef __APP_H__
#define	__APP_H__

typedef struct 
{
    u8  R_MODE;
    u8  R_MENU;
    u8  R_TEST;
    u8  Count64Hz;
    u8  Count256Hz;
	UBYTE McuHeartFlag;
	UBYTE McuHaltFlag;
}T_Skeleton;
MyDef xdata volatile T_Skeleton  Framework;
    #define R_MODE         Framework.R_MODE
    #define R_MENU         Framework.R_MENU
    #define R_TEST         Framework.R_TEST
    #define Count64Hz      Framework.Count64Hz
    #define B_128HzFlag    Framework.McuHeartFlag.Bit.bit0 
    #define B_64HzFlag     Framework.McuHeartFlag.Bit.bit1 
    #define B_32HzFlash    Framework.McuHeartFlag.Bit.bit2 
    #define B_16HzFlash    Framework.McuHeartFlag.Bit.bit3 
    #define B_8HzFlash     Framework.McuHeartFlag.Bit.bit4 
    #define B_4HzFlash     Framework.McuHeartFlag.Bit.bit5 
    #define B_2HzFlash     Framework.McuHeartFlag.Bit.bit6 
    #define B_1HzFlash     Framework.McuHeartFlag.Bit.bit7 
    #define R_HALT         Framework.McuHaltFlag.ucVal  
    #define B_HALT         Framework.McuHaltFlag.Bit.bit0  
    #define B_BuzXor       Framework.McuHaltFlag.Bit.bit1  
MyDef xdata volatile u8 R_MODEBUF;
MyDef xdata volatile UBYTE RTCFlag;
    #define B_32HzFlag  RTCFlag.Bit.bit2 
    #define B_16HzFlag  RTCFlag.Bit.bit3 
    #define B_8HzFlag   RTCFlag.Bit.bit4 
    #define B_4HzFlag   RTCFlag.Bit.bit5 
    #define B_2HzFlag   RTCFlag.Bit.bit6 
    #define B_1HzFlag   RTCFlag.Bit.bit7 

MyDef xdata volatile u8 HaltFlag;

MyDef xdata u8 R_1LevelSetMENU;
enum {
    D_Time1  ,   
    D_Hand1  ,  
    D_Holiday,     
    D_TempCtrlModeLen,     
};

enum {
    /* 正常模式菜单枚举值 */
    D_NOR  ,   
    D_SET  ,   
    D_SET1 ,   
    D_TES  ,   
    D_OFF  ,   
};

enum {
    /* 测试模式菜单枚举值 */
    D_SHOWALL    ,
    D_SHOWVER    ,
    D_SHOWRSSI   ,
    D_MOTORONOFF ,
};

enum {
    /* 一级设置菜单显示模式枚举值 */

    D_1StartTemp        ,		
    D_1StopTemp         ,		
    D_1HighTemp         ,
    D_1LowTemp          ,
    D_1Calib	        ,
    //D_1ChildLock_Mode   ,	
    //D_1CF_Mode          ,
    D_1MENULEN          ,
};

enum {
    /* 二级设置菜单显示模式枚举值 */
    D_StartTimer,  
    D_StopTimer , 
    D_StartTemp , 
    D_StopTemp  ,
    D_MENULEN   ,
};



/* ***************************************************************** */
/* ***************************************************************** */


MyDef xdata UBYTE AFlag1;
    #define B_ParamChange 	            AFlag1.Bit.bit0
    #define B_PowerMode 	            AFlag1.Bit.bit1
    #define B_PowerModeLast             AFlag1.Bit.bit5 //设备电源状态
    #define B_SET_NOR                   AFlag1.Bit.bit6 //设备电源状态


/* ***************************************************************** */
/* ***************************************************************** */


enum {
    D_PowerOn	 ,   
    D_PowerOff	 ,   
    D_Pause	     ,   
};
enum {
    D_Auto	 ,   
    D_Hand	 ,   
};   

typedef struct 
{
	u8 ModeReturn;
	u8 BackLight;
	u8 LowPowerRead;
	u16 TempRead;
	u16 RxTimeDown;
	u8 Lcd;
	u8 HeatingStateOn;
    u16 Motor;    
    s8 MotorPWM;  
    u8 TestSLEEP;  
}T_Cnt;
MyDef xdata T_Cnt CntTime;
    #define D_BackLightCnt	        10//10秒	
    #define D_ReturnCnt	            30//30秒	
    #define D_TempReadTimer         60//60//10秒间隔//60秒	
    /* 轮询分辨率64hz */


    #define D_TempReadCycle	        (60 * 8)// 7秒	
 //   #define D_TempReadCycle	        (2 * 8)// 7秒	
    #define D_TempReadCnt	        (D_TempReadCycle-(1 * 8))
    #define D_AskCmdCnt1	            (10 * 8)
    #define D_AskCmdCnt2	            (20 * 8)
    #define D_AskCmdCnt3	            (30 * 8)
    #define D_AskCmdCnt4	            (40 * 8)
    #define D_AskCmdCnt5	            (50 * 8)
    #define D_AskCmdCnt	            (D_TempReadCycle-(4 * 8))// 上报温度前3秒查询命令
    #define D_PairCmdCnt	        (D_TempReadCycle-(6 * 8))
    #define D_MotorTimer	        6000
    #define D_LowPowerRead	        (2 * 8)// 
    #define D_InitTempReadCnt	    (D_TempReadCnt-2)// 


    /* #define D_PairCmdCnt	        (4)// 
    #define D_TempReadCnt	        (1 *8)// 1秒频率，测试温度准确性 */

    #define D_RxTimeOutSleep	    (32)  // 32*64hz=500ms;/* 64hz扫描，最长延时500ms, */


MyDef xdata u8 R_ID_ADD64MS;

#define	STM0_ENABLE()				(_st0on = 1)
/* ***************************************************************** */
/* ***************************************************************** */
void F_SetStartTimer(u16* Timer);
extern code u8 crc_table[256];
u8 GetCrc(u8 * lpBuff, u8 ucLen,u8 intcrc);
u8 GetSum(u8 * lpBuff, u8 ucLen);
u8 F_GetSum(u8 *addr, u8 length);
u8 F_GetCRC(u8 *pBuff, u8 ucLen);
void F_SwapBigEnd(u8* a , u8* b);
u8 Mystrcpy(char *strDest, const char *strSrc);
void F_TrigTxInt();
u16 F_PollingCmd(volatile u16 temp,u8 cmd);

void F_OnPower();		
void F_OffPower();	
void F_Enter_TestMode();	


void F_SetShowSoftVerFlag();
void F_SetShowLcdAllFlag();
void F_SetShowWifiRssiFlag();
void F_SetOnOffMotorFlag();
void F_Return_NorMode();

void F_ShowSoftVer();
void F_ShowLcdAll();
void F_OnOffMotor();
void F_RefreshTestHmi();

void F_TempCtrlModeSet();

void F_SetSvTemp(u16* SvTemp);

void F_Enter_SetMode();
void F_MenuNext();
void F_SetDataIncFlag();
void F_SetDataDecFlag();
void F_RstFramework();
void F_SetHmiFlashCheak();

void F_HandFaMenCtrl();
void F_HandFaMenCtrlHAD(u8 OnOff);
void F_HeatingRadiatorOnOffCheak();


#endif   