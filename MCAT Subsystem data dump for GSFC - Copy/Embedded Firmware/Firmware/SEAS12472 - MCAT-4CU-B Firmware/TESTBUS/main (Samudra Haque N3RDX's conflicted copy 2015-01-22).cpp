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
//#include "i2cmaster.h"    // Used for master-only I2C

// Instruct the C++ compiler not to mangle the function name
extern "C"
{
    void UserMain(void *pd);
}

// Name for development tools to identify this application
const char *AppName = "I2C2Serial TESTBUS";

BYTE buffer[I2C_MAX_BUF_SIZE];
char I2CInputBuffer[I2C_MAX_BUF_SIZE];      // User-created I2C input buffer
char *inbuf = I2CInputBuffer;               // Pointer to user I2C buffer
BYTE address = 0x24; //from IP addr = 192.168.1.24
BYTE I2CStat;

BYTE Ascii2Byte(char *buf);
void menu(void);

// Main task
void UserMain(void *pd)
{
    InitializeStack();
    if (EthernetIP == 0)GetDHCPAddress();
    OSChangePrio(MAIN_PRIO);
    EnableAutoUpdate();
    EnableTaskMonitor();
    EnableSmartTraps();

    iprintf("TESTBUS MOD54415 I2C-to-Serial Demo\r\n");

#ifdef _I2CMULTI_H
    // While address is invalid
    while ((address < 0x07) || (address > 0x78)) {
        iprintf("Enter 7-bit (2-digit hex) slave address for this device, ");
        iprintf("the Philips I2C protocol states that all 7-bit addresses ");
        iprintf("are valid EXCEPT the groups 0000XXX and 1111XXX.  Devices ");
        iprintf("must have unique addresses to communicate:  ");
        *buffer = 0x0000;
        address = Ascii2Byte(gets((char*) buffer));
        iprintf("\r\n");
    }

    printf("\r\n%x\r\n", address);
    I2CInit(address);               // Initialize I2C with entered slave address
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
                I2CStat = I2CSendBuf(address,
                                     buffer,
                                     strlen((const char*) buffer) + 1);

                if (I2CStat == I2C_OK)
                    iprintf("Sent successfully\r\n");
                else {
                    iprintf("Failed to send to address %x due to error:  ");
                    iprintf("%d\r\n", address, I2CStat);
                }
            }
            else if (buffer[0] == '2') {
                address = 0;

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
   iprintf("(1) Master mode send a string to a specified address\r\n");
   iprintf("(2) Master mode receive a string from a specified address\r\n");

#ifdef _I2CMULTI_H
   iprintf("(3) Store a string for slave mode transmit\r\n");
#endif // _I2CMULTI_H

   iprintf("(?) Display this menu\r\n");
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
