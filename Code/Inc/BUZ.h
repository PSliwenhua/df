#ifndef __BUZ_H__
#define __BUZ_H__

typedef struct 
{
	UBYTE Flag;
	UBYTE AlarmFlag;
	u8 Cycle2s;
	u8 Cycle125ms;
	u8 AlarmCnt;
}T_Buz;
MyDef T_Buz volatile Buz;
    #define B_BuzEn       		Buz.Flag.Bit.bit0
    #define B_BuzKeyEn       	Buz.Flag.Bit.bit1
    #define B_BuzAlramEn        Buz.Flag.Bit.bit2
    #define B_BuzKeyBreak       Buz.Flag.Bit.bit3
//    #define B_BuzXor	        Buz.Flag.Bit.bit4


#define D_BuzAlarmTime 	    5//5秒
#define M_BuzDrive() 	  (P06 ^= 1) //tog(P06, GPIO_PIN_0)
#define M_BuzOn() 	      (P06 = 1) //set(P06, GPIO_PIN_0)//  { TM2_ENABLE(); B_BuzXor = 1;clr(_pf, GPIO_PIN_7); }
#define M_BuzOff()        (P06 = 0) //clr(P06, GPIO_PIN_0)//  { TM2_DISABLE();B_BuzXor = 0;set(_pf, GPIO_PIN_7); }

void F_KeyVoiceCheak(u8 KeyValueValid);
u8 F_KeyBreakFault();
void F_BuzAlarmOverDownCnt();
void F_Buz10hzBiBiAlarmCheakCntTask();

#endif
