#ifndef _Flash_H_
#define _Flash_H_

enum
{
	CMD_DATA_AREA_READ 					= 1,	
	CMD_DATA_AREA_WIRTE 				= 2,	
	CMD_DATA_AREA_ERASE_SECTOR 	= 3,
	CMD_FLASH_ERASE_ALL 				= 4,
	CMD_CODE_AREA_READ 					= 5,	
	CMD_CODE_AREA_WRITE 				= 6,
	CMD_CODE_AREA_ERASE_SECTOR 	= 7,
};
enum
{
	CMD_FLASH_UNLOCK 				= 0x28,
	CMD_CODE_AREA_UNLOCK 		= 0x29,
	CMD_DATA_AREA_UNLOCK 		= 0x2A,
	IFB_AREA_UNLOCK 				= 0x2B,
	CMD_FLASH_LOCK 					= 0xAA,
};

 //寄存器FSCMD位定义
#define IFEN		(1<<7)

void Data_Area_Sector_Erase(unsigned char SectorNumber);
void Data_Area_Write_Byte(unsigned int Address,unsigned char Data);
void Data_Area_Mass_Write(unsigned int Address,unsigned char *pData,unsigned int Length);
unsigned char Data_Area_Read_Byte(unsigned int Address);
void Data_Area_Mass_Read(unsigned int Address,unsigned char *pData,unsigned int Length);

#define C_Default_StartTemp	250	
#define C_Default_StopTemp	260	
#define C_Stop_Temp_Max		370
#define C_Start_Temp_Min	50
#define C_Calib_Min			-50		
#define C_Calib_Max			50			
#define C_HighTempAlarm		370
#define C_LowTempAlarm 		50
#define C_HighTempAlarm_Max	500
#define C_LowTempAlarm_Min 	-99

#define F_Default_StartTemp	770	
#define F_Default_StopTemp	780	
#define F_Stop_Temp_Max		990
#define F_Start_Temp_Min	410
#define F_Calib_Min			-99			
#define F_Calib_Max			99			
#define F_HighTempAlarm		990
#define F_LowTempAlarm 		410
#define F_HighTempAlarm_Max	1220
#define F_LowTempAlarm_Min 	142

/* code u8 FlashEEIdData[32] _at_ D_FLASHEE_ID_BASE_ADDR;	  // 写ID次数32byte/3byte=10次
code u8 FlashFreqData[32] _at_ D_FLASHEE_FREQ_BASE_ADDR;  // 频率校准次数32byte/2byte=16次 */

extern code u8 T_TheVaParam_TempC_InitData[];
extern code u8 T_TheVaParam_TempF_InitData[];
extern code u8 T_TheVaTSEG1_Addr[];
/* extern code u8 T_TheVaTSEG_C[];
extern code u8 T_TheVaTSEG_F[]; */

u8 F_Data_Area_Mass_Read(unsigned int Address,unsigned char *pData,unsigned int Length);
MyDef unsigned char UserDataBuff[10];
MyDef unsigned char BuffTemp[13];

#define D_TheVaParam_Addr   0x0000u//0x4700u//EEPROM 第0x0010u字节存储起始地址
#define D_TheVaTSEG1_Addr   0x0030u//0x4730u//EEPROM 第0x0000u字节存储起始地址
#define D_TheVaTSEG2_Addr   0x0040u//0x4740u//EEPROM 第0x0000u字节存储起始地址
#define D_TheVaTSEG3_Addr   0x0050u//0x4750u//EEPROM 第0x0000u字节存储起始地址
#define D_TheVaTSEG4_Addr   0x0060u//0x4760u//EEPROM 第0x0000u字节存储起始地址
#define D_TheVaTSEG5_Addr   0x0070u//0x4770u//EEPROM 第0x0000u字节存储起始地址
#define D_TheVaTSEG6_Addr   0x0080u//0x4780u//EEPROM 第0x0000u字节存储起始地址
#define D_TheVaTSEG7_Addr   0x0090u//0x4790u//EEPROM 第0x0000u字节存储起始地址
#define D_TheVaTSEG8_Addr   0x00A0u//0x47A0u//EEPROM 第0x0000u字节存储起始地址
#define D_TheVaTSEG9_Addr   0x00B0u//0x47B0u//EEPROM 第0x0000u字节存储起始地址
#define D_TheVaTSEG10Addr   0x00C0u//0x47C0u//EEPROM 第0x0000u字节存储起始地址
#define D_TheVaTSEG11Addr   0x00D0u//0x47D0u//EEPROM 第0x0000u字节存储起始地址
#define D_TheVaTSEG12Addr   0x00E0u//0x47E0u//EEPROM 第0x0000u字节存储起始地址

extern code u16 T_TheVaEEpromParamAddr[13];

void Save_Data_To_Eeprom(u16 addr,u16 len,u8 *ndata);
void F_SaveDataToEEprom();
void Read_Eeprom_To_RAM(u16 addr,u16 len,u8 *ndata,const u8* init);
void F_ReadEEpromToRAM();
void F_ReadSlaveIDEEpromToRAM();
#define FLASH_SIZE		18
void F_Flash_Init_Set();

#endif