/* 
 * File:   CDetailReadings.cpp
 * Author: jules
 * 
 * Created on 31 December 2016, 13:18
 */
#include "GenericTypeDefs.h"
#include "Compiler.h"

#include "CDetailReadings.h"

CDetailReadings::CDetailReadings() 
{
    memset(&m_PowerPacket,0, sizeof(m_PowerPacket));
}

CDetailReadings::CDetailReadings(const CDetailReadings& orig) 
{
}

CDetailReadings::~CDetailReadings() 
{
}
void CDetailReadings::Add(long nPower, long nVoltage, long nCurrent)
{
    READING* pReading = m_PowerPacket.m_Readings + m_PowerPacket.m_nReadings;
    pReading->m_nPower = nPower;
    pReading->m_nCurrent = nCurrent;
    pReading->m_nVoltage = nVoltage;
    m_PowerPacket.m_nReadings++;
    if ( m_PowerPacket.m_nReadings >= MAX_READINGS )
    {
        // TODO Write out packet
        m_PowerPacket.m_nReadings = 0;
    }
}
