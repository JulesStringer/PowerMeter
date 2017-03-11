#ifndef _DEBUG_FLAGS_INCLUDED
#define _DEBUG_FLAGS_INCLUDED
#define DEBUG_ANONYMOUS         0x00000001
#define DEBUG_TICK              0x00000002
#define DEBUG_PROGRAMMANAGER    0x00000004
#define DEBUG_UART              0x00000008
#define DEBUG_UDP               0x00000010
#define DEBUG_UART_TARGET       0x00000020
#define DEBUG_UART_RECEIVER     0x00000040
#define DEBUG_IP_TARGET         0x00000080
#define DEBUG_EXCEPTION         0x00000100
#define DEBUG_INITIALISE        0x00000200
#define DEBUG_USB               0x00000400
#define DEBUG_SERVER            0x00000800
#define DEBUG_ERROR             0x00001000
#define DEBUG_PACKETQUEUE       0x00002000
#define DEBUG_IP_RECEIVER       0x00004000
#define DEBUG_TARGETMANAGER     0x00008000
#define DEBUG_PROGRAM           0x00010000
#define DEBUG_STATUS            0x00020000
#define DEBUG_UART1             0x00040000
#define DEBUG_UART2             0x00080000
#define DEBUG_RADIO             0x00100000
#endif

#ifndef _BUSY_FLAGS_INCLUDED
#define _BUSY_FLAGS_INCLUDED
#define BUSY_UART1              0x01
#define BUSY_UART2              0x02
#define BUSY_IP                 0x04
#define BUSY_USB                0x08
#define BUSY_MIWI               0x10
#define BUSY_PSU                0x20
#define BUSY_CUP1               0x40
#define BUSY_CUP2               0x80
#endif
// TODO replace message strings with codes
// look these up in UDPDEbug.c
// 