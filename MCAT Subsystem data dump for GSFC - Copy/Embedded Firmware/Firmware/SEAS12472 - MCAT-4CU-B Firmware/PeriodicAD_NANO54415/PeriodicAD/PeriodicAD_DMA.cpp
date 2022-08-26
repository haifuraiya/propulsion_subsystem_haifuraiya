/**************************************************************************//**
 *
 * Copyright 1998-2013 NetBurner, Inc.  ALL RIGHTS RESERVED
 *   Permission is hereby granted to purchasers of NetBurner Hardware
 *   to use or modify this computer program for any use as long as the
 *   resultant program is only executed on NetBurner provided hardware.
 *
 *   No other rights to use this program or it's derivatives in part or
 *   in whole are granted.
 *
 *   It may be possible to license this or other NetBurner software for
 *   use on non-NetBurner Hardware.
 *   Please contact sales@Netburner.com for more information.
 *
 *   NetBurner makes no representation or warranties
 *   with respect to the performance of this computer program, and
 *   specifically disclaims any responsibility for any damages,
 *   special or consequential, connected with the use of this program.
 *
 *---------------------------------------------------------------------
 * NetBurner, Inc.
 * 5405 Morehouse Drive
 * San Diego, California 92121
 *
 * information available at:  http://www.netburner.com
 * E-Mail info@netburner.com
 *
 * Support is available: E-Mail support@netburner.com
 *
 *****************************************************************************/

#include <basictypes.h>
#include <constants.h>
#include <ucos.h>
#include <sim.h>
#include <dspi.h>
#include <cfinter.h>
#include <intcdefs.h>
#include <HiResTimer.h>
#include "PeriodicAD.h"
#include "PeriodicAD_DMA.h"

static bool dmaInited = false;
static bool timerRunning = false;
static bool timerSet = false;
static HiResTimer *pTimer = NULL;
static void (*interruptFunction)(void *, void *);
static int timerChannel = 0;
static void *bufferPtrs[3];
static int bufferFrontFilled;

// Initialize the DMA channel for the ADC reads
int initADC_DMA(int channel, int timerNum)
{ 
    volatile edma_tcdstruct &tmrTcd = sim2.edma.tcd[DMA_CH_DTER_0 + timerNum];
    dmaInited = false;

    // If the timer is running, abort
    if (timerRunning)
        return 0;
    // get the HiResTimer associated with the timer we want; make sure it's not in use
    pTimer = HiResTimer::getHiResTimer(timerNum);

    if ( ( channel < 0 ) || ( channel > 7 ) 
            || (pTimer == NULL) || ( timerNum < 0 ) 
            || ( timerNum > 3 ) ) 
        return 0;
    timerChannel = timerNum;

    // Leave the group priorities alone, but clear all others
    sim2.edma.cr &= CR_CLEAR_NON_GRP_PRIO;

    // set the start address for the DMA transfer
    tmrTcd.saddr  = (vudword)&sim2.adc.rslt[channel];
    tmrTcd.attr   = TCD_ATTR_16BIT_TRANS;
    tmrTcd.soff   = 0; // source offset; this must be 0 
    tmrTcd.nbytes = 2; // number of bytes transfered per request
    tmrTcd.slast  = 0; // source offset applied at completion of all requests, before resetting
    tmrTcd.doff   = 2; // destination offset, how much to move dest addr after each request

    tmrTcd.csr    = 0x8006; // enable both halfway and complete interrupts
    dmaInited = true;
    return 1;
}

// stop the DMA Timer
inline void stopTimer(volatile timerstruct *simTimer)
{
    simTimer->tmr &= ~(0x06); // stop the timer
}

// stop the DMA Timer and clear its counts
inline void stopClearTimer(volatile timerstruct *simTimer)
{
    simTimer->tmr &= ~(0x06); // stop the timer
    simTimer->tcn = 0x0; // clear the timer count
    simTimer->ter = 0x3; // clear the event register
}

/*
 * Starts the selected DMA timer. 
 */
inline void startTimer(volatile timerstruct *simTimer)
{
    // Setting the CLK bits to 01 on the DTMR register, starting the timer
    simTimer->tmr |= 0x2;
};

INTERRUPT( ADC_DMA_ISR0, 0x2700 )
{
    // clear the reference event
    sim2.edma.cint = DMA_CH_DTER_0; 
    sim2.timer[timerChannel].ter = 0x2; // clear any timer event flag
    bufferFrontFilled = (bufferFrontFilled + 1) & 0x1; // toggle state
    if (interruptFunction)
        interruptFunction(bufferPtrs[bufferFrontFilled], 
                bufferPtrs[bufferFrontFilled+1]);
}

INTERRUPT( ADC_DMA_ISR1, 0x2700 )
{
    // clear the reference event
    sim2.edma.cint = DMA_CH_DTER_1; 
    sim2.timer[timerChannel].ter = 0x2;
    bufferFrontFilled = (bufferFrontFilled + 1) & 0x1;
    if (interruptFunction)
        interruptFunction(bufferPtrs[bufferFrontFilled], 
                bufferPtrs[bufferFrontFilled+1]);
}

INTERRUPT( ADC_DMA_ISR2, 0x2700 )
{
    // clear the reference event
    sim2.edma.cint = DMA_CH_DTER_2; 
    sim2.timer[timerChannel].ter = 0x2;
    bufferFrontFilled = (bufferFrontFilled + 1) & 0x1;
    if (interruptFunction)
        interruptFunction(bufferPtrs[bufferFrontFilled], 
                bufferPtrs[bufferFrontFilled+1]);
}

INTERRUPT( ADC_DMA_ISR3, 0x2700 )
{
    // clear the reference event
    sim2.edma.cint = DMA_CH_DTER_3; 
    sim2.timer[timerChannel].ter = 0x2;
    bufferFrontFilled = (bufferFrontFilled + 1) & 0x1;
    if (interruptFunction)
        interruptFunction(bufferPtrs[bufferFrontFilled], 
                bufferPtrs[bufferFrontFilled+1]);
}

// Set the DMA timer's delay in us
static double setTimerDelayus(uint32_t period)
{
    // Calculate the prescaler and the reference ticks for the timer
    DWORD ReferenceTicks = 0xFFFFFFFF;
    DWORD prescaler;
    double InterruptTime = (double)period * 10000000;
    if (period != 0)
    {
        if (period > 1000000)
        {
            prescaler = (period >> 19 ) * NB_CPU_CLK / 0x00001FFF;
        }
        else
        {
            prescaler = (period * NB_CPU_CLK) / 0xFFFFFFFF;
        }
        InterruptTime /= (double) (prescaler + 1.0);
        ReferenceTicks = (InterruptTime * (double) NB_CPU_CLK);
    }


    sim2.timer[timerChannel].txmr = 0x80; // set the DMAEN bit and clear the others
    sim2.timer[timerChannel].tmr = 0x19 | ((WORD) prescaler << 8); // enable DMA requests, restart on trigger, and enable timer and prescaler.
    sim2.timer[timerChannel].trr = ReferenceTicks; // set the delay cycles

    timerSet = true;
    return (double)ReferenceTicks / (double)NB_CPU_CLK * (double)prescaler;
}

// Set the timer to delay in us
double setSamplePeriod(uint32_t period)
{
    stopClearTimer(&sim2.timer[timerChannel]);
    return setTimerDelayus(period);
}

// Set the timer to trigger at a specific frequency (in Hz)
double setSampleFreq(uint32_t freq)
{
    // MCF5441X RM 39.2
    stopClearTimer(&sim2.timer[timerChannel]);
    sim2.timer[timerChannel].txmr = 0x80;
    sim2.timer[timerChannel].tmr = 0x19;
    sim2.timer[timerChannel].trr = NB_CPU_CLK / freq + ((NB_CPU_CLK % freq) >= (freq >> 1));
    timerSet = true;
    return (double)NB_CPU_CLK / (double)sim2.timer[timerChannel].trr;
}

// Start the DMA Timer, transfers, and ISR
int startADC_DMA(void *buffer, uint32_t bufferSize, void (*isrFunc)(void *, void *))
{
    volatile timerstruct *simTimer = NULL;

    // Is the timer already running?
    if (timerRunning) 
        return DMA_ERR_TMRRUNNING;
    // Are the timer delay values set?
    if (!timerSet)
        return DMA_ERR_TMRNOTSET;

    switch (timerChannel)
    {
        case 0:
            SETUP_DMA8_ISR( ADC_DMA_ISR0, 2 );
            simTimer = &sim2.timer[0];
            break;
        case 1:
            SETUP_DMA9_ISR( ADC_DMA_ISR1, 2 );
            simTimer = &sim2.timer[1];
            break;
        case 2:
            SETUP_DMA10_ISR( ADC_DMA_ISR2, 2 );
            simTimer = &sim2.timer[2];
            break;
        case 3:
            SETUP_DMA11_ISR( ADC_DMA_ISR3, 2 );
            simTimer = &sim2.timer[3];
            break;
        default:
            return DMA_ERR_CHNOTSET;
    }

    interruptFunction = isrFunc;
    timerRunning = true;
    bufferFrontFilled = 0;

    volatile edma_tcdstruct &tmrTcd = sim2.edma.tcd[8+timerChannel];

    tmrTcd.daddr = (DWORD)buffer; // set the destination address for the DMA transfer
    // set the destination offset upon completion of DMA transfer count
    //   Note: this is a negative value equal to the amount of buffer space used, implementing
    //          a ring buffer
    tmrTcd.dlast_sga = -1 * (bufferSize & 0xFFFFFFF7); 
    tmrTcd.biter = tmrTcd.citer = bufferSize >> 1; // set transfer counts 
    sim2.edma.serq = 8 + timerChannel; // Enable hardware requests on the channel

    // find ptrs to transfer start and end locations
    bufferPtrs[0] = buffer;
    bufferPtrs[1] = (void *)((DWORD)buffer + bufferSize >> 1);
    bufferPtrs[2] = (void *)((DWORD)buffer + ((bufferSize >> 1) * 2));
    
    // stop and restart the timer.
    stopClearTimer(simTimer);
    startTimer(simTimer);

    return DMA_ERR_NOERR;
}

// Stop the DMA Timer and ADC
void stopADC_DMA()
{
    switch (timerChannel)
    {
        case 0:
            stopTimer(&sim2.timer[0]);
            break;
        case 1:
            stopTimer(&sim2.timer[1]);
            break;
        case 2:
            stopTimer(&sim2.timer[2]);
            break;
        case 3:
            stopTimer(&sim2.timer[3]);
            break;
        default:
            return;
    }
    // Disable hardware requests on the dma channel
    sim2.edma.cerq = 8 + timerChannel;
    StopAD(); // Stop the AD converter
    timerRunning = false;
    interruptFunction = NULL;
    pTimer->releaseTimer(); // Release the HiResTimer associated with the DMA Timer
}
