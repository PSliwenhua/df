#ifndef __RADIO_H__
#define __RADIO_H__

/* RF state machine */
typedef enum {
    RF_STATE_IDLE = 0,
    RF_STATE_RX_START,
    RF_STATE_RX_WAIT,
    RF_STATE_RX_DONE,
    RF_STATE_RX_TIMEOUT,
    RF_STATE_TX_START,
    RF_STATE_TX_WAIT,
    RF_STATE_TX_DONE,
    RF_STATE_TX_TIMEOUT,
    RF_STATE_ERROR,
} EnumRFStatus;

/* RF process function results */
typedef enum {
    RF_IDLE = 0,
    RF_BUSY,
    RF_RX_DONE,
    RF_RX_TIMEOUT,
    RF_TX_DONE,
    RF_TX_TIMEOUT,
    RF_ERROR,
} EnumRFResult;

//#define ENABLE_ANTENNA_SWITCH

#define FIFOThreshold   14  //不能设置小于最小包数据长度

#define D_SetRSSI  (-98)//(-105)
//#define D_RSSI 1

void RF_ASKInit();


void CMT2300A_Collision_Detec(void);
void F_CMT2300A_ReadSendData();
void CMT2300A_ReadRegConfig();
void F_CMT2300A_GolongTx();
void F_CMT2300A_Golong20dbm_10dbmTx();
void Radio_GoRx_VariableLen();
void Radio_GoTx_VariableLen();
void RF_Init(void);
void RF_Config(void);
//EnumRFResult RF_Process(void);
void F_ReadOption();


#endif
