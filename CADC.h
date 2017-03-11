/* 
 * File:   CADC.h
 * Author: jules
 *
 * Created on 30 December 2016, 13:33
 */

#ifndef CADC_H
#define	CADC_H

#include <stdint.h>
class CADC {
protected:
    uint8_t m_nSamples;
    void Initialise(uint8_t nSamples);
public:
    CADC();
    CADC(const CADC& orig);
    virtual ~CADC();
    void Start();
    void Stop();
    bool Service(uint16_t* pBuf);
    void InitialiseALT(uint8_t ch0, uint8_t ch1, uint8_t nSamples);
    void InitialiseSingle(uint8_t ch, uint8_t nSamples);
    uint16_t Average(uint8_t ch, uint32_t nTicks);
    uint16_t Average(uint8_t ch0, uint8_t ch1, uint8_t nOffset, uint32_t nTicks);
private:
};
#endif	/* CADC_H */

