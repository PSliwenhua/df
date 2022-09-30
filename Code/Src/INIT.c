#include "Main.h"

void F_LCD_INIT(u8 lcdrv)
{
	P51F = P51_COM0_SETTING;
	P50F = P50_COM1_SETTING;
	P47F = P47_COM2_SETTING;
	P46F = P46_COM3_SETTING;
	
	P45F = P45_SEG29_SETTING;	
	P44F = P44_SEG28_SETTING;	
	P43F = P43_SEG27_SETTING;
	P42F = P42_SEG26_SETTING; 
	P41F = P41_SEG25_SETTING;
	P40F = P40_SEG24_SETTING;
	P37F = P37_SEG23_SETTING; 
	P36F = P36_SEG22_SETTING; 
	P35F = P35_SEG21_SETTING;  
	P34F = P34_SEG20_SETTING;
	P31F = P31_SEG17_SETTING;
	P30F = P30_SEG16_SETTING;
	P24F = P24_SEG12_SETTING;
	P23F = P23_SEG11_SETTING;
	P15F = P15_SEG5_SETTING;
	P14F = P14_SEG4_SETTING;



	//P14F = P14_SEG4_SETTING;	/* INDEX = 0就对应配置的第一个seg */
	//P15F = P15_SEG5_SETTING;
	//P23F = P23_SEG11_SETTING;
	//P24F = P24_SEG12_SETTING;
	//P30F = P30_SEG16_SETTING;
	//P31F = P31_SEG17_SETTING;
	//P34F = P34_SEG20_SETTING;
	//P35F = P35_SEG21_SETTING;  
	//P36F = P36_SEG22_SETTING; 
	//P37F = P37_SEG23_SETTING; 
	//P40F = P40_SEG24_SETTING;
	//P41F = P41_SEG25_SETTING;
	//P42F = P42_SEG26_SETTING; 
	//P43F = P43_SEG27_SETTING;
	//P44F = P44_SEG28_SETTING;	
	//P45F = P45_SEG29_SETTING;	


	GPIO_Init(P00F,P00_VP3_SETTING);
	GPIO_Init(P01F,P01_VP2_SETTING);
	GPIO_Init(P02F,P02_VP1_SETTING);
	GPIO_Init(P03F,P03_CUP1_SETTING);
	GPIO_Init(P04F,P04_CUP2_SETTING);

	LCDIVH = 0;                                   	//设置LCD时钟分频，目标帧频率为64HZ
	LCDIVL = 0;	
	LCCAD = 0;																		//关闭LCD_CAD
	
	LCPMP = PCKD(2) | PMPE(1);                    	//设置三相时钟分频、使能
	LCCFG =	DMOD_5ua | BIAS_1_3 | LCDRV_LEV(lcdrv); //设置LCD驱动电流、偏压(bias)、驱动强度
//	LCCON = LEN_IRCL | LCD_TYPE(2) | LCE(0);      	//设置LCD时钟源、选择LCD模式、使能LCD
	LCCON = LEN_XOSCL | LCD_TYPE(2) | LCE(0);	
	Delay_ms(30);
	Delay_ms(30);
	Delay_ms(30);
	LCCON |= LCE(1);
}

void F_LcdAll(u8 ndata)
{
	u8 i = 0;
	for(i = 0; i < 16; i++)
	{
		INDEX = i;
		LCDAT = ndata;
	}
}

void F_TM0_INIT()
{
	TMOD = (TMOD&0xFC)|0x00; 	//模式选择: 定时器0，模式0。
	TH0 = TH_VAL;    			//高8位装初值
	TL0 = TL_VAL;    			//低8位装初值
	TR0 = 1;      				//定时器0使能  
	ET0 = 1;      				//定时器0中断使能
	PT0 = 0;      				//设置定时器0中断优先级为低优先级
}

void F_WDT_INIT()
{
	WDCON = WDTS_XOSCL | WDRE_reset;   	//设置看门狗时钟源为XOSCL，模式为复位模式
	WDVTHH = 0;							//看门狗复位阈值高八位设置 当前值为5s
	WDVTHL = 0x5f;						//看门狗复位阈值低八位设置	
	GCC_CLRWDT();						//喂狗
}

void F_EXINT0_INIT(u8 GPIO)
{
	P33F = INPUT;						//P33设置为输入功能
	IT0CON = GPIO;						//设置GPIO为INT0中断引脚
	EX0 = 1;							//INT0中断使能
	IE0 = 1;							//外部中断0中断使能
	IT0 = 0;							//设置INT0为上升沿触发
	PX0 = 1;							//设置INT0中断为最高优先级
}

void F_EXINT1_INIT(u8 GPIO)
{
	P32F = INPUT;						//P32设置为输入功能
	IT1CON = GPIO;					    //设置GPIO为INT1中断引脚
	EX1 = 1;							//INT1中断使能
	IE1 = 1;							//外部中断1中断使能
	IT1 = 0;							//设置INT1为上升沿触发
	PX1 = 1;							//设置INT1中断为最高优先级
	PX1 = 0;							//设置INT1中断为最高优先级
}

u32 Read_32bit_UID(void)				
{
	ULONG ID;
	LOCK  = 0x2B;	
	FSCMD = 0x80;	
	PTSH = 0x01;				
	PTSL = 0x00;        			
	FSCMD = 0x81;	
	ID.Byte.byte0 = FSDAT;
	ID.Byte.byte1 = FSDAT;
	ID.Byte.byte2 = FSDAT;
	ID.Byte.byte3 = FSDAT;
	FSCMD = 0;
	LOCK = 0xAA;
	return ID.dwVal;
}

void F_MORTO_INIT()
{
	P16F = OUTPUT;	
	P17F = OUTPUT;	
	P54F = OUTPUT;	
	P25F = INPUT;	
	P26F = INPUT;	
	//进省电模式之前，悬浮的IO设置为高阻上拉
	GPIO_Init(P05F,HIGH_Z|PU_EN);
	GPIO_Init(P06F,HIGH_Z|PU_EN);
	//P05 = 0;	
	//P06 = 0;	
	M_LEDOUT();
	M_LEDOFF();
}

//EPCON寄存器定义
#define EPPL(N)	(N<<7)

void F_TOUCH_KEY_INIT()
{
	TOUCH_SDA_IN;  
	TOUCH_SCL_IN;
	/* P20F = INPUT|PU_EN;											//P10设置为输入模式
	INDEX = 0;												//EPCON为带索引的寄存器，设置INDEX=0 对应INT2
	EPCON = EPPL(1) | P20_INDEX;			//设置P10为INT2中断引脚
	INT2EN = 1; 											//外部中断2中断使能
	EPIE |= 0x01;											//INT2中断使能 */
}

#define	CONST_XDATA_RAM_Start	0x0//xdataRAM的起始地址（根据硬件连线计算）
#define	CONST_XDATA_RAM_Len	0x03FFu//xdataRAM的长度
#define	CONST_XDATA_RAM_Value	0x0//xdataRAM的要填充的数值　

void F_INIT_XDATA_RAM()
{
	u8 xdata * ptr = 0;
	for (ptr=CONST_XDATA_RAM_Start; ptr<CONST_XDATA_RAM_Len; ptr++)
	{
		*ptr = CONST_XDATA_RAM_Value;
	}
}

void F_LVD_INIT()
{
	/* LVDCON = LVDE(1) | LVDS_reset | LVDTH_2p0V;	//设置LVD使能,设置LVD为复位模式,检测电压为2.0V
	// 	LVDCON = LVDE(1) | LVDS_reset | LVDTH_2p7V;	//设置LVD使能,设置LVD为复位模式,检测电压为2.7V
	// 	LVDCON = LVDE(1) | LVDS_reset | LVDTH_3p7V;	//设置LVD使能,设置LVD为复位模式,检测电压为3.7V
	// 	LVDCON = LVDE(1) | LVDS_reset | LVDTH_4p4V;	//设置LVD使能,设置LVD为复位模式,检测电压为4.4V
	//INT4EN = 1; 								//INT4 中断使能 */


	LVDCON = LVDE(1) | LVDS_int | LVDTH_2p0V;	//设置LVD使能,设置LVD为中断模式,检测电压为2.0V
// 	LVDCON = LVDE(1) | LVDS_int | LVDTH_2p7V;	//设置LVD使能,设置LVD为中断模式,检测电压为2.7V
// 	LVDCON = LVDE(1) | LVDS_int | LVDTH_3p7V;	//设置LVD使能,设置LVD为中断模式,检测电压为3.7V
// 	LVDCON = LVDE(1) | LVDS_int | LVDTH_4p4V;	//设置LVD使能,设置LVD为中断模式,检测电压为4.4V

	INT4EN = 1; 								//INT4 中断使能
}