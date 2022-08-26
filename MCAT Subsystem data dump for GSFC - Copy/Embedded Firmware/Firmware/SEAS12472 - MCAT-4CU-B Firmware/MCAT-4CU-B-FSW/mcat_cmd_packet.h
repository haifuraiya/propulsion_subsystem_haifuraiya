 /* mcat_cmd_packet.h - C++ header file for MCAT command packet specifications
 *
 *  Created on: Oct 3, 2014
 *   Copyright 2014-2015 The George Washington University. ALL RIGHTS RESERVED. Patents Pending
 * Author: Samudra Haque (SH), G19124781, N3RDX, samudra@gwu.edu, samudra.haque@gmail.com
 *
 */

#ifndef MCAT_CMD_PACKET_H_
#define MCAT_CMD_PACKET_H_


//MCAT CMD Packet definition compliant to Version 1B Rev C (10/1/2014 HAQUE)
//All lengths are in BYTES (unsigned char)
#define LEN_MCAT_CMD_PACKET 45 //Total Command Packet Length (including null?)

//Block - General
//lengths
#define LEN_CMD_BLOCK_G 2 //bytes
#define LEN_MCAT_CMD_PACKET_VERSION 2 //bytes
//predefined values
#define MCAT_CMD_PACKET_VERSION "1B"
#define MCAT_CMD_PACKET_VERSION_1B


#ifdef MCAT_CMD_PACKET_VERSION_1B

//Block - CU - Control Unit section
//lengths
#define LEN_CMD_BLOCK_CU 3 //bytes, whole section
#define LEN_CMD_BLOCK_CU_MODE 3
//constant values
#define MODE_CHANGE_TO_IDLE "IDL"
#define MODE_CHANGE_TO_STANDBY "SBY"
#define MODE_CHANGE_TO_RUN "RUN"
#define MODE_CHANGE_TO_FIRE "FIR"
//default values
#define DEF_CMD_MODE "IDL"

//Block - PM - Power Management section
/*
 * In Version 1B, for BRICSAT-p, this is being handled by CU mode change function
 */


//Block - IPD - IGBT Pre-Driver section
//lengths
#define LEN_CMD_BLOCK_IPD 36 //whole section
#define LEN_CMD_BLOCK_IPD_TP1 3
#define LEN_CMD_BLOCK_IPD_PCH1 6
#define LEN_CMD_BLOCK_IPD_TP2 3
#define LEN_CMD_BLOCK_IPD_PCH2 6
#define LEN_CMD_BLOCK_IPD_TP3 3
#define LEN_CMD_BLOCK_IPD_PCH3 6
#define LEN_CMD_BLOCK_IPD_TP4 3
#define LEN_CMD_BLOCK_IPD_PCH4 6
//constant values
//default values
#define DEF_CMD_TP1 "00A" //10 Hz
#define DEF_CMD_TP2 "00A" //10 Hz
#define DEF_CMD_TP3 "00A" //10 Hz
#define DEF_CMD_TP4 "00A" //10 Hz
#define DEF_PCH1 "00001E" //30 pulses at 10 Hz = 3 seconds
#define DEF_PCH2 "00001E" //30 pulses at 10 Hz = 3 seconds
#define DEF_PCH3 "00001E" //30 pulses at 10 Hz = 3 seconds
#define DEF_PCH4 "00001E" //30 pulses at 10 Hz = 3 seconds

//BLock - PPU - Plasma Power Unit section
//lengths
#define LEN_CMD_BLOCK_PPU 4 //whole section
#define LEN_CMD_BLOCK_PPU_P18H1 1
#define LEN_CMD_BLOCK_PPU_P18H2 1
#define LEN_CMD_BLOCK_PPU_P18H3 1
#define LEN_CMD_BLOCK_PPU_P18H4 1
//constant values
//default values
#define DEF_CMD_P18H1 "N"
#define DEF_CMD_P18H2 "N"
#define DEF_CMD_P18H3 "N"
#define DEF_CMD_P18H4 "N"

//Block - MNPS - MxN Power Switch
/*
 * In Version 1B, not implemented
 */
//Block - SBITE - Sensors/Built in Test Equipment
/*
 * In Version 1B not implemented
 */
#else
#error Which MCAT Command Packet spec?
#endif //MCAT_CMD_PACKET_VERSION == "1B"

#endif /* MCAT_CMD_PACKET_H_ */
