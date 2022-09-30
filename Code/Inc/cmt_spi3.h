#ifndef __CMT_SPI3_H
#define __CMT_SPI3_H

//#include "Main.h"

/* ************************************************************************
*  The following need to be modified by user
*  ************************************************************************ */
#define cmt_spi3_csb_out()      (P12F = OUTPUT)//set(P12F,OUTPUT)
#define cmt_spi3_fcsb_out()     (P13F = OUTPUT)//set(P13F,OUTPUT)
#define cmt_spi3_sclk_out()     (P10F = OUTPUT)//set(P10F,OUTPUT)
#define cmt_spi3_sdio_out()     (P11F = OUTPUT)//set(P11F,OUTPUT)
#define cmt_spi3_sdio_in()      (P11F = INPUT)//set(P11F,INPUT)

#define cmt_spi3_csb_1()       (P12=1)//set(P12,GPIO_PIN_0)
#define cmt_spi3_csb_0()       (P12=0)//clr(P12,GPIO_PIN_0)
#define cmt_spi3_fcsb_1()      (P13=1)//set(P13,GPIO_PIN_0)
#define cmt_spi3_fcsb_0()      (P13=0)//clr(P13,GPIO_PIN_0)
#define cmt_spi3_sclk_1()      (P10=1)//set(P10,GPIO_PIN_0)
#define cmt_spi3_sclk_0()      (P10=0)//clr(P10,GPIO_PIN_0)
#define cmt_spi3_sdio_1()      (P11=1)//set(P11,GPIO_PIN_0)
#define cmt_spi3_sdio_0()      (P11=0)//clr(P11,GPIO_PIN_0)
#define cmt_spi3_sdio_read()   (P11)//tst(P11,GPIO_PIN_0)
/* ************************************************************************ */


void cmt_spi3_delay(void);
//void cmt_spi3_delay_us(void);

void cmt_spi3_init(void);

void cmt_spi3_send(u8 data8);
u8 cmt_spi3_recv(void);

void cmt_spi3_write(u8 addr, u8 dat);
void cmt_spi3_read(u8 addr, u8* p_dat);

void cmt_spi3_write_fifo(u8* p_buf, u16 len);
void cmt_spi3_read_fifo(u8* p_buf, u16 len);

#endif
