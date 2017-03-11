/* 
 * File:   CDetailReadings.h
 * Author: jules
 *
 * Created on 31 December 2016, 13:18
 */

#ifndef CDETAILREADINGS_H
#define	CDETAILREADINGS_H

#define MAX_READINGS 512

typedef struct tagREADING
{
    long m_nVoltage;    // signed 32 bit value scaled by 1000 - expected range -325000 to +325000
    long m_nCurrent;    // signed 32 bit value in milliamps - expected range -100000 to + 100000
    long m_nPower;      // signed 32 bit value in watts
}READING;
typedef struct tagPOWERPACKET
{
    int m_nReadings;
    READING m_Readings[MAX_READINGS];
}POWERPACKET;

class CDetailReadings {
public:
    CDetailReadings();
    CDetailReadings(const CDetailReadings& orig);
    virtual ~CDetailReadings();
    void Add(long nPower, long nVoltage, long nCurrent);
private:
    POWERPACKET m_PowerPacket;
};

#endif	/* CDETAILREADINGS_H */

