/* 
 * File:   boarddef.h
 * Author: Jules
 *
 * Created on 20 April 2013, 11:20
 */

#ifndef BOARDDEF_INCLUDED_H
#define	BOARDDEF_INCLUDED_H

#ifdef	__cplusplus
extern "C" {
#endif
// need to determine if TCP/IP and USB Host can co-reside
// if other software not present. THEY CAN'T

#define SWITCH_NO 210// 210 to 219 are reserved for these boards
// 210 Routes to Uarts at position A now reclaimed for power meter
// 211 Routes to Uarts at position B
// 212 Routes to Uarts at position C
// 213 Routes to Uart in AV cabinet
// 214 Test Router to bus on test rig. This is a Version 1.12 board
// 215 MiWi to Ethernet Bridge
//     Holds status records for everything and has USB memory stick for packet log
//     if space allows also has HTTP
//     Or is PSU to ethernet bridge!
// 216 is HTTP server if 215 doesn't have memory for everything.
// 217 is DAC in AV cabinet
// 218 is ADC by main TV
//
// Enable test UART patterns - sends program toggle at tick interval
//#define TEST_TRANSMIT 1


//#define DEBUG_IP_PACKETS 0
#define DECODE_WEB_PACKET 0

#define U5_RS485 1  // also LED on spare pin (SS1)
#define U5_DAC   2
#define U5_ADC   3
#define U5_FLASH 4  // not available on V12 board
#define U5_IO    5
#define U5_OTG   6  // not available on V12 board
#define U5_MIWI  7  // MiWi wireless protocol transceiver
#define U5_PSU   8  // SPI interface to power supply board.
#define U5_POWERMETER 9

#define SCK_USB 1
#define SCK_U5  2
#define SCK_ETH 3

// USB options
// DEVICE
// HOST
// OTG

#if (SWITCH_NO == 210) || (SWITCH_NO == 211)
// Prototype board installed at position A
#define BROADCAST_PACKET 0
#define VERSION_1_16 0
//#define SERVER_ID 'A'
//#define USE_UART2 0
//#define USE_UART1 0
// Uart2 reversed as Uart1 on prototype board seems to be broken.
//#define G_UART1 g_Uart2
//#define G_UART2 g_Uart1
#define U5_OPTION U5_POWERMETER
// Spare AN10 and AN4
#define USE_ETHERNET 0
#if (SWITCH_NO == 210)
#define MY_IP_LAST 29
#elif(SWITCH_NO == 211)
#define MY_IP_LAST 30
#endif
//#define USE_USB 0
#define USE_LIGHT 0
// array sized to accomodate all current boards
// reduced from 150 to 140 because not enough stack
//#define NUMBER_PROGRAMS 140
//#define NUMBER_LIGHT_BOARDS 36
//#define NUMBER_OTHER_BOARDS 100
// This one forwards packets to the logging port
//#define HAS_LOG 0
#elif (SWITCH_NO == 212)
// Production board installed at position C
#define BROADCAST_PACKET 0
#define VERSION_1_16 0
#define SERVER_ID 'C'
#define USE_UART1 0
#define USE_UART2 0
//#define U5_OPTION U5_RS485
#define U5_OPTION 0
#define USE_ETHERNET 0
#define MY_IP_LAST 31
//#define USE_USB 0
#define USE_LIGHT 0
//#define AWAKE_LED 0
// array sized to accomodate all current boards
#define NUMBER_PROGRAMS 140
#define NUMBER_LIGHT_BOARDS 36
#define NUMBER_OTHER_BOARDS 100
#elif (SWITCH_NO == 213)
// Production board installed in AV cabinet
#define BROADCAST_PACKET 0
#define VERSION_1_16 0
#define SERVER_ID 'D'
#define USE_UART1 0
#define USE_UART2 0
// Uart2 reversed as Uart1 on prototype board seems to be broken.
//#define G_UART1 g_Uart2
//#define G_UART2 g_Uart1
#define U5_OPTION U5_RS485
#define USE_ETHERNET 0
#define MY_IP_LAST 32
//#define USE_USB 0
#define USE_LIGHT 0
// array sized to accomodate all current boards
#define NUMBER_PROGRAMS 150
#define NUMBER_LIGHT_BOARDS 36
#define NUMBER_OTHER_BOARDS 100
// This one forwards packets to the logging port
//#define HAS_LOG 0
// can reduce this when other boards have been built and installed
// array sized to accomodate AV boards
//#define NUMBER_PROGRAMS 30
//#define NUMBER_LIGHT_BOARDS 1
//#define NUMBER_OTHER_BOARDS 10
#elif (SWITCH_NO == 214)
// Test rig master board
#define BROADCAST_PACKET 0
#define VERSION_1_12 0
#define SERVER_ID 'Z'
// don't install UART handling code
#define USE_UART1 0
#define USE_UART2 0
#define U5_OPTION U5_RS485
#define USE_ETHERNET 0
#define MY_IP_LAST 37
#define USE_LIGHT 0
// array sized to accomodate all current boards
#define NUMBER_PROGRAMS 130
#define NUMBER_LIGHT_BOARDS 24
#define NUMBER_OTHER_BOARDS 80
#elif (SWITCH_NO == 215)
// Production board used for bridge between MiWi and Ethernet
// 
#define BROADCAST_PACKET 0
#define VERSION_1_16 0
#define SERVER_ID 'Y'
// don't install UART handling code
//#define USE_UART1 0
//#define USE_UART2 0
#define U5_OPTION U5_PSU
//#define U5_OPTION 0
#define USE_ETHERNET 0
#define USE_LIGHT 0
// array sized to accomodate all current boards
#define NUMBER_PROGRAMS 100
#define NUMBER_LIGHT_BOARDS 36
#define NUMBER_OTHER_BOARDS 100
// This one forwards packets to the logging port
// use TCP and HTTP
//#define STACK_USE_TCP 0
//#define STACK_USE_HTTP_SERVER 0
//#define MPFS_BUFFER_LEN 2000
#define MY_IP_LAST 34
// USB Host for memory stick to contain
// Logging records
// Web site
//#define USE_USB 0
// Probably not space for light programs
//#define USE_LIGHT 0
// array sized to minimum
//#define NUMBER_PROGRAMS 256
#elif (SWITCH_NO == 216)
// Production board used for web site
// need to determine if TCP/IP and USB Host can co-reside
// if other software not present. THEY CAN'T
#define BROADCAST_PACKET 0
#define VERSION_1_16 0
#define SERVER_ID 'Z'
// don't install UART handling code
//#define USE_UART2 0
#define U5_OPTION 0
#define USE_ETHERNET 0
// use TCP and HTTP
#define STACK_USE_TCP 0
#define STACK_USE_HTTP_SERVER 0
#define MPFS_BUFFER_LEN 5500
#define MY_IP_LAST 35
// USB Host for memory stick to contain
// Logging records
// Web site
//#define USE_USB 0
// Probably not space for light programs
//#define USE_LIGHT 0
// array sized to minimum
//#define NUMBER_PROGRAMS 256
//#define NUMBER_LIGHT_BOARDS 1
//#define NUMBER_OTHER_BOARDS 1
#elif (SWITCH_NO == 219)
// Prototype board used for USB and RS422
// USB , n X RS422 channels
#define BROADCAST_PACKET 0
#define VERSION_1_16 0
#define SERVER_ID 'B'
#define USE_UART1 0
#define USE_UART2 0
//#define U5_OPTION U5_RS485
//#define USE_ETHERNET 0
//#define MY_IP_LAST 30
#define USE_USB 0
// array sized to accomodate all current boards
#define NUMBER_PROGRAMS 140
#define NUMBER_LIGHT_BOARDS 36
#define NUMBER_OTHER_BOARDS 100
#define USE_LIGHT 0
#endif

#if !defined(USE_UART1) && !defined(USE_UART2)
#define NO_UART 0
#endif
#if defined(USE_UART1) || defined(USE_UART2) /*|| defined(USE_USB)*/
#define ASCII_PACKETS
#endif

#if !defined(G_UART1)
#define G_UART1 g_Uart1
#endif

#if !defined(G_UART2)
#define G_UART2 g_Uart2
#endif
// Determine array sizes for storing status information
// There are currently
// 8  Audio boards
// 34 Switch and motion sensor boards
// 27 Light controller boards
//
// was 64
// there are about 98 entries in programtraits
//#define NUMBER_PROGRAMS 100
#if !defined(NUMBER_PROGRAMS)
#define NUMBER_PROGRAMS 150
#endif
#if !defined(NUMBER_LIGHT_BOARDS)
// was 16
#define NUMBER_LIGHT_BOARDS 36
#endif
// there are currently 68 boards in total
#if !defined(NUMBER_OTHER_BOARDS)
// was 32
//#define NUMBER_OTHER_BOARDS 50
// there are 42 switch and audio boards
#define NUMBER_OTHER_BOARDS 100
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* BOARDDEF_H */

