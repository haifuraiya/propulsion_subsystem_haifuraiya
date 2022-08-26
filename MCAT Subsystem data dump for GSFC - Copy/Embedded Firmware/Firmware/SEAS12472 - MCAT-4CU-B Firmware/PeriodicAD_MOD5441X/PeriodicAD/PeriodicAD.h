/******************************************************************************
 * Copyright 2012 NetBurner, Inc.  ALL RIGHTS RESERVED
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

#define ADC_CR1_STOP            0x4000
#define ADC_CR1_START           0x2000
#define ADC_CR1_LOOP            0x0002
#define ADC_CR2_INIT_OFF        0x0000
#define ADC_ZCCR_OFF            0x0000
#define ADC_SDIS_ENABLE_ALL     0x0000
#define ADC_SDIS_DISABLE_ALL    0x0000


void InitSingleEndAD();     // Setup the A/D converter to be ready to run

void StartAD();             // Start A/D conversion set.

void StartADLoop();         // Start A/D conversion set, continuous loop mode.

void StopAD();              // Stop A/D conversion set.

bool ADDone();              // Return true if the conversion is complete

WORD GetADResult(int ch);   // Return the AD Result








