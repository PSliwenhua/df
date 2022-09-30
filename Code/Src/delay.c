#include "Main.h"
/*********************************************************************************************************************/
void Delay_50us(unsigned int n)	   
{
	unsigned char i;

	while(n--)
	{
		for(i=0;i<71;i++);
	}
}
void Delay_ms(unsigned int delay_nms)
{
	while(delay_nms--)
	{
		Delay_50us(20);
	}
}
void Delay_us(unsigned int n)	   
{
	unsigned char i;

	while(n--)
	{
		for(i=0;i<2;i++);
	}
}
/*********************************************************************************************************************/
