#ifndef _Thermistor_H_
#define _Thermistor_H_


#define TEMP_INVALID		 ((WORD)0x07ffu)

enum{
	TEST_RRC,
	TEST_TRC,
};
enum{
	DTEMP_C,
	DTEMP_F,
};

enum{
	D_MotorOff,
	D_MotorOn,
};
enum{
	D_Daytime,
	D_Night  ,
};
MyDef xdata UBYTE PWMFlag;
	#define B_A		PWMFlag.Bit.bit0
	#define B_A_   	PWMFlag.Bit.bit1
	#define B_B  	PWMFlag.Bit.bit2
	#define B_B_    PWMFlag.Bit.bit3

void F_GetTemperatureCheak();
void F_CutTempUnitCF();
int F_ChangeCtoF(int temp);
int F_ChangeFtoC(int temp);
void F_HeatingRadiatorOnOffCheakTask();
int F_Calib_ChangeCtoF(int temp);
int F_Calib_ChangeFtoC(int temp);


#endif 
