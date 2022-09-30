#ifndef _System_clock_H_
#define _System_clock_H_

//CKCON寄存器定义
#define ILCKE		(1<<7)
#define IHCKE		(1<<6)
#define XLCKE		(1<<3)
#define XLSTA		(1<<2)


//CKSEL寄存器定义
#define RTCKS(N)		(N<<7)

#define CKSEL_IRCH	0	
#define CKSEL_IRCL	2
#define CKSEL_XOSCL	4


void Sys_Clk_Set_IRCH(void);
void Sys_Clk_Set_IRCL(void);
void Sys_Clk_Set_XOSCL(void);
void Sys_Clk_Switch(u8 Clk);

	//CKCON 寄存器定义
	#define XLCKE  (1<<3)
	#define XLSTA  (1<<2)
	//RTCON 定义
	#define RTCE(N)  (N<<7)
	#define MSE(N)  (N<<6)
	#define HSE(N)  (N<<5)
	#define SCE(N)  (N<<4)
	#define MCE(N)  (N<<3)
	#define HCE(N)  (N<<2)
	#define RTCWE(N) (N<<1)
	//RTCIF 定义
	#define RTC_MF  (1<<2)
	#define RTC_HF  (1<<1)
	#define RTC_AF  (1<<0)
    
void RTC_WriteHour(unsigned char hour);
void RTC_WriteMinute(unsigned char minute);
void RTC_WriteSecond(unsigned char second);
void F_RTM_INIT(void);
void F_RTC_INIT(void);
void F_RAM_INIT(void);
void F_TM2_INIT(void);

//寄存器T2CON定义
#define TR2(N)   (N<<6)
#define T2R(N)   (N<<4)   //N=0~3
#define T2IE(N)  (N<<3)
#define UCKS(N)  (N<<2)
#define T2P(N)   (N)	    //N=0~3

//寄存器T2MOD定义
#define TF2			 (1<<7)
#define CF2			 (1<<6)
#define RF2			 (1<<5)
#define CCFG(N)	 (N<<3)	  //N=0~3
#define T2M(N)	 (N)		  //N=0~3


MyDef u16 T2CapValue;
MyDef u16 T2CapValueBuf;
MyDef u16 T2CycleIntv;
MyDef u16 T2CycleIntvBuf;
MyDef u16 T2CycleFlag1;
MyDef u16 MotorCapCnt;


#endif