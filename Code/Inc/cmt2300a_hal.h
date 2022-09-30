
#ifndef __CMT2300A_HAL_H__
#define __CMT2300A_HAL_H__

/* ************************************************************************
*  The following need to be modified by user
*  ************************************************************************ */
//#define CMT2300A_SetGpio1In()           GPIOE_OUT(RF_CSB_PIN)
//#define CMT2300A_SetGpio2In()           GPIOA_FLOAT_INPUT(RF_IRQ_PIN)
#define CMT2300A_SetGpio3In()             (P32F = INPUT)//set(P32F,INPUT)    //GPIOA_OPENPD_INPUT(RF_IRQ_PIN)
     
//#define CMT2300A_ReadGpio1()            tst(P_IO_PortA_Data,RF_CSB_PIN)	
#define CMT2300A_ReadGpio2()              P32 //  tst(P_IO_PortA_Data,RF_IRQ_PIN)	
//#define CMT2300A_ReadGpio3()            GPIOE_OUT(RF_CSB_PIN)
//#define CMT2300A_DelayMs(ms)            system_delay_ms(ms)
//#define CMT2300A_DelayUs(us)            system_delay_us(us)
//#define CMT2300A_GetTickCount()         g_nSysTickCount
/* ************************************************************************ */

void CMT2300A_InitGpio(void);

u8 CMT2300A_ReadReg(u8 addr);
void CMT2300A_WriteReg(u8 addr, u8 dat);

void CMT2300A_ReadFifo(u8 buf[], u16 len);
void CMT2300A_WriteFifo(u8 *buf, u16 len);

#endif
