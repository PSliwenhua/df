#ifndef __CA51F4_H__
#define __CA51F4_H__

sfr P0              = 0x80;
sfr SP              = 0x81;
sfr DP0L            = 0x82;
sfr DP0H            = 0x83;
sfr DP1L            = 0x84;
sfr DP1H            = 0x85;
sfr PWCON           = 0x86;
sfr PCON            = 0x87;
sfr TCON            = 0x88;
sfr TMOD            = 0x89;
sfr TL0             = 0x8a;
sfr TL1             = 0x8b;
sfr TH0             = 0x8c;
sfr TH1             = 0x8d;
sfr IT1CON          = 0x8e;
sfr IT0CON          = 0x8f;

sfr P1              = 0x90;

sfr SCON           = 0x9a;
sfr SBUF           = 0x9b;
sfr SRELL          = 0x9c;
sfr SRELH          = 0x9d;


sfr P2              = 0xa0;

sfr IE              = 0xa8;
sfr WDCON           = 0xaa;
sfr WDFLG           = 0xab;
sfr WDVTHL          = 0xac;
sfr WDVTHH          = 0xad;

sfr P3              = 0xb0;
sfr I2CCON          = 0xb1;
sfr I2CADR          = 0xb2;
sfr I2CADM          = 0xb3;
sfr I2CCR           = 0xb4;
sfr I2CDAT          = 0xb5;
sfr I2CSTA          = 0xb6;
sfr I2CFLG          = 0xb7;
sfr IP              = 0xb8;
sfr ADCON           = 0xb9;
sfr ADCFGL          = 0xba;
sfr ADCFGH          = 0xbb;
sfr ADCDL           = 0xbc;
sfr ADCDH           = 0xbd;

sfr P4              = 0xc0;
sfr TKCON           = 0xc1;
sfr TKCFG           = 0xc2;
sfr TKMTS           = 0xc3;
sfr TKCHS           = 0xc4;
sfr ATKML           = 0xc5;
sfr ATKMH           = 0xc6;
sfr TKIF            = 0xc7;
sfr T2CON           = 0xc8;
sfr T2MOD           = 0xc9;
sfr T2CL            = 0xca;
sfr T2CH            = 0xcb;
sfr TL2             = 0xcc;
sfr TH2             = 0xcd;
sfr TKMSL           = 0xce;
sfr TKMSH           = 0xcf;

sfr PSW             = 0xd0;
sfr PWMDIVH         = 0xd1;
sfr PWMDUTL         = 0xd2;
sfr PWMDUTH         = 0xd3;
sfr PWMIF           = 0xd4;

sfr P5              = 0xd8;
sfr PWMEN           = 0xda;
sfr PWMCMX          = 0xdc;
sfr PWMCON          = 0xdd;
sfr PWMCFG          = 0xde;
sfr PWMDIVL         = 0xdf;

sfr ACC             = 0xe0;
sfr LCCON           = 0xe1;
sfr LCCFG           = 0xe2;
sfr LCDAT           = 0xe3;
sfr LCDIVL          = 0xe4;
sfr LCDIVH          = 0xe5;

sfr EXIE            = 0xe8;
sfr RTCSS           = 0xe9;
sfr RTAS            = 0xea;
sfr RTAM            = 0xeb;
sfr RTAH            = 0xec;
sfr RTMSS           = 0xed;
sfr RTCIF           = 0xee;
sfr LVDCON          = 0xef;

sfr B               = 0xf0;
sfr RTCON           = 0xf1;
sfr RTCS            = 0xf2;
sfr RTCM            = 0xf3;
sfr RTCH            = 0xf4;
sfr RTCDL           = 0xf5;
sfr RTCDH           = 0xf6;
sfr INDEX           = 0xf7;
sfr EXIP            = 0xf8;
sfr EPIE            = 0xf9;
sfr EPIF            = 0xfa;
sfr EPCON           = 0xfb;
sfr IDLSTL          = 0xfc;
sfr IDLSTH          = 0xfd;
sfr STPSTL          = 0xfe;
sfr STPSTH          = 0xff;


/*  BIT Register  */
/*	PSW	*/
sbit CY   		= 0xD7;
sbit AC   		= 0xD6;
sbit F0   		= 0xD5;
sbit RS1  		= 0xD4;
sbit RS0  		= 0xD3;
sbit OV   		= 0xD2;
sbit DPS   		= 0xD1;
sbit P    		= 0xD0;
		  		
/*	TCON	*/
sbit TF1  		= 0x8F;
sbit TR1  		= 0x8E;
sbit TF0  		= 0x8D;
sbit TR0  		= 0x8C;
sbit IE1  		= 0x8B;
sbit IT1  		= 0x8A;
sbit IE0  		= 0x89;
sbit IT0  		= 0x88;
/*	IE	*/
sbit EA   		= 0xAF;
sbit ES1  		= 0xAE;
sbit ET2  		= 0xAD;
sbit ES0	   	= 0xAC;
sbit ET1  		= 0xAB;
sbit EX1  		= 0xAA;
sbit ET0  		= 0xA9;
sbit EX0  		= 0xA8;

/*	IP	*/ 
sbit PS1  		= 0xBE;
sbit PT2  		= 0xBD;
sbit PS0   		= 0xBC;
sbit PT1  		= 0xBB;
sbit PX1  		= 0xBA;
sbit PT0  		= 0xB9;
sbit PX0  		= 0xB8;
/*	T2CON	*/
sbit TF2   		= 0xCF;
sbit TR2  		= 0xCE;
sbit T2R1  		= 0xCD;
sbit T2R0  		= 0xCC;
sbit T2IE       = 0xCB;
sbit UCKS  		= 0xCA;
sbit T2P1  		= 0xC9;
sbit T2P0  		= 0xC8;
/*	EXIE	*/
sbit INT9EN   		= 0xEF;
sbit INT8EN  		= 0xEE;
sbit INT7EN  		= 0xED;
sbit INT6EN	   		= 0xEC;
sbit INT5EN  		= 0xEB;
sbit INT4EN  		= 0xEA;
sbit INT3EN  		= 0xE9;
sbit INT2EN  		= 0xE8;
/*	P0	*/
sbit P00		= P0^0;
sbit P01		= P0^1;
sbit P02		= P0^2;
sbit P03		= P0^3;
sbit P04		= P0^4;
sbit P05		= P0^5;
sbit P06		= P0^6;
sbit P07		= P0^7;
/*	P1	*/     	
sbit P10		= P1^0;
sbit P11		= P1^1;
sbit P12		= P1^2;
sbit P13		= P1^3;
sbit P14		= P1^4;
sbit P15		= P1^5;
sbit P16		= P1^6;
sbit P17		= P1^7;
/*	P2	*/        	
sbit P20		= P2^0;
sbit P21		= P2^1;
sbit P22		= P2^2;
sbit P23		= P2^3;
sbit P24		= P2^4;
sbit P25		= P2^5;
sbit P26		= P2^6;
sbit P27		= P2^7;

/*	P3	*/
sbit P30		= P3^0;
sbit P31		= P3^1;
sbit P32		= P3^2;
sbit P33		= P3^3;
sbit P34		= P3^4;
sbit P35		= P3^5;
sbit P36		= P3^6;
sbit P37		= P3^7;	

/*	P4	*/
sbit P40		= P4^0;
sbit P41		= P4^1;
sbit P42		= P4^2;
sbit P43		= P4^3;
sbit P44		= P4^4;
sbit P45		= P4^5;
sbit P46		= P4^6;
sbit P47		= P4^7;		

/*	P5	*/
sbit P50		= P5^0;
sbit P51		= P5^1;
sbit P52		= P5^2;
sbit P53		= P5^3;
sbit P54		= P5^4;
sbit P55		= P5^5;
#endif  //__CA51F4_H__
