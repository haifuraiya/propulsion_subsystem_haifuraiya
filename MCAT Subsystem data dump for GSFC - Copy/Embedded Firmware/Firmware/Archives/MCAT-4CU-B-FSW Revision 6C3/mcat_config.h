/*
 * mcat_config.h - C++ header file for MCAT-4CU controller
 *
 * Copyright 2014-2015 The George Washington University. ALL RIGHTS RESERVED. Patents Pending
 * Author: Samudra Haque (SH), G19124781, N3RDX, samudra@gwu.edu, samudra.haque@gmail.com
 * 9/25/2014
 */

#ifndef MCAT_CONFIG_H_
#define MCAT_CONFIG_H_



#define GROUNDTESTING //define GROUNDTESTING for extra messages, or comment out this line if not needed

//general variables
char stringVersion[2];


//define DMA TIMER section relevant values
DWORD doPulseStack[USER_TASK_STK_SIZE];
DWORD uint32_counter = 0;
DWORD PulseCount = 0;
DWORD MaxCount = 1;
DWORD endCountCh1 = 0;
DWORD endCountCh2 = 0;
DWORD endCountCh3 = 0;
DWORD endCountCh4 = 0;
int TS1Count = 0;
bool Continuous = FALSE;
OS_SEM SemPulse;
OS_SEM SempTP;


//uCOS task section relevant values
OS_SEM P18H1Sem, P18H2Sem, P18H3Sem, P18H4Sem;
int Ch1Prio=62;//recommend user priority 46 to 62, 46 >> 62 priority
int Ch2Prio=61;
int Ch3Prio=60;
int Ch4Prio=59;

//logic definitions
int HIGH=1; int NHIGH = 0;
int LOW=0; int NLOW = 1;
int ON=1; int OFF = 0;
int ACTIVE=1; int INACTIVE=0;

int countUP; //interrupt cycle

#define MCAT_PPU_CHANNELS 4 // number of PPU channels
#define TEST_PULSE_COUNT 5 //min number of counts per test run

#ifdef TESTCU
#include <pins.h>
#include <bsp.h>
//GPIO PIN definition TESTCU
#define SW_RUNPMA Pins[23]
#define SW_TP1 Pins[12]
#define SW_P18L12 Pins[16]
#define SW_P18H12 Pins[25]
#define SW_P18L34 Pins[49]
#define SW_P18H34 Pins[50]
#else
#ifdef FLTCU
#include <pins.h>
//GPIO PIN definition FLTCU
#define SW_RUNPMA Pins[23]
#define SW_TP1 Pins[31]
#define SW_P18H4 Pins[32]
#define SW_P18H3 Pins[33]
#define SW_P18H2 Pins[34]
#define SW_P18H1 Pins[35]
#define SW_P18L4 Pins[36]
#define SW_P18L3 Pins[37]
#define SW_P18L2 Pins[38]
#define SW_P18L1 Pins[39]

#define SW_P18L12 Pins[99]
#define SW_P18H12 Pins[99]
#define SW_P18L34 Pins[99]
#define SW_P18H34 Pins[99]

#endif //FLTCU
#endif //TESTCU

/*
* TESTBUS (MOD54415), TESTCU (NANO54414)/FLTCU (NANO54414) I2C address
*/
#define CU_I2C_SLAVE_ADDR 0x26 // hardcoded I2C slave address.
#define TESTBUS_I2C_SLAVE_ADDR 0x24 //hardcoded I2C slave address

/*
* TESTCU/FLTCUsoftware build information
*/
#define CU_SUBSYSTEM "MCAT-4CU-B Subsystem" //root name of proj.
#define CU_PROJECT "Micro-Cathode Arc Thruster Subsystem for USNA BRICSAT-p Cubesat" //add an extra leading space here for formatting
#define CU_BUILD_MAJOR "6"  // numeric single digit
#define CU_BUILD_MINOR "C" // alpha only single digit
#define CU_AUTHOR " samudra@gwu.edu N3RDX"
/*
 * special config for USNA Bricsat mission
 */
#define BRICSAT
#define HIDDENMENU

#ifdef BRICSAT
DWORD limitPulseCount = 50; //stop at pulses

#else
DWORD limitPulseCount = 0; //effectively we pulse continuously
#endif //BRICSAT

//history
//A - initial version
//B - conditional defines for TESTCU and FLTCU configuration 10/22/2014 SH MPNL
#define CU_VERSION_LEN 10 //numeric

/* history of TESTCU/FLTCU
 * Version 5A was the First Light configuration of MCAT-4CU with 2 x MCAT-2C boards in correct configuration. 10/6/2014 @2000
 * Version 6A test version for general software commands checkout and adjustment of trigger pulse timing.
 */

/*
* TESTBUS software build information
*/
#define TB_BUILD_MAJOR "1"  // numeric
#define TB_BUILD_MINOR "A" // alpha only
#define TB_VERSION_LEN 10 //numeric

/*
* General Build Information
*/
#define BUILD_TIMESTAMP "201409251844"
#define BUILD_APP_TASKMON "M2CU-4G"
#define BUILD_APP_TITLE "Micro-Cathode Arc Thruster 2-Ch Control Unit - Remote Test Program"
#define BUILD_DATE __DATE__
#define BUILD_TIME __TIME__


#endif /* MCAT_CONFIG_H_ */
