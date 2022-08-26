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

#define DMA_CH_DTER_0   8
#define DMA_CH_DTER_1   9
#define DMA_CH_DTER_2   10
#define DMA_CH_DTER_3   11

#define DMA_ERR_NOERR       0
#define DMA_ERR_CHNOTSET    1
#define DMA_ERR_TMRNOTSET   2
#define DMA_ERR_TMRRUNNING  3

// Initialize the dma timer to sample the ADC
int initADC_DMA(int channel = 0, int timerNum = 3);

// Set the sample period for the ADC (in us)
double setSamplePeriod(uint32_t period);

// Set the sample frequency (in Hz)
double setSampleFreq(uint32_t freq);

// Start logging the ADC using DMA. The period is in units of 1 us
int startADC_DMA(void *buffer, uint32_t bufferSize, void (*isrfunc)(void *, void *));

// Stop the DMA Timer and ADC
void stopADC_DMA();
