#ifndef __TIMER__H__
#define	__TIMER__H__

typedef struct {
	/* u8 Second;
	u8 Minute;
	u8 Hour;
	u8 Day;
	u8 Month;
	u8 Year;
	u8 Week;
	u8 State; */
	
	u8 Year;
	u8 Month;
	u8 Day;
	u8 Hour;
	u8 Minute;
	u8 Second;
	u8 Week;
	u8 State;
}SYSTEMTIME;
MyDef xdata SYSTEMTIME SysTime;

enum{
	D_SECOND_INC ,
	D_MINUTE_INC ,
	D_HOUR_INC   ,
	D_DAY_INC    ,
	D_MONTH_INC  ,
	D_YEAR_INC   ,
};

u8 F_CntServe(u8 *temp,u8 len);
u16 F_u16CntServe(u16 *temp,u16 len);
void F_SysTimeCntTask();
void F_TimeSever();
void F_Rf_Connect_Cmd(u8 cmd);

u8 F_GetYearData(u8 ucYear);/* Return:   low nibble(Week), other is not leap year) */
u8 F_GetMaxDay(u8 ucMonth, u8 ucYear);/* 返回值为：每个月份最大天数 */
u8 F_GetWeek(u8 ucDay,u8 ucMonth,u8 ucYear);/* 返回值为：星期天数 */
u8 F_GetRtcTime();
//===============================================================================================================
// 平年的每个月的最大天数               1月 2月 3月 4月 5月 6月 7月 8月 9月10月11月12月 
static code u8 T_MonthDays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
// 高4bits为闰年余数表，低4bits为平年余数表 1月   2月   3月   4月   5月   6月   7月   8月   9月  10月  11月  12月
static code u8 T_MonthWeek[13] = {0x00, 0x00, 0x33, 0x43, 0x06, 0x21, 0x54, 0x06, 0x32, 0x65, 0x10, 0x43, 0x65};
//===============================================================================================================


#endif
