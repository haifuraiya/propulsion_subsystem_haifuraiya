/******************************************************************************
 *
 * Copyright 1998-2012 NetBurner, Inc.  ALL RIGHTS RESERVED
 *   Permission is hereby granted to purchasers of NetBurner Hardware
 *   to use or modify this computer program for any use as long as the
 *   resultant program is only executed on NetBurner provided hardware.
 *
 *   No other rights to use this program or it's derivitives in part or
 *   in whole are granted.
 *
 *   It may be possible to license this or other NetBurner software for
 *   use on non NetBurner Hardware. Please contact Licensing@Netburner.com
 *   for more information.
 *
 *   NetBurner makes no representation or warranties with respect to the
 *   performance of this computer program, and specifically disclaims any
 *   responsibility for any damages, special or consequential, connected
 *   with the use of this program.
 *
 *   NetBurner, Inc
 *   5405 Morehouse Drive
 *   San Diego Ca, 92121
 *   http://www.netburner.com
 *
 *****************************************************************************/
/******************************************************************************
 *
 * PeriodicAD - DMA Driven, periodic sampling Analog to Digital example
 *   
 *  This example shows how to setup a periodic sampling Analog to Digital 
 *  conversion with buffering. It uses the onboard Analog to Digital Converter
 *  in loop mode to continuously sample. It then utilizes the DMA Timer to 
 *  trigger a dma transfer from the selected ADC channel, to the next location 
 *  in the sample buffer. The example includes interrupt triggers at a half-full
 *  and completely full buffer. Finally, the specific result of the application
 *  is to sample for some period of time, record the data to an output .wav file,
 *  and repeat.  
 *
 *****************************************************************************/
#include "predef.h"
#include <startnet.h>
#include <stdio.h>
#include <sim5441X.h>           /*on-chip register definitions*/
#include <ucos.h>
#include <utils.h>
#include <serial.h>
#include <iosys.h>
#include <sim.h>
#include <autoupdate.h>
#include <counters.h>
#include <ethernet.h>
#include <dhcpclient.h>
#include <HiResTimer.h>
#include "PeriodicAD.h"
#include "PeriodicAD_DMA.h"
#include "wavWriter.h"
#include "FileSystemUtils.h"

#define BUFFERSIZE  2048
#define DATABUFFERSIZE  0x800000
#define HALFBSIZE   BUFFERSIZE/2
#define MAJORSAMPLECOUNT 128

// valid channels are 0-3
#define ADC_CHANNEL 0
#define SAMPLE_FREQ 8000
#define DMA_TIMER   0

BYTE sampleBuffer[BUFFERSIZE] FAST_USER_VAR;
BYTE dataBuffer[DATABUFFERSIZE];
OS_SEM ADC_DMA_SEM;
bool frontFilled = false;
HiResTimer *timer = NULL;

extern "C"
{
   void UserMain( void *pd );
};

extern unsigned long CPU_CLOCK;

const char *AppName = "MOD5441X Buffered A/D Example";

void dmaTriggerFunc( void *start, void *end )
{
    frontFilled = !frontFilled;
    OSSemPost(&ADC_DMA_SEM);
}

void static openStdIO_IRQMode()
{
    int fds0 = SimpleOpenSerial(0, 115200);

    ReplaceStdio(0, fds0);
    ReplaceStdio(1, fds0);
    ReplaceStdio(2, fds0);
}

void static setUpFlash()
{
    f_enterFS();
#ifdef MOD5441X
    int drv = OpenOffBoardFlash();
    int rv = f_chdrive( drv );
    if (rv == F_NO_ERROR)
    {
        printf("External Flash opened.\r\n");
    }
    else
    {
        printf("FAILED TO OPEN EXTERNAL FLASH.\r\n");
    }
#elif defined NANO54415
    InitExtFlash();
#endif
}

void static initializeADC( int channel, uint32_t freq, int timerNum )
{
    InitSingleEndAD();
    StartADLoop();
    initADC_DMA(channel, timerNum);
    setSampleFreq(freq);
}

void UserMain(void *pd)
{

    OSChangePrio(MAIN_PRIO);

    InitializeStack();
    EnableAutoUpdate();
    GetDHCPAddressIfNecessary();
    openStdIO_IRQMode();

    // Initialize the A/D DMA sampling semaphore
    OSSemInit(&ADC_DMA_SEM, 0);

    printf("Starting Application: %s\r\n", AppName);

    // set up offboard flash and filesystem
    setUpFlash();

    // Initialize the ADC for sampling on channel 0, and sample 8000 Hz, 
    // triggering sample with DMA Timer 0
    initializeADC( ADC_CHANNEL, SAMPLE_FREQ, DMA_TIMER );

    int wavFd, fileIndex;
    char fn[15];
    fileIndex = 0;
    int bytesWritten = 0;
    while (1)
    {
        sprintf(fn, "adc8k%d.wav", fileIndex);
        printf("Starting log: %s\r\n", fn);

        // Start sampling, transferring the samples into 'sampleBuffer' of size 'BUFFERSIZE'
        //   When the DMA engine reaches halfway or fully fills the buffer
        //   it will trigger 'dmaTriggerFunc'
        startADC_DMA( sampleBuffer, BUFFERSIZE, dmaTriggerFunc );

        bytesWritten = 0;
        for (int i = 0; i < MAJORSAMPLECOUNT; i++)
        {
            // Wait for half a buffer worth of samples
            OSSemPend(&ADC_DMA_SEM, 0);
            putchar('.');
            // then transfer them to a larger, non-SRAM buffer.
            //   This can be anything here; this is the point where you will process 
            //   half a buffer's worth of samples. This example simply stores them 
            //   for later.
            memcpy( dataBuffer + i * HALFBSIZE, 
                    (sampleBuffer + (frontFilled ? 0 : HALFBSIZE)), 
                    HALFBSIZE );
            bytesWritten += HALFBSIZE;
        }
        stopADC_DMA(); // stop the DMA timer, channel, and ADC

        // Write the samples out to a wav file
        //  WARNING: using the wavWriter uses a lot of stack space, as it 
        //  creates a swap buffer (default 512 bytes) for doing endian 
        //  swapping for file writes
        // Opening a file with the wavWriter returns a file descriptor 
        //  for a write-only file. It also expects the data in exactly the form
        //  and value of the ADC result register, with 0 offset (therefore unsigned).
        wavFd = openNewWav( fn, 1, 8000 );
        if (wavFd)
        {
            write(wavFd, (const char *)dataBuffer, bytesWritten);
            close(wavFd);
            printf("\r\nWrote %d bytes to disk, in file %s.\r\n", 
                    MAJORSAMPLECOUNT*HALFBSIZE, fn);
            fileIndex = (fileIndex + 1) % 511;
        }
    }
}

