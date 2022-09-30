#include "Main.h"

void CMT2300A_Collision_Detec(void)
{
	u8 dat = 0x00;
    cmt_spi3_read(CMT2300A_CUS_SYS10, &dat);
    dat |= CMT2300A_MASK_COL_DET_EN;
    CMT2300A_WriteReg(CMT2300A_CUS_SYS10, CMT2300A_MASK_COL_DET_EN);
}

void F_CMT2300A_ReadSendData()
{
	u8 tmp[32];
	CMT2300A_EnableReadFifo();
	CMT2300A_ReadFifo(tmp, 32);
	return;
}
void CMT2300A_ReadRegConfig()
{
	u8 i;
	//u8 tmp[0x60];
	for(i=0; i<=0x60; i++)
		//tmp[i] = CMT2300A_ReadReg(CMT2300A_CMT_BANK_ADDR+i);
		CMT2300A_ReadReg(CMT2300A_CMT_BANK_ADDR+i);
	return;
}

void F_CMT2300A_GolongTx()
{	
	Radio_GoTx_VariableLen();
	Count64Hz = 0;
	CMT2300A_GoTx();
	while(Count64Hz < 3*64)
		Delay_ms(1);//GCC_CLRWDT();
	CMT2300A_ClearInterruptFlags();
    Count64Hz = 0;
}

void F_CMT2300A_Golong20dbm_10dbmTx()
{	
	/* u8 i;
	Radio_GoTx_VariableLen();
	for(i=0;i<30;i++)
	{
		CMT2300A_WriteReg(0x5C, T_Power[i][0]);
		CMT2300A_WriteReg(0x5D, T_Power[i][1]);
		Count64Hz = 0;
		CMT2300A_GoTx();
		while(Count64Hz < 3*64)
			Delay_ms(1);//GCC_CLRWDT();
		CMT2300A_ClearInterruptFlags();
		Count64Hz = 0;
	} */
}

void Radio_GoRx_VariableLen()
{
	CMT2300A_GoStby();
	CMT2300A_ClearRxFifo();
	//CMT2300A_ClearInterruptFlags();
	CMT2300A_WriteReg(CMT2300A_CUS_INT_CLR2,CMT2300A_MASK_PKT_DONE_CLR);
	CMT2300A_EnableReadFifo();
	CMT2300A_WriteReg(CMT2300A_CUS_INT2_CTL,CMT2300A_INT_SEL_PKT_OK);//数据包发送完成 中断映射
//	CMT2300A_WriteReg(CMT2300A_CUS_INT2_CTL,CMT2300A_INT_SEL_RX_FIFO_NMTY);//RX_FIFO非空中断 映射
//	CMT2300A_WriteReg(CMT2300A_CUS_INT2_CTL,CMT2300A_INT_SEL_RX_FIFO_WBYTE);//RX_FIFO非空中断 映射 //字节中断
	CMT2300A_EnableInterrupt(CMT2300A_MASK_PKT_DONE_EN);
	CMT2300A_GoRx();
}

void Radio_GoTx_VariableLen()
{
	CMT2300A_GoStby();
	CMT2300A_ClearTxFifo();
	//CMT2300A_ClearInterruptFlags();
	CMT2300A_WriteReg(CMT2300A_CUS_INT_CLR1, CMT2300A_MASK_TX_DONE_CLR);
	CMT2300A_EnableWriteFifo();
	CMT2300A_WriteReg(CMT2300A_CUS_INT2_CTL,CMT2300A_INT_SEL_TX_DONE);
//	CMT2300A_WriteReg(CMT2300A_CUS_INT2_CTL,CMT2300A_INT_SEL_TX_FIFO_NMTY);//TX_FIFO非空中断 映射
	CMT2300A_EnableInterrupt(CMT2300A_MASK_TX_DONE_EN);
//	CMT2300A_SetPayloadLength(FIFO_Depth);
}

void RF_Init(void)
{
    u8 tmp;
    CMT2300A_InitGpio();
    CMT2300A_Init();
    Delay_ms(2);
    /* Config registers */
    CMT2300A_ConfigRegBank(CMT2300A_CMT_BANK_ADDR       , &g_cmt2300aCmtBank[R_RfFreq][0]       , CMT2300A_CMT_BANK_SIZE       );
    CMT2300A_ConfigRegBank(CMT2300A_SYSTEM_BANK_ADDR    , &g_cmt2300aSystemBank[R_RfFreq][0]    , CMT2300A_SYSTEM_BANK_SIZE    );
    CMT2300A_ConfigRegBank(CMT2300A_FREQUENCY_BANK_ADDR , &g_cmt2300aFrequencyBank[R_RfFreq][0] , CMT2300A_FREQUENCY_BANK_SIZE );
    CMT2300A_ConfigRegBank(CMT2300A_DATA_RATE_BANK_ADDR , &g_cmt2300aDataRateBank[R_RfFreq][0]  , CMT2300A_DATA_RATE_BANK_SIZE );
    CMT2300A_ConfigRegBank(CMT2300A_BASEBAND_BANK_ADDR  , &g_cmt2300aBasebandBank[R_RfFreq][0]  , CMT2300A_BASEBAND_BANK_SIZE  );
    CMT2300A_ConfigRegBank(CMT2300A_TX_BANK_ADDR        , &g_cmt2300aTxBank[R_RfFreq][0]        , CMT2300A_TX_BANK_SIZE        );
    // xosc_aac_code[2:0] = 2
    tmp = (~0x07) & CMT2300A_ReadReg(CMT2300A_CUS_CMT10);
    CMT2300A_WriteReg(CMT2300A_CUS_CMT10, tmp|0x02);
    RF_Config();
}

void RF_Config(void)
{
//#ifdef ENABLE_ANTENNA_SWITCH
    /* If you enable antenna switch, GPIO1/GPIO2 will output RX_ACTIVE/TX_ACTIVE,
       and it can't output INT1/INT2 via GPIO1/GPIO2 */
//    CMT2300A_EnableAntennaSwitch(0);
    
//#else
    /* Config GPIOs */
        CMT2300A_ConfigGpio(
			CMT2300A_GPIO1_SEL_DCLK | /* INT1 > GPIO1 */
			CMT2300A_GPIO2_SEL_DCLK | /* INT2 > GPIO2 */
			CMT2300A_GPIO3_SEL_INT2
		);
    
      /* Config interrupt */
      /* CMT2300A_ConfigInterrupt(
        CMT2300A_INT_SEL_TX_DONE, // Config INT1 
        CMT2300A_INT_SEL_PKT_OK   // Config INT2 
      );
      CMT2300A_WriteReg(CMT2300A_CUS_INT2_CTL,CMT2300A_INT_SEL_PKT_OK);
	  CMT2300A_WriteReg(CMT2300A_CUS_INT2_CTL,CMT2300A_INT_SEL_TX_DONE); */
//#endif

    /* Enable interrupt */
    /*   CMT2300A_EnableInterrupt(
        CMT2300A_MASK_TX_DONE_EN  |
		CMT2300A_MASK_PREAM_OK_EN |
		CMT2300A_MASK_SYNC_OK_EN  |
		CMT2300A_MASK_NODE_OK_EN  |
		CMT2300A_MASK_CRC_OK_EN   |
        CMT2300A_MASK_PKT_DONE_EN
        ); */
    
    /* Disable low frequency OSC calibration */
    CMT2300A_EnableLfosc(FALSE);
    
    /* Use a single 64-byte FIFO for either Tx or Rx */
    CMT2300A_EnableFifoMerge(FALSE);
    
  //  CMT2300A_SetFifoThreshold(FIFOThreshold);
    CMT2300A_SetFifoThreshold(31);
    
    /* This is optional, only needed when using Rx fast frequency hopping */
    /* See AN142 and AN197 for details */
//  CMT2300A_SetAfcOvfTh(12);  
//	CMT2300A_SetFrequencyStep(80); 

    CMT2300A_SetPayloadLength(FIFO_Depth); 
    /* Go to sleep for configuration to take effect */
    CMT2300A_GoSleep();
}


