/* 
 * File:   CAccumulator.h
 * Author: jules
 *
 * Created on 31 December 2016, 13:38
 */

#ifndef CACCUMULATOR_H
#define	CACCUMULATOR_H

#include <stdint.h>

class CAccumulator {
public:
    CAccumulator();
    CAccumulator(const CAccumulator& orig);
    virtual ~CAccumulator();
    void Add(int32_t nValue);
    void Add(double dValue);
    void Reset();
    int16_t Mean();
    int16_t Mean(double dFactor);
    int16_t Min();
    int16_t Max();
    uint32_t RMS();
    uint32_t RMS(double dFactor);
    uint32_t Count();
private:
    int16_t m_nMin;
    int16_t m_nMaximum;
    double m_dSquared;
    double m_dTotal;
    uint32_t m_nCount;
};

#endif	/* CACCUMULATOR_H */

