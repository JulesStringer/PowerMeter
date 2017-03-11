/* 
 * File:   hardwareprofile_1_12.h
 * Author: Jules
 *
 * Created on 27 April 2013, 19:36
 */

#ifndef HARDWAREPROFILE_1_16_H
#define	HARDWAREPROFILE_1_16_H

#ifdef	__cplusplus
extern "C" {
#endif

// Configuration for RS485 port 1 (U6)
// TX is on pin 11 RB4
#define TX_ANSEL                   (PRODL)
#define TX_TRIS                    (TRISBbits.TRISB4)
#define TX_PIN                     1
#define TX_RPR                     (RPB4R)
// DI is on pin 7 RB3
#define DI_ANSEL                   (ANSELBbits.ANSB3)
#define DI_TRIS                    (TRISBbits.TRISB3)
#define DI_IO                      (LATBbits.LATB3)
#define DI_PORT                    (PORTBbits.RB3)

// RX is on pin 12 RA4
#define RX_ANSEL                   (PRODL)
#define RX_TRIS                    (TRISAbits.TRISA4)
#define RX_PIN                     2
// configuration for UART2 U8 - disabled whilst programming and debugging
//#define USE_UART2 0
// pin 14 is RX - RB5
#define RX2_ANSEL                  (PRODL)
#define RX2_TRIS                   (TRISBbits.TRISB5)
#define RX2_PIN                    1
// pin 25 is TX RB14
#define TX2_ANSEL                  (ANSELBbits.ANSB14)
#define TX2_IO                     (LATBbits.LATB14)
#define TX2_TRIS                   (TRISBbits.TRISB14)
#define TX2_PIN                    2
#define TX2_RPR                    (RPB14R)
// pin 6 is transmit enable RB2
#define DI2_ANSEL                  (ANSELBbits.ANSB2)
#define DI2_TRIS                   (TRISBbits.TRISB2)
#define DI2_IO                     (LATBbits.LATB2)
#define DI2_PORT                   (PORTBbits.RB2)

// U5 configuration
// U5 is superceded by several pluggable headers
// so that a SOIC8 can be mounted on breakout board
// some configurations are incompatible with UART2
// SOIC pins    PIC pin                 Name
// 1            3       SDO1/SDI1       RA1
// 2            25      SCK1            RB14
// 3            2       SS1             RA0
// 4            6       REFCLKO/SDO1    RB2
#if U5_OPTION==U5_POWERMETER
#define VOLTAGE_PIN 0   // AN0
#define CURRENT_PIN 1   // AN1
#define VOLTAGE_ANSEL (ANSELAbits.ANSA0)
#define CURRENT_ANSEL (ANSELAbits.ANSA1)
#define VOLTAGE_TRIS (TRISAbits.TRISA0)
#define CURRENT_TRIS (TRISAbits.TRISA1)
#else
#warning "U5 Option not defined or invalid"
#endif

// Configuration for ethernet
#if defined(USE_ETHERNET)
// ENC PIN  PIC PIN Usage
// 4        16  INT0 active low
#define INT0_TRIS       (TRISBbits.TRISB7)
#define INT0_ANSEL      (PRODL)
// 6 SO     24  SDI2 (3)
#define ENC_SDI_TRIS       (TRISBbits.TRISB13)
#define ENC_SDI_ANSEL      (ANSELBbits.ANSB13)
#define ENC_SDI_PIN        3
#define ENC_SDI_RPR        (SDI1R)
// 7 SI     17  SDO2 (4)
#define ENC_SDO_TRIS       (TRISBbits.TRISB8)
#define ENC_SDO_ANSEL      (PRODL)
#define ENC_SDO_PIN        4
#define ENC_SDO_RPR        (RPB8R)
// 8        26  SCK2
#define ENC_SCK_TRIS       (TRISBbits.TRISB15)
#define ENC_SCK_ANSEL      (ANSELBbits.ANSB15)
// 9        18  CS
#define ENC_CS_TRIS     (TRISBbits.TRISB9)
#define ENC_CS_ANSEL    (PRODL)
#define ENC_CS_IO       (LATBbits.LATB9)
#define ENC_CS_PIN      4
#define ENC_CS_RPR      (RPB9R)
//
#define ENC_SPISTAT SPI2STAT
#define ENC_SPISTATbits SPI2STATbits
#define ENC_SPIBRG SPI2BRG
#define ENC_SPICON1bits SPI2CONbits
#define ENC_SSPBUF SPI2BUF
#else
// SCK2 and other ethernet pins not defined
#define ENC_SCK_TRIS  (PRODL)
#define ENC_SCK_ANSEL (PRODL)
#define INT0_TRIS       (PRODL)
#define INT0_ANSEL      (PRODL)
#define ENC_SDI_TRIS       (PRODL)
#define ENC_SDI_ANSEL      (PRODL)
#define ENC_SDI_PIN        3
#define ENC_SDI_RPR        (PRODL)
#define ENC_SDO_TRIS       (PRODL)
#define ENC_SDO_ANSEL      (PRODL)
#define ENC_SDO_PIN        3
#define ENC_SDO_RPR        (PRODL)
#define ENC_CS_TRIS     (PRODL)
#define ENC_CS_ANSEL    (PRODL)
#define ENC_CS_IO       (PRODL)
#endif

#ifdef USE_SCK1
#define SCK1_TRIS  (TRISBbits.TRISB14)
#define SCK1_ANSEL (ANSELBbits.ANSB14)
#else
#define SCK1_TRIS  (PRODL)
#define SCK1_ANSEL (PRODL)
#endif

#ifdef SDI1_PHY_PIN
#if SDI1_PHY_PIN==3
#define SDI1_TRIS       (TRISAbits.TRISA1)
#define SDI1_ANSEL      (ANSELAbits.ANSA1)
#define SDI1_PIN        0
#define SDI1_RPR        (RPA1R)
#endif
#else
#define SDI1_TRIS       (PRODL)
#define SDI1_ANSEL      (PRODL)
#define SDI1_PIN        0
#define SDI1_RPR        (PRODL)
#endif

#ifdef SDO1_PHY_PIN
#if SDO1_PHY_PIN==3
// pin 3 is SDO1 - DIN RA1
#define SDO1_TRIS       (TRISAbits.TRISA1)
#define SDO1_ANSEL      (ANSELAbits.ANSA1)
#define SDO1_PIN        3
#define SDO1_RPR        (RPA1R)
#endif
#else
#define SDO1_TRIS       (PRODL)
#define SDO1_ANSEL      (PRODL)
#define SDO1_PIN        0
#define SDO1_RPR        (PRODL)
#endif

#ifdef SS1_PHY_PIN
#if SS1_PHY_PIN==2
// pin 2 is !SS1 - LRCIN - RA0
#define SS1_TRIS        (TRISAbits.TRISA0)
#define SS1_ANSEL       (ANSELAbits.ANSA0)
#define SS1_PIN         3
#define SS1_RPR         (RPA0R)
#endif
#else
#define SS1_TRIS        (PRODL)
#define SS1_ANSEL       (PRODL)
#define SS1_PIN         0
#define SS1_RPR         (PRODL)
#endif

#ifdef REFCLKO_PHY_PIN
#if REFCLKO_PHY_PIN==6
// pin 6 is REFCLKO1 - MCLK - B2
#define REFCLK_TRIS     (TRISBbits.TRISB2)
#define REFCLK_ANSEL    (ANSELBbits.ANSB2)
#define REFCLK_PIN      7
#define REFCLK_RPR      (RPB2R)
#endif
#else
#define REFCLK_TRIS     (PRODL)
#define REFCLK_ANSEL    (PRODL)
#define REFCLK_PIN      7
#define REFCLK_RPR      (PRODL)
#endif

#if defined(USE_USB)
// in this case a 16mhz crystal must be fitted to Q2 between pins 9 and 10
//#warning USE USB defined
#define self_power          0
//#define USB_SUPPORT_DEVICE 0
#endif

// define LED_AWAKE
#if U5_OPTION == U5_RS485
#define LED_AWAKE_IO     (LATAbits.LATA0)
#define LED_AWAKE_TRIS   (TRISAbits.TRISA0)
#define LED_AWAKE_ANSEL  (ANSELAbits.ANSA0)
#define LED_AWAKE_PORT   (PORTAbits.RA0)
#else
#define LED_AWAKE_IO      (PRODL)
#define LED_AWAKE_TRIS    (PRODL)
#define LED_AWAKE_ANSEL   (PRODL)
#define LED_AWAKE_PORT    (PRODL)
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* HARDWAREPROFILE_1_16_H */

