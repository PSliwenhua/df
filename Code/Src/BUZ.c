#include "Main.h"

void F_KeyVoiceCheak(u8 KeyValueValid)
{
    if(KeyValueValid)
    {   if(B_BuzEn == _TRUE)
        {   B_BuzKeyEn = _TRUE;//键值生效，蜂鸣器鸣叫1次
            Buz.Cycle125ms = _FALSE;
            Buz.Cycle2s = _FALSE;//避免按键按的足够快，出现连声。
        }
    }
}

u8 F_KeyBreakFault()
{
    if((Buz.AlarmFlag.ucVal)||(B_BuzXor))
    {   B_BuzKeyBreak = _TRUE;
        Buz.AlarmFlag.ucVal = _FALSE;
        B_BuzKeyEn = _FALSE;
        M_BuzOff();          
        Buz.Cycle125ms = _FALSE;
        Buz.Cycle2s = _FALSE;
        Key.Value = _FALSE;
        return _TRUE;
    }	
    return _FALSE;
}

void F_BuzAlarmOverDownCnt()
{   
    if(Buz.AlarmFlag.ucVal)
    {   if(F_CntServe((u8 *)&Buz.AlarmCnt,D_BuzAlarmTime)==_TRUE)
            Buz.AlarmFlag.ucVal = _FALSE;
    }
}

void F_Buz10hzBiBiAlarmCheakCntTask()
{   
   if(B_PowerMode == D_PowerOn)
   {   
       if((B_BuzKeyEn)||(Buz.AlarmFlag.ucVal))
       {   Buz.Cycle125ms++;
           if(Buz.Cycle125ms >= 6)//15.625*7 =100MS
           {   Buz.Cycle125ms = _FALSE;
               Buz.Cycle2s++;
                switch (Buz.Cycle2s)
                {	case 1:case 3:case 5:case 7:
                            M_BuzOn();
                        break;				
                    case 2:case 4:case 6:case 10:
                            M_BuzOff();
                            if(B_BuzKeyEn)
                            {   B_BuzKeyEn = _FALSE;
                                Buz.Cycle125ms = _FALSE;
                                Buz.Cycle2s = _FALSE;
                            }
                        break;					
                    case 14://Di.Di.Di......Di.Di.Di......
                            B_BuzKeyEn = _FALSE;
                            Buz.Cycle2s = _FALSE;
                        break;
                }
           }
       }
   }
}

