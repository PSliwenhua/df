#ifndef __SYSINIT_H__
#define __SYSINIT_H__

#define LCD_2_4V    (0)
#define LCD_2_7V    (1)
#define LCD_3_0V	(2)
#define LCD_3_3V	(3)
#define LCD_3_6V	(4)
#define LCD_3_9V	(5)
#define LCD_4_2V	(6)
#define LCD_4_5V	(7)

void F_LCD_INIT(u8 lcdrv);
void F_LcdAll(u8 ndata);

#define INT_TIME	2000			//定时时间，单位为us	/* 适用于8Mhz主频率 */
#define	TH_VAL		(unsigned char)((0x2000 - (INT_TIME*(FOSC/1000))/12000)>>5)
#define	TL_VAL		(unsigned char)(0x2000 - (INT_TIME*(FOSC/1000))/12000)&0x1F

void F_TM0_INIT();

//WDFLG定义
#define WDIF		    (1<<1)
#define WDRF		    (1<<0)
#define WDTS_DISABLE	(0<<5)
#define WDTS_IRCH		(1<<5)
#define WDTS_IRCL		(1<<6)
#define WDTS_XOSCL		(1<<7)
#define WDRE_reset		(1<<0)
#define WDRE_int		(0<<0)
#define GCC_CLRWDT()	(WDFLG = 0xA5)/* 喂狗 */
void F_WDT_INIT();

enum 
{
	P00_INDEX = 0,
	P01_INDEX = 1,
	P02_INDEX = 2,
	P03_INDEX = 3,
	P04_INDEX = 4,
	P05_INDEX = 5,
	P06_INDEX = 6,
	P07_INDEX = 7,
	P10_INDEX = 8,
	P11_INDEX = 9,
	P12_INDEX = 10,
	P13_INDEX = 11,
	P14_INDEX = 12,
	P15_INDEX = 13,
	P16_INDEX = 14,
	P17_INDEX = 15,
	P20_INDEX = 16,
	P21_INDEX = 17,
	P22_INDEX = 18,
	P23_INDEX = 19,
	P24_INDEX = 20,
	P25_INDEX = 21,
	P26_INDEX = 22,
	P27_INDEX = 23,
	P30_INDEX = 24,
	P31_INDEX = 25,
	P32_INDEX = 26,
	P33_INDEX = 27,
	P34_INDEX = 28,
	P35_INDEX = 29,
	P36_INDEX = 30,
	P37_INDEX = 31,
	P40_INDEX = 32,
	P41_INDEX = 33,
	P42_INDEX = 34,
	P43_INDEX = 35,
	P44_INDEX = 36,
	P45_INDEX = 37,
	P46_INDEX = 38,
	P47_INDEX = 39,
	P50_INDEX = 40,
	P51_INDEX = 41,
	P52_INDEX = 42,
	P53_INDEX = 43,
	P54_INDEX = 44,
};
void F_EXINT0_INIT(u8 GPIO);
void F_EXINT1_INIT(u8 GPIO);

u32 Read_32bit_UID(void);
void F_MORTO_INIT();


void F_TOUCH_KEY_INIT();
void F_INIT_XDATA_RAM();

#define LVDE(N)			(N<<7)
#define LVDS_reset		(1<<6)
#define LVDS_int		(0<<6)
#define LVDF			(1<<5)

#define LVDTH_2p0V		0
#define LVDTH_2p7V		1
#define LVDTH_3p7V		2
#define LVDTH_4p4V		3
void F_LVD_INIT();


#endif
