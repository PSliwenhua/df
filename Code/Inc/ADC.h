#ifndef __ADC_H__
#define __ADC_H__



#define M_ADC_OFF()   		{_sadc0 = NO_AN_Channel;}
#define D_AD_Times 12       // 14连续读取次数

enum{			
    D_Battery_10PP ,
    D_Battery_25PP ,
    D_Battery_50PP ,
    D_Battery_75PP ,
    D_Battery_100P ,  
    D_Battery_FULL ,
    D_Battery_UNKN ,
};

#define D_Voltage6_4v	3724
#define D_Voltage5_8v	3351
#define D_Voltage5_4v	3103
#define D_Voltage5_0v	2855
#define D_Voltage4_6v	2607

enum{			
    D_Battery     ,
    D_Type_C      ,
};
typedef struct 
{  UBYTE Flag;
	u8 CntOpenPower;
	u8 CntRead;
	u8 Level;
	u8 Charge;
	u16 Adc;
	u16 AdcLast;
	u8 Supply;
}T_Battery;
MyDef xdata T_Battery Cell;//Battery;
    #define D_DetecBattery	        60//60秒	
    #define R_Supply             Cell.Supply
    #define B_OpenCellReadPower  Cell.Flag.Bit.bit0
    #define B_DetecBattery       Cell.Flag.Bit.bit1
    #define B_DetecBatteryXor    Cell.Flag.Bit.bit2
MyDef xdata u8 R_Battery;
/*     #define Cell.Flag.Bit.bit3
    #define Cell.Flag.Bit.bit4 */

typedef struct
{
	u16 Adc;
	u16 AdcLast;
	s16 Temp;
	u8 State;
}NTC_TEMP;
MyDef xdata NTC_TEMP  NTC;
#define M_NTC_Ctrl_GND_OFF()      (P55 = 1)//set(P55, GPIO_PIN_0)
#define M_NTC_Ctrl_GND_ON()       (P55 = 0)//clr(P55, GPIO_PIN_0)
u16 abs58(s16 temp);
u16 F_GetMid(u16 *p, u8 length);
u16 F_Average_AD_Convert();
void F_AdcReadBattery(void);
void F_AdcReadBatteryCnt(void);
u16 F_GetADCTemperature();


//ADCON定义
#define AST(N)		(N<<7)					//ADC启动 ， AST=0结束
#define ADIE(N)		(N<<6)					//中断使能
#define ADIF			(1<<5)					 	//中断标志
#define HTME(N) 	(N<<2)					//N=0-7			 //采样时间设置, 时间为2的HTME次方的时钟周期
#define VSEL(N) 	(N)							//N=0-3			 //选择参考电压 0-内部 1-VDD 2-外部

//ADCFGL定义													   
#define ACKD(N)			(N<<5)  			//N=0-7			 //ADC时钟分频	  分频倍数=（ACKD+1)
#define ADCALE(N)		(N<<4) 					 //ADC校正，	  选择内部参考电压才有效 
#define ADCHS(N)		(N) 					//N=0-15		 //ADC通道选择 ， 1-13对应通道0-12

//ADCFGH定义
#define VTRIM(N)	(N)						 		//0-63	   校正内部参考电压

//ADOPC定义
#define GAIN(N)	(N)						//增益
enum 
{
  ADC_REF_INNER  	= 0,
  ADC_REF_VDD  		= 1,
  ADC_REF_Outer  	= 2
};



enum 
{
  NO_AMP = 0,
  AMP_GAIN_1_4 = 1,
  AMP_GAIN_1_3 = 2,
  AMP_GAIN_1_2 = 3,
};

enum 
{
  ADC_CH0  	= 1,
  ADC_CH1  	= 2,
  ADC_CH2  	= 3,
  ADC_CH3  	= 4,
  ADC_CH4  	= 5,
  ADC_CH5  	= 6,
  ADC_CH6  	= 7,
  ADC_CH7  	= 8,
  ADC_VDD  	= 9,
};
void F_ADC_INIT();

#endif
