/*****************************************************************************
 *
 *  TESTBUS main.cpp for GWU MpNL's Micro-Cathode Arc Thruster (MCAT) Subsystem
 *
 * Copyright 2014-2015 The George Washington University. ALL RIGHTS RESERVED. Patents Pending
 * Author: Samudra Haque (SH), G19124781, N3RDX, samudra@gwu.edu, samudra.haque@gmail.com
 * 9/25/2014
 *
 * Incorporating: adaptations from Netburner Inc. "MOD5270 I2CSerial" sample program.
 *
 *
 * When choosing TESTBUS - you will have support for Ethernet, GPIO etc. available on the MOD-DEV-70 carrier board
 *
 */
/*********************
 * Modification History:
 * TBD
 *
 */

/*******************************************************************************
 *
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
/*******************************************************************************
 * MOD5270 I2C2Serial
 *
 * This program will illustrate how to use the NetBurner I2C driver to transmit
 * multi-master or master-only I2C.  This application should be used with
 * multiple NetBurner modules in multi-master mode and at most one if any are
 * configured to be master-only.
 ******************************************************************************/

#include "predef.h"
#include <stdio.h>
#include <ctype.h>
#include <startnet.h>
#include <autoupdate.h>
#include <dhcpclient.h>
#include <taskmon.h>
#include <smarttrap.h>
#include <string.h>

#include "i2cmulti.h"       // Used for multi-master I2C
#include <mcat_config.h>
#include <iostream>
#include <iomanip>
#include <string>
#include "mcat_cmd_packet.h"
using namespace std;

// Instruct the C++ compiler not to mangle the function name
extern "C"
{
void UserMain(void *pd);
}

// Name for development tools to identify this application
const char *AppName = "TESTBUS";

BYTE buffer[I2C_MAX_BUF_SIZE];
BYTE cmdBuffer[I2C_MAX_BUF_SIZE]; //command buffer to CU
BYTE tlmBuffer[I2C_MAX_BUF_SIZE]; //telemetry buffer from CU

char I2CInputBuffer[I2C_MAX_BUF_SIZE];      // User-created I2C input buffer
char *inbuf = I2CInputBuffer;               // Pointer to user I2C buffer
BYTE myI2CSlaveAddr = TESTBUS_I2C_SLAVE_ADDR;
BYTE cuI2CSlaveAddr = CU_I2C_SLAVE_ADDR;
BYTE I2CStat;

BYTE Ascii2Byte(char *buf);
void menu(void);
void mcatSendSampleCMD(void);
void mcatSendSampleCMD2(void);
// Main task
void UserMain(void *pd)
{
	InitializeStack();
	if (EthernetIP == 0)GetDHCPAddress();
	OSChangePrio(MAIN_PRIO);
	EnableAutoUpdate();
	EnableTaskMonitor();
	EnableSmartTraps();

	iprintf("TESTBUS Control Program Version TBD\r\n");

#ifdef _I2CMULTI_H
	// While address is invalid
	//address = TESTBUS_I2C_MASTER_ADDR; //unused, but good to test bidirectional I2C hardcoded address.
	/* while ((address < 0x07) || (address > 0x78)) {
        iprintf("Enter 7-bit (2-digit hex) slave address for this device, ");
        iprintf("the Philips I2C protocol states that all 7-bit addresses ");
        iprintf("are valid EXCEPT the groups 0000XXX and 1111XXX.  Devices ");
        iprintf("must have unique addresses to communicate:  ");
	 *buffer = 0x0000;
        address = Ascii2Byte(gets((char*) buffer));
        iprintf("\r\n");
    }*/

	printf("\r\n%x\r\n", myI2CSlaveAddr);
	I2CInit(myI2CSlaveAddr);               // Initialize I2C with entered slave address
#endif // _I2CMULTI_H

#ifdef _I2CMASTER_H
	I2CInit();
#endif // _I2CMASTER_H

	menu();

	while (1) {
		if (charavail()) {
			*buffer = 0x0000;
			gets((char*) buffer);

			if (buffer[0] == '1') {

				// we want to send a test I2C frame to CU

				iprintf("Master Tx:  ");
				gets((char*) cmdBuffer);
				iprintf("\r\n");

				// Send the buffer size plus one to include the null character
				I2CStat = I2CSendBuf(cuI2CSlaveAddr,
						cmdBuffer,
						strlen((const char*) cmdBuffer) + 1);

				if (I2CStat == I2C_OK)
					iprintf("Sent successfully\r\n");
				else {
					iprintf("Failed to send to address %x due to error:  ");
					iprintf("%d\r\n", cuI2CSlaveAddr, I2CStat);
				}
			}
			else if (buffer[0] == '2') {

				// we want to retrieve current telemetry from CU

				tlmBuffer[30] = '\0'; //we are only concerned about first 30 bytes .. this can change

				// Read 30 bytes from the selected address
				I2CStat = I2CReadBuf(cuI2CSlaveAddr, tlmBuffer, 30);

				if (I2CStat == I2C_OK) {
					iprintf("Master Rx:  %s\r\n", tlmBuffer);
					iprintf("Received successfully\r\n");
				}
				else
					iprintf("Failed to read due to error:  %d\r\n", I2CStat);
			}
#ifdef _I2CMULTI_H
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
#endif // _I2CMULTI_H
			else if (buffer[0]== '9') {
				// send a sample command packet draft shown 9/27 SH
				mcatSendSampleCMD();
			} else if (buffer[0] == '8') {
				mcatSendSampleCMD2();
			}


			else
				menu();
		}

#ifdef _I2CMULTI_H
		if (I2CRXAvail()) {
			OSTimeDly(2);               // Delay 100 ms to read all input data

			while (I2CRXAvail()) { *inbuf++ = I2CGetByte(); }
			inbuf = I2CInputBuffer;
			printf("%s\r\n", inbuf);
		}
#endif // _I2CMULTI_H
	}
}


/*
 * The following function converts the first two ASCII chars of a string to a
 * single hex value
 */
BYTE Ascii2Byte(char *buf)
{
	char conv[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
			'A', 'B', 'C', 'D', 'E', 'F'};
	BYTE temp = 0;

	for (int i = 0; i < 16; i++) {
		if (toupper(buf[1]) == conv[i]) temp = i;
	}

	for (int i = 0; i < 16; i++) {
		if (toupper(buf[0]) == conv[i]) temp |= i << 4;
	}

	return temp;
}


void menu(void)
{
	iprintf("\r\nEnter the following characters to perform I2C tasks:\r\n");
	iprintf("(1) Master mode send test alphanumeric string to CU from cmdBuffer\r\n");
	iprintf("(2) Master mode receive test alphanumeric from CU slave buffer into tlmBuffer\r\n");


#ifdef _I2CMULTI_H
	iprintf("(3) Store a string for slave mode transmit\r\n");
#endif // _I2CMULTI_H
	iprintf("(9) Send Sample MCAT command packet\r\n");
	iprintf("(8) Send Sample Active command packet\r\n");

	iprintf("(?) Display this menu\r\n");
}

void mcatSendSampleCMD2(void) {
	BYTE cmdBuffer[LEN_MCAT_CMD_PACKET];
	//BYTE appendCMDbuf[LEN_MCAT_CMD_PACKET];

	//general block cmds
	BYTE cmdVersion[] = MCAT_CMD_PACKET_VERSION;
	//CU block cmds
	BYTE cmdMode[LEN_CMD_BLOCK_CU_MODE];
	BYTE mcatModeIdle[] = MODE_CHANGE_TO_IDLE;
	BYTE mcatModeStandby[] = MODE_CHANGE_TO_STANDBY;
	BYTE mcatModeRun[] = MODE_CHANGE_TO_RUN;
	BYTE mcatModeFire[] = MODE_CHANGE_TO_FIRE;
	//IPD Block params
	BYTE cmdTP1[]=DEF_CMD_TP1;
	BYTE cmdTP2[]=DEF_CMD_TP2;
	BYTE cmdTP3[]=DEF_CMD_TP3;
	BYTE cmdTP4[]=DEF_CMD_TP4;
	BYTE cmdPCH1[]=DEF_PCH1;
	BYTE cmdPCH2[]=DEF_PCH2;
	BYTE cmdPCH3[]=DEF_PCH3;
	BYTE cmdPCH4[]=DEF_PCH4;
	//PPU Block cmds
	BYTE cmdP18H1[]="N";
	BYTE cmdP18H2[]="Y";
	BYTE cmdP18H3[]="Y";
	BYTE cmdP18H4[]="N";


	int addOnly; //number of Bytes to add at tail of cmdBuffer variable
	int currPos=0; // current position of cmdBuffer content in the variable

	printf("Command Version:%s\n",cmdVersion);

	cout << "Version: [" << cmdVersion << "]" << endl;

	//cmdBuffer is blank at this point


	//Append cmdVersion
	addOnly=sizeof(cmdVersion);
	memcpy(cmdBuffer,cmdVersion,addOnly);
	currPos=addOnly-1;
	cout << "Part 1/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;

	//Append cmdMode
	// here we choose to select default, mcatModeRUN ...
	addOnly=sizeof(mcatModeFire);
	memcpy(cmdBuffer + currPos, mcatModeFire, addOnly);
	currPos=currPos + (addOnly-1);
	cout << "Part 2/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;



	//Append cmdTP1
	addOnly=sizeof(cmdTP1);
	memcpy(cmdBuffer + currPos, cmdTP1, addOnly);
	currPos=currPos + (addOnly-1);
	cout << "Part 3/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;


	//Append cmdPCH1
	addOnly=sizeof(cmdPCH1);
	memcpy(cmdBuffer + currPos, cmdPCH1, addOnly);
	currPos=currPos + (addOnly-1);
	cout << "Part 4/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;

	//Append cmdTP2
	addOnly=sizeof(cmdTP2);
	memcpy(cmdBuffer + currPos, cmdTP2, addOnly);
	currPos=currPos + (addOnly-1);
	cout << "Part 5/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;

	//Append cmdPCH2
	addOnly=sizeof(cmdPCH2);
	memcpy(cmdBuffer + currPos, cmdPCH2, addOnly);
	currPos=currPos + (addOnly-1);
	cout << "Part 6/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;

	//Append cmdTP3
	addOnly=sizeof(cmdTP3);
	memcpy(cmdBuffer + currPos, cmdTP3, addOnly);
	currPos=currPos + (addOnly-1);
	cout << "Part 7/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;

	//Append cmdPCH3
	addOnly=sizeof(cmdPCH3);
	memcpy(cmdBuffer + currPos, cmdPCH3, addOnly);
	currPos=currPos + (addOnly-1);
	cout << "Part 8/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;

	//Append cmdTP4
	addOnly=sizeof(cmdTP4);
	memcpy(cmdBuffer + currPos, cmdTP4, addOnly);
	currPos=currPos + (addOnly-1);
	cout << "Part 9/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;

	//Append cmdPCH4
	addOnly=sizeof(cmdPCH4);
	memcpy(cmdBuffer + currPos, cmdPCH4, addOnly);
	currPos=currPos + (addOnly-1);
	cout << "Part 10/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;

	//Append cmdP18H1
	addOnly=sizeof(cmdP18H1);
	memcpy(cmdBuffer + currPos, cmdP18H1, addOnly);
	currPos=currPos + (addOnly-1);
	cout << "Part 11/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;

	//Append cmdP18H2
	addOnly=sizeof(cmdP18H2);
	memcpy(cmdBuffer + currPos, cmdP18H2, addOnly);
	currPos=currPos + (addOnly-1);
	cout << "Part 12/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;

	//Append cmdP18H3
	addOnly=sizeof(cmdP18H3);
	memcpy(cmdBuffer + currPos, cmdP18H3, addOnly);
	currPos=currPos + (addOnly-1);
	cout << "Part 13/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;

	//Append cmdP18H4
	addOnly=sizeof(cmdP18H4);
	memcpy(cmdBuffer + currPos, cmdP18H4, addOnly);
	currPos=currPos + (addOnly-1);
	cout << "Part 14/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;

	// Send the composed cmdBuffer  plus one to include the null character
	I2CStat = I2CSendBuf(cuI2CSlaveAddr,
			cmdBuffer,
			strlen((const char*) cmdBuffer) + 1);

	if (I2CStat == I2C_OK)
		iprintf("Sent successfully\r\n");
	else {
		iprintf("Failed to send to address %x due to error:  ");
		iprintf("%d\r\n", cuI2CSlaveAddr, I2CStat);
	}


}

void mcatSendSampleCMD(void) {
	BYTE cmdBuffer[LEN_MCAT_CMD_PACKET];
	//BYTE appendCMDbuf[LEN_MCAT_CMD_PACKET];

	//general block cmds
	BYTE cmdVersion[] = MCAT_CMD_PACKET_VERSION;
	//CU block cmds
	BYTE cmdMode[LEN_CMD_BLOCK_CU_MODE];
	BYTE mcatModeIdle[] = MODE_CHANGE_TO_IDLE;
	BYTE mcatModeStandby[] = MODE_CHANGE_TO_STANDBY;
	BYTE mcatModeRun[] = MODE_CHANGE_TO_RUN;
	BYTE mcatModeFire[] = MODE_CHANGE_TO_FIRE;
	//IPD Block params
	BYTE cmdTP1[]=DEF_CMD_TP1;
	BYTE cmdTP2[]=DEF_CMD_TP2;
	BYTE cmdTP3[]=DEF_CMD_TP3;
	BYTE cmdTP4[]=DEF_CMD_TP4;
	BYTE cmdPCH1[]=DEF_PCH1;
	BYTE cmdPCH2[]=DEF_PCH2;
	BYTE cmdPCH3[]=DEF_PCH3;
	BYTE cmdPCH4[]=DEF_PCH4;
	//PPU Block cmds
	BYTE cmdP18H1[]="N";
	BYTE cmdP18H2[]="N";
	BYTE cmdP18H3[]="N";
	BYTE cmdP18H4[]="N";


	int addOnly; //number of Bytes to add at tail of cmdBuffer variable
	int currPos=0; // current position of cmdBuffer content in the variable

	printf("Command Version:%s\n",cmdVersion);

	cout << "Version: [" << cmdVersion << "]" << endl;

	//cmdBuffer is blank at this point


	//Append cmdVersion
	addOnly=sizeof(cmdVersion);
	memcpy(cmdBuffer,cmdVersion,addOnly);
	currPos=addOnly-1;
	cout << "Part 1/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;

	//Append cmdMode
	// here we choose to select default, mcatModeIdle ...
	addOnly=sizeof(mcatModeIdle);
	memcpy(cmdBuffer + currPos, mcatModeIdle, addOnly);
	currPos=currPos + (addOnly-1);
	cout << "Part 2/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;



	//Append cmdTP1
	addOnly=sizeof(cmdTP1);
	memcpy(cmdBuffer + currPos, cmdTP1, addOnly);
	currPos=currPos + (addOnly-1);
	cout << "Part 3/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;


	//Append cmdPCH1
	addOnly=sizeof(cmdPCH1);
	memcpy(cmdBuffer + currPos, cmdPCH1, addOnly);
	currPos=currPos + (addOnly-1);
	cout << "Part 4/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;

	//Append cmdTP2
	addOnly=sizeof(cmdTP2);
	memcpy(cmdBuffer + currPos, cmdTP2, addOnly);
	currPos=currPos + (addOnly-1);
	cout << "Part 5/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;

	//Append cmdPCH2
	addOnly=sizeof(cmdPCH2);
	memcpy(cmdBuffer + currPos, cmdPCH2, addOnly);
	currPos=currPos + (addOnly-1);
	cout << "Part 6/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;

	//Append cmdTP3
	addOnly=sizeof(cmdTP3);
	memcpy(cmdBuffer + currPos, cmdTP3, addOnly);
	currPos=currPos + (addOnly-1);
	cout << "Part 7/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;

	//Append cmdPCH3
	addOnly=sizeof(cmdPCH3);
	memcpy(cmdBuffer + currPos, cmdPCH3, addOnly);
	currPos=currPos + (addOnly-1);
	cout << "Part 8/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;

	//Append cmdTP4
	addOnly=sizeof(cmdTP4);
	memcpy(cmdBuffer + currPos, cmdTP4, addOnly);
	currPos=currPos + (addOnly-1);
	cout << "Part 9/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;

	//Append cmdPCH4
	addOnly=sizeof(cmdPCH4);
	memcpy(cmdBuffer + currPos, cmdPCH4, addOnly);
	currPos=currPos + (addOnly-1);
	cout << "Part 10/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;

	//Append cmdP18H1
	addOnly=sizeof(cmdP18H1);
	memcpy(cmdBuffer + currPos, cmdP18H1, addOnly);
	currPos=currPos + (addOnly-1);
	cout << "Part 11/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;

	//Append cmdP18H2
	addOnly=sizeof(cmdP18H2);
	memcpy(cmdBuffer + currPos, cmdP18H2, addOnly);
	currPos=currPos + (addOnly-1);
	cout << "Part 12/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;

	//Append cmdP18H3
	addOnly=sizeof(cmdP18H3);
	memcpy(cmdBuffer + currPos, cmdP18H3, addOnly);
	currPos=currPos + (addOnly-1);
	cout << "Part 13/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;

	//Append cmdP18H4
	addOnly=sizeof(cmdP18H4);
	memcpy(cmdBuffer + currPos, cmdP18H4, addOnly);
	currPos=currPos + (addOnly-1);
	cout << "Part 14/14: [" << cmdBuffer  << "]" << " added " << addOnly << "bytes; " << " currPos: [" << currPos << "]" << endl; //desk check
	cout << "String Length of cmdBuffer: " << strlen((char *)cmdBuffer)<<endl;

	// Send the composed cmdBuffer  plus one to include the null character
	I2CStat = I2CSendBuf(cuI2CSlaveAddr,
			cmdBuffer,
			strlen((const char*) cmdBuffer) + 1);

	if (I2CStat == I2C_OK)
		iprintf("Sent successfully\r\n");
	else {
		iprintf("Failed to send to address %x due to error:  ");
		iprintf("%d\r\n", cuI2CSlaveAddr, I2CStat);
	}


}

/*
#include "predef.h"
#include <stdio.h>
#include <ctype.h>
#include <startnet.h>
#include <autoupdate.h>
#include <dhcpclient.h>
#include <smarttrap.h>
#include <taskmon.h>

//
//added by SH 9/20/14
//

#include "i2cmaster.h"
#include <iostream>
using namespace std;
#include <pins.h>
#include <pinconstant.h>
//
//
//



extern "C" {
void UserMain(void * pd);
}

const char * AppName="TESTBUS";

void UserMain(void * pd) {
	InitializeStack();
	if (EthernetIP == 0) GetDHCPAddress();
	OSChangePrio(MAIN_PRIO);
	EnableAutoUpdate();
	StartHTTP();
	EnableTaskMonitor();

#ifndef _DEBUG
	EnableSmartTraps();
#endif


	iprintf("Application started again\n");

	cout << "Assigning GPIO pins" << endl;
	J2[15].function(PINJ2_15_GPIO); // Test LED
	J2[39].function(PINJ2_39_I2C0_SDA); // I2C SDA
	J2[41].function(PINJ2_42_I2C0_SCL); // I2C SCL

	for( int x =0; x<128; x++)
	{
		cout << "Testing I2C Address:" << x << endl;
		if( I2CStart( x, I2C_START_READ ) < I2C_TIMEOUT )
			iprintf("We have a %X on the bus\r\n", x );
		I2CStop();
	}
	iprintf("Completed scan of I2C bus\n");

	while (1) {
		cout << "LED ON" << endl;
		J2[15].set();
		OSTimeDly(TICKS_PER_SECOND);
		cout << "OFF" << endl;
		J2[15].clr();
		OSTimeDly(TICKS_PER_SECOND);
	}
}
 */


