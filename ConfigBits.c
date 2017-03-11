#include <GenericTypeDefs.h>
#include <p32xxxx.h>

unsigned char PRODL;

#if defined(__32MX250F128B__)
// DEVCFG0 ---------------------------------------------------------------
// code protection bit off
#pragma config CP=OFF
// boot flash write protect
#pragma config BWP=OFF
// program flash write protect bits
#pragma config PWP=OFF
// Debug pair selection - this selects pins 4,5
#pragma config ICESEL=ICS_PGx1
// JTAG debugging
#pragma config JTAGEN=OFF
// Background debugging - no setting is this done by programmer?

// DEVCFG1 ---------------------------------------------------------------
// watchdog timer window size
#pragma config FWDTWINSZ=WINSZ_25
// Watchdog timer enable bit
// Off - can be enabled in software
#pragma config FWDTEN=OFF
// Watchdog timer window disable - so in window mode
#pragma config WINDIS=OFF
// Watchdog timer postscale bits
//#pragma config WDTPS=PS1048576
//#pragma config WDTPS=PS2048 // this should give 2.048 seconds before timeout.
// if there is a lot of activity 2.048 seems to cause frequent resets so try something bigger.
#pragma config WDTPS=PS16384  // try 16.384 seconds instead. -- makes no difference.
// clock switching and monitor selection disabled
#pragma config FCKSM=CSECME
// Peripheral bus clock divisor default value
#pragma config FPBDIV=DIV_2
// disable clock output
#pragma config OSCIOFNC=OFF
// Primary oscillator configuration
// suspect OFF isn't right
#pragma config POSCMOD=OFF
// Internal External oscillator switchover
#pragma config IESO=OFF
// Secondary oscillator enable
#pragma config FSOSCEN=ON
// Fast RC oscillator with PLL
#pragma config FNOSC=FRCPLL

// DEVCFG2 --------------------------------------------------------------
// Default PLL output divisor bits
#pragma config FPLLODIV=DIV_2
// USB PLL Enable - because we are using FRCPLL don't need PLL
// for USB
#pragma config UPLLEN=OFF
// USB Pll Divisor
// Need to get from xtal frequency to 4Mhz
#pragma config UPLLIDIV=DIV_12
// FPLL Multiplier
#pragma config FPLLMUL=MUL_20
// PLL Input divisor
#pragma config FPLLIDIV=DIV_2

// DEVCFG3 -------------------------------------------------------------
// USBID is USB Managed
#pragma config FUSBIDIO=OFF
// USBID is USB Managed
#pragma config FVBUSONIO=OFF
// Peripheral pin reconfiguration is allowed
//#pragma config IOLOCK=0
// Peripheral pin selection is one per reconfiguration
#pragma config IOL1WAY=OFF
// Peripheral module disable configuration bit is one per configuration
#pragma config PMDL1WAY=ON
// UserID is bits 0-15

// CFGCON ---------------------------------------------------------------
// IOLOCK - Peripheral pin select lock
// PMDLOCK - Peripheral module disabled bit
// JTAGEN - JTAG Enable port enable
// TDOEN - TDO Enable to 2 wire JTAG

// DEVID ----------------------------------------------------------------
// Device ID and revision ID
// VER - 4 bit version
// DIVID - 28 bits - device ID
#warning "PIC32MX250F128B block included"
#else
#warning CONFIG bits not defined
#endif



