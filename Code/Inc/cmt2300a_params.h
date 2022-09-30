#ifndef __CMT2300A_PARAMS_H
#define __CMT2300A_PARAMS_H

/* [CMT Bank] */
static code u8 g_cmt2300aCmtBank[4][CMT2300A_CMT_BANK_SIZE] = {
    {
      0x00,
      0x66,
      0xEC,  
      0x1D,  
      0x70,  
      0x80,  
      0x14,  
      0x08,  
      0x91,  
      0x02,  
      0x02,  
      0xD0,
    },
    {
      0x00,
      0x66,
      0xEC,  
      0x1D,  
      0x70,  
      0x80,  
      0x14,  
      0x08,  
      0x11,  
      0x02,  
      0x02,  
      0x00,
    },
    {
      0x00,		
      0x66,
      0xEC,
      0x1D,
      0x70,
      0x80,
      0x14,
      0x08,
      0x11,
      0x02,
      0x02,
      0x00,
    	
    },      
    {
      0x00,		
      0x66,
      0xEC,
      0x1D,
      0x70,
      0x80,
      0x14,
      0x08,
      0x11,
      0x02,
      0x02,
      0x00,
    }     
};

/* [System Bank] */
static code u8 g_cmt2300aSystemBank[4][CMT2300A_SYSTEM_BANK_SIZE] = {

    {
      0xAE,
      0xE0,
      0x45,
      0x00,
      0x00,
      0xF4,
      0x10,
      0xE2,
      0x42,
      0x20,
      0x48,//0x30 RSSI读数有变化 //在 SYNC_OK 有效时检测//无滤波
      0x81,
    },
    {
      0xAE,
      0xE0,
      0x45,
      0x00,
      0x00,
      0xF4,
      0x10,
      0xE2,
      0x42,
      0x20,
      0x48,//0x30 RSSI读数有变化 //在 SYNC_OK 有效时检测//无滤波
      0x81,
    },    
    {
      0xAE,
      0xE0,
      0x45,
      0x00,
      0x00,
      0xF4,
      0x10,
      0xE2,
      0x42,
      0x20,
      0x48,//0x30,//0x30 RSSI读数有变化 //在 SYNC_OK 有效时检测//无滤波
      0x81,
      
    },
    {
      0xAE,
      0xE0,
      0x45,
      0x00,
      0x00,
      0xF4,
      0x10,
      0xE2,
      0x42,
      0x20,
      0x48,//0x30 RSSI读数有变化 //在 SYNC_OK 有效时检测//无滤波
      0x81,
    }
};

/* [Frequency Bank] */
static code u8 g_cmt2300aFrequencyBank[4][CMT2300A_FREQUENCY_BANK_SIZE] = {
  
    {
      0x42,
      0x98,
      0xD1,
      0x1C,
      0x42,
      0x81,
      0x1F,
      0x1C,
    },
    {
      0x42,
      0x16,
      0x16,
      0x8D,
      0x42,
      0x0B,
      0xBD,
      0x1C,
    },
    {
      0x46,
      0x6D,
      0x80,
      0x86,
      0x46,
      0x62,
      0x27,
      0x16,
      
    },
    {
      0x46,
      0x61,
      0xC3,
      0x8D,
      0x46,
      0x56,
      0x6A,
      0x1D,
    }
};

/* [Data Rate Bank] */
static code u8 g_cmt2300aDataRateBank[4][CMT2300A_DATA_RATE_BANK_SIZE] = {
    
    {
      0xF2,
      0x5C,
      0x22,
      0x10,
      0xD3,
      0x13,
      0x0A,//0x16,
      0x0A,
      0x8F,
      0x5A,
      0x29,
      0x29,
      0xC0,
      0xB1,
      0x01,
      0x53,
      0x18,
      0x00,
      0xB4,
      0x00,
      0x00,
      0x01,
      0x00,
      0x00,
    },
    {
      0x6B,
      0xAD,
      0x20,
      0x11,
      0xF2,
      0x36,
      0x15,
      0x0A,
      0x8F,
      0x38,
      0x29,
      0x29,
      0xC0,
      0xE7,
      0x05,
      0x53,
      0x10,
      0x00,
      0xB4,
      0x00,
      0x00,
      0x01,
      0x00,
      0x00,
    },
    {
      0x6B,
      0xAD,
      0x20,
      0x11,
      0xF2,
      0x36,
      0x16,
      0x0B,
      0x8F,
      0x38,
      0x29,
      0x29,
      0xC0,
      0xE7,
      0x05,
      0x53,
      0x10,
      0x00,
      0xB4,
      0x00,
      0x00,
      0x01,
      0x00,
      0x00,
      
    },
    {
      0x6B,
      0xAD,
      0x20,
      0x11,
      0xF2,
      0x36,
      0x15,
      0x0B,
      0x8F,
      0x38,
      0x29,
      0x29,
      0xC0,
      0xE7,
      0x05,
      0x53,
      0x10,
      0x00,
      0xB4,
      0x00,
      0x00,
      0x01,
      0x00,
      0x00,
    }
};

/* [Baseband Bank] */
static code u8 g_cmt2300aBasebandBank[4][CMT2300A_BASEBAND_BANK_SIZE] = {
  
    {
      0x12,
      0x05,
      0x00,
      0xAA,//0xAA,//
      0x04,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0xD4,
      0x2D,
      0xAA,
      0x00,//msb00	//lsb02
      0x1F,//0x10 = 17 0x1F = 32
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x60,
      0xFF,
      0x02,//01 //02 preamble	0xAA
      0x00,
      0x1F,
      0x10,
    },
    {
      0x12,
      0x05,
      0x00,
      0xAA,//0xAA,//
      0x04,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0xD4,
      0x2D,
      0xAA,
      0x00,//msb00	//lsb02
      0x1F,//0x10 = 17 0x1F = 32
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x60,
      0xFF,
      0x02,//01 //02 preamble	0xAA
      0x00,
      0x1F,
      0x10,
    },
    {
      0x12,
      0x05,
      0x00,
      0xAA,//0xAA,//
      0x04,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0xD4,
      0x2D,
      0xAA,
      0x00,//msb00	//lsb02
      0x1F,//0x10 = 17 0x1F = 32
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x60,
      0xFF,
      0x02,//01 //02 preamble	0xAA
      0x00,
      0x1F,
      0x10,      
    },
    {
      0x12,
      0x05,
      0x00,
      0xAA,//0xAA,//
      0x04,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0xD4,
      0x2D,
      0xAA,
      0x00,//msb00	//lsb02
      0x1F,//0x10 = 17 0x1F = 32
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x60,
      0xFF,
      0x02,//01 //02 preamble	0xAA
      0x00,
      0x1F,
      0x10,
    }
  
};

/* [Tx Bank] */
static code u8 g_cmt2300aTxBank[4][CMT2300A_TX_BANK_SIZE] = {
  
    {
      0x70,//0x50FSK //0x70GFSK
      0x6C,
      0x15,
      0x00,
      0x01,
      0x30,
      0x00,
      0x8A,//0x8A, // ?????
      0x18,
      0x3F,
      0x7F,
    },
    {
      0x70,//0x50FSK //0x70GFSK
      0xB6,
      0x0A,
      0x00,
      0x08,
      0x70,
      0x00,
      0x8A,//0x8A, // ?????
      0x18,
      0x3F,
      0x7F,
    },
    {
      0x70,//0x50FSK //0x70GFSK
      0x07,// 0x07,
      0x0B,//0x0B,
      0x00,
      0x08,
      0x70,
      0x00,
	  0x8A,	
	  0x18,//20dbm
      0x3F,
      0x7F,
    	    	    	
    },
    {
      0x70,//0x50FSK //0x70GFSK
      0x6C,
      0x15,
      0x00,
      0x04,
      0x50,
      0x00,
      0x8A,//0x8A, // 功率
      0x18,
      0x3F,
      0x7F,
    }
};   


#endif