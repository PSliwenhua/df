
#ifndef _INTERRUPT_h_
#define _INTERRUPT_h_

#define	EMI_ENABLE()			(EA = 1)
#define	EMI_DISABLE()			(EA = 0)
#define	TM0_ENABLE()			{ET0 = 1;TR0 = 1; }
/* #define	TM1_ENABLE()			(_t1on = 1)
#define	TM2_ENABLE()			(_t2on = 1)
#define	TM3_ENABLE()			(_t3on = 1) */
#define	TM0_DISABLE()			{ET0 = 0;TR0 = 0; }
/* #define	TM1_DISABLE()			(_t1on = 0)
#define	TM2_DISABLE()			(_t2on = 0)
#define	TM3_DISABLE()			(_t3on = 0) */


#endif

