#ifndef _Main_H_
#define _Main_H_

#ifdef MainS
	#define MyDef
#else
	#define MyDef extern
#endif

#define VERSION0 Shuzi_0
#define VERSION1 Shuzi_1
#include <intrins.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <absacc.h>
//#include "MC96F6508A.h"
#include "TypeDef.h"

#include "ca51f4_config.h"		
#include "ca51f4sfr.h"
#include "ca51f4xsfr.h"
#include "gpiodef_f4.h"
#include "system_clock.h"

#include "uart.h"
#include "delay.h"


#include "INTERRUPT.h" 
#include "INIT.h"
#include "TIMER.h" 
#include "APP.h"
#include "KEY.h" 
#include "Buz.h" 
#include "LCD.h"
#include "ADC.h" 
#include "LVD.h" 
#include "Flash.h" 

#include "cmt2300a_defs.h"
#include "cmt2300a_params.h"
#include "cmt2300a.h"
#include "CMT_SPI3.h"
#include "radio.h"
#include "ThermostaticValve.h" 
#include "RF.h" 
#include "GPIO_DEFS.h"
#include "CMT2300A_HAL.h"
#include "Thermistor.h" 

MyDef xdata UUWORD SaveFlag;
	#define D_SaveThevaDATA SaveFlag.Bit.bit0  
	#define D_SaveTimerSEG1 SaveFlag.Bit.bit1  
	#define D_SaveTimerSEG2 SaveFlag.Bit.bit2  
	#define D_SaveTimerSEG3 SaveFlag.Bit.bit3  
	#define D_SaveTimerSEG4 SaveFlag.Bit.bit4  
	#define D_SaveTimerSEG5 SaveFlag.Bit.bit5  
	#define D_SaveTimerSEG6 SaveFlag.Bit.bit6  
	#define D_SaveTimerSEG7 SaveFlag.Bit.bit7  
	#define D_SaveTimerSEG8 SaveFlag.Bit.bit8  
	#define D_SaveTimerSEG9 SaveFlag.Bit.bit9  
	#define D_SaveTimerSEGA SaveFlag.Bit.bit10 
	#define D_SaveTimerSEGB SaveFlag.Bit.bit11 
	#define D_SaveTimerSEGC SaveFlag.Bit.bit12 


#define  D_FrameIntvl	4		//帧传送间隔 1ms*4 = 4MS
#define  D_FrameTimeOut	3		//帧传送间隔 1ms*3 = 3MS

enum{			
   _FALSE		,    
   _TRUE  		,   
};
enum{	
   _Close  		,  		
   _Open		   ,    
};
enum{			
   _Normal		,    
   _Error   	,   
};

enum{	
   _Clear		,  		
   _Install		,    
};
enum{	
   _DN		   ,  		
   _EN		   ,    
};
enum{	
   _LowLevel	,    
   _HighLevel	,  		
};
enum{			
   _OFF			,    
   _ON	   	,   
};
enum{			
   _NO_POINT	,    
   _HAVE_POINT  ,   
};


void F_NOP(u16 NOPTT);
		
void F_LEDON();
void F_LEDOFF();

#define M_LEDOUT()          (P07F = OUTPUT)
#define M_LEDON()           (P07 = 0)  //clr(P07, GPIO_PIN_0)
#define M_LEDOFF()          (P07 = 1)  //set(P07, GPIO_PIN_0)
#define M_LEDFLASH()        (P07 ^= 1) //tog(P07, GPIO_PIN_0)
//#define //M_TESTTIME()        (_nop_())
#define M_TESTTIME()        {P55F = OUTPUT;tog(P55, GPIO_PIN_0);              \
                              _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();\
                              _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();\
                              _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();\
                              _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();\
                              tog(P55, GPIO_PIN_0);}

#define M_PHS1       P17
#define M_PHS2       P16
#define M_EN         P54
#define M_A1         P17
#define M_B1         P16

#endif
