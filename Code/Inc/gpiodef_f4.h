#ifndef _GPIODEF_H_
#define _GPIODEF_H_
enum
{
	HIGH_Z		            = 0,					
	INPUT		            	= 1,          
	OUTPUT		            = 2,          
                     
	P54_PWM0_SETTING		= 4,
	P06_PWM1_SETTING		= 4,
	P30_PWM2_SETTING		= 4,
                        
	P27_ADC0_SETTING		= 3,
	P31_ADC1_SETTING		= 3,
	P32_ADC2_SETTING		= 3,
	P33_ADC3_SETTING		= 3,
	P34_ADC4_SETTING		= 3,
	P35_ADC5_SETTING		= 3,
	P36_ADC6_SETTING		= 3,
	P37_ADC7_SETTING		= 3,
	P37_ADC_VREF_SETTING    = 4,

	P10_SEG0_SETTING		= 6,
	P11_SEG1_SETTING 		= 6, 
	P12_SEG2_SETTING		= 6,
	P13_SEG3_SETTING 		= 6, 
	P14_SEG4_SETTING		= 6,
	P15_SEG5_SETTING 		= 6, 
	P16_SEG6_SETTING		= 6,
	P17_SEG7_SETTING 		= 6, 
	P20_SEG8_SETTING		= 6,
	P21_SEG9_SETTING 		= 6, 
	P22_SEG10_SETTING		= 6,
	P23_SEG11_SETTING 		= 6, 
	P24_SEG12_SETTING		= 6,
	P25_SEG13_SETTING 		= 6, 
	P26_SEG14_SETTING		= 6,
	P27_SEG15_SETTING 		= 6, 
	P30_SEG16_SETTING		= 6,
	P31_SEG17_SETTING 		= 6, 
	P32_SEG18_SETTING		= 6,
	P33_SEG19_SETTING 		= 6, 
	P34_SEG20_SETTING		= 6,
	P35_SEG21_SETTING 		= 6, 
	P36_SEG22_SETTING		= 6,
	P37_SEG23_SETTING 		= 6, 
	P40_SEG24_SETTING		= 6,
	P41_SEG25_SETTING 		= 6, 
	P42_SEG26_SETTING		= 6,
	P43_SEG27_SETTING 		= 6, 
	P44_SEG28_SETTING		= 6,
	P45_SEG29_SETTING 		= 5,
	
	
	P45_COM4_SETTING		= 6,
	P46_COM3_SETTING		= 6,
	P47_COM2_SETTING		= 6,
	P50_COM1_SETTING		= 6,
	P51_COM0_SETTING		= 6,

	P10_CAP_SETTING		    = 5,
  P06_TK0_SETTING		    = 5,
	P11_TK1_SETTING		    = 5,
	P12_TK2_SETTING		    = 5,
	P13_TK3_SETTING		    = 5,
	P14_TK4_SETTING		    = 5,
	P15_TK5_SETTING		    = 5,
	P16_TK6_SETTING		    = 5,
	P17_TK7_SETTING		    = 5,
	P20_TK8_SETTING		    = 5,
	P21_TK9_SETTING		    = 5,
	P22_TK10_SETTING		= 5,
	P23_TK11_SETTING		= 5,
	P24_TK12_SETTING		= 5,
	P25_TK13_SETTING		= 5,
	P26_TK14_SETTING		= 5,
	P05_TK15_SETTING		= 5,

	P06_TLCON_SETTING		= 6,
		
  P00_VP3_SETTING			= 6,
	P01_VP2_SETTING			= 6,
	P02_VP1_SETTING			= 6,
	
	P03_CUP1_SETTING		= 6,
	P04_CUP2_SETTING		= 6,

	P22_UART_TX_SETTING		= 3,      
	P21_UART_RX_SETTING		= 3,      
                           
	P06_I2C_SDA_SETTING		= 3,      
	P05_I2C_SCL_SETTING		= 3,                            	
                        
	P26_T0_SETTING			= 1,        
	P23_T1_SETTING			= 1,        
	P24_T2_SETTING			= 1,        
                        
	P55_RESET_SETTING		= 3,			  	

	P25_T2CP_SETTING		= 3,  
	P25_T2EX_SETTING		= 1,  

	P07_SWIM_SETTING		= 3,

	P52_XOSCL_OUT_SETTING	= 3,
	P53_XOSCL_IN_SETTING	= 3,

	PU_EN				= 0x80,
	PD_EN				= 0x40,
	OP_EN				= 0x20,
};	
#define  GPIO_Init(reg,val)	reg = val
/******************************************************************************/

#endif
