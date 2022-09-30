#ifndef __LVD_H__
#define __LVD_H__

#define	LVD_ENABLE()			_lvden = 1
#define	LVD_DISABLE()			_lvden = 0
#define	LVD_ISR_ENABLE()		_lve = 1
#define	LVD_ISR_DISABLE()		_lve = 0
#define	LVD_SET_FLAG()			_lvf = 1
#define	LVD_CLEAR_FLAG()		_lvf = 0
#define	LVD_GET_FLAG()			_lvf


void F_LvdDetectBattery();

#endif
