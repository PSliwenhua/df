#include "Main.h"

void cmt_spi3_delay(void)
{
    u8 n = 7;
    while(n--);
}

//void cmt_spi3_delay_us(void)
//{
//    u8 n = 8;
//    while(n--);
//}

void cmt_spi3_init(void)
{
    cmt_spi3_csb_1();
    cmt_spi3_csb_out();
    cmt_spi3_csb_1();   /* CSB has an internal pull-up resistor */
    
    cmt_spi3_sclk_0();
    cmt_spi3_sclk_out();
    cmt_spi3_sclk_0();   /* SCLK has an internal pull-down resistor */
    
    cmt_spi3_sdio_1();
    cmt_spi3_sdio_out();
    cmt_spi3_sdio_1();
    
    cmt_spi3_fcsb_1();
    cmt_spi3_fcsb_out();
    cmt_spi3_fcsb_1();  /* FCSB has an internal pull-up resistor */

    cmt_spi3_delay();
}

void cmt_spi3_send(u8 data8)
{
    u8 i;
    for(i=0; i<8; i++)
    {
        cmt_spi3_sclk_0();
        
        /* Send byte on the rising edge of SCLK */
        if(data8 & 0x80)
            cmt_spi3_sdio_1();
        else 
		    cmt_spi3_sdio_0();
          
//        cmt_spi3_delay();
        Delay_us(1);
        data8 <<= 1;
        cmt_spi3_sclk_1();
//        cmt_spi3_delay();
        Delay_us(1);
    }
}

u8 cmt_spi3_recv(void)
{
    u8 i;
    u8 data8 = 0xFF;

    for(i=0; i<8; i++)
    {
        cmt_spi3_sclk_0();
//        cmt_spi3_delay();
     //   Delay_us(1);
        _nop_();_nop_();_nop_();_nop_();_nop_();
        data8 <<= 1;

        cmt_spi3_sclk_1();

        /* Read byte on the rising edge of SCLK */
        if(cmt_spi3_sdio_read())
            data8 |= 0x01;
        else
            data8 &= ~0x01;
    //    Delay_us(1);
        _nop_();_nop_(); _nop_();_nop_();_nop_();
//        cmt_spi3_delay();
    }

    return data8;
}

void cmt_spi3_write(u8 addr, u8 dat)
{
    cmt_spi3_sdio_1();
    cmt_spi3_sdio_out();

//    cmt_spi3_sclk_0();
//    cmt_spi3_sclk_out();
    cmt_spi3_sclk_0(); 

//    cmt_spi3_fcsb_1();
//    cmt_spi3_fcsb_out();
    cmt_spi3_fcsb_1();

    cmt_spi3_csb_0();

    /* > 0.5 SCLK cycle */
//    cmt_spi3_delay();
//    cmt_spi3_delay();

    /* r/w = 0 */
    cmt_spi3_send(addr&0x7F);

    cmt_spi3_send(dat);

    cmt_spi3_sclk_0();

    /* > 0.5 SCLK cycle */
//    cmt_spi3_delay();
//    cmt_spi3_delay();

    cmt_spi3_csb_1();
    
    cmt_spi3_sdio_1();
    cmt_spi3_sdio_in();
    
    cmt_spi3_fcsb_1();    
}

void cmt_spi3_read(u8 addr, u8* p_dat)
{
    cmt_spi3_sdio_1();
    cmt_spi3_sdio_out();

//    cmt_spi3_sclk_0();
//    cmt_spi3_sclk_out();
    cmt_spi3_sclk_0(); 

//    cmt_spi3_fcsb_1();
//    cmt_spi3_fcsb_out();
    cmt_spi3_fcsb_1();

    cmt_spi3_csb_0();

    /* > 0.5 SCLK cycle */
//    cmt_spi3_delay();
//    cmt_spi3_delay();

    /* r/w = 1 */
    cmt_spi3_send(addr|0x80);

    /* Must set SDIO to input before the falling edge of SCLK */
    cmt_spi3_sdio_in();
    
    *p_dat = cmt_spi3_recv();

    cmt_spi3_sclk_0();

    /* > 0.5 SCLK cycle */
//    cmt_spi3_delay();
//    cmt_spi3_delay();
    
    cmt_spi3_csb_1();
    
    cmt_spi3_sdio_1();
    cmt_spi3_sdio_in();
    
    cmt_spi3_fcsb_1();
}

void cmt_spi3_write_fifo(u8* p_buf, u16 len)
{
    u16 i;
    
//    cmt_spi3_fcsb_1();
//    cmt_spi3_fcsb_out();
    cmt_spi3_fcsb_1();

//    cmt_spi3_csb_1();
//    cmt_spi3_csb_out();
    cmt_spi3_csb_1();

    cmt_spi3_sclk_0();
    cmt_spi3_sclk_out();
    cmt_spi3_sclk_0();

    cmt_spi3_sdio_out();
    
   
    for(i=0; i<len; i++)
    {
        cmt_spi3_fcsb_0();

        /* > 1 SCLK cycle */
//        cmt_spi3_delay();
//        cmt_spi3_delay();

        cmt_spi3_send(p_buf[i]);
        cmt_spi3_sdio_0();
        cmt_spi3_sclk_0();
        /* > 2 us */
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();

        cmt_spi3_fcsb_1();
        
       // if(i == 0)
       //    //GCC_DELAY(5);/* 这个参数要调整 */  
       //    //Delay_50us(1);
       //    Delay_us(10);
       // else if(i == 1)
       //     //GCC_DELAY(350);//等待接收机配置有效载荷数据时间
       //    //  Delay_50us(1);
       //      Delay_us(50);
       // else
       //     //GCC_DELAY(130);/* 这个参数要调整 */
       //     // Delay_50us(1);
       //      Delay_us(20);
        
        /* > 4 us */
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();
    }
       
    cmt_spi3_sdio_in();   
    cmt_spi3_fcsb_1();
}

void cmt_spi3_read_fifo(u8* p_buf, u16 len)
{
    u16 i;

    cmt_spi3_fcsb_1();
//    cmt_spi3_fcsb_out();
//    cmt_spi3_fcsb_1();

    cmt_spi3_csb_1();
//    cmt_spi3_csb_out();
//    cmt_spi3_csb_1();

    cmt_spi3_sclk_0();
//    cmt_spi3_sclk_out();
//    cmt_spi3_sclk_0();

    cmt_spi3_sdio_in();

    for(i=0; i<len; i++)
    {
        cmt_spi3_fcsb_0();

        /* > 1 SCLK cycle */
//        cmt_spi3_delay();
//        cmt_spi3_delay();
        cmt_spi3_sdio_in();
        p_buf[i] = cmt_spi3_recv();
        cmt_spi3_sdio_out();
        cmt_spi3_sdio_0();
        cmt_spi3_sclk_0();

        /* > 2 us */
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();

        cmt_spi3_fcsb_1();

        /* > 4 us */
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();
//        cmt_spi3_delay_us();
    }

    cmt_spi3_sdio_in();
    cmt_spi3_sdio_0();
    cmt_spi3_fcsb_1();
}
