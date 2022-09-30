#ifndef _Uart_H_
#define _Uart_H_

#define UART_TX_BUF_SIZE		20
#define UART_RX_BUF_SIZE		100

typedef struct
{
	unsigned char head;
	unsigned char tail;
}T_Buf_Info;


MyDef T_Buf_Info xdata	uart_send;
MyDef T_Buf_Info xdata	uart_rev;
MyDef unsigned char xdata uart_tx_buf[UART_TX_BUF_SIZE];
MyDef unsigned char xdata uart_rx_buf[UART_RX_BUF_SIZE];
MyDef bit uart_tx_flag;	
//#define Uart_PutChar(n)

void Uart_PutChar(unsigned char bdat);
void Uart_Initial(unsigned long int baudrate);

#ifdef PRINT_EN
void uart_printf(char *fmt,...);
#endif

#endif