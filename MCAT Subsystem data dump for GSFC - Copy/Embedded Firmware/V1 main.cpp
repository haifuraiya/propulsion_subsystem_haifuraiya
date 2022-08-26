/*****************************************************************************
 *
 * TESTCU/FLTCU shared main.cpp for GWU MpNL's Micro-Cathode Arc Thruster (MCAT) Subsystem
 *
 * Copyright 2014-2015 The George Washington University. ALL RIGHTS RESERVED. Patents Pending
 * Author: Samudra Haque (SH), G19124781, N3RDX, samudra@gwu.edu, samudra.haque@gmail.com
 * 9/25/2014
 *
 * Incorporating: adaptations from Netburner Inc. "MOD5270 I2CSerial" sample program.
 * Incorporating: modifications by SH to accomodate multichanneli2c.h instead of i2cmulti.h
 *
 * The FSW I2C operates in SLAVE mode.
 * This NBECLIPSE build configuration is in two modes:
 *    TESTCU - for NANO54415 in NANO Carrier Board Rev 1.3 (Netburner)
 *    FLTCU - for NANO54415 in MCAT-4CU-B-V2K1 Controller Board (GWU)
 *
 * When choosing TESTCU - you will have support for Ethernet, GPIO etc. available on the NANO carrier board
 *
 */

/*********************
 * Modification History:
 * 5A: Initial version, I2C test code only; created two build environments TESTCU (ground test) and FLTCU (flight hardware)
 */

/*
 * Copyright 1998-2013 NetBurner, Inc.  ALL RIGHTS RESERVED
 *
 * Permission is hereby granted to purchasers of NetBurner hardware to use or
 * modify this computer program for any use as long as the resultant program is
 * only executed on NetBurner-provided hardware.
 *
 * No other rights to use this program or its derivatives in part or in whole
 * are granted.
 *
 * It may be possible to license this or other NetBurner software for use on
 * non-NetBurner hardware.  Please contact licensing@netburner.com for more
 * information.
 *
 * NetBurner makes no representation or warranties with respect to the
 * performance of this computer program, and specifically disclaims any
 * responsibility for any damages, special or consequential, connected with use
 * of this program.
 *
 * ----------------------------------------------------------------------------
 *
 * NetBurner, Inc.
 * 5405 Morehouse Drive
 * San Diego, CA  92121
 *
 * Information available at:  http://www.netburner.com
 * Support available at:      http://support.netburner.com
 *
 ******************************************************************************/

/*
 #ifdef NANO54415
 #error DOUBLE WOW NANO54415 is defined !!!!
 #else
 #ifdef MCF5441X
 #error WOW MCF5441X constant is defined !!!!
 #endif
 #endif
 */


#include "predef.h"
#include <stdio.h>
#include <ctype.h>
#include <startnet.h>
#include <autoupdate.h>
#include <dhcpclient.h>
#include <taskmon.h>
#include <smarttrap.h>
#include <string.h>


/*
 * Includes and defines for MCAT-4CU-B-FSW codebase
 */
#include <multichanneli2c.h> //modified by SH 9/21/14 only for NANO54414

#include <iostream>
#include <iomanip>
#include <string>
#include "mcat_config.h" //all variables

using namespace std;

//global variables
string cmdVersion="";
string cmdMode="";
string s_cmdTP1="";
string s_cmdTP2="";
string s_cmdTP3="";
string s_cmdTP4="";
string s_cmdPCH1="";
string s_cmdPCH2="";
string s_cmdPCH3="";
string s_cmdPCH4="";
long cmdTP1, cmdTP2, cmdTP3, cmdTP4, cmdPCH1, cmdPCH2, cmdPCH3, cmdPCH4;
string s_cmdP18H1="";
string s_cmdP18H2="";
string s_cmdP18H3="";
string s_cmdP18H4="";
bool cmdP18H1, cmdP18H2, cmdP18H3, cmdP18H4;

//function defines
void parseCMDPacket (char CMDPacket[I2C_MAX_BUF_SIZE]);
void parseBlockG (string BlockG);
void parseBlockCU (string BlockCU);
void parseBlockIPD (string BlockIPD);
void parseBlockPPU (string BlockPPU);

BYTE Ascii2Byte(char *buf);
void menu(void);

// Instruct the C++ compiler not to mangle the function name
extern "C" {
void UserMain(void *pd);
}


// Name for development tools to identify this application
#ifdef TESTCU
const char *AppName = "I2C2Serial TESTCU";
#warning TESTCU build in progress ----------------------------------------------
#else
#ifdef FLTCU
const char *AppName = "I2C2Serial FLTCU";
#warning FLTCU build in progress ----------------------------------------------
#else
#error Subsystem choice must be either FLTCU or TESTCU
#endif
#endif

//globals
BYTE buffer[I2C_MAX_BUF_SIZE];
char I2CInputBuffer[I2C_MAX_BUF_SIZE]; // User-created I2C input buffer
char *inbuf = I2CInputBuffer; // Pointer to user I2C buffer
BYTE address = CU_I2C_SLAVE_ADDR; //assigned I2C Slave Address for this Control Unit
BYTE I2CStat;



// Main task
void UserMain(void *pd) {
	//extern const char* AppName;


	// Name for development tools to identify this application
#ifdef TESTCU
	const char *SubSystem = "TESTCU";
#else
#ifdef FLTCU
	const char *SubSystem = "FLTCU";
#endif
#endif



	InitializeStack();
	if (EthernetIP == 0)
		GetDHCPAddress();
	OSChangePrio(MAIN_PRIO);
	EnableAutoUpdate();
	EnableTaskMonitor();
	EnableSmartTraps();

	iprintf("%s I2C-to-Serial Demo\r\n", SubSystem);



	printf("\r\nI2C Address set to %x\r\n", address);
	I2CInit(address); // Initialize I2C with entered slave add


	menu();

	while (1) {
		if (charavail()) {
			*buffer = 0x0000;
			gets((char*) buffer);

			if (buffer[0] == '1') {


				cout<< "Disabled I2C Master Transmit"<<endl;

				/*

				address = 0;

				// While address is valid
				while ((address < 0x07) || (address > 0x78)) {
					iprintf("Enter valid 7-bit (2-digit hex) destination ");
					iprintf("address for master transmit:  ");
				 *buffer = 0x0000;
					address = Ascii2Byte(gets((char*) buffer));
					iprintf("\r\n");
				}

				iprintf("Master Tx:  ");
				gets((char*) buffer);
				iprintf("\r\n");

				// Send the buffer size plus one to include the null character
				I2CStat = I2CSendBuf(address, buffer,
						strlen((const char*) buffer) + 1);

				if (I2CStat == I2C_OK)
					iprintf("Sent successfully\r\n");
				else {
					iprintf("Failed to send to address %x due to error:  ");
					iprintf("%d\r\n", address, I2CStat);
				}*/
			} else if (buffer[0] == '2') {

				cout<< "Disabled I2C Master Receive"<<endl;

				/*address = 0;

				// While address is valid
				while ((address < 0x07) || (address > 0x78)) {
					iprintf("Enter valid 7-bit (2-digit hex) destination ");
					iprintf("address for master receive:  ");
				 *buffer = 0x0000;
					address = Ascii2Byte(gets((char*) buffer));
					iprintf("\r\n");
				}

				buffer[30] = '\0';

				// Read 30 bytes from the selected address
				I2CStat = I2CReadBuf(address, buffer, 30);

				if (I2CStat == I2C_OK) {
					iprintf("Master Rx:  %s\r\n", buffer);
					iprintf("Received successfully\r\n");
				} else
					iprintf("Failed to read due to error:  %d\r\n", I2CStat);*/
			}
#ifdef _MULTICHANNELI2C_H
			else if (buffer[0] == '3') {
				iprintf("Enter string to store for slave transmit:  ");
				gets((char*) buffer);
				iprintf("\r\n");

				// Fill slave transmission buffer with string
				I2CStat = I2CFillSlaveTXBuf(buffer,
						strlen((const char*) buffer) + 1);

				if (I2CStat == I2C_OK)
					iprintf("Slave transmit buffer fill successful\r\n");
				else
					iprintf("Failed to read due to error:  %d\r\n", I2CStat);
			}
#endif // _MULTICHANNELI2C_H
			else
				menu();
		}

#ifdef _MULTICHANNELI2C_H
		if (I2CRXAvail()) {
			OSTimeDly(2); // Delay 100 ms to read all input data

			while (I2CRXAvail()) {
				*inbuf++ = I2CGetByte();
			}
			inbuf = I2CInputBuffer;
			printf("must parse Characters found in the I2C Input buffer: [%s]\r\n", inbuf);
			cout << "[" << I2CInputBuffer << "]" <<endl;
			parseCMDPacket(I2CInputBuffer);




		}
#endif // _MULTICHANNELI2C_H
	}
}


void parseCMDPacket (char cmdPacket[I2C_MAX_BUF_SIZE]){

	//define
	int currPOS = 0; //marks the current position of the cursor in the string
	string cmdVersion = ""; //length in LEN_MCAT_CMD_PACKET_VERSION
	string cmdBlockG = ""; //length of CU command Block LEN_MCAT_BLOCK_G
	string cmdBlockCU = ""; //length of CU command block LEN_CMD_BLOCK_CU
	string cmdBlockIPD = ""; //length LEN_CMD_BLOCK_IPD
	string cmdBlockPPU = ""; //length LEN_CMD_BLOCK_PPU

	cout << "About to parse Command Packet containing " << strlen((char *) cmdPacket) << " bytes" << endl;
	cout << "The packet contains: [" << cmdPacket << "]" << endl;

	//convert cmdPacket char array to C++ string object
	string strCMD (cmdPacket);

	//extract entire Block of commands for G
	cmdBlockG = strCMD.substr(currPOS, LEN_CMD_BLOCK_G);
	currPOS = currPOS + LEN_CMD_BLOCK_G;
	cout << "G Block: [" << cmdBlockG << "]" << endl;
	parseBlockG(cmdBlockG);

	//extract entire Block of commands for CU
	cmdBlockCU = strCMD.substr(currPOS, LEN_CMD_BLOCK_CU);
	currPOS = currPOS + LEN_CMD_BLOCK_CU;
	cout << "CU Block: [" << cmdBlockCU << "]" << endl;
	parseBlockCU(cmdBlockCU);

	if (cmdMode == MODE_CHANGE_TO_IDLE){
		cout << "Mode must be set to IDLE" << endl;
	}

	//Block PM support not in present version - skipping

	//extract entire Block IPD
	cmdBlockIPD = strCMD.substr(currPOS, LEN_CMD_BLOCK_IPD);
	currPOS = currPOS + LEN_CMD_BLOCK_IPD;
	cout << "IPD Block: [" << cmdBlockIPD << "]" << endl;
	parseBlockIPD(cmdBlockIPD);


	//extract entire Block PPU
	cmdBlockPPU = strCMD.substr(currPOS, LEN_CMD_BLOCK_PPU);
	currPOS = currPOS + LEN_CMD_BLOCK_PPU;
	cout << "PPU Block: [" << cmdBlockPPU << "]" << endl;
	parseBlockPPU(cmdBlockPPU);

	//Block MNPS support not in present version - skipping

	//Block SBITE support not in present version - skipping
}



void parseBlockG (string BlockG){
	//this routine will parse elements of the G Command Block
	int currPOS = 0; //set position of cursor to first pos of the block

	//extract version information of cmdPacket received over I2C
	cmdVersion = BlockG.substr(currPOS, LEN_MCAT_CMD_PACKET_VERSION);
	currPOS = currPOS + LEN_MCAT_CMD_PACKET_VERSION;
	cout << "Command Packet Version: [" << cmdVersion << "]" << endl;
}

void parseBlockCU (string BlockCU){
	//this routine will parse elements of the CU Command Block
	int currPOS = 0; //set position of cursor to first pos of the block

	cmdMode = BlockCU.substr(currPOS, LEN_CMD_BLOCK_CU_MODE); //cmdMode is global
	currPOS = currPOS + LEN_CMD_BLOCK_CU_MODE;
	cout << "Mode [" << cmdMode << "]" << endl;
}


void parseBlockIPD (string BlockIPD){
	//this routine will parse elements of the IPD Command Block
	int currPOS = 0; //set position of cursor to first pos of the block
char *endptr;
	//process s_cmdTP1
	s_cmdTP1 = BlockIPD.substr(currPOS, LEN_CMD_BLOCK_IPD_TP1);
	cmdTP1 = strtol(s_cmdTP1.c_str(),&endptr,16);
	currPOS = currPOS + LEN_CMD_BLOCK_IPD_TP1;
	cout << "TP1 string [" << s_cmdTP1 << "]" << endl;
	cout << "TP1 integer [" <<  cmdTP1 << "]" << endl;
	//process s_cmdPCH1
	s_cmdPCH1 = BlockIPD.substr(currPOS, LEN_CMD_BLOCK_IPD_PCH1);
	cmdPCH1 = strtol(s_cmdPCH1.c_str(),&endptr,16);
	currPOS = currPOS + LEN_CMD_BLOCK_IPD_PCH1;
	cout << "PCH1 [" << s_cmdPCH1 << "]" << endl;
	cout << "PCH1 integer [" <<  cmdPCH1 << "]" << endl;
	//process s_cmdTP2
	s_cmdTP2 = BlockIPD.substr(currPOS, LEN_CMD_BLOCK_IPD_TP2);
	cmdTP2 = strtol(s_cmdTP2.c_str(),&endptr,16);
		currPOS = currPOS + LEN_CMD_BLOCK_IPD_TP2;
		cout << "TP2 string [" << s_cmdTP2 << "]" << endl;
		cout << "TP2 integer [" <<  cmdTP2 << "]" << endl;
	//process s_cmdPCH2
		s_cmdPCH2 = BlockIPD.substr(currPOS, LEN_CMD_BLOCK_IPD_PCH2);
			cmdPCH2 = strtol(s_cmdPCH2.c_str(),&endptr,16);
			currPOS = currPOS + LEN_CMD_BLOCK_IPD_PCH2;
			cout << "PCH2 [" << s_cmdPCH2 << "]" << endl;
			cout << "PCH2 integer [" <<  cmdPCH2 << "]" << endl;
	//process s_cmdTP3
	s_cmdTP3 = BlockIPD.substr(currPOS, LEN_CMD_BLOCK_IPD_TP3);
	cmdTP3 = strtol(s_cmdTP3.c_str(),&endptr,16);
		currPOS = currPOS + LEN_CMD_BLOCK_IPD_TP3;
		cout << "TP3 string [" << s_cmdTP3 << "]" << endl;
		cout << "TP3 integer [" <<  cmdTP3 << "]" << endl;
	//process s_cmdPCH3
		s_cmdPCH3 = BlockIPD.substr(currPOS, LEN_CMD_BLOCK_IPD_PCH3);
			cmdPCH3 = strtol(s_cmdPCH3.c_str(),&endptr,16);
			currPOS = currPOS + LEN_CMD_BLOCK_IPD_PCH3;
			cout << "PCH3 [" << s_cmdPCH3 << "]" << endl;
			cout << "PCH3 integer [" <<  cmdPCH3 << "]" << endl;

	//process s_cmdTP4
	s_cmdTP4 = BlockIPD.substr(currPOS, LEN_CMD_BLOCK_IPD_TP4);
	cmdTP4 = strtol(s_cmdTP4.c_str(),&endptr,16);
		currPOS = currPOS + LEN_CMD_BLOCK_IPD_TP4;
		cout << "TP4 string [" << s_cmdTP4 << "]" << endl;
		cout << "TP4 integer [" <<  cmdTP4 << "]" << endl;
	//process s_cmdPCH4
		s_cmdPCH4 = BlockIPD.substr(currPOS, LEN_CMD_BLOCK_IPD_PCH4);
			cmdPCH4 = strtol(s_cmdPCH4.c_str(),&endptr,16);
			currPOS = currPOS + LEN_CMD_BLOCK_IPD_PCH4;
			cout << "PCH4 [" << s_cmdPCH4 << "]" << endl;
			cout << "PCH4 integer [" <<  cmdPCH4 << "]" << endl;
}

void parseBlockPPU (string BlockPPU){

int currPOS=0;
	//process cmdP18H1
	s_cmdP18H1 = BlockPPU.substr(currPOS, LEN_CMD_BLOCK_PPU_P18H1);
	if (s_cmdP18H1 == "Y") {
		cmdP18H1 = TRUE;
	} else {
		cmdP18H1 = FALSE;
	}
	currPOS = currPOS + LEN_CMD_BLOCK_PPU_P18H1;
	cout << "P18H1 [" << cmdP18H1 << "]" << endl;

	//process cmdP18H2
	s_cmdP18H2 = BlockPPU.substr(currPOS, LEN_CMD_BLOCK_PPU_P18H2);
		if (s_cmdP18H2 == "Y") {
			cmdP18H2 = TRUE;
		} else {
			cmdP18H2 = FALSE;
		}
		currPOS = currPOS + LEN_CMD_BLOCK_PPU_P18H2;
		cout << "P18H2 [" << cmdP18H2 << "]" << endl;

	//process cmdP18H3
		s_cmdP18H3 = BlockPPU.substr(currPOS, LEN_CMD_BLOCK_PPU_P18H3);
			if (s_cmdP18H3 == "Y") {
				cmdP18H3 = TRUE;
			} else {
				cmdP18H3 = FALSE;
			}
			currPOS = currPOS + LEN_CMD_BLOCK_PPU_P18H3;
			cout << "P18H3 [" << cmdP18H3 << "]" << endl;

	//process cmdP18H4
			s_cmdP18H4 = BlockPPU.substr(currPOS, LEN_CMD_BLOCK_PPU_P18H4);
				if (s_cmdP18H4 == "Y") {
					cmdP18H4 = TRUE;
				} else {
					cmdP18H4 = FALSE;
				}
				currPOS = currPOS + LEN_CMD_BLOCK_PPU_P18H4;
				cout << "P18H4 [" << cmdP18H4 << "]" << endl;

}



//	cmdMode = BlockCU.substr(currPOS, LEN_CMD_BLOCK_CU_MODE);
//	currPOS = currPOS + LEN_CMD_BLOCK_CU_MODE;
//	cout << "My Mode: [" << cmdMode << "]" << endl;
//}


/*
 * The following function converts the first two ASCII chars of a string to a
 * single hex value
 */
BYTE Ascii2Byte(char *buf) {
	char conv[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B',
			'C', 'D', 'E', 'F' };
	BYTE temp = 0;

	for (int i = 0; i < 16; i++) {
		if (toupper(buf[1]) == conv[i])
			temp = i;
	}

	for (int i = 0; i < 16; i++) {
		if (toupper(buf[0]) == conv[i])
			temp |= i << 4;
	}

	return temp;
}

void menu(void) {
	iprintf("\r\nEnter the following characters to perform I2C tasks:\r\n");
	iprintf("(1) Master mode send a string to a specified address\r\n");
	iprintf("(2) Master mode receive a string from a specified address\r\n");

#ifdef _MULTICHANNELI2C_H
	iprintf("(3) Store a string for slave mode transmit\r\n");
#endif // _MULTICHANNELI2C_H
	iprintf("(?) Display this menu\r\n");
}

