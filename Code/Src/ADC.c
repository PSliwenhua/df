#include "Main.h"

code unsigned char TemperatureTable[60] = {
	0x1D,0x1E,0x1E,0x1F,0x1F,0x20,0x21,0x21,0x22,0x22,	//  -9C ->   0C
	0x23,0x23,0x24,0x24,0x24,0x25,0x25,0x25,0x26,0x26,	//   1C ->  10C
	0x26,0x26,0x27,0x27,0x27,0x27,0x27,0x27,0x27,0x27,	//  11C ->  20C
	0x27,0x27,0x26,0x26,0x26,0x26,0x26,0x25,0x25,0x25,	//  21C ->  30C
	0x24,0x24,0x24,0x23,0x23,0x22,0x22,0x22,0x21,0x21,	//  31C ->  40C
	0x20,0x20,0x1F,0x1F,0x1E,0x1E,0x1D,0x1D,0x1C,0x1C,	//  41C ->  50C
};

void F_ADC_INIT()
{
	P55F = OUTPUT;	//ADC控制脚
	/**********设置ADC引脚功能*************************************************************/
	P27F = P27_ADC0_SETTING;	//设置P27为ADC引脚功能
	// 	P31F = P31_ADC1_SETTING;	//设置P31为ADC引脚功能
	// 	P32F = P32_ADC2_SETTING;	//设置P32为ADC引脚功能
	// 	P33F = P33_ADC3_SETTING;	//设置P33为ADC引脚功能
	// 	P34F = P34_ADC4_SETTING;	//设置P34为ADC引脚功能
	// 	P35F = P35_ADC5_SETTING;	//设置P35为ADC引脚功能
	// 	P36F = P36_ADC6_SETTING;	//设置P36为ADC引脚功能
	// 	P37F = P37_ADC7_SETTING;	//设置P37为ADC引脚功能
	// 		P37F = P37_ADC_VREF_SETTING;	//如果ADC参考电压选择为外部参考电压，需要设置P37为外部参考电压引脚，并且ADC7通道不能使用。
	/**********初始化ADC寄存器（设置ADC时钟、选择ADC参考电压、设置ADC运放）****************************/
	// 	ADCON = AST(0) | ADIE(0) | HTME(7) | VSEL(ADC_REF_INNER);		//设置ADC参考电压为内部1.5V
		ADCON = AST(0) | ADIE(0) | HTME(7) | VSEL(ADC_REF_VDD);				//设置ADC参考电压为VDD
	// 	ADCON = AST(0) | ADIE(0) | HTME(7) | VSEL(ADC_REF_Outer);		//设置ADC参考电压为外部参考电压
		ADOPC = GAIN(NO_AMP);
	/**************************************************************************************************/


	/**********设置ADC通道和时钟分频*********************************************************************/
	// 	ADCFGL = ACKD(7) | ADCALE(1) | ADCHS(ADC_VDD);	//选择ADC通道为1/4VDD
		ADCFGL = ACKD(7) | ADCALE(1) | ADCHS(ADC_CH0);	//选择ADC0通道
	// 	ADCFGL = ACKD(7) | ADCALE(1) | ADCHS(ADC_CH1);	//选择ADC1通道
	// 	ADCFGL = ACKD(7) | ADCALE(1) | ADCHS(ADC_CH2);	//选择ADC2通道
	// 	ADCFGL = ACKD(7) | ADCALE(1) | ADCHS(ADC_CH3);	//选择ADC3通道
	// 	ADCFGL = ACKD(7) | ADCALE(1) | ADCHS(ADC_CH4);	//选择ADC4通道
	// 	ADCFGL = ACKD(7) | ADCALE(1) | ADCHS(ADC_CH5);	//选择ADC5通道
	// 	ADCFGL = ACKD(7) | ADCALE(1) | ADCHS(ADC_CH6);	//选择ADC6通道
	// 	ADCFGL = ACKD(7) | ADCALE(1) | ADCHS(ADC_CH7);	//选择ADC7通道
	/**************************************************************************************************/

}

u16 F_GetMid(u16 *p, u8 length)
{
    u8 i,j;
    u16 temp;
    for(i=1; i<length; i++)
    {   for(j=0; j<length-i; j++)
        {   if(p[j] < p[j+1])
            {   temp   = p[j];
                p[j]   = p[j+1];
                p[j+1] = temp;    
            }
        }
    }
    return p[length>>1];
}

u16 F_Average_AD_Convert()
{
	u8 i = 0;
	u16 tData[D_AD_Times];
	u16 tBuffer = 0;
	for(i = 0; i < D_AD_Times;i++)
	{
		ADCON |= AST(1);								//启动ADC转换
		while(!(ADCON & ADIF));							//等待ADC转换完成
		ADCON |= ADIF;									//清除ADC中断标志
		tData[i] = ADCDH*256 + ADCDL;					//读取AD值
		tData[i] >>= 4;
	//	////uart_printf ("ADC Value = %u\n",tData[i]);	//打印AD值
		//Delay_ms(100);
	}
	F_GetMid(tData,D_AD_Times);// 排序 	
	for(i = 5;i < 7;i ++)	   //D_AD_Times = 12	
		tBuffer += tData[i];
	return	tBuffer >>= 1; 
}

u16 abs58(s16 temp)
{	
	if(temp < 0)
		return	temp = ~temp+1;
	return	temp;
}

u16 F_GetADCTemperature()
{
	u8 i = 60;
	u8 TempScale = 0;
	u8 RadixTemp = 0;
	F_ADC_INIT();
 	M_NTC_Ctrl_GND_ON(); 
//	Delay_ms(100);/* 必须延时足够1ms，等待电压稳定，否则温度检测偏高 */
	NTC.Adc = F_Average_AD_Convert();
	//////uart_printf ("ADC Value = %u\n",NTC.Adc);	//打印AD值
	M_NTC_Ctrl_GND_OFF();    
	/* 使用MOS管，没有导通压降。控制NTC检测温度。检测温度正常
		使用三极管，有导通压降。检测温度偏低5度。
	 */

	//if(abs58(NTC.AdcLast - NTC.Adc) >= 8)
	//{
		NTC.AdcLast = NTC.Adc;
		if(NTC.Adc >= 0x0CFCu)
			return 0;		// <-10C
		else if(NTC.Adc <= 0x04B3u)
			return 500+100;	// >50C
		else
			NTC.Adc -= 0x04B3u;
		i = 60;
		while(1)
		{
			TempScale = TemperatureTable[i];//存每1度的差值
			if(NTC.Adc < TempScale)
				break;
			i--;
			NTC.Adc -= TempScale;
		}
		RadixTemp = (NTC.Adc * 10 )/ TempScale;
		return (i * 10 + RadixTemp);
	//}else
	//	return	Temp.C+100;
}

