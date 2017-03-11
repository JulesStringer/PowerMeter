/* 
 * File:   compiler.h
 * Author: Jules
 *
 * Created on 26 April 2013, 18:34
 */

#ifndef COMPILER1_H
#define	COMPILER1_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <p32xxxx.h>
//#include <plib.h>
//#include "C:\microchip_solutions_v2013-02-15\Microchip\include\compiler.h"
typedef enum
{
    // Configure the interrupt module for Mult-vector mode.
    INT_SYSTEM_CONFIG_MULT_VECTOR,
    // Configure the interrupt module for Single Vectored mode.
    INT_SYSTEM_CONFIG_SINGLE_VECTOR
}INT_SYSTEM_CONFIG;
//void __attribute__ ((nomips16)) INTConfigureSystem(INT_SYSTEM_CONFIG config);
void __attribute__ ((nomips16)) INTEnableSystemMultiVectoredInt(void);

void __attribute__((noreturn)) SoftReset(void);

#define FAR
#define ROM
#define PTR_BASE		unsigned long
#define ROM_PTR_BASE	unsigned long

#define ClearWDT() (WDTCONSET = _WDTCON_WDTCLR_MASK)

#ifdef _DMAC
	#define	mSYSTEMUnlock(intStat, dmaSusp)	do{intStat=INTDisableInterrupts(); dmaSusp=DmaSuspend(); \
						SYSKEY = 0, SYSKEY = 0xAA996655, SYSKEY = 0x556699AA;}while(0)
#else
	#define	mSYSTEMUnlock(intStat, dmaSusp)	do{intStat=INTDisableInterrupts(); \
						SYSKEY = 0, SYSKEY = 0xAA996655, SYSKEY = 0x556699AA;}while(0)
#endif	// _DMAC

#define strlenpgm(a) strlen(a)
#ifdef	__cplusplus
}
#endif

#endif	/* COMPILER_H */

