#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_

#define NULL	((void *)0)
    
#define FALSE	0
#define TRUE	1

#define _SUCC	0
#define _FAIL	1

enum{		
   IO_ON,	 	
   IO_OFF,	    
};
#define _OUTPUT 0
#define _IN     1

#define _ENABLE     1
#define _DISABLE    0

//	数据格式及错误返回代码
#define INVALID_DATA_8			((BYTE)0xff)
#define INVALID_DATA_16			((WORD)0xffffu)
#define INVALID_DATA_32			((D32WORD)0x00ffffffu)		

#define NULL_DATA_8				((BYTE)0x7f)
#define NULL_DATA_16			((WORD)0x7fffu)
#define NULL_DATA_32			((D32WORD)0x007fffffu)	

// Seletc Memory Mode
#if 1
    // C51 Core MCU
	/* 低地址存高位数据，高地址存低位数据 */
	#define BIG_ENDIAN
	#define BIG_ENDIAN_BIT_0         (0x8000u)  /* 必须如此、大端 */
	#define BIG_ENDIAN_BIT_1         (0x4000u)  
	#define BIG_ENDIAN_BIT_2         (0x2000u)  
	#define BIG_ENDIAN_BIT_3         (0x1000u)  
	#define BIG_ENDIAN_BIT_4         (0x0800u)  
	#define BIG_ENDIAN_BIT_5         (0x0400u)  
	#define BIG_ENDIAN_BIT_6         (0x0200u)  
	#define BIG_ENDIAN_BIT_7         (0x0100u)  
	#define BIG_ENDIAN_BIT_8         (0x0080u)  
	#define BIG_ENDIAN_BIT_9         (0x0040u)  
	#define BIG_ENDIAN_BIT_10        (0x0020u)  
	#define BIG_ENDIAN_BIT_11        (0x0010u)  
	#define BIG_ENDIAN_BIT_12        (0x0008u)  
	#define BIG_ENDIAN_BIT_13        (0x0004u)  
	#define BIG_ENDIAN_BIT_14        (0x0002u)  
	#define BIG_ENDIAN_BIT_15        (0x0001u)  	
#else
	/* 低地址存低位数据，高地址存高位数据 */
	#define LITTLE_ENDIAN   
	#define LITTLE_ENDIAN_BIT_0         (0x0001u)  /* 必须如此、大端 */
	#define LITTLE_ENDIAN_BIT_1         (0x0002u)  
	#define LITTLE_ENDIAN_BIT_2         (0x0004u)  
	#define LITTLE_ENDIAN_BIT_3         (0x0008u)  
	#define LITTLE_ENDIAN_BIT_4         (0x0010u)  
	#define LITTLE_ENDIAN_BIT_5         (0x0020u)  
	#define LITTLE_ENDIAN_BIT_6         (0x0040u)  
	#define LITTLE_ENDIAN_BIT_7         (0x0080u)  
	#define LITTLE_ENDIAN_BIT_8         (0x0100u)  
	#define LITTLE_ENDIAN_BIT_9         (0x0200u)  
	#define LITTLE_ENDIAN_BIT_10        (0x0400u)  
	#define LITTLE_ENDIAN_BIT_11        (0x0800u)  
	#define LITTLE_ENDIAN_BIT_12        (0x1000u)  
	#define LITTLE_ENDIAN_BIT_13        (0x2000u)  
	#define LITTLE_ENDIAN_BIT_14        (0x4000u)  
	#define LITTLE_ENDIAN_BIT_15        (0x8000u)  	
#endif



// Typedef
#ifndef __BOOLEAN
	#define __BOOLEAN
	typedef unsigned char BOOL;
#endif	

#ifndef __CHAR8
	#define __CHAR8
	typedef char	CHAR;
#endif /* #ifndef _CHAR8 */

#ifndef __UINT8
	#define __UINT8
	typedef unsigned char UINT8;
	#define BOOL UINT8
	#define BYTE UINT8
	#define u8 UINT8
#endif /* #ifndef _UINT8 */	

#ifndef __INT8
	#define __INT8
	typedef signed char INT8;
	#define s8 INT8
#endif /* #ifndef _INT8 */

#ifndef __SHORT16
	#define __SHORT16
	typedef short SHORT16;
#endif /* #ifndef _SHORT16 */

#ifndef __INT16
	#define __INT16
	typedef int INT16;
	#define s16 INT16
#endif /* #ifndef _INT16 */

#ifndef __UINT16
	#define __UINT16
	typedef unsigned int UINT16;
	#define WORD UINT16
	#define u16 UINT16
#endif /* #ifndef _WORD */

#ifndef __INT32
	#define __INT32
	typedef long INT32;
	#define s32 INT32
#endif /* #ifndef _INT32 */

#ifndef __UINT32
	#define __UINT32
	typedef unsigned long UINT32;
//	#define DWORD UINT32
	#define D32WORD UINT32
	#define u32 UINT32
#endif /* #ifndef _UINT32 */

/*****************************************************************************/
/* Derived Data Structure                                     			     */
/*****************************************************************************/
#if defined(BIG_ENDIAN)
	typedef union
	{
		BYTE    ucVal;
		struct
		{
			BYTE  bit0      : 1;				/* bit 7 */
			BYTE  bit1      : 1;				/* bit 6 */
			BYTE  bit2      : 1;				/* bit 5 */ 
			BYTE  bit3      : 1;				/* bit 4 */
			BYTE  bit4      : 1;				/* bit 3 */
			BYTE  bit5      : 1;				/* bit 2 */
			BYTE  bit6      : 1;				/* bit 1 */ 
			BYTE  bit7      : 1;				/* bit 0 */
		}Bit;		
		struct
		{
			BYTE  bit7654    : 4;				/* bit 7 */
			BYTE  bit3210    : 4;				/* bit 6 */
		}BitHL;
	} LCDBYTE;

	typedef union
	{
		BYTE    ucVal;
		struct
		{
			BYTE  bit0      : 1;				/* bit 7 */
			BYTE  bit1      : 1;				/* bit 6 */
			BYTE  bit2      : 1;				/* bit 5 */ 
			BYTE  bit3      : 1;				/* bit 4 */
			BYTE  bit4      : 1;				/* bit 3 */
			BYTE  bit5      : 1;				/* bit 2 */
			BYTE  bit6      : 1;				/* bit 1 */ 
			BYTE  bit7      : 1;				/* bit 0 */
		}Bit;		
		struct
		{
			BYTE  bit7654    : 4;				/* bit 7 */
			BYTE  bit3210    : 4;				/* bit 6 */
		}BitHL;
	} UBYTE;

	typedef union
	{
		WORD wVal;
		struct
		{
			BYTE   byte1;					    /* bit 15 ~  8 */
			BYTE   byte0;					    /* bit 7  ~  0 */
		}Byte;		
		struct
		{
			UBYTE   FLAG1;					    /* bit 15 ~  8 */
			UBYTE   FLAG0;					    /* bit 7  ~  0 */
		}FLAG;		
		struct
		{
			s8   sbyte1;					    /* bit 15 ~  8 */
			s8   sbyte0;					    /* bit 7  ~  0 */
		}sByte;
	} UWORD;
	typedef union
	{
		WORD wVal;
		struct
		{
			BYTE  bit15      : 1;				/* bit 15 */
			BYTE  bit14      : 1;				/* bit 14 */
			BYTE  bit13      : 1;				/* bit 13 */ 
			BYTE  bit12      : 1;				/* bit 12 */
			BYTE  bit11      : 1;				/* bit 11 */
			BYTE  bit10      : 1;				/* bit 10 */
			BYTE  bit9       : 1;				/* bit 9  */ 
			BYTE  bit8       : 1;				/* bit 8  */
			BYTE  bit7       : 1;				/* bit 7  */
			BYTE  bit6       : 1;				/* bit 6  */
			BYTE  bit5       : 1;				/* bit 5  */ 
			BYTE  bit4       : 1;				/* bit 4  */
			BYTE  bit3       : 1;				/* bit 3  */
			BYTE  bit2       : 1;				/* bit 2  */
			BYTE  bit1       : 1;				/* bit 1  */ 
			BYTE  bit0       : 1;				/* bit 0  */
		}Bit;	
	} UUWORD;
	typedef union
	{
		INT16 wVal;
		struct
		{
			INT8   byte1;					   /* bit 15 ~  8 */
			INT8   byte0;					   /* bit 7  ~  0 */
		}Byte;
	} SWORD;

	typedef union
	{
		UINT32 dwVal;
		struct
		{
			WORD  MSB;					   		/* MSB word code */
			WORD  LSB;				       		/* LSB word code */
		}Word;
		struct
		{
			BYTE   byte3;					    /* bit 31 ~ 24 */
			BYTE   byte2;					    /* bit 23 ~ 16 */
			BYTE   byte1;					 	/* bit 15 ~  8 */
			BYTE   byte0;					    /* bit 7  ~  0 */
		}Byte;		
		struct
		{
			UBYTE   FLAG3;					    /* bit 31 ~ 24 */
			UBYTE   FLAG2;					    /* bit 23 ~ 16 */
			UBYTE   FLAG1;					 	/* bit 15 ~  8 */
			UBYTE   FLAG0;					    /* bit 7  ~  0 */
		}FLAG;
	} ULONG;

	typedef union
	{
		u8 value[4];
		INT32 lVal;
		struct
		{
			INT16  MSB;					      	/* MSB word code */
			INT16  LSB;					 	  	/* LSB word code */
		}Word;
		struct
		{
			INT8   byte3;					   	/* bit 31 ~ 24 */
			INT8   byte2;					   	/* bit 23 ~ 16 */
			INT8   byte1;					   	/* bit 15 ~  8 */
			INT8   byte0;					   	/* bit 7  ~  0 */
		}Byte;
	} SLONG;	

	typedef union
	{
		struct
		{
			UINT32 MSB;
			UINT32 LSB;
		}Long;
		struct
		{
			WORD  word3;
			WORD  word2;
			WORD  word1;
			WORD  word0;
		}Word;
		struct
		{
			BYTE   byte7;					   /* bit 63 ~ 56 */
			BYTE   byte6;					   /* bit 55 ~ 48 */
			BYTE   byte5;					   /* bit 47 ~ 40 */
			BYTE   byte4;					   /* bit 39 ~ 32 */

			BYTE   byte3;					   /* bit 31 ~ 24 */
			BYTE   byte2;					   /* bit 23 ~ 16 */	
			BYTE   byte1;					   /* bit 15 ~  8 */
			BYTE   byte0;					   /* bit 7  ~  0 */
		}Byte;
	} ULONGLONG;
#endif

#if defined(LITTLE_ENDIAN)
	typedef union
	{
		BYTE    ucVal;
		struct
		{
			BYTE  bit0      : 1;				/* bit 0 */
			BYTE  bit1      : 1;				/* bit 1 */
			BYTE  bit2      : 1;				/* bit 2 */ 
			BYTE  bit3      : 1;				/* bit 3 */
			BYTE  bit4      : 1;				/* bit 4 */
			BYTE  bit5      : 1;				/* bit 5 */
			BYTE  bit6      : 1;				/* bit 6 */ 
			BYTE  bit7      : 1;				/* bit 7 */
		}Bit;
	} UBYTE;
	typedef union
	{
		WORD wVal;
		struct
		{
			BYTE   byte0;					    /* bit 7  ~  0 */
			BYTE   byte1;					    /* bit 15 ~  8 */
		}Byte;
		struct
		{
			s8   sbyte0;					    /* bit 7  ~  0 */
			s8   sbyte1;					    /* bit 15 ~  8 */
		}sByte;  
		struct
		{
			UBYTE   FLAG0;					    /* bit 7  ~  0 */
			UBYTE   FLAG1;					    /* bit 15 ~  8 */
		}FLAG;                               
	} UWORD;

	typedef union
	{
		WORD wVal;
		struct
		{
			BYTE   byte0;					    /* bit 7  ~  0 */
			BYTE   byte1;					    /* bit 15 ~  8 */
		}Byte;
		struct
		{
			s8   sbyte0;					    /* bit 7  ~  0 */
			s8   sbyte1;					    /* bit 15 ~  8 */
		}sByte;  
		struct
		{
			UBYTE   FLAG0;					    /* bit 7  ~  0 */
			UBYTE   FLAG1;					    /* bit 15 ~  8 */
		}FLAG;
		struct
		{
			BYTE  bit0      : 1;				/* bit 0 */
			BYTE  bit1      : 1;				/* bit 1 */
			BYTE  bit2      : 1;				/* bit 2 */ 
			BYTE  bit3      : 1;				/* bit 3 */
			BYTE  bit4      : 1;				/* bit 4 */
			BYTE  bit5      : 1;				/* bit 5 */
			BYTE  bit6      : 1;				/* bit 6 */ 
			BYTE  bit7      : 1;				/* bit 7 */
			
			BYTE  bit8      : 1;				/* bit 8  */
			BYTE  bit9      : 1;				/* bit 9  */
			BYTE  bit10     : 1;				/* bit 10 */ 
			BYTE  bit11     : 1;				/* bit 11 */
			BYTE  bit12     : 1;				/* bit 12 */
			BYTE  bit13     : 1;				/* bit 13 */
			BYTE  bit14     : 1;				/* bit 14 */ 
			BYTE  bit15     : 1;				/* bit 15 */
		}Bit;                                      
	} UUWORD;

	typedef union
	{
		INT16 wVal;
		struct
		{
			INT8   byte0;					   	/* bit 7  ~  0 */
			INT8   byte1;					   	/* bit 15 ~  8 */
		}Byte;
	} SWORD;

	typedef union
	{
		UINT32 dwVal;
		struct
		{	
			WORD  LSB;				       		/* LSB word code */
			WORD  MSB;					  		/* MSB word code */
		}Word;
		struct
		{
			BYTE   byte0;					    /* bit 7  ~  0 */
			BYTE   byte1;					 	/* bit 15 ~  8 */
			BYTE   byte2;					    /* bit 23 ~ 16 */
			BYTE   byte3;					    /* bit 31 ~ 24 */
		}Byte;
	} ULONG;

	typedef union
	{
		INT32 lVal;
		struct
		{
			INT16  LSB;					 	  /* LSB word code */
			INT16  MSB;					      /* MSB word code */
		}Word;
		struct
		{
			INT8   byte0;					   /* bit 7  ~  0 */
			INT8   byte1;					   /* bit 15 ~  8 */
			INT8   byte2;					   /* bit 23 ~ 16 */
			INT8   byte3;					   /* bit 31 ~ 24 */
		}Byte;
	} SLONG;

	typedef union
	{
		struct
		{
			UINT32 LSB;
			UINT32 MSB;
		}Long;
		struct
		{
			WORD  word0;
			WORD  word1;
			WORD  word2;
			WORD  word3;
		}Word;
		struct
		{
			BYTE   byte0;					   /* bit 7  ~  0 */	
			BYTE   byte1;					   /* bit 15 ~  8 */
			BYTE   byte2;					   /* bit 23 ~ 16 */
			BYTE   byte3;					   /* bit 31 ~ 24 */
			
			BYTE   byte4;					   /* bit 39 ~ 32 */
			BYTE   byte5;					   /* bit 47 ~ 40 */
			BYTE   byte6;					   /* bit 55 ~ 48 */
			BYTE   byte7;					   /* bit 63 ~ 56 */
		}Byte;
	} ULONGLONG;
#endif

// Bit
#define	set(val, bits) ((val) |= (bits))
#define	clr(val, bits) ((val) &= ~(bits))
#define	tst(val, bits) ((val) & (bits))
#define	tog(val, bits) ((val) ^= (bits))

// 函数指针
typedef void (*pFun)(void);
typedef void (*pFunc)(u8);

#endif
