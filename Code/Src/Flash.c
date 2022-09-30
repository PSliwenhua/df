#include "Main.h"

/***********************************************************************************
函 数 名：Data_Area_Erase_Sector										 	
功能描述：擦除数据区空间的一个扇区						
函数说明：								
输    入：unsigned char SectorNumber	扇区号，范围 0-31										
返    回：无																	
***********************************************************************************/
void Data_Area_Sector_Erase(unsigned char SectorNumber)
{
	unsigned int SectorAddress;
	FSCMD 	= 	0;
	SectorAddress = 0x80*SectorNumber;
	LOCK  = CMD_DATA_AREA_UNLOCK;						//数据区解锁
	PTSH = (unsigned char)(SectorAddress>>8);			//填写扇区地址
	PTSL = (unsigned char)(SectorAddress);				//填写扇区地址	
	FSCMD = CMD_DATA_AREA_ERASE_SECTOR;					//执行擦除扇区操作
	LOCK  = CMD_FLASH_LOCK;						    	//对FLASH加锁
} 


/***********************************************************************************
函 数 名：Data_Area_Write_Byte											 	
功能描述：向FLASH数据区写入一个字节数据																	
输    入：unsigned int Address	数据区空间写入地址											
					unsigned char Data		写入数据												
返    回：无																	
***********************************************************************************/
void Data_Area_Write_Byte(unsigned int Address,unsigned char Data)
{
	FSCMD 	= 	0;
	LOCK  = CMD_DATA_AREA_UNLOCK;						//数据区解锁
	PTSH = (unsigned char)(Address>>8);			//填写高位地址
	PTSL = (unsigned char)Address;        	//填写低位地址
	FSCMD = CMD_DATA_AREA_WIRTE;						//执行写操作
	FSDAT = Data;														//装载数据	
	LOCK  = CMD_FLASH_LOCK;						    	//对FLASH加锁
} 



/***********************************************************************************
函 数 名：Data_Area_Mass_Write										 	
功能描述：向FLASH数据区批量写入数据																	
输    入：unsigned int wAddress	  数据区空间写入起始地址											
					unsigned char *pData		数据指针，指向写入数据缓存数组
					unsigned char Length		写入数据长度												
返    回：无																	
***********************************************************************************/
void Data_Area_Mass_Write(unsigned int Address,unsigned char *pData,unsigned int Length)
{
	unsigned int i;
	FSCMD 	= 	0;
	LOCK  = CMD_DATA_AREA_UNLOCK;						//数据区解锁
	PTSH = (unsigned char)(Address>>8);			//填写高位地址
	PTSL = (unsigned char)Address;        	//填写低位地址
	FSCMD = CMD_DATA_AREA_WIRTE;						//执行写操作
	for(i = 0; i < Length; i++)
	{
		////uart_printf ("wire = 0x%x\n",(u16)(*pData));		//装载数据	
		FSDAT = *pData++;	
	}
	LOCK  = CMD_FLASH_LOCK;						    	//对FLASH加锁
} 



/***********************************************************************************
函 数 名：Data_Area_Read_Byte											 	
功能描述：从FLASH数据区读出一字节数据																
输    入：unsigned int Address	数据区空间读地址																							
返    回：读取的一字节数据																	
***********************************************************************************/
unsigned char Data_Area_Read_Byte(unsigned int Address)
{	
	unsigned char Data_Temp;
	FSCMD 	= 	0;
	PTSH = (unsigned char)(Address>>8);				//填写高位地址
	PTSL = (unsigned char)Address;        				//填写低位地址
	FSCMD = CMD_DATA_AREA_READ;							//执行读操作
	Data_Temp = FSDAT;
	LOCK  = CMD_FLASH_LOCK;						    	//对FLASH加锁
	return Data_Temp;
} 



/***********************************************************************************
函 数 名：Data_Area_Mass_Read										 	
功能描述：从FLASH数据区批量读出数据																	
输    入：unsigned int Address	  数据区空间读起始地址											
					unsigned char *pData		数据指针，指向读出数据缓存数组
					unsigned char Length		读数据长度												
返    回：无																	
***********************************************************************************/
void Data_Area_Mass_Read(unsigned int Address,unsigned char *pData,unsigned int Length)
{
	unsigned int i;
	FSCMD 	= 	0;
	PTSH = (unsigned char)(Address>>8);				//填写高位地址
	PTSL = (unsigned char)Address;        				//填写低位地址
	FSCMD = CMD_DATA_AREA_READ;							//执行读操作
	for(i = 0; i < Length; i++)
	{	
		////uart_printf ("READ = 0x%x\n",(u16)(*pData));										
		*pData++ = FSDAT;
	}
	LOCK  = CMD_FLASH_LOCK;						    	//对FLASH加锁
} 


void Save_Data_To_Eeprom(u16 addr,u16 len,u8 *ndata)
{
	u8 i;
	u8 k = 5;
	u8 tmp[20];
	u8* p = &tmp[0];
	u8 crc;
	crc = 0;
	*(ndata+len) = GetCrc((u8 *)&*ndata,len,0xFF);
	crc = GetCrc((u8 *)&*ndata,len,0xFF);
	while(k--)
	{
		for(i = 0; i<len+1; i++)
			Data_Area_Write_Byte(*(ndata+i),(addr+i));	/* 设置默认参数 */
		for(i = 0; i<len+1; i++)
			tmp[i] = Data_Area_Read_Byte(addr+i);

		crc = GetCrc((u8 *)&*p,len,0xFF);
		if(*(p+len) == GetCrc((u8 *)&*p,len,0xFF))
			break;
		////////////M_TESTTIME();
		////////////M_TESTTIME();
		////////////M_TESTTIME();
	}
}

u16 F_PollingCmd22(volatile u16 temp,u8 cmd)
{
	static volatile u16 i;/* 加了静态修饰，导致问题。 i 不会变化?? */
	static volatile u16 tempbuf = 0;
	tempbuf = temp;
	Save_Cmd_Iqe_Index = cmd;
	for (i = 0x0001u; i <= 0x8000u; i<<=1)
	{	
		if(tempbuf&i)
		{	tempbuf &= ~i;
			break;
		}
		else		   		 
			Save_Cmd_Iqe_Index++;
		if(i == 0x8000u)
			break;	
		/* 在什么地方被清除掉？ */
	}
	return tempbuf;
}


void F_SaveDataToEEprom()
{	
	//u8 len;
	//if(SaveFlag.wVal & 0x1FFFu) /* 查询 待保存数据 命令帧数量 */
	//{	SaveFlag.wVal = F_PollingCmd22(SaveFlag.wVal,1);
	//	len = Save_Cmd_Iqe_Index - 1;/* 必须的 */
	//	if(len == 0)
	//		Save_Data_To_Eeprom(T_TheVaEEpromParamAddr[len],16-2,(u8 *)&TheVa.Param);
	//	else
	//		Save_Data_To_Eeprom(T_TheVaEEpromParamAddr[len],8,(u8 *)&TheVa.TSEG[len-1]);
	//}
	if(SaveFlag.wVal)
	{	SaveFlag.wVal = 0;
		Data_Area_Sector_Erase(0);
		TheVa.Sum = GetSum((u8 *)&TheVa,sizeof(TheVa)-1);
		Data_Area_Mass_Write(0,(u8 *)&TheVa,sizeof(TheVa));/* 设置默认参数 */
		
	//	////uart_printf ("UIsdfD= ");
		//Data_Area_Mass_Read(0,(u8 *)&TheVa,sizeof(TheVa));	
	}
}
/* static ULONG SlaveID;
SlaveID.dwVal = Read_32bit_UID(); */
void Read_Eeprom_To_RAM(u16 addr,u16 len,u8 *ndata,const u8* init)
{
	u8 k = 5;
	ULONG SlaveID;
	while(k--)
	{
		Data_Area_Mass_Read(addr,ndata,len);
		////uart_printf ("SUMCNT = 0x%x\n",(u16)GetSum((u8 *)&*ndata,len-1));
		////uart_printf ("SD = 0x%x\n",(u16)*(ndata+len-1));
		if( *(ndata+len-1) != GetSum((u8 *)&*ndata,len-1))
		{
			memcpy(ndata,init,len);	
			SlaveID.dwVal = Read_32bit_UID();				
			TheVa.Param.Slave_ID_HSB = SlaveID.Byte.byte0;
			TheVa.Param.Slave_ID_LSB = SlaveID.Byte.byte1;
			*(ndata+len-1) = GetSum((u8 *)&*ndata,len-1);
			Data_Area_Sector_Erase(0);			/* 擦除数据扇区0 */
			Data_Area_Mass_Write(addr,ndata,len);/* 设置默认参数 */
			////uart_printf ("SUM = 0x%x\n",(u16)*(ndata+len-1));
		}else
			break;
	}
}



code u8 T_TheVaParam_TempC_InitData[] = {
	/* FamilyCode \SetPayloadLen \Master_ID_HSB \Master_ID_LSB	 */	
    0xFE,0x00,0x00,0x00,
    /* Slave_ID_HSB \Slave_ID_LSB CH\DPID */ 
    0x00,0x00,0x00,0x00,
    /* Mode \Mode1 	 */         /* 0x01 阀门状态首次为开启状态 */    /* 保存是首次开启状态，避免影响到复位参数 */
    0x00,0x80,
	/* Default_StartTemp \Default_StopTemp 	 */ 
	(u8)(C_Default_StartTemp>>8),(u8)C_Default_StartTemp,(u8)(C_Default_StopTemp>>8),(u8)C_Default_StopTemp,
    /*  \HighTempAlarm \LowTempAlarm  \Calib  \Conect*/
    (u8)(C_HighTempAlarm>>8),(u8)C_HighTempAlarm,(u8)(C_LowTempAlarm>>8),(u8)C_LowTempAlarm,0x00,0x0A,0x00,
};
code u8 T_TheVaParam_TempF_InitData[]   = {
	/* FamilyCode \SetPayloadLen \Master_ID_HSB \Master_ID_LSB	 */	
    0xFE,0x00,0x00,0x00,
    /* Slave_ID_HSB \Slave_ID_LSB CH\DPID */ 
    0x00,0x00,0x00,0x00,
    /* Mode \Mode1 	 */         /* 0x01 度F */    /* 保存是首次开启状态，避免影响到复位参数 */
    0x80,0x80,					/* 0x01 阀门状态首次为开启状态 */
	/* Default_StartTemp \Default_StopTemp 	 */ 
	(u8)(F_Default_StartTemp>>8),(u8)F_Default_StartTemp,(u8)(F_Default_StopTemp>>8),(u8)F_Default_StopTemp,
    /*  \HighTempAlarm \LowTempAlarm  \Calib  \Conect*/
    (u8)(F_HighTempAlarm>>8),(u8)F_HighTempAlarm,(u8)(F_LowTempAlarm>>8),(u8)F_LowTempAlarm,0x00,0x0A,0x00,
};

 code u8 T_TheVaTSEG1_Addr[] = { 0xFF,0xFF,0xFF,0xFF, (u8)290>>8,(u8)(290),(u8)310>>8,(u8)(310),/* crc带加 */};/* 大端低位地址存放高位数据  */

// code u8 T_TheVaTSEG_C[] = {0xFF,0xFF,0xFF,0xFF, (u8)(250>>8),(u8)(250),(u8)(260>>8),(u8)(260),(u8)(0xFB),};/* 大端低位地址存放高位数据  */
// code u8 T_TheVaTSEG_F[] = {0xFF,0xFF,0xFF,0xFF, (u8)(770>>8),(u8)(770),(u8)(780>>8),(u8)(780),};/* 大端低位地址存放高位数据  */


/* 字节序 注意 */

code u8 T_TheVaParam_TempC_EN[]   = {
		/* FamilyCode \SetPayloadLen \Master_ID_HSB \Master_ID_LSB	 */	
    0xFE,0x00,0x00,0x00,
    /* Slave_ID_HSB \Slave_ID_LSB CH\DPID */ 
    0x00,0x00,0x00,0x00,
    /* Mode \Mode1 	 */         /* 0x01 阀门状态首次为开启状态 */    /* 保存是首次开启状态，避免影响到复位参数 */
    0x80,0x80,
	/* Default_StartTemp \Default_StopTemp 	 */ 
	(u8)(C_Default_StartTemp>>8),(u8)C_Default_StartTemp,(u8)(C_Default_StopTemp>>8),(u8)C_Default_StopTemp,
    /*  \HighTempAlarm \LowTempAlarm  \Calib  \Conect*/
    (u8)(C_HighTempAlarm>>8),(u8)C_HighTempAlarm,(u8)(C_LowTempAlarm>>8),(u8)C_LowTempAlarm,0x00,0x0A,0x00,
	0xFF,0xFF,0xFF,0xFF, (u8)(290>>8),(u8)(290),(u8)(310>>8),(u8)(310),
	0xFF,0xFF,0xFF,0xFF, (u8)(290>>8),(u8)(290),(u8)(310>>8),(u8)(310),
	0xFF,0xFF,0xFF,0xFF, (u8)(290>>8),(u8)(290),(u8)(310>>8),(u8)(310),
	0xFF,0xFF,0xFF,0xFF, (u8)(290>>8),(u8)(290),(u8)(310>>8),(u8)(310),
	0xFF,0xFF,0xFF,0xFF, (u8)(290>>8),(u8)(290),(u8)(310>>8),(u8)(310),
	0xFF,0xFF,0xFF,0xFF, (u8)(290>>8),(u8)(290),(u8)(310>>8),(u8)(310),
	0xFF,0xFF,0xFF,0xFF, (u8)(290>>8),(u8)(290),(u8)(310>>8),(u8)(310),
	0xFF,0xFF,0xFF,0xFF, (u8)(290>>8),(u8)(290),(u8)(310>>8),(u8)(310),
	0xFF,0xFF,0xFF,0xFF, (u8)(290>>8),(u8)(290),(u8)(310>>8),(u8)(310),
	0xFF,0xFF,0xFF,0xFF, (u8)(290>>8),(u8)(290),(u8)(310>>8),(u8)(310),
	0xFF,0xFF,0xFF,0xFF, (u8)(290>>8),(u8)(290),(u8)(310>>8),(u8)(310),
	0xFF,0xFF,0xFF,0xFF, (u8)(290>>8),(u8)(290),(u8)(310>>8),(u8)(310),
};/* 必须加括号 */


 code u16 T_TheVaEEpromParamAddr[13] = {
	D_TheVaParam_Addr,
	D_TheVaTSEG1_Addr,
	D_TheVaTSEG2_Addr,
	D_TheVaTSEG3_Addr,
	D_TheVaTSEG4_Addr,
	D_TheVaTSEG5_Addr,
	D_TheVaTSEG6_Addr,
	D_TheVaTSEG7_Addr,
	D_TheVaTSEG8_Addr,
	D_TheVaTSEG9_Addr,
	D_TheVaTSEG10Addr,
	D_TheVaTSEG11Addr,
	D_TheVaTSEG12Addr,
};

void F_ReadEEpromToRAM()
{	
	/* 写入扇区0 */
	Read_Eeprom_To_RAM(0,sizeof(TheVa),(u8 *)&TheVa,(u8 *)&T_TheVaParam_TempC_EN);
	B_MotorCtrlState = TheVa.Param.Mode1.Bit.bit2;/* 电机状态自检 */
}

void F_ReadSlaveIDEEpromToRAM()
{	
	ULONG SlaveID;/* 不能使用 volatile 修饰SlaveID变量否则导致，ID读取失败。 */
	SlaveID.dwVal = Read_32bit_UID();				
	if((TheVa.Param.Slave_ID_HSB != SlaveID.Byte.byte0)
	 ||(TheVa.Param.Slave_ID_LSB != SlaveID.Byte.byte1))
	{
		////uart_printf ("Slave_ID_HSB  = %x\n",(u16)SlaveID.Byte.byte0);
		////uart_printf ("Slave_ID_LSB  = %x\n",(u16)SlaveID.Byte.byte1);
		TheVa.Param.Slave_ID_HSB = SlaveID.Byte.byte0;
		TheVa.Param.Slave_ID_LSB = SlaveID.Byte.byte1;
		D_SaveThevaDATA = _TRUE;
		F_SaveDataToEEprom();
	}	
	R_ID_ADD64MS = F_GetCRC((u8 *)&SlaveID.Byte.byte0,sizeof(SlaveID.dwVal));
	if(R_ID_ADD64MS&0x0F)
		R_ID_ADD64MS &= 0x0F;
	else
		R_ID_ADD64MS >>= 4;
}

void F_Flash_Init_Set()
{
    PADRD	= FLASH_SIZE*8 - 2;		//划分FLASH最后2个扇区，倒数2*128字节为数据空间	地址为0x4700u.双扇区存储
}