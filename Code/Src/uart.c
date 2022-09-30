#include "Main.h"

/*********************************************************************************************************************/
/*********************************************************************************************************************/
#ifdef UART_EN
//注意： 以下波特率参数对应主时钟为16M，如选择另外的主时钟频率，参数须重新计算。
code unsigned long int BR_TAB[]=
{
	1200,
	2400,
	4800,
	9600,
	19200,
	38400,
	57600,
	115200,
};
code unsigned int BR_SET_TAB[][2]=
{
	{416,31},
	{208,31},
	{104,31},
	{52,31},
	{26,31},
	{13,31},
	{10,27},
	{5,27},
};
void Uart_Initial(unsigned long int baudrate)
{

	unsigned int value_temp;
	unsigned char i;

	uart_send.head=0;
	uart_send.tail=0;
	uart_rev.head=0;
	uart_rev.tail=0;
	uart_tx_flag=0;

	for(i=0;i<sizeof(BR_TAB)/4;i++)
	{
		if(baudrate == BR_TAB[i])
		{
			value_temp = 0x400 - BR_SET_TAB[i][0];
			UDCKS = 0x80 | BR_SET_TAB[i][1]; 
			break;
		}
	}
	if(i == sizeof(BR_TAB)/4) return;	//如果所设置的波特率不在表格中，可自行添加。

	GPIO_Init(P22F,P22_UART_TX_SETTING);
	GPIO_Init(P21F,P21_UART_RX_SETTING);

	SRELH = (unsigned char)(value_temp>>8);
	SRELL = (unsigned char)(value_temp);
	
	SCON = 0xD0;
	ES1 =	1;	
}
void Uart_PutChar(unsigned char bdat)
{
	unsigned char free_space;
	unsigned char tail_tmp;
	while(1)
	{		
		tail_tmp = uart_send.tail;
		if(uart_send.head < tail_tmp)
		{
			free_space = tail_tmp - uart_send.head;
		}
		else
		{
			free_space = UART_TX_BUF_SIZE + tail_tmp - uart_send.head;
		}		
		if(free_space > 1)
		{
			ES1 = 0; 
			uart_send.head++;
			uart_send.head %= UART_TX_BUF_SIZE;
			uart_tx_buf[uart_send.head] = bdat;
			if(!uart_tx_flag)
			{
				ES1 = 1;
				uart_send.tail++;
				uart_send.tail %= UART_TX_BUF_SIZE;		
				SBUF = uart_tx_buf[uart_send.tail];				
				uart_tx_flag = 1;		
			}
			else
			{
				ES1 = 1;	
			}			
			break;
		}
	}
}
void UART_ISR (void) interrupt 6	
{
	if(SCON & 0x01)
	{
		SCON = (SCON&~(0x03))|0x01;			 
		uart_rev.head++;
	  uart_rev.head %= UART_RX_BUF_SIZE;
		uart_rx_buf[uart_rev.head]=SBUF;
	}
	if(SCON & 0x02)
	{
		SCON = (SCON&~(0x03))|0x02;	
		if(uart_send.head!=uart_send.tail)
		{
			uart_send.tail++;
			uart_send.tail %= UART_TX_BUF_SIZE;
			SBUF=uart_tx_buf[uart_send.tail];				
		}
		else
		{
			uart_tx_flag=0;
		}		
	}
}
#endif


#ifdef PRINT_EN
void UartPutStr(char *str)
{
	while(*str)
	{	
 		Uart_PutChar(*str++);
	}
}
void uart_printf(char *fmt,...) 
{
    va_list ap;
    char xdata string[256];
    va_start(ap,fmt);
    vsprintf(string,fmt,ap);
    UartPutStr(string);
    va_end(ap);
}
#endif
/*********************************************************************************************************************/
