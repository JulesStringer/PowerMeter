#include "compiler.h"

unsigned int __attribute__((nomips16)) INTDisableInterrupts(void)
{
    unsigned int status = 0;

    asm volatile("di    %0" : "=r"(status));

    return status;
}
unsigned int __attribute__((nomips16))  INTEnableInterrupts(void)
{
    unsigned int status = 0;

    asm volatile("ei    %0" : "=r"(status));

    return status;
}
void __attribute__ ((nomips16)) INTEnableSystemMultiVectoredInt(void)
{
    unsigned int val;

    // set the CP0 cause IV bit high
    asm volatile("mfc0   %0,$13" : "=r"(val));
    val |= 0x00800000;
    asm volatile("mtc0   %0,$13" : "+r"(val));

    INTCONSET = _INTCON_MVEC_MASK;

    // set the CP0 status IE bit high to turn on interrupts
    INTEnableInterrupts();

}
extern __inline__ int __attribute__((always_inline)) DmaSuspend(void)
{
    int suspSt;
    if(!(suspSt=DMACONbits.SUSPEND))
    {
        DMACONSET=_DMACON_SUSPEND_MASK;     // suspend
        while((DMACONbits.DMABUSY));    // wait to be actually suspended
    }
    return suspSt;
}
void __attribute__((noreturn)) SoftReset(void)
{
	int	intStat;
	int	dmaSusp;
	volatile int* p = &RSWRST;

	mSYSTEMUnlock(intStat, dmaSusp);
	RSWRSTSET=_RSWRST_SWRST_MASK;
	*p;

	while(1);
}
