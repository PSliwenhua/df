#ifndef __GPIO_DEFS_H
#define __GPIO_DEFS_H

////#include "Main.h"
//#include "TypeDef.h"
/* 
#define GPIO_Pin_0                 ((UINT8)0x01)  
#define GPIO_Pin_1                 ((UINT8)0x02)  
#define GPIO_Pin_2                 ((UINT8)0x04)  
#define GPIO_Pin_3                 ((UINT8)0x08)  
#define GPIO_Pin_4                 ((UINT8)0x10)  
#define GPIO_Pin_5                 ((UINT8)0x20)  
#define GPIO_Pin_6                 ((UINT8)0x40)  
#define GPIO_Pin_7                 ((UINT8)0x80)  



#define CMT_FCSB_GPIO               P0
#define CMT_FCSB_GPIO_DDR           P0IO
#define CMT_FCSB_GPIO_PU            P0PU
#define CMT_FCSB_GPIO_OD            P0OD
#define CMT_FCSB_GPIO_PIN           GPIO_Pin_3

#define CMT_CSB_GPIO                P1
#define CMT_CSB_GPIO_DDR            P1IO
#define CMT_CSB_GPIO_PU             P1PU
#define CMT_CSB_GPIO_OD             P1OD
#define CMT_CSB_GPIO_PIN            GPIO_Pin_0

#define CMT_SDIO_GPIO               P1
#define CMT_SDIO_GPIO_DDR           P1IO
#define CMT_SDIO_GPIO_PU            P1PU
#define CMT_SDIO_GPIO_OD            P1OD
#define CMT_SDIO_GPIO_PIN           GPIO_Pin_1

#define CMT_SCLK_GPIO               P1
#define CMT_SCLK_GPIO_DDR           P1IO
#define CMT_SCLK_GPIO_PU            P1PU
#define CMT_SCLK_GPIO_OD            P1OD
#define CMT_SCLK_GPIO_PIN           GPIO_Pin_2

#define CMT_GPIO1_GPIO              P0
#define CMT_GPIO1_GPIO_DDR          P0IO
#define CMT_GPIO1_GPIO_PU           P0PU
#define CMT_GPIO1_GPIO_OD           P0OD
#define CMT_GPIO1_GPIO_PIN          GPIO_Pin_2

#define CMT_GPIO2_GPIO              P0
#define CMT_GPIO2_GPIO_DDR          P0IO
#define CMT_GPIO2_GPIO_PU           P0PU
#define CMT_GPIO2_GPIO_OD           P0OD
#define CMT_GPIO2_GPIO_PIN          GPIO_Pin_1

#define CMT_GPIO3_GPIO              P0
#define CMT_GPIO3_GPIO_DDR          P0IO
#define CMT_GPIO3_GPIO_PU           P0PU
#define CMT_GPIO3_GPIO_OD           P0OD
#define CMT_GPIO3_GPIO_PIN          GPIO_Pin_0

#define LED1_RF                     P5
#define LED1_RF_DDR                 P5IO
#define LED1_RF_PU                  P5PU
#define LED1_RF_OD                  P5OD
#define LED1_RF_PIN                 GPIO_Pin_4

#define LED2_PWR                    P5
#define LED2_PWR_DDR                P5IO
#define LED2_PWR_PU                 P5PU
#define LED2_PWR_OD                 P5OD
#define LED2_GPIO_PIN               GPIO_Pin_3

#define MOTOR_GPIO                  P1
#define MOTOR_GPIO_DDR              P1IO
#define MOTOR_GPIO_PU               P1PU
#define MOTOR_GPIO_OD               P1OD
#define MOTOR_GPIO_PIN              GPIO_Pin_4

#define MOTOREN_GPIO                P1
#define MOTOREN_GPIO_DDR            P1IO
#define MOTOREN_GPIO_PU             P1PU
#define MOTOREN_GPIO_OD             P1OD
#define MOTOREN_GPIO_PIN            GPIO_Pin_5

#define JP1_GPIO                    P2
#define JP1_GPIO_DDR                P2IO
#define JP1_GPIO_PU                 P2PU
#define JP1_GPIO_OD                 P2OD
#define JP1_GPIO_PIN                GPIO_Pin_0

#define JP2_GPIO                    P2
#define JP2_GPIO_DDR                P2IO
#define JP2_GPIO_PU                 P2PU
#define JP2_GPIO_OD                 P2OD
#define JP2_GPIO_PIN                GPIO_Pin_1

#define JP3_GPIO                    P2
#define JP3_GPIO_DDR                P2IO
#define JP3_GPIO_PU                 P2PU
#define JP3_GPIO_OD                 P2OD
#define JP3_GPIO_PIN                GPIO_Pin_2

#define JP4_GPIO                    P2
#define JP4_GPIO_DDR                P2IO
#define JP4_GPIO_PU                 P2PU
#define JP4_GPIO_OD                 P2OD
#define JP4_GPIO_PIN                GPIO_Pin_3 */
//-------------------------------------------
// GPIO闂傚倷娴囧▔鏇㈠窗閹版澘鍑犲┑鐘宠壘缁狀垰顪冪€ｎ亪顎楃粭鎴︽⒑鐠団€冲幐缂佽埖宀稿顐﹀箻鐠囧弶顥濋梺闈涚墕濡顢旈崼鏇熲拺閻犳亽鍔岄弸鎴︽煛鐎ｎ亶鐓兼鐐茬箻閺佹捇鏁撻敓锟�
//-------------------------------------------
/* 
// 闂傚倷娴囧▔鏇㈠窗閹版澘鍑犲┑鐘宠壘缁狀垶鏌ｉ幋锝呅撻柡鍛倐閺岋繝宕掑Ο琛″亾閺嶎偀鍋撳槌栧劅PIO -> 闂傚倷娴囧▔鏇㈠窗閹版澘鍑犲┑鐘宠壘缁狀垶鏌ｉ幋锝呅撻柡鍛倐閹綊宕剁捄杞板缂備浇椴哥换鍫ュ蓟閵娾晜鍋勯柛娑橈功娴煎嫰姊鸿ぐ鎺濇闁稿繑锕㈠顐﹀箻鐠囧弶顥濋梺闈涚墕濡顢旈崼鏇熲拺閻犳亽鍔岄弸鎴︽煛鐎ｎ亶鐓兼鐐茬箻閹粓鎳為妷锔筋仧闂備礁鎼崐鍫曞磹閺嶎偀鍋撳鐐
#define GPIO_OpenPuInput(_PU, _DDR, _PIN) 	            \         			
      set(_PU,_PIN),                                    \
      clr(_DDR,_PIN)


// 闂傚倷娴囧▔鏇㈠窗閹版澘鍑犲┑鐘宠壘缁狀垶鏌ｉ幋锝呅撻柡鍛倐閺岋繝宕掑Ο琛″亾閺嶎偀鍋撳槌栧劅PIO -> 闂傚倷娴囧▔鏇㈠窗閹版澘鍑犲┑鐘宠壘缁狀垶鏌ｉ幋锝呅撻柡鍛倐閹綊宕剁捄杞板缂備浇椴哥换鍫ュ蓟閵娾晜鍋勭紒瀣硶閸旂敻姊虹憴鍕祷妞ゆ垵妫涢埀顒佽壘缂嶅﹪寮婚妸鈺傚亜闁告稑锕︽导鍕⒑瑜版帩妫戦柛蹇旓耿瀵偊骞樼拠鍙夘棟闂侀潧鐗嗗Λ妤咁敂閿燂拷
#define GPIO_ClosePuInput(_PU, _DDR, _PIN) 	            \   		
      clr(_PU,_PIN),                                    \
      clr(_DDR,_PIN)


// 闂傚倷娴囧▔鏇㈠窗閹版澘鍑犲┑鐘宠壘缁狀垶鏌ｉ幋锝呅撻柡鍛倐閺岋繝宕掑Ο琛″亾閺嶎偀鍋撳槌栧劅PIO -> 闂傚倷娴囧▔鏇㈠窗閹版澘鏄ラ柛娑欐綑缁犵喖鎮楅敐搴′簻妞ゅ繐鐖煎铏规崉閵娿儲鐎鹃梺鍝勵儏椤兘鐛箛娑欏€婚柤鎭掑劜濞呫垽姊洪崫鍕偓鍫曞磹閺嶎偀鍋撳鐐(闂備礁鎲￠悷顖涚椤忓牆鏋侀柟鎹愵嚙濡﹢鏌曢崼婵囶棞妞ゅ繐鐖煎铏规崉閵娿儲鐎鹃梺鍝勵儏椤兘鐛箛娑欐啣闁稿本绻勯ˇ浼存⒒娴ｈ姤纭堕柛鐘冲姍瀵憡绻濆顒傤唵闂佺粯鍨兼慨銈夊疾閹间焦鐓涢柛灞久埀顒佺墱閳ь剚鑹剧紞濠囧蓟閵娾晜鍋勯柛娑橈功娴煎嫰姊鸿ぐ鎺濇闁稿繑锕㈠顐﹀箻鐠囧弶顥濋梺闈涚墕濡顢旈崼鏇熲拺閻犳亽鍔岄弸鎴︽煛鐎ｎ亶鐓兼鐐茬箻閹粓鎳為妷锔筋仧缂傚倷鐒︾粊鎾磻閹绘瑩姊绘担鑺ョ《闁哥姵娲樻穱濠囶敇閻樺弶鐎虫繝銏ｆ硾椤戝懘顢旈懜娈挎闁绘垵娲︾€氾拷)
#define GPIO_ClosePuOutput(_GPIO, _PU, _DDR, _PIN)   	\	
	  clr(_PU,_PIN),                                    \
	  set(_DDR,_PIN)


// 闂傚倷娴囧▔鏇㈠窗閹版澘鍑犲┑鐘宠壘缁狀垶鏌ｉ幋锝呅撻柡鍛倐閺岋繝宕掑Ο琛″亾閺嶎偀鍋撳槌栧劅PIO -> 闂傚倷娴囧▔鏇㈠窗閹版澘鏄ラ柛娑欐綑缁犵喖鎮楅敐搴′簻妞ゅ繐鐖煎铏规崉閵娿儲鐎鹃梺鍝勵儏椤兘鐛箛娑欏€婚柤鎭掑劜濞呫垽姊洪崫鍕偓鍫曞磹閺嶎偀鍋撳顒傜Ш闁哄被鍔戦幃銏ゅ川婵犲嫪绱曢梻浣哥秺椤ユ捇宕楀鈧顐﹀箻鐠囧弶顥濋梺闈涚墕濡顢旈崼鏇熲拺閻犳亽鍔屽▍鎰版煙閸戙倖瀚�1
#define GPIO_ClosePuOutput1(_GPIO, _PU, _DDR, _PIN) 	\
      clr(_PU,_PIN),                                    \
      set(_DDR,_PIN),                                   \
      set(_GPIO,_PIN)


// 闂傚倷娴囧▔鏇㈠窗閹版澘鍑犲┑鐘宠壘缁狀垶鏌ｉ幋锝呅撻柡鍛倐閺岋繝宕掑Ο琛″亾閺嶎偀鍋撳槌栧劅PIO -> 闂傚倷娴囧▔鏇㈠窗閹版澘鏄ラ柛娑欐綑缁犵喖鎮楅敐搴′簻妞ゅ繐鐖煎铏规崉閵娿儲鐎鹃梺鍝勵儏椤兘鐛箛娑欏€婚柤鎭掑劜濞呫垽姊洪崫鍕偓鍫曞磹閺嶎偀鍋撳顒傜Ш闁哄被鍔戦幃銏ゅ川婵犲嫪绱曢梻浣哥秺椤ユ捇宕楀鈧顐﹀箻鐠囧弶顥濋梺闈涚墕濡顢旈崼鏇熲拺閻犳亽鍔屽▍鎰版煙閸戙倖瀚�0
#define GPIO_ClosePuOutput0(_GPIO, _PU, _DDR, _PIN)     \	
      clr(_PU,_PIN),                                    \
      set(_DDR,_PIN),                                   \
	  clr(_GPIO,_PIN)

// 闂傚倷娴囧▔鏇㈠窗閹版澘鍑犲┑鐘宠壘缁狀垶鏌ｉ幋锝呅撻柡鍛倐閺岋繝宕掑Ο琛″亾閺嶎偀鍋撳槌栧劅PIO -> 闂傚倷娴囧▔鏇㈠窗閹版澘鏄ラ柛娑欐綑缁犵喖鎮楅敐搴′簻妞ゅ繐鐖煎铏规崉閵娿儲鐎鹃梺鍝勵儏椤兘鐛箛娑欏€婚柤鎭掑劜濞呫垽姊洪崫鍕偓鍫曞磹閺嶎偀鍋撳顒傜Ш闁哄被鍔戦幃銏ゅ川婵犲嫪绱曢梻浣哥秺椤ユ捇宕楀鈧顐﹀箻鐠囧弶顥濋梺闈涚墕濡顢旈懜娈挎闁绘劖娼欓埢鏇㈡煛娴ｈ宕岀€殿噮鍓熸俊鍫曞幢濡ゅ﹣绱﹂梺鍝勵槺閸庢劙宕滈悢鐓庢瀬闁规崘顕уΛ姗€鏌曢崼婵囶棞妞ゅ繐鐖煎铏规崉閵娿儲鐝㈤梺鐟板殩閹凤拷
#define GPIO_ClosePuReverOut(_GPIO, _PU, _DDR, _PIN)     \	
      clr(_PU,_PIN),                                    \
      set(_DDR,_PIN),                                   \
	  clr(_GPIO,_PIN)

// 闂傚倷娴囧▔鏇㈠窗閹版澘鍑犲┑鐘宠壘缁狀垶鏌ｉ幋锝呅撻柡鍛倐閺岋繝宕掑Ο琛″亾閺嶎偀鍋撳槌栧劅PIO -> 闂傚倷娴囧▔鏇㈠窗閹版澘鍑犲┑鐘宠壘缁狀垶鏌ｉ幋锝呅撻柡鍛倐閺岋繝宕掑Ο琛″亾閺嶎偀鍋撳顒傜Ш闁哄被鍔戦幃銏ゅ川婵犲嫪绱曢梻浣哥秺椤ユ捇宕楀鈧顐﹀箻缂佹ɑ娅㈤梺璺ㄥ櫐閹凤拷
#define GPIO_Mode_Out_PP(_PP, _DDR, _PIN)             	\							
      set(_DDR,_PIN),                                   \
      clr(_PP,_PIN)


// 闂傚倷娴囧▔鏇㈠窗閹版澘鍑犲┑鐘宠壘缁狀垶鏌ｉ幋锝呅撻柡鍛倐閺岋繝宕掑Ο琛″亾閺嶎偀鍋撳槌栧劅PIO -> 闂傚倷娴囧▔鏇㈠窗閹版澘鍑犲┑鐘宠壘缁狀垶姊洪崹顕呭剳缁绢厸鍋撻梻鍌欐祰濞夋洟宕伴幇鏉垮嚑濠电姵鑹剧粻顖炴煟閹达絽袚闁哄懏鎮傞弻銊╂偆閸屾稑顏�
#define GPIO_Mode_Out_OD(_OD, _DDR, _PIN)            	\           							
      set(_DDR,_PIN),                                   \
	  set(_OD,_PIN)


//闂傚倷娴囧▔鏇㈠窗閹版澘鍑犲┑鐘宠壘缁狀垳鈧懓瀚妯煎緤缁轰揪IOX_Bit濠电偠鎻徊鐣岀矓瑜版帒鏋侀柟鎹愵嚙濡﹢鏌曢崼婵囶棞妞ゅ繐鐖奸弻娑欑節韫囨柨顏�
#define READ_GPIO_PIN(x)            tst(x,x##_PIN)

//GPIOX_Bit濠电偠鎻徊鐣岀矓瑜版帒鏋侀柟鎹愵嚙濡﹢鏌曢崼婵囶棞妞ゅ骏鎷�1闂傚倷娴囧▔鏇㈠窗閹版澘鍑犲┑鐘宠壘缁狀垶鏌ㄩ悤鍌涘0
#define SET_GPIO_H(x)               GPIO_ClosePuOutput1(x, x##_PU, x##_DDR, x##_PIN)
#define SET_GPIO_L(x)               GPIO_ClosePuOutput0(x, x##_PU, x##_DDR, x##_PIN)

//闂傚倷娴囧▔鏇㈠窗閹版澘鍑犲┑鐘宠壘缁狀垶鏌ｉ幋锝呅撻柡鍛倐閺岋繝宕掑Ο琛″亾閺嶎偀鍋撳槌栧劅PIO婵犵妲呴崹顏堝焵椤掆偓绾绢厾娑甸埀锟�
#define SET_GPIO_OUT(x)             GPIO_Mode_Out_PP(x##_OD, x##_DDR, x##_PIN)
#define SET_GPIO_IN(x)              GPIO_ClosePuInput(x##_PU, x##_DDR, x##_PIN)
#define SET_GPIO_OD(x)              GPIO_Mode_Out_OD(x##_OD, x##_DDR, x##_PIN)
 */

#endif
