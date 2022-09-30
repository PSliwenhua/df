#ifndef __KEY__H__
#define	__KEY__H__

#define GPIO_PIN_0        (0x0001u)  /*!< Pin 0 selected */
#define GPIO_PIN_1        (0x0002u)  /*!< Pin 1 selected */
#define GPIO_PIN_2        (0x0004u)  /*!< Pin 2 selected */
#define GPIO_PIN_3        (0x0008u)  /*!< Pin 3 selected */
#define GPIO_PIN_4        (0x0010u)  /*!< Pin 4 selected */
#define GPIO_PIN_5        (0x0020u)  /*!< Pin 5 selected */
#define GPIO_PIN_6        (0x0040u)  /*!< Pin 6 selected */
#define GPIO_PIN_7        (0x0080u)  /*!< Pin 7 selected */
#define GPIO_PIN_8        (0x0100u)  /*!< Pin 0 selected */
#define GPIO_PIN_9        (0x0200u)  /*!< Pin 1 selected */
#define GPIO_PIN_10       (0x0400u)  /*!< Pin 2 selected */
#define GPIO_PIN_11       (0x0800u)  /*!< Pin 3 selected */
#define GPIO_PIN_12       (0x1000u)  /*!< Pin 4 selected */
#define GPIO_PIN_13       (0x2000u)  /*!< Pin 5 selected */
#define GPIO_PIN_14       (0x4000u)  /*!< Pin 6 selected */
#define GPIO_PIN_15       (0x8000u)  /*!< Pin 7 selected */

//------------------------------------------------------------
//	按键全速扫描 消抖计数
//------------------------------------------------------------
#define KeyDebounceCnt 2
/*------------------------------------------------------------
						BS83B04C按键软件编码
--------------------------------------------------------------
			b7    b6    b5    b4  |   b3    b2    b1    b0
--------------------------------------------------------------
键值定义：	STOP  SUM   SUM   SUM |  KEY3  KEY2  KEY1  KEY0
--------------------------------------------------------------*/
#define D_KEY1_VALUE    		(0x0E)
#define D_KEY2_VALUE    		(0x0D)
#define D_KEY3_VALUE    		(0x0B)
#define D_KEY4_VALUE     		(0x07)
#define D_KEY_NULL     			(0x0F)
#define	D_ONE_KEY_CHLICK		(1<<4)
#define	D_TWO_KEY_CHLICK		(2<<4)
#define	D_THR_KEY_CHLICK		(3<<4)
#define	D_FOR_KEY_CHLICK		(4<<4)
#define	D_NUL_KEY_CHLICK		(0<<4)
#define D_KEY_STOP 				(0X80)
#define	TOUCH_KEY1_VALUE 		(D_KEY_STOP|D_ONE_KEY_CHLICK|D_KEY1_VALUE)/* 0x9E */
#define	TOUCH_KEY2_VALUE 		(D_KEY_STOP|D_ONE_KEY_CHLICK|D_KEY2_VALUE)/* 0x9D */
#define	TOUCH_KEY3_VALUE 		(D_KEY_STOP|D_ONE_KEY_CHLICK|D_KEY3_VALUE)/* 0x9B */
#define	TOUCH_KEY4_VALUE 		(D_KEY_STOP|D_ONE_KEY_CHLICK|D_KEY4_VALUE)/* 0x97 */
#define	TOUCH_KEYUP_VALUE 		(D_KEY_STOP|D_NUL_KEY_CHLICK|D_KEY_NULL  )
#define INC_KEY  				(TOUCH_KEY3_VALUE)	
#define MEN_KEY  				(TOUCH_KEY2_VALUE)	
#define DEC_KEY  				(TOUCH_KEY1_VALUE)	
#define INC_KEY2S		 		(u8)(INC_KEY << 1)
#define MEN_KEY2S				(u8)(MEN_KEY << 1)
#define DEC_KEY2S				(u8)(DEC_KEY << 1)
#define TEST_KEY2S				(u8)(INC_KEY2S|DEC_KEY2S)

#define KEY_NULL	   			0
#define D_KeyTimerOut	 		16//64hz*16=250ms		
#define D_LongKey64Hz	 		64*2//长按2秒(15.625) 		
#define TOUCH_SDA_IO      		P20//tst(P20,GPIO_PIN_0)			
#define TOUCH_SDA_IN      		(P20F = INPUT)//set(P20F,INPUT)			
#define TOUCH_SDA_OUT      		(P20F = OUTPUT)//set(P20F,OUTPUT)	
#define TOUCH_SDA_OUT1      	(P20 = 1)	//set(P20,GPIO_PIN_0)			
#define TOUCH_SDA_OUT0      	(P20 = 0)	//clr(P20,GPIO_PIN_0)	

#define TOUCH_SCL_IN      		(P33F = INPUT)//set(P33F,INPUT)			
#define TOUCH_SCL_OUT      		(P33F = OUTPUT)//set(P33F,OUTPUT)	
#define TOUCH_SCL_OUT1      	(P33 = 1)	//set(P33,GPIO_PIN_0)			
#define TOUCH_SCL_OUT0      	(P33 = 0)	//clr(P33,GPIO_PIN_0)	
typedef struct 
{
	UBYTE Flag;
	u8 Last;
	u8 Now;
	u8 Down; 	
	u8 Up;	
	u8 ValueBuf;
	u8 Value;
	u8 SetValue;
	u16 KeepCnt;
	u8 Speed;
	u8 DebounceCnt;
	u8 NowBuf;
	u8 TimerOut;
	u8 Pulse;
}T_Key;
MyDef xdata T_Key volatile Key;

#define	B_Key64HzScan		Key.Flag.Bit.bit0		 
#define	B_Key64HzStep		Key.Flag.Bit.bit1		 
#define	B_KeyChange			Key.Flag.Bit.bit2		 
#define	B_IncDecKeyHold		Key.Flag.Bit.bit3		 
#define B_INCFLAG			Key.Flag.Bit.bit4		 
#define B_DECFLAG 			Key.Flag.Bit.bit5	
#define B_Starthead			Key.Flag.Bit.bit6	
	 
void F_KeyRstFactory();
void F_KeyValueGetScan();
void F_KeyValueCheak();
void F_KeySever();
void F_KeySetMenuSever();


#endif
