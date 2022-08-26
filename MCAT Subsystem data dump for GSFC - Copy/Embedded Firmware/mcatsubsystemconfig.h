/*
 * mcatsubsystemconfig.h
 *
 * Copyright 2014-2015 The George Washington University. ALL RIGHTS RESERVED. Patents Pending
 * Author: Samudra Haque (SH), G19124781, N3RDX, samudra@gwu.edu, samudra.haque@gmail.com
 * 9/25/2014
 */

#ifndef MCATSUBSYSTEMCONFIG_H_
#define MCATSUBSYSTEMCONFIG_H_

#define CU_I2C_SLAVE_ADDR 0x26 // hardcoded I2C slave address.
#define TESTBUS_I2C_SLAVE_ADDR 0x24 //hardcoded test I2C master address
#define MCAT_I2C_CMD_PACKET_LEN 34

char MCAT_CMD[4]; //4 chars for each command IDLE, STBY, ENTP, ENTC, DITC, DITP
/*
 * IDLE - Go to Idle Mode .. CU command block
 * STBY - Go to Standby Mode .. PM command block
 * ENTP - Enable Trigger Pulse(s) .. Trigger Pulses (TP), IGBT Pre-Driver (IPD) and P18L command block
 * ENTC - Enable Thruster Channel(s) .. P18H command block
 * DITC - Disable Thruster Channel(s) .. P18H command block
 * DITP - Disable Trigger Pulses (TP, IPD, P18L command block)
 *
 */
#define MCAT_CMD_GO_IDLE_MODE 'IDLE' //limited to 4 characters
#define MCAT_CMD_GO_STANDBY_MODE "STBY"
#define MCAT_CMD_ENABLE_TRIGGER_PULSES "ENTP"
#define MCAT_CMD_ENABLE_THRUSTER_CHANNELS "ENTC"
#define MCAT_CMD_DISABLE_THRUSTER_CHANNELS "DITC"
#define MCAT_CMD_DISABLE_TRIGGER_PULSES "DITP"

char MCAT_CMD_QUERY[4]; //4 chars for each type of status inquiry
/*
 * TLM1 - Telemetry Enquiry - single response requested
 * TLMC - Telemetry Enquiry - continuous response requested
 * TLMS - Stop Telemetry feed
 */
#define MCAT_CMD_QUERY_TLM_SINGLE "TLM1"
#define MCAT_CMD_QUERY_TLM_CONTINUOUS "TLMC"
#define MCAT_CMD_QUERY_TLM_STOP "TLMS"


#define BUILD_MAJOR "5"  // numeric
#define BUILD_MINOR "A" // alpha only
#define VERSION_LEN 10 //numeric

#define BUILD_TIMESTAMP "201409251844"
#define BUILD_APP_TASKMON "M2CU-4G"
#define BUILD_APP_TITLE "Micro-Cathode Arc Thruster 2-Ch Control Unit - Remote Test Program"


#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//MCAT CMD parameter defines V1
#define MCAT_CMD_VERSION_LEN 2 //bytes
#define MCAT_CMD_MODE_LEN 3 //bytes


//Block - General
#define DEF_CMD_VERSION "V1"
//Block - CU - Control Unit section
#define LEN_CMD_CU //whole section
#define LEN_CMD_CU_BITE 1 //bytes, built in test equipment
#define LEN_CMD_CU_TIME 4 //bytes time_t
//predefined values for the sub-commands
#define MODE_CHANGE_TO_IDLE "M11"
#define MODE_CHANGE_TO_STANDBY "M21"
#define DEF_CMD_CU_TIME "0000"

//Block - PM - Power Management section
#define LEN_CMD_PM 2 //whole section
#define LEN_CMD_PM_BITE //bytes, built in test equipment

//Block - IPD - IGBT Pre-Driver section
#define LEN_CMD_IPD 2 //whole section
#define LEN_CMD_IPD_BITE //bytes, built in test equipment

//Block - PPU - Plasma Power Unit section
#define LEN_CMD_PPU 2 //whole section
#define LEN_CMD_PPU_BITE //bytes, built in test equipment

//Block - MNPS - MxN Power Switch section
#define LEN_CMD_MNPS 2 //whole section
#define LEN_CMD_MNPS_BITE //bytes, built in test equipment

//Block - SENS - Sensors Section
#define LEN_CMD_SENSORS 2 //whole section
#define LEN_CMD_SENSORS_BITE //bytes, built in test equipment

//delete me
#define MCAT_CMD_QUERY_TLM_STOP "TLMS"


#endif /* MCATSUBSYSTEMCONFIG_H_ */
