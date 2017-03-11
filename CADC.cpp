/* 
 * File:   CADC.cpp
 * Author: jules
 * 
 * Created on 30 December 2016, 13:33
 */

#include <lega-c/proc/p32mx250f128b.h>
#include "hardwareprofile.h"
#include "CADC.h"
extern "C"
{
#include "TCPIP/Tick.h"
};

CADC::CADC()
    : m_nSamples(0)
{
}

CADC::CADC(const CADC& orig) 
{
}

CADC::~CADC() 
{
}
void CADC::Initialise(uint8_t nSamples)
{
    m_nSamples = nSamples;
    // Initialise ADC
    AD1CON1CLR = 0x8000;    // disable ADC before configuration
    //AD1CON1 = 0x00E0;       // internal counter ends sampling and starts conversion (auto-convert), manual sample
//    AD1PCFG = 0xFFC0;       // All but AN0, AN1 are digital inputs not on PC32MX2
    AD1CON1bits.SIDL = 0;   // Continue operation in idle
    AD1CON1bits.FORM = 0;   // 16 bit integer result
    AD1CON1bits.SSRC = 0x7; // Internal counter ends sampling and starts converting
    AD1CON1bits.CLRASAM = 0; // Buffer contents overwritten
    AD1CON1bits.ASAM = 0;    // sampling begins when SaMp bit is set 
    AD1CON2 = 0;            // AD1CON2<15:13> set voltage reference to pins AVSS/AVDD
    AD1CON2bits.SMPI = nSamples - 1;   // 15 samples per interrupt
                             // This enables 8 voltage readings and 7 current readings
                             // average of pair of voltages should be contemporaneous with current
//    AD1CON3 = 0x0f01;       // TAD = 4*TPB, acquisition time = 15*TAD
    AD1CON3 = 0;
    AD1CON3bits.ADRC = 1;   // Use Peripheral bus derived clock
    AD1CON3bits.SAMC = 31; // Sample time 1 TAD (200ns)
    AD1CON3bits.ADCS = 2; // TAD = 4 * TPB (200ns)
    AD1CSSL = 0; // do not scan inputs
}
void CADC::InitialiseALT(uint8_t ch0, uint8_t ch1, uint8_t nSamples)
{
    Initialise(nSamples);
    AD1CON2bits.ALTS = 1;   // Alternate inputs between MUXA and MUXB
    AD1CHS = 0;
    AD1CHSbits.CH0SA = ch0;
    AD1CHSbits.CH0SB = ch1;
    AD1CON1bits.ADON = 1;
}
void CADC::InitialiseSingle(uint8_t ch, uint8_t nSamples)
{
    Initialise(nSamples);
    AD1CON2bits.ALTS = 0;   // Alternate inputs between MUXA and MUXB
    AD1CHS = 0;
    AD1CHSbits.CH0SA = ch;
    AD1CHSbits.CH0SB = 0;
    AD1CON1bits.ADON = 1;
}
void CADC::Start()
{
    AD1CON1bits.ASAM = 1;
    IFS0bits.AD1IF = 0;
}
void CADC::Stop()
{
    AD1CON1bits.ASAM = 0;
}
bool CADC::Service(uint16_t* pBuf)
{
    if ( IFS0bits.AD1IF)
    {
        AD1CON1bits.ASAM = 0;
        uint8_t n;
        volatile uint32_t* pADCBUF = &ADC1BUF0;
        // SFRs are align at 16 byte boundaries so need to add 4 to get correct alignment!
        // Others have also found this. Look at the addresses in the variables window to verify this.
        for( n = 0; n < m_nSamples; n++, pBuf++, pADCBUF+=4)
        {
            *pBuf = *pADCBUF;
        }
        // Clear interrupt
        IFS0bits.AD1IF = 0;
        return true;
    }
    return false;
}
uint16_t CADC::Average(uint8_t ch, uint32_t nTicks)
{
    uint32_t nTotal = 0;
    uint32_t nCount = 0;
    InitialiseSingle(ch, 16);
    uint32_t dwSecondTick = TickGet() + nTicks;
    Start();
    while ( TickGet() < dwSecondTick )
    {
        ClearWDT();
#if defined(USE_ETHERNET)
        StackTask();
        StackApplications();
#endif
        if ( IFS0bits.AD1IF)
        {
            AD1CON1bits.ASAM = 0;
            uint8_t n;
            volatile uint32_t* pADCBUF = &ADC1BUF0;
            // SFRs are align at 16 byte boundaries so need to add 4 to get correct alignment!
            // Others have also found this. Look at the addresses in the variables window to verify this.
            for( n = 0; n < 16; n++, pADCBUF+=4)
            {
                nTotal += *pADCBUF;
                nCount++;
            }
            // Clear interrupt
            IFS0bits.AD1IF = 0;
            Start();
        }
    }
    Stop();
    return nTotal / nCount;
 }
uint16_t CADC::Average(uint8_t ch0, uint8_t ch1, uint8_t nOffset, uint32_t nTicks)
{
    uint32_t nTotal = 0;
    uint32_t nCount = 0;
    InitialiseALT(ch0, ch1, 16);
    uint32_t dwSecondTick = TickGet() + nTicks;
    Start();
    while ( TickGet() < dwSecondTick )
    {
        ClearWDT();
#if defined(USE_ETHERNET)
        StackTask();
        StackApplications();
#endif
        if ( IFS0bits.AD1IF)
        {
            AD1CON1bits.ASAM = 0;
            uint8_t n;
            volatile uint32_t* pADCBUF = &ADC1BUF0;
            // SFRs are align at 16 byte boundaries so need to add 4 to get correct alignment!
            // Others have also found this. Look at the addresses in the variables window to verify this.
            for( n = nOffset; n < 7; n++, pADCBUF+=8)
            {
                nTotal += *pADCBUF;
                nCount++;
            }
            // Clear interrupt
            IFS0bits.AD1IF = 0;
            Start();
        }
    }
    Stop();
    return nTotal / nCount;
}
