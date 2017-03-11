/* 
 * File:   hardwareprofile.h
 * Author: Jules
 *
 * Created on 20 April 2013, 11:15
 */

#ifndef HARDWAREPROFILE_INCLUDED_H
#define	HARDWAREPROFILE_INCLUDED_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <p32xxxx.h>
#include "boarddef.h"
#include "debugflags.h"

extern unsigned char PRODL;

#define CLOCK_FREQ          (40000000ul)
#define GetSystemClock()    CLOCK_FREQ			// Hz
// need to check clocks
#define GetInstructionClock()	(GetSystemClock()/1)	// Normally GetSystemClock()/4 for PIC18, GetSystemClock()/2 for PIC24/dsPIC, and GetSystemClock()/1 for PIC32.  Might need changing if using Doze modes.
#define GetPeripheralClock()	(GetSystemClock()/2)	// Normally GetSystemClock()/4 for PIC18, GetSystemClock()/2 for PIC24/dsPIC, and GetSystemClock()/1 for PIC32.  Divisor may be different if using a PIC32 since it's configurable.

#define NO_BRIDGE 0
#define NO_ACKNOWLEDGE 0
#define ENCODE_PACKET 0

//#define OUTPUT_DEBUG_UART1
#ifdef USE_ETHERNET
//#define OUTPUT_DEBUG_IP
#endif

#if defined(OUTPUT_DEBUG_IP) || defined(OUTPUT_DEBUG_UART1)
#define DEBUG_OUTPUT
#endif

//#define USB_MALLOC(x) dummy_malloc(x)

#ifdef VERSION_1_10
#include "hardwareprofile_1_10.h"
#elif defined(VERSION_1_11)
#include "hardwareprofile_1_11.h"
#elif defined(VERSION_1_12)
#include "hardwareprofile_1_12.h"
#elif defined(VERSION_1_16)
#include "hardwareprofile_1_16.h"
#endif

#define DEBUG_PutString(psz)
#define DEBUG_PutChar(ch)
#define DEBUG_PutHexUINT8(u8)
#define UART2PrintString(psz)

//void WriteUART1String(const char* psz);
//void WriteUART2String(const char* psz);
#if defined(USE_ETHERNET) && defined(DEBUG_OUTPUT)
void WriteIP(unsigned long dwFlags, const char* psz, unsigned long lVal);
#define WRITEIP(a,b) (WriteIP(dwFlags, a,b))
#define WRITEIP2(dwFlags,a,b) (WriteIP(dwFlags, a, b))
//#define PrintDec(a) (WriteIP(DEBUG_RADIO, "", a))
void WriteMAC(unsigned long dwFlags, const char* psz, unsigned char* pMac);
#define WRITEMAC(dwFlags, a,b) (WriteMAC(dwFlags, a,b))
void WriteIPMAC(unsigned long dwFlags, const char* psz, unsigned long lVal, unsigned char* pMac);
#define WRITEIPMAC(dwFlags, a,b,c) (WriteIPMAC(dwFlags, a,b,c))
#else
#define WRITEIP(a,b)
#define WRITEIP2(dwFlags, a,b)
#define WRITEMAC(dwFlags, a,b)
#define WRITEIPMAC(dwFlags, a,b,c)
#endif

#if defined(DEBUG_OUTPUT)
void WriteDebugString(unsigned long dwFlags, const char* psz);
#define WRITESTRING(flags, a) (WriteDebugString(flags, a))
//#define ConsolePutROMString(psz) (WriteDebugString(DEBUG_RADIO, psz))
#else
#define WRITESTRING(flags, a)
#endif
#if defined(DEBUG_OUTPUT)
void WriteTimeStamp(unsigned long dwFlags, const char* psz);
#define WRITETIMESTAMP(flags, a) (WriteTimeStamp(flags, a))
#else
#define WRITETIMESTAMP(flags, a)
#endif

#ifndef USE_ETHERNET
#define UDPFlush()
#endif
unsigned long GetTickCount();

#ifdef	__cplusplus
}
#endif

#endif	/* HARDWAREPROFILE_H */

