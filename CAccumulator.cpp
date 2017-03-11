/* 
 * File:   CAccumulator.cpp
 * Author: jules
 * 
 * Created on 31 December 2016, 13:38
 */

#include "CAccumulator.h"

uint32_t IntSqrt(uint32_t d);

CAccumulator::CAccumulator() 
    : m_nMin(0)
    , m_nMaximum(0)
    , m_dSquared(0)
    , m_dTotal(0)
    , m_nCount(0)
{
    
}

CAccumulator::CAccumulator(const CAccumulator& orig) 
{
}

CAccumulator::~CAccumulator() 
{
}
void CAccumulator::Add(int32_t nValue)
{
    if ( m_nCount == 0 )
    {
        m_nMin = nValue;
        m_nMaximum = nValue;
    }
    else
    {
        if ( nValue < m_nMin )
        {
            m_nMin = nValue;
        }
        if ( nValue > m_nMaximum )
        {
            m_nMaximum = nValue;
        }
    }
    double dValue = nValue;
    m_dSquared += (dValue * dValue);
    m_dTotal += dValue;
    m_nCount++;
}
void CAccumulator::Add(double dValue)
{
    int32_t nValue = dValue;
    if ( m_nCount == 0 )
    {
        m_nMin = nValue;
        m_nMaximum = nValue;
    }
    else
    {
        if ( nValue < m_nMin )
        {
            m_nMin = nValue;
        }
        if ( nValue > m_nMaximum )
        {
            m_nMaximum = nValue;
        }
    }
    m_dSquared += (dValue * dValue);
    m_dTotal += dValue;
    m_nCount++;
}
void CAccumulator::Reset()
{
    m_nMin = 0;
    m_nMaximum = 0;
    m_dSquared = 0;
    m_dTotal = 0;
    m_nCount = 0;
}
int16_t CAccumulator::Mean()
{
    if ( m_nCount > 0 )
    {
        return (int16_t)(m_dTotal / m_nCount);
    }
    return 0;
}
int16_t CAccumulator::Mean(double dFactor)
{
    if ( m_nCount > 0 )
    {
        return (int16_t)((m_dTotal * dFactor) / m_nCount);
    }
    return 0;
}
int16_t CAccumulator::Min(){ return m_nMin;}
int16_t CAccumulator::Max(){ return m_nMaximum;}
uint32_t CAccumulator::RMS()
{
    if ( m_nCount > 0 )
    {
        return IntSqrt(m_dSquared / m_nCount);   
    }
    return 0;
}
uint32_t CAccumulator::RMS(double dFactor)
{
    if ( m_nCount > 0 )
    {
        return IntSqrt(m_dSquared * dFactor * dFactor / m_nCount);   
    }
    return 0;
}
uint32_t CAccumulator::Count(){return m_nCount;}
