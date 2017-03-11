#include "PowerMeter.h"
#include "hardwareprofile.h"
#include "CADC.h"

#define NSAMPLES 15

extern "C"
{
#define THIS_IS_STACK_APPLICATION
//#define __TCP_C
#include "TCPIP/TCPIP.h"
#include "/DEV/SmallBoards/include/packet.h"
typedef long time_t;
#define NO_SERVERS 0
#include "/DEV/HomeAutomation/include/logpacket.h"
};
#include "GenericTypeDefs.h"
#include "Compiler.h"
//#include "/DEV/HomeAutomation/include/machine.h"
#include "CDetailReadings.h"
#include "CAccumulator.h"

APP_CONFIG AppConfig;

BYTE GetBoardID()
{
    return SWITCH_NO;
}
void InitialiseBoard()
{
    //
    //  Allow Peripheral pin reassignment during startup
    //  This seems to be necessary to set up UART1 at least TX1 on pin 11
    //  RX1 pin 12 not proven.
    //
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    CFGCONbits.IOLOCK = 0;   // Allow configuration to be set
    //
    //  Oscillator setup - set to 40Mhz
    //
    OSCCONbits.SOSCEN = 0;   // Disable secondary oscillator
    OSCCONbits.CLKLOCK = 0;  // Unlock clock to set up oscillator
    OSCCONbits.FRCDIV = 1;   // Divide by 2 to get in range 4 - 5 mhz
    OSCCONbits.PLLMULT = 5;  // Multiply by 20 to get 80mhz
    OSCCONbits.PLLODIV = 1;  // divide by 2 to get 40Mhz
    OSCCONbits.NOSC = 1;     // FRC via FRCPLL
    OSCCONbits.UFRCEN = 1;   // Use FRC as USB clock
    OSCCONbits.OSWEN = 1;    // Initiate oscillator switch
    while(OSCCONbits.OSWEN);  // wait for it to complete
//    while(OSCCONbits.COSC != 1); // wait for new oscillator
    while(!OSCCONbits.SLOCK);
    while(!OSCCONbits.PBDIVRDY);
    // so peripheral clock is 20Mhz this gives a more accurate 19.2k baud
    // than the default 5Mhz
    // by default PBDIV is 2 - can leave it there
    // wait for ready before setting bits
    OSCCONbits.PBDIV = 1;
    // do we need to wait for USB lock?
    // yes - but need to use primary oscillator for USB.
    OSCCONbits.CLKLOCK = 1;  // Now we have set up the oscillator leave it
    REFOCON = 0;
    REFOCONbits.RODIV = 1; // divide by 2
    REFOCONbits.ON = 1;
    REFOCONbits.ACTIVE = 1;
    INTEnableSystemMultiVectoredInt();
#if defined(USE_ETHERNET)
// 4        16  INT0 active low
#if defined(INT0_TRIS)
    INT0_TRIS = 1;
    INT0_ANSEL  = 0;
// Set INT0EP to interrupt on falling edge (0)
    INTCONbits.INT0EP = 0;
#endif
// 6 SO     24  SDI2 (3)
    ENC_SDI_TRIS = 1;
    ENC_SDI_ANSEL = 0;
    SDI2R = ENC_SDI_PIN;
// 7 SI     17  SDO2 (4)
    ENC_SDO_TRIS = 0;
    ENC_SDO_ANSEL = 0;
    ENC_SDO_RPR = ENC_SDO_PIN;
// 8        26  S1111CK2
    ENC_SCK_TRIS = 0;
    ENC_SCK_ANSEL = 0;
// 9        18  CS
    ENC_CS_TRIS = 0;
    ENC_CS_ANSEL = 0;
//    ENC_CS_RPR = ENC_CS_PIN;
    memset(&AppConfig, 0, sizeof(AppConfig));
    AppConfig.MyIPAddr.v[0] = 192;
    AppConfig.MyIPAddr.v[1] = 168;
    AppConfig.MyIPAddr.v[2] = 1;
    AppConfig.MyIPAddr.v[3] = MY_IP_LAST;
    AppConfig.MyMask.v[0] = 255;
    AppConfig.MyMask.v[1] = 255;
    AppConfig.MyMask.v[2] = 255;
    AppConfig.MyMask.v[3] = 0;
    AppConfig.DefaultIPAddr = AppConfig.MyIPAddr;
    AppConfig.DefaultMask = AppConfig.MyMask;
    AppConfig.MyMACAddr.v[0] = MY_DEFAULT_MAC_BYTE1;
    AppConfig.MyMACAddr.v[1] = MY_DEFAULT_MAC_BYTE2;
    AppConfig.MyMACAddr.v[2] = MY_DEFAULT_MAC_BYTE3;
    AppConfig.MyMACAddr.v[3] = MY_DEFAULT_MAC_BYTE4;
    AppConfig.MyMACAddr.v[4] = MY_DEFAULT_MAC_BYTE5;
    AppConfig.MyMACAddr.v[5] = MY_IP_LAST;
    AppConfig.MyGateway = AppConfig.MyIPAddr;
    AppConfig.MyGateway.v[3] = 254;
    AppConfig.PrimaryDNSServer = AppConfig.MyGateway;

    TickInit();
    StackInit();
    SetLEDConfig(0x3212);
#else
    TickInit();
#endif
    VOLTAGE_TRIS = 1;
    VOLTAGE_ANSEL = 1;
    CURRENT_TRIS = 1;
    CURRENT_ANSEL = 1;

    CFGCONbits.IOLOCK = 1;   // Freeze configuration
}
unsigned char g_Serial = 0;
void SendUDPPort(int nPort, BYTE* pData, int len)
{
    // it appears that leaving socket open for a long time
    // remote MAC address gets overwritten causing writes to fail.
    // overwriting address looks like source of data read.
    // Opening socket is not expensive, so do this as close as possible 
    // to writing data.
    UDP_SOCKET hUDP = UDPOpenEx(0,UDP_OPEN_SERVER,nPort,nPort);
    if ( UDPIsOpened(hUDP))
    {
        WORD wMax = UDPIsPutReady(hUDP);
        if ( wMax >= len )
        {
            // this might not be able to write a whole packet
            int nWritten = UDPPutArray(pData, len);
            if ( nWritten != len )
            {
                // couldn't write it all
            }
            UDPFlush();
        }
        UDPClose(hUDP);
    }
}
void SendUDPPacket(PACKET* pPacket)
{
    PIPEHDR PH;
    PH.m_Type = PRT_PACKET;
    PH.m_Len = sizeof(PACKET);
    int l = sizeof(PACKET) + sizeof(PIPEHDR);
    pPacket->Serial = g_Serial;
    g_Serial++;
    char p[l];
    memcpy(p, &PH, sizeof(PIPEHDR));
    memcpy(p+sizeof(PIPEHDR), pPacket, sizeof(PACKET));
    SendUDPPort(HA_UDPPORT, (BYTE*)p, l);
    SendUDPPort(HA_LOGPORT, (BYTE*)p, l);
}
uint32_t IntSqrt(uint32_t d)
{
    uint32_t  op  = d;
    // what if d is > long
    uint32_t res = 0;
    uint32_t one = 1uL << 30; // The second-to-top bit is set: 
    //use 1u << 14 for uint16_t type; use 1uL<<30 for uint32_t type

    // "one" starts at the highest power of four
    // <= than the argument.
    while (one > op)
    {
        one >>= 2;
    }

    while (one != 0)
    {
        if (op >= res + one)
        {
            op = op - (res + one);
            res = res +  2 * one;
        }
        res >>= 1;
        one >>= 2;
    }
    return res;
}
uint16_t results[16];
int main(int argc, char** argv)
{
    InitialiseBoard();
    ARPAnnounce();
    
    int MilliTicks = TICKS_PER_SECOND / 1000;
    DWORD dwMilliTick = TickGet() + MilliTicks;
    DWORD dwSecondTick = TickGet() + TICKS_PER_SECOND;

    PACKET Packet;
    memset(&Packet, 0, sizeof(PACKET));
    Packet.State = PACKET_COMPLETE;
    Packet.Command = 'S';
    Packet.Source = GetBoardID();
    BYTE nPacketState = 0;
    int nSamples = NSAMPLES;
    CADC adc;
    // Calibrate voltage and current central values
    int16_t nMeanVoltage = 512;
    int16_t nMeanCurrent = 512;
    // loop for a second getting average of current and voltage readings.
    nMeanVoltage = adc.Average(VOLTAGE_PIN, CURRENT_PIN, 0, TICKS_PER_SECOND);
    nMeanCurrent = adc.Average(VOLTAGE_PIN, CURRENT_PIN, 1, TICKS_PER_SECOND);
    // Now accumulate RMS Voltage as measured voltage from transformer is not trusted

    double dRMSVoltage = 0.0;
    CAccumulator VoltageAccumulator;
    adc.InitialiseSingle(VOLTAGE_PIN, nSamples);
    adc.Start();
    dwSecondTick = TickGet() + TICKS_PER_SECOND;
    
    while ( TickGet() < dwSecondTick )
    {
        ClearWDT();
#if defined(USE_ETHERNET)
        StackTask();
        StackApplications();
#endif
        if ( adc.Service(results))
        {
            uint8_t n;
            for( n = 0; n < nSamples; n++)
            {
                VoltageAccumulator.Add( (int32_t)results[n] - nMeanVoltage);
            }
            adc.Start();
        }
    }
    adc.Stop();
    if ( VoltageAccumulator.Count() > 0)
    {
        dRMSVoltage = (double)VoltageAccumulator.RMS(100.0)/100.0;
    }
    Packet.Pin = STATUS_PIN_RAW_VOLTAGE;
    Packet.Reading = (uint16_t)dRMSVoltage;
    SendUDPPacket(&Packet);
    
    // Recalculate means as these seem to be higher later in the run
//    nMeanVoltage = adc.Average(VOLTAGE_PIN, CURRENT_PIN, 0, TICKS_PER_SECOND);
//    nMeanCurrent = adc.Average(CURRENT_PIN, CURRENT_PIN, 1, TICKS_PER_SECOND);
    // Main loop
    VoltageAccumulator.Reset();

    CAccumulator CurrentAccumulator;
//    double dVoltageFactor = 325.0 / (365.33 / 1.178);
//    double dVoltageFactor = 240.0 / dRMSVoltage; 
    double dVoltageFactor = 243.7/326.0;
    // we assume a mains voltage here from measurements at wall socket.
    // When charging V is between 242 and 247
    // later it drops to circa 240.
//    double dCurrentFactor = 141.4 / (438.34 / 1.414);
    double dCurrentFactor = 330.0 / 1024.0; // 100 * VRef / 1024 assuming 1V to 100Amps
    CAccumulator PowerAccumulator;
//    CDetailReadings PowerDetail;
    nSamples = 16;
    adc.InitialiseALT(VOLTAGE_PIN, CURRENT_PIN, nSamples);
    adc.Start();
    bool bSampled = false;
    dwSecondTick = TickGet() + TICKS_PER_SECOND;
    CAccumulator MeanCurrent;
    CAccumulator MeanVoltage;
    bool bFirst = true;
    while(1)
    {
        ClearWDT();
#if defined(USE_ETHERNET)
        StackTask();
        StackApplications();
#endif
        if ( adc.Service(results))
        {
            adc.Start();
            bSampled = true;
            uint8_t n;
            for( n = 0; n < 15; n += 2)
            {
                int16_t nVoltage = ((int16_t)results[n] - nMeanVoltage);
                double dVoltage = nVoltage * dVoltageFactor;
                VoltageAccumulator.Add(dVoltage);
                MeanVoltage.Add((int32_t)results[n]);
            }
            for( n = 1; n < 15; n+= 2)
            {
                int32_t nVoltage = ((int32_t)((results[n+1] + results[n-1])>>1) - nMeanVoltage);
                double dVoltage = nVoltage * dVoltageFactor;
                int32_t nCurrent = (int32_t)(results[n] - nMeanCurrent);
                MeanCurrent.Add((int32_t)results[n]);
                double dCurrent = nCurrent * dCurrentFactor;
                CurrentAccumulator.Add(dCurrent);

                double dPower = dCurrent * dVoltage;
                PowerAccumulator.Add(dPower);

//                PowerDetail.Add((long)dPower, (long)(dVoltage * 1000), (long)(dCurrent * 1000));
            }
        }
        // Average readings over a second and send summary packet
        if ( TickGet() > dwSecondTick && bSampled)
        {
            nMeanCurrent = MeanCurrent.Mean();
            MeanCurrent.Reset();
            nMeanVoltage = MeanVoltage.Mean();
            MeanVoltage.Reset();
            switch(nPacketState)
            {
            case 0:
                Packet.Pin = STATUS_PIN_MAINS_POWER;
                Packet.Reading = (int16_t)PowerAccumulator.Mean();
                PowerAccumulator.Reset();
                break;
            case 1:
                Packet.Pin = STATUS_PIN_MAINS_CURRENT;
                Packet.Reading = (uint16_t)CurrentAccumulator.RMS(10.0);
                CurrentAccumulator.Reset();
                break;
            case 2:
                Packet.Pin = STATUS_PIN_MAINS_VOLTAGE;
                Packet.Reading = (uint16_t)VoltageAccumulator.RMS(10.0);
                VoltageAccumulator.Reset();
                break;        
            }
            if ( bFirst )
            {
                // Discard the first reading because it is shown to be inaccurate.
                PowerAccumulator.Reset();
                CurrentAccumulator.Reset();
                VoltageAccumulator.Reset();
                bFirst = false;
            }
            else
            {
                SendUDPPacket(&Packet);
                //SendUDPPacket(hLogSocket, &Packet);
                nPacketState++;
                if ( nPacketState > 2)
                {
                    nPacketState = 0;
                }
            }
            DWORD dwTick = TickGet();
            dwSecondTick = TickGet() + TICKS_PER_SECOND;
        }
    }
    return 0;
}
