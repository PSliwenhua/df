#ifndef __LCD__H__
#define __LCD__H__
#include"main.h"

//========================================
enum{
    Shuzi_0,Shuzi_1,Shuzi_2,Shuzi_3,Shuzi_4,Shuzi_5,Shuzi_6,Shuzi_7,Shuzi_8,Shuzi_9,
    Shuzi_A,Shuzi_b,Shuzi_C,Shuzi_d,Shuzi_E,Shuzi_F,Shuzi_H,Shuzi_I,Shuzi_L,Shuzi_N,
    Shuzi_O,Shuzi_P,Shuzi_U,Shuzi_o1,Shuzi_o2,
    Shuzi_NEGATIVE,Shuzi_NULL,
	Shuzi_T,Shuzi_S,Shuzi_r,Shuzi_V,Shuzi_G,
    Shuzi_Max
};
extern code u8 T_Shuzi[ Shuzi_Max ];
/* static code u8 T_Shuzi[ Shuzi_Max ] =
{ 
  0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,//0 to 9
  0x77,0x7c,0x39,0x5E,0x79,0x71,0x76,0x06,0x38,0x37,//A b C d E F H I L N
  0x3f,0x73,0x3e,0x63,0x5c,//O,P,U 上o 下o 
  0x40,0x00,//-  NULL
  0x78,0x6D,0x50,0x7E,0x3D//T S r U
}; */
#define Shuzi_INVALID Shuzi_NEGATIVE//无效- 负号-
#define Shuzi_NEG     Shuzi_NEGATIVE//无效- 负号-

enum{
   _ONE			, // 个位  
   _DEC	   		, // 十位
};
/*----------------------------------------------------------------------------
-----------------------------------------------------------------------------*/

#define D_LCDLEN 45
//MyDef xdata LCDBYTE LCD_DATA[D_LCDLEN];
#define D_COM_Length	0x40	/* 4COM */
#define COM0	        0x01  //点亮位      
#define COM1	        0x02 
#define COM2	        0x04 
#define COM3	        0x08 
#define COM4	        0x10 
#define COM5	        0x20 
#define COM6	        0x40 
#define COM7	        0x80 
#define	LCD_Baseaddr	0x0400u//基地址  
#define SEG0	        0x00u  //地址         
#define SEG1	        0x01u       
#define SEG2	        0x02u       
#define SEG3	        0x03u       
#define SEG4	        0x04u      
#define SEG5	        0x05u      
#define SEG6	        0x06u      
#define SEG7	        0x07u     
#define SEG8	        0x08u     
#define SEG9	        0x09u                  
#define SEG10	        0x0Au                 
#define SEG11	        0x0Bu                  
#define SEG12	        0x0Cu                  
#define SEG13	        0x0Du                  
#define SEG14	        0x0Eu                    
#define SEG15	        0x0Fu                  
#define SEG16	        0x10u                     
#define SEG17	        0x11u                     
#define SEG18	        0x12u                       
#define SEG19	        0x13u                    
#define SEG20	        0x14u                     
#define SEG21	        0x15u                      
#define SEG22	        0x16u   
#define SEG23	        0x17u                    
#define SEG24	        0x18u                   
#define SEG25	        0x19u                    
#define SEG26	        0x1Au                     
#define SEG27	        0x1Bu                    
#define SEG28	        0x1Cu                      
#define SEG29	        0x1Du                      
#define SEG30	        0x1Eu                      
#define SEG31	        0x1Fu  
#define SEG32	        0x20u
#define SEG33	        0x21u
#define SEG34	        0x22u
#define SEG35	        0x23u
#define SEG36	        0x24u
#define SEG37	        0x25u
#define SEG38	        0x26u
#define SEG39	        0x27u
#define SEG40	        0x28u
#define SEG41	        0x29u
#define SEG42	        0x2Au
#define SEG43	        0x2Bu
#define SEG44	        0x2Cu
#define SEG45	        0x2Du

enum {
	T_Number1_A1,B1,C1,D1,E1,F1,G1,/* 1 */
	T_Number2_A1,B2,C2,D2,E2,F2,G2,/* 2 */
	T_Number3_A1,B3,C3,D3,E3,F3,G3,/* 3 */
	T_Number4_A1,B4,C4,D4,E4,F4,G4,/* 4 */
}; 

//static code u8 T_A_SegDispEn[2][7] =
//{
//    {COM0,COM1,COM3,COM3,COM2,COM1,COM2,},/* B */
//    {COM3,COM2,COM1,COM0,COM1,COM3,COM2,},/* A */
//};
//static code u8 T_A_SegDotAddr[2][28] =
//{   
//    {   SEG4, SEG5 ,SEG5 ,SEG4 ,SEG4 ,SEG4 ,SEG5 , /* T_Number_5 */   
//        SEG6, SEG7 ,SEG7 ,SEG6 ,SEG6 ,SEG6 ,SEG7 , /* T_Number_4 */
//        SEG8, SEG9 ,SEG9 ,SEG8 ,SEG8 ,SEG8 ,SEG9 , /* T_Number_3 */
//        SEG10,SEG11,SEG11,SEG10,SEG10,SEG10,SEG11, /* T_Number_2 */
//    },
//    {   SEG12,SEG12,SEG12,SEG12,SEG13,SEG13,SEG13, /* T_Number_1 */
//        SEG10,SEG10,SEG10,SEG10,SEG11,SEG11,SEG11, /* T_Number_2 */
//        SEG8 ,SEG8 ,SEG8 ,SEG8 ,SEG9 ,SEG9 ,SEG9 , /* T_Number_3 */
//        SEG6 ,SEG6 ,SEG6 ,SEG6 ,SEG7 ,SEG7 ,SEG7 , /* T_Number_4 */
//    },
//};                     
//
//static code u8 T_A_XdotDispEn[2][11] =
//{
//    {COM0,COM0,COM1,COM2,COM3,COM3,COM2,COM0,COM0,COM1,COM0,},
//    {COM0,COM0,COM1,COM2,COM3,COM3,COM2,COM0,COM0,COM1,COM0,},
//};
//static code u8 T_A_XdotAddr[2][11] =
//{
//    {SEG5 ,SEG15,SEG15,SEG15,SEG15,SEG2 ,SEG2 ,SEG11,SEG14,SEG14,SEG9 ,}, 
//    {SEG13,SEG1 ,SEG1 ,SEG1 ,SEG1 ,SEG14,SEG14,SEG3 ,SEG2 ,SEG2 ,SEG7 ,},
//};    

enum {
 // /* COM0 + SEG13   */ Icon_S1    , /* RF连接图标 */ 
 // /* COM0 + SEG1  */ Icon_S19   , /* RF 信号格1 */  
 // /* COM1 + SEG1  */ Icon_S18   , /* RF 信号格2 */
 // /* COM2 + SEG1  */ Icon_S17   , /* RF 信号格3 */
 // /* COM3 + SEG1  */ Icon_S16   , /* RF 信号格4 */
 // /* COM3 + SEG14   */ Icon_S2    , /* 后退 */
 // /* COM2 + SEG14   */ Icon_S3    , /* 前进 */
 // /* COM0 + SEG3  */ Icon_S11   , /* TEMP */   
 // /* COM0 + SEG2  */ Icon_S12_F , /* F */
 // /* COM1 + SEG2  */ Icon_S13_C , /* C */
 // /* COM0 + SEG7   */ Icon_P2    , /* 小数点 */
//
 // /* COM0 + SEG5  */ Icon_S20   , /* RF连接图标 */
 // /* COM0 + SEG15   */ Icon_S4    , /* RF 信号格1 */
 // /* COM1 + SEG15   */ Icon_S5    , /* RF 信号格2 */
 // /* COM2 + SEG15   */ Icon_S6    , /* RF 信号格3 */
 // /* COM3 + SEG15   */ Icon_S7    , /* RF 信号格4 */
 // /* COM3 + SEG2  */ Icon_S14   , /* 后退 */
 // /* COM2 + SEG2  */ Icon_S15   , /* 前进 */
 // /* COM0 + SEG11   */ Icon_S10   , /* TEMP */   
 // /* COM0 + SEG14   */ Icon_S9    , /* F */
 // /* COM1 + SEG14   */ Icon_S8    , /* C */
 // /* COM0 + SEG9   */ Icon_P1    , /* 小数点 */

    Icon_RF_Connect  ,
    Icon_OnHeating1  ,
    Icon_OnHeating2  ,
    Icon_OnHeating3  ,
    Icon_OnHeating4  ,
    Icon_Stop_Temp         ,
    Icon_Start_Temp         ,
    Icon_Temp_monCF        ,
    Icon_TempF       ,
    Icon_TempC       ,
    Icon_Temp_Dot     ,

    B_Icon_RF_Connect  ,
    B_Icon_OnHeating1  ,
    B_Icon_OnHeating2  ,
    B_Icon_OnHeating3  ,
    B_Icon_OnHeating4  ,
    B_Icon_Dec         ,
    B_Icon_Add         ,
    B_Icon_Temp        ,
    B_Icon_TempF       ,
    B_Icon_TempC       ,
    B_Icon_TempDot     ,
}; 

static code u8 T_A_XdotEnmu[2][11] =
{
    {   Icon_RF_Connect     ,
        Icon_OnHeating1     ,
        Icon_OnHeating2     ,
        Icon_OnHeating3     ,
        Icon_OnHeating4     ,
        Icon_Stop_Temp            ,
        Icon_Start_Temp            ,
        Icon_Temp_monCF     ,
        Icon_TempF          ,
        Icon_TempC          ,
        Icon_Temp_Dot       ,
    },
    {
         B_Icon_RF_Connect  ,
         B_Icon_OnHeating1  ,
         B_Icon_OnHeating2  ,
         B_Icon_OnHeating3  ,
         B_Icon_OnHeating4  ,
         B_Icon_Dec         ,
         B_Icon_Add         ,
         B_Icon_Temp        ,
         B_Icon_TempF       ,
         B_Icon_TempC       ,
         B_Icon_TempDot     ,
    }, 
};      

MyDef u8 LcdDisp;

enum{	
   _D_DN		,  		
   _D_EN		,    
};

MyDef xdata u8 R_Bcd[6];

MyDef xdata UWORD R_LcdFlag;
    #define	B_RefreshSecDot		            R_LcdFlag.FLAG.FLAG0.Bit.bit0  // 1:
    #define	B_RefreshTimeFormat		        R_LcdFlag.FLAG.FLAG0.Bit.bit1  // 1:
    #define	B_RefreshTime		            R_LcdFlag.FLAG.FLAG0.Bit.bit2  // 1:
    #define B_RefreshWifiIcon		        R_LcdFlag.FLAG.FLAG0.Bit.bit3  // 1:
    #define	B_RefreshBatteryIcon	        R_LcdFlag.FLAG.FLAG0.Bit.bit4  // 1:
    #define	B_RefreshPVvalue       	        R_LcdFlag.FLAG.FLAG0.Bit.bit5  // 1:
    #define	B_RefreshHandAutoModeIcon       R_LcdFlag.FLAG.FLAG0.Bit.bit6  // 1:
    #define	B_RefreshOnHeatingIcon          R_LcdFlag.FLAG.FLAG0.Bit.bit7  // 1:


    #define	B_RefreshSetHmi		            R_LcdFlag.FLAG.FLAG1.Bit.bit2  // 1:
    #define	B_RefreshTemp		            R_LcdFlag.FLAG.FLAG1.Bit.bit3  // 1:
/*     #define	      R_LcdFlag.FLAG.FLAG1.Bit.bit3  // 1:
    #define	      R_LcdFlag.FLAG.FLAG1.Bit.bit4  // 1:
    #define	      R_LcdFlag.FLAG.FLAG1.Bit.bit5  // 1:
    #define	      R_LcdFlag.FLAG.FLAG1.Bit.bit6  // 1:
    #define	      R_LcdFlag.FLAG.FLAG1.Bit.bit7  // 1: */


MyDef xdata u8 R_test44;
u8 F_Change5BCD(long num,u8 dec);
void F_DisplayDot(u8 dot,u8 Status);
void F_DisplayShuzi(u8 addr,u8 num);
void F_RefreshWaterFlow();
void F_LcdRefreshSever();

void F_DisplayDotTest(u8 Status);
void F_LcdSetDot(u8 Addr,u8 Data);
void F_PowerOnLcdAllCheak();


//LCCON定义
#define LEN_IRCH			(1<<5)
#define LEN_IRCL			(2<<5)
#define LEN_XOSCL			(4<<5)
#define LCD_TYPE(N)		(N<<1)
#define LCE(N)				(N<<0)

//LCCFG定义
#define DMOD_5ua		(0<<6)
#define DMOD_40ua		(1<<6)
#define DMOD_80ua		(2<<6)
#define DMOD_130ua		(3<<6)

#define BIAS_1_4		(0<<4)
#define BIAS_1_2		(1<<4)
#define BIAS_1_3		(2<<4)

#define LCDRV_LEV(N)		(N) //N=0-7

//LCCAD定义
#define CAD_MOD(N)		(N<<2)	//N=0-3
#define CAD_LTH(N)		(N<<0)	//N=0-3

//LCPMP定义
#define PCKD(N)		(N<<1)	//N=0-7
#define PMPE(N)		(N<<0)	//N=0-1

void LCD_Test(void);
void LCD_init(void);



#endif