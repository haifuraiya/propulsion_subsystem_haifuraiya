
/*
 * Samudra Haque, G19124781, GWU 201407111527
 */


#include "predef.h"
#include <stdio.h>
#include <ctype.h>
#include <startnet.h>
#include <autoupdate.h>
#include <dhcpclient.h>
#include <pins.h>


extern "C" {
void UserMain(void * pd);
}

const char * AppName = "MOD54415 LED #1 Blink";



void UserMain(void * pd) {
	// Stock initialization code
	InitializeStack();
	if (EthernetIP == 0)
		GetDHCPAddress();
	OSChangePrio(MAIN_PRIO);
	EnableAutoUpdate();

	iprintf("%s | Application started\r\n", AppName);


#ifdef MOD5441X
	/* Configure MOD54415 pins J2-15, as GPIO. */
	J2[15].function(PINJ2_15_GPIO);  // MOD-DEV-70CR - LED1
	/* also same as J2[16,18,23,17,19,20,24] for LED2-LED8	 */
	J2[24].function(PINJ2_24_GPIO);  // MOD-DEV-70CR - LED8
#elif NANO54415
	Pins[31].function (PIN_31_GPIO); // Port G-5 GPIO & SW Logic Trigger Pulse 1
#else
#error CPP FAIL [samudra] hardware you are trying to compile for not supported by this application.
#endif


	while (1) {
		/*
		 * Increment the counter once every second
		 */
		OSTimeDly(TICKS_PER_SECOND);

		J2[15] = 1;	// Toggle Pin J2[15] (LED#1) HIGH
		J2[24] = 0; // Toggle Pin J2[24] (LED#8) LOW
		OSTimeDly(2*TICKS_PER_SECOND);	// Wait 1 second
		J2[15] = 0;	// Toggle Pin J2[15] (LED#1) LOW
		J2[24] = 1; // Toggle Pin J2[24] (LED#8) HIGH
		OSTimeDly(2fffff*TICKS_PER_SECOND);	// Wait 0.5 second
	}
}
