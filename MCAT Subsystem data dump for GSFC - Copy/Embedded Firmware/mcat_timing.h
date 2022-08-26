/*
 * mcat_timing.h
 *
 *  Created on: Oct 3, 2014
 *      Author: samudra
 */

#ifndef MCAT_TIMING_H_
#define MCAT_TIMING_H_

int TSRD = 623; //default Time Slice Reference (TSR) value .147mS/.147mS/.147mS NANO54415 DMATIMER4 (matlab) 10/2/14
int TSR = TSRD; //utilize default produced

//the MCAT-2C PPUs work between 1..50 Hz only.
int PPU_SAFE_OPS_MIN = 1;
int PPU_SAFE_OPS_MAX = 50;

//declare EOCC_array - F=1 Hz has largest delay between trigger pulses.
long EOCC_array[50] = {
		99954, 49954, 33288, 24954, 19954, 16621, 14240, 12454, 11065, 9954,
		9045, 8288, 7647, 7097, 6621, 6204, 5837, 5510, 5218, 4954,
		4716, 4500, 4302, 4121, 3954, 3801, 3658, 3526, 3403, 3288,
		3180, 3079, 2985, 2896, 2812, 2732, 2657, 2586, 2518, 2454,
		2393, 2335, 2280, 2227, 2177, 2128, 2082, 2038, 1995, 1954
};

//default values
int MCHCD = 0;
int TPHCD = 14;
int TPLCD = 29;
//int TPLCD = 42; //testing only
int MCLCD = 44;
int EOCCD = 99954; //default values above give F=1 Hz.
int EOCCD50 = EOCC_array[50-1]; //test case for 50 Hz.
int EOCCD10 = EOCC_array[10-1]; //test case for 10 Hz

//assigning timing components for this implementation
int MCHC = MCHCD;
int TPHC = TPHCD;
int TPLC = TPLCD;
int MCLC = MCLCD;
int EOCC = EOCCD;




// Safe copy of the DMATIMER4 matlab run

/*
 * NANO54415) DMA Timer Calc V2 for MCAT-4CU-B-V2K1
Samudra Haque (samudra@gwu.edu)
02-Oct-2014 16:08:01

[Chosen Impulse Timing Components]

t1    = 0.147 mS        (Pre-TP MC activation)
t2    = 0.147 mS        (TP activiation)
t3    = 0.147 mS        (Post TP MC activation)
tr    = 0.0008 mS    (assumed rise-time)
tf    = 0.0008 mS    (assumed fall time)
tpre  = 0.0024 mS    (assumed time for sensor/startup)
tpost = 0.0024 mS    (assumed time for sensor/shutdown)


[SINGLE SHOT PULSE]

Active Time (ta): 0.0004514

Events (inclusive of rise/fall times):
MCH 0 mS
TPH 0.1478 mS
TPL 0.2956 mS
MCL 0.4434 mS

[CONTINUOUS OPERATION]

Full Cycles: 2215
Partial Cycles: 0.330084
Idle Time per period (td): 6.72686e-05 mS
Active Time, per period (ta): 0.0004514

Events (inclusive of rise/fall times):
MCH 0 mS
TPH 0.1478 mS
TPL 0.2956 mS
MCL 0.4434 mS
EOC 0.451467 mS
Checking Total time period for 2215 full cycles is: 1 seconds

[MCF54415 DMA TIMER and Interrupt Count Values]

Time Step (TSR): 10 uS
REFVAL: 623
DIVIDER:1
PRESCALER:1

[TS Counter Values (MCHC, TPHC, TPLC, MCLC, EOCC)]
in ascending order of event time

         0         0
    0.0001   14.0000
    0.0003   29.0000
    0.0004   44.0000
    0.0005   45.0000

[Table of Frequency vs td (TS Counts)]

*/

#endif /* MCAT_TIMING_H_ */
