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
 *    FLTCU - for NANO54415 in MCAT-4CU-B-V2K1 contro18Ler Board (GWU)
 *
 * When choosing TESTCU - you will have support for Ethernet, GPIO etc. available on the NANO carrier board
 *
 */



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
#include <math.h>


/*
 * Includes and defines for MCAT-4CU-B-FSW codebase
 */
#include <assert.h>
#include <multichanneli2c.h> //modified by SH 9/21/14 only for NANO54414
#include <sim5441x.h>
//#include <ucos.h>
#include <cfinter.h>
#include <iostream>
#include <iomanip>
#include <string>
#include "mcat_config.h" //all variables
#include "mcat_cmd_packet.h" //MCAT Command Packet Specs
#include "mcat_timing.h" //MCAT Trigger Pulse Specs
#include "periph_clocks.h" //from netburner for disabling peripherals

using namespace std;

/*
 * GLOBAL VARIABLES
 */
DWORD startPulseCount, endPulseCount;
BOOL toggleHFlag;
char idQ[80]; //quick query ID string
char idCU[160]; //identifier string for the control unit
char verCU[2]; //version number
string cmdVersion=""; //string of command packet version
string cmdMode=""; //string of command mode to be set
string cmdModeCurrent=""; //string of command mode the system is currently in.
string s_freqTP1=""; //string of Trigger Pulse 1 Frequency
string s_freqTP2=""; //string of Trigger Pulse 2 Frequency (future use only)
string s_freqTP3=""; //string of Trigger Pulse 3 Frequency (future use only)
string s_freqTP4=""; //string of Trigger Pulse 4 Frequency (future use only)
string s_countCh1="";//string of Channel 1 pulse count to be executed
string s_countCh2="";//string of Channel 2 pulse count to be executed
string s_countCh3="";//string of Channel 3 pulse count to be executed
string s_countCh4="";//string of Channel 4 pulse count to be executed
//numeric values for the Frequency and Pulse Counts
long freqTP1 = 10;
long freqTP2 = 10;
long freqTP3 = 10;
long freqTP4 = 10;
long countCh1 = 0;
long countCh2 = 0;
long countCh3 = 0;
long countCh4 = 0;
string s_cmdP18H1="";//string of fire command for PPU1
string s_cmdP18H2="";//string of fire command for PPU2
string s_cmdP18H3="";//string of fire command for PPU3
string s_cmdP18H4="";//string of fire command for PPU4
bool cmdP18H1, cmdP18H2, cmdP18H3, cmdP18H4;//boolean flags for the PPUx firing commands, one per ch.

/*
 * Function defines
 */

void parseCMDPacket (char CMDPacket[I2C_MAX_BUF_SIZE]);
void parseBlockG (string BlockG);
void parseBlockCU (string BlockCU);
void parseBlockIPD (string BlockIPD);
void parseBlockPPU (string BlockPPU);

BYTE Ascii2Byte(char *buf);
void menu(void);

// Instruct the C++ compiler not to mangle the function name
extern "C" {
void UserMain(void * pd);
//void displayCLIMenu();
void displayConfig();
//void doPulses(void *pdata);
void stopPulses(void *pdata);
//    void doTP(void *pdata);
void initDMATIMER1();

void SetIntc(long func, int vector, int level, int prio); //sets up the 5270/54415 interrupt contro18Ler
// void tzsetchar(char * tzenv);
//void ShowLocalIPAddr(int sock, PCSTR url);
//void ShowRemoteIPAddr(int sock, PCSTR url);
// void ShowAppRevision(int sock, PCSTR url);
//void ShowImpulseComponentEvents(int sock, PCSTR url);
// void PrintTimeStruct(struct tm&bt);
//void pollNTPServer();
//void writeTimeStampUTC();
// void htmlDisplayUTCClock(int sock, PCSTR url);
void setDefaults();
void disableAll();


}

// Name for development tools to identify this application
#ifdef TESTCU
const char *AppName = "TESTCU";
#warning TESTCU build in progress ----------------------------------------------
#else
#ifdef FLTCU
const char *AppName = "FLTCU";
#warning FLTCU build in progress ----------------------------------------------
#else
#error Choose FLTCU or TESTCU
#endif
#endif

//globals below
BYTE buffer[I2C_MAX_BUF_SIZE];
char I2CInputBuffer[I2C_MAX_BUF_SIZE]; // User-created I2C input buffer
char *inbuf = I2CInputBuffer; // Pointer to user I2C buffer
BYTE address = CU_I2C_SLAVE_ADDR; //assigned I2C Slave Address for this Control Unit
BYTE I2CStat;
string menuVersion;
//globals above



void debugPrint(string debugMsg){
#ifdef GROUNDTESTING
	cout << endl <<  __FILE__ << " / " << __LINE__ << " / " << __func__ << "[" << debugMsg << "]" << endl;
#endif
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
INTERRUPT(func_isr, 0x2600)
{
	sim2.timer[0].ter |= 0x02; //Clear the DTIM0 ref event flag
	// we acknowledge the INTERRUPT, but check first if our PulseCount has exceeded MaxCount
	// meanwhile, the ISR is still running, and can do other functions, the program will not output signals
	// unless desired
	if ((PulseCount <= MaxCount) || (Continuous == TRUE)) {
		if (TS1Count == MCHC) {
			//we must activate magnetic coil here MCH
			//Pins[PINMC] = NHIGH; //(inverted) activate magnetic coil
			//#ifdef GROUNDTESTING
			//		iprintf("U");
			//#endif
			TS1Count++;
		} else {
			if (TS1Count == TPHC) {
				/* testing inversion of logic due to onboard V2K1 tests conducted 10/5/2014 HAQUE/DENZ
				 * This happened as well during MCAT-3CU-PS3 testing at NASA ARC.
				 * Possible design problem fro SW_TP1 to OK1/K1 instead of OK1/A1, and is dissimilar to OK2, OK3.
				 *SW_TP1.clr(); // inverted due to PPUV7x/V8 hybrid
				 *SW_TP1.clr();  If the pulse seems inverted, please ensure we are using a non-inverting optocoupler
				 * in digital logic switch mode (not linear mode) that puts out
				 * VCC high for VIN high, and 0V for VIN low.
				 */

				SW_TP1.set();
				TS1Count++;
			} else {
				{
					if (TS1Count == TPLC) {
						/* testing inversion of logic due to onboard V2K1 tests conducted 10/5/2014 HAQUE/DENZ
						 * This happened as well during MCAT-3CU-PS3 testing at NASA ARC
						 * SW_TP1.set(); //inverted due to PPUV7x/V8 hybrid
						 *
						 * If the pulse seems inverted, please ensure we are using a non-inverting optocoupler
						 * in digital logic switch mode (not linear mode) that puts out
						 * VCC high for VIN high, and 0V for VIN low.
						 */

						SW_TP1.clr();
						TS1Count++;
					} else {
						if (TS1Count == MCLC) {
							//we must deactivate magnetic coil here MCL
							//Pins[PINMC] = NLOW; //(inverted) deactivate magnetic coil
#ifdef GROUNDTESTING
							iprintf(">");
#endif
							TS1Count++;
						} else {

							if (TS1Count == EOCC) { // end cycle after delay
								TS1Count = 0; //restart
								PulseCount++;
								//iprintf(" %d ",PulseCount);
							} else
								//iprintf(" nothing to do .....................S...............");
								TS1Count++; //go to next cycle
						}
					}
				}
			}
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////

void controlPMA(BOOL PMFlag) {
	assert ((PMFlag == OFF) || (PMFlag == ON));
	if (PMFlag == ON) {
		//activate Power Management
		SW_RUNPMA.set();
#ifdef GROUNDTESTING
		debugPrint("PMA turned on");
#endif

	}
	else {
		//deactivate Power management
		SW_RUNPMA.clr();
		debugPrint("PMA turned off");
	}
}

void control18L(int requestedChannel, int  LFlag) {
	/*
	 * control18L - controls the P18L line of the given channel number
	 * Channel = 1/2/3/4
	 * Condition = true/false (enable/disable)
	 */
	assert ((requestedChannel > 0) && (requestedChannel <= MCAT_PPU_CHANNELS) );
	assert ((LFlag == ON) || (LFlag == OFF));
	//#ifdef GROUNDTESTING
	//cout << "control18L: Value of requestedChannel is: [" <<requestedChannel<<"] and LFlag is: [" <<  LFlag << "]"<<endl;
	//#endif
	switch (requestedChannel) {
	case 1:
#ifdef GROUNDTESTING
		cout << "Processing P18L for Ch. 1" << endl;

#endif
		if (LFlag == ON){
#ifdef FLTCU
			SW_P18L1.set();
			cout << "Enabled P18L1" << endl;
#endif //FLTCU
#ifdef TESTCU
			debugPrint("TESTCU: Should enable P18L1 now" );
#endif //TESTCU
		}

		else {
#ifdef FLTCU
			SW_P18L1.clr();
			cout << "Disabled P18L1" << endl;
#endif //FLTCU
#ifdef TESTCU
			debugPrint("TESTCU: Should disable P18L1 now");
#endif //TESTCU
		}
		break;
	case 2:
#ifdef GROUNDTESTING
		cout << "Processing P18L for Ch. 2" << endl;

#endif
		if (LFlag == ON){

#ifdef FLTCU
			SW_P18L2.set();
			cout << "Enabled P18L2" << endl;
#endif //FLTCU
#ifdef TESTCU
			debugPrint("TESTCU: Should Enable P18L2 now" );
#endif //TESTCU
		}

		else {
#ifdef FLTCU
			SW_P18L2.clr();
			cout << "Disabled P18L2" << endl;
#endif //FLTCU
#ifdef TESTCU
			debugPrint( "TESTCU: Should Disable P18L2 now" );
#endif //TESTCU
		}
		break;
	case 3:
#ifdef GROUNDTESTING
		cout << "Processing P18L for Ch. 3" << endl;

#endif
		if (LFlag == ON){

#ifdef FLTCU
			SW_P18L3.set();
			cout << "Enabled P18L3" << endl;
#endif //FLTCU
#ifdef TESTCU
			debugPrint( "TESTCU: Should Enable P18L3 now" );
#endif //TESTCU
		}

		else {

#ifdef FLTCU
			SW_P18L3.clr();
			cout << "Disabled P18L3" << endl;
#endif //FLTCU
#ifdef TESTCU
			debugPrint( "TESTCU: Should Disable P18L3 now" );
#endif //TESTCU
		}
		break;
	case 4:
#ifdef GROUNDTESTING
		cout << "Processing P18L for Ch. 4" << endl;

#endif
		if (LFlag == ON){
#ifdef FLTCU

			SW_P18L4.set();
			cout << "Enabled P18L4" << endl;
#endif //FLTCU
#ifdef TESTCU
			debugPrint("TESTCU: Should enable P18L4 now" );
#endif //TESTCU

		}

		else {
#ifdef FLTCU
			SW_P18L4.clr();
			cout << "Disabled P18L4" << endl;
#endif //FLTCU
#ifdef TESTCU
			debugPrint( "TESTCU: Should disable P18L4 now" );
#endif //TESTCU
		}
		break;
	default:
		cout << "Cannot process P18L for unknown channel";
	}

};
void control18Hmanual(int requestedChannel, int HFlag){
	/*
	 * control18Hmanual - manually controls the P18H line of the given channel number
	 * Channel = 1-4
	 * Condition = true/false (enable/disable), processed individual for a single channel each pass
	 * We only allow pulsing in this function for TEST_PULSE_COUNT
	 * WARNING do users: do not invoke this function without first activating a contro18L line, and waiting 5xPulse counts.
	 */
	assert ((requestedChannel > 0) && (requestedChannel <= MCAT_PPU_CHANNELS) );
	assert ((HFlag == ON) || (HFlag == OFF));
	//#ifdef GROUNDTESTING
	//cout << "control18Hmanual: Value of requestedChannel is: [" <<requestedChannel<<"] and HFlag is: [" << HFlag << "]"<<endl;
	//#endif
	switch (requestedChannel) {
	case 1:
#ifdef GROUNDTESTING
		cout << "Processing P18H for Ch. 1" << endl;
#endif

		if (HFlag == ON){
#ifdef FLTCU
			SW_P18H1.set();
			cout << "Enabled P18H1" << endl;
#endif //FLTCU
#ifdef TESTCU
			debugPrint("TESTCU: Should enable P18H1 now");
#endif //TESTCU
			//			countCh1 = TEST_PULSE_COUNT;
			//			endCountCh1 = PulseCount + countCh1;
			//			cmdP18H1 = TRUE;
			//			cmdModeCurrent = MODE_CHANGE_TO_FIRE;
		}

		else {
#ifdef FLTCU
			SW_P18H1.clr();
			cout << "Disabled P18H1" << endl;

			cmdP18H1 = FALSE;
#endif //FLTCU
#ifdef TESTCU
			debugPrint("TESTCU: Should disable P18H1 now" );
#endif //TESTCU
		};
		break;
	case 2:
#ifdef GROUNDTESTING
		cout << "Processing P18H for Ch. 2" << endl;

#endif

		if (HFlag == ON){
#ifdef FLTCU
			SW_P18H2.set();
			cout << "Enabled P18H2" << endl;
#endif //FLTCU
#ifdef TESTCU
			debugPrint( "TESTCU: Should enable P18H2 now" );
#endif //TESTCU
		}

		else {
#ifdef FLTCU
			SW_P18H2.clr();
			cout << "Disabled P18H2" << endl;
#endif //FLTCU
#ifdef TESTCU
			debugPrint("TESTCU: Should disable P18H2 now" );
#endif //TESTCU};
			break;
	case 3:
#ifdef GROUNDTESTING
		cout << "Processing P18H for Ch. 3" << endl;

#endif
		if (HFlag == ON){
#ifdef FLTCU
			SW_P18H3.set();
			cout << "Enabled P18H3" << endl;
#endif //FLTCU
#ifdef TESTCU
			debugPrint("TESTCU: Should enable P18H3 now" );
#endif //TESTCU
		}

		else {
#ifdef FLTCU
			SW_P18H3.clr();
			cout << "Disabled P18H3" << endl;
#endif //FLTCU
#ifdef TESTCU
			debugPrint( "TESTCU: Should disable P18H3 now" );
#endif //TESTCU
		};
		break;
	case 4:
#ifdef GROUNDTESTING
		cout << "Processing P18H for Ch. 4" << endl;
#endif

		if (HFlag == ON){
#ifdef FLTCU
			SW_P18H4.set();
			cout << "Enabled P18H4" << endl;
#endif //FLTCU
#ifdef TESTCU
			debugPrint( "TESTCU: Should enable P18H4 now" );
#endif //TESTCU
		}

		else {
#ifdef FLTCU
			SW_P18H4.clr();
			cout << "Disabled P18H4" << endl;
#endif //FLTCU
#ifdef TESTCU
			debugPrint( "TESTCU: Should disable P18H4 now");
#endif //TESTCU
		};
		break;
	default:
		cout << "Cannot process P18H line for unknown channel" << endl;
		}
	}
}
//	void toggle18H1(void *)
//	{
//		/*
//		 * toggle18H1 -
//		 *  RTOS task to process the enable/disable function of SW_P18H1  by scan for all of the conditions:
//		 *  cmdModeCurrent == MODE_CHANGE_TO_FIRE
//		 *  PCH1 > 0
//		 *
//		 */
//		while (1) {
//			OSSemPend(&P18H1Sem,0);
//
//			if ((cmdModeCurrent == MODE_CHANGE_TO_FIRE)
//					&& (cmdP18H1 == TRUE)
//					&& (PulseCount < endCountCh1) ) {
//
//				// enable the line
//				//check for current status first
//				if (!SW_P18H1)  {
//					// we are LOW, must go HIGH, so enable
//#ifdef GROUNDTESTING
//					cout << endl << endl << endl << endl << "P18H1 needs to be enabled"<< endl;
//#endif
//					SW_P18H1.set();
//				} else {
//#ifdef GROUNDTESTING
//					cout << "skipping" << endl;
//#endif
//				}
//			}
//			else {
//				if (!SW_P18H1) {
//					//skip
//					cout << "skipped" <<endl;
//				} else {
//					cout << endl << "P18H1 is to be disabled" <<endl;
//					SW_P18H1.clr();
//				}
//			}
//
//
//		} //infinite loop for controlP18H1
//
//	}


void setTP1(long Frequency ){
	/*
	 * define the EOCC appropriate to the frequency of TP asked for, based upon an array of numbers.
	 * input is Frequency in units Hz.
	 * WARNING: input validation is present in this routine. the Frequency asked for is checked to be within 1..50 Hz.
	 * WARNING: for MCAT-4CU-B valid ranges are 1..50 Hz, defined in mcat_timing.h, if out of bounds, lowest is selected.
	 */
	assert ((Frequency >= PPU_SAFE_OPS_MIN) && (Frequency <= PPU_SAFE_OPS_MAX )) ;
	if (Frequency >= PPU_SAFE_OPS_MIN && Frequency <= PPU_SAFE_OPS_MAX){
		EOCC = EOCC_array[ Frequency - 1];
		cout << endl << endl << "Frequency set to " << Frequency << " Hz, (EOCC = " << EOCC << ")" << endl;
	}

	else {
		//invalid frequency request, set to 10 Hz;
		EOCC = EOCCD10;
		cout << endl << endl << "Invalid Frequency asked for: Frequency set 10Hz, (EOCC = " << EOCC << ")" << endl;
	}

};

void controlTP1(BOOL TP1Flag){
	/*
	 * enable / disable the trigger pulse, based upon flag
	 */
	if (TP1Flag){
		//specify and enable the high resolution DMA TIMER (typ. 10 uS)
		iprintf("Starting TP1 with EOCC %d\n",EOCC);
		//		cout << "Starting TP1 with EOCC:" << EOCC << endl;
		Continuous = TRUE;
		TS1Count = 0; //initalize interrupt counter TS1 (DMATIMER1 Time Slice
		sim2.timer[0].tmr = 0x001A; //system clock divided by 1
		sim2.timer[0].txmr = 0x00;
		sim2.timer[0].ter |= 0x02;
		sim2.timer[0].trr = TSR * 2; //TSR from MATLAB available in mcat_timing.h
		sim2.timer[0].tcn = 1;

		///from 5270 code set /// DO NOT USE	SetIntc((long) &func_isr, 19, 1, 1);
		SetIntc(0, (long)&func_isr, 32, 1 ); //valid for NANO54415 and MOD54415
		//enable the timer
		sim2.timer[0].tmr |= 0x0001;

	} else {
		//disable the DMATIMER
		Continuous = FALSE;
		sim2.timer[0].tmr = 0x001A; //disable timer 0?
		SW_TP1.clr(); ////// test 3V > 5V level transl. - signal TP1 OFF
		//		cout << "Stopping MCAT pulse train after " << PulseCount << "pulses" << endl;
		iprintf("Stopping TP1 trigger pulse after %d pulses\n",PulseCount);
		PulseCount = 0;
	}
}
;


void goFIR(){
	// assumption, we are in a mode that allow safe transition into FIR mode
	// This mode deals with CU, PM, IPD, PPU functions
	cmdModeCurrent = MODE_CHANGE_TO_FIRE;
};
void goFIRfromRUN(){
	//assumption, we are in RUN mode, and need to consider countChXXX numbers
	if (countCh1 > 0)
		endCountCh1 = PulseCount +  countCh1;
	else
		endCountCh1 = 0;

	if (countCh2 > 0)
		endCountCh2 = PulseCount + countCh2;
	else
		endCountCh2 = 0;

	if (countCh3 > 0)
		endCountCh3 = PulseCount + countCh3;
	else
		endCountCh3 = 0;

	if (countCh4 > 0)
		endCountCh4 = PulseCount + countCh4;
	else
		endCountCh4 = 0;

	cmdModeCurrent = MODE_CHANGE_TO_RUN;

};
void goFIRfromSBY(){
	//assumption we are in SBY mode
	cmdModeCurrent = MODE_CHANGE_TO_FIRE;
};
void goFIRfromIDL(){
	//assumption we are in IDL mode
	cmdModeCurrent = MODE_CHANGE_TO_FIRE;
};

void goRUN(){
	// assumption: we are in a mode that allows safe transition into RUN mode
	// This mode primarily deals with CU, PM, IPD functions
	//goRUNfromFIR(); //load the current pulse counts and expected end pulse counts

	cmdModeCurrent = MODE_CHANGE_TO_RUN;
	//We need to know the IPD section details
	//We need to set the Pulse Repetitive Frequency (PRF)
	//We need to enable the DMATIMER to generate interrupts
	//We need to enable the P18L lines for all channels.
};
void goRUNfromFIR(){
	// assumption: we are in FIR mode
	cmdModeCurrent = MODE_CHANGE_TO_RUN;
};
void goRUNfromSBY(){
	//assumption: we are in SBY mode
	cmdModeCurrent = MODE_CHANGE_TO_RUN;
};
void goRUNfromIDL(){
	//assumption: we are in IDL mode
	cmdModeCurrent = MODE_CHANGE_TO_RUN;
};

void goSBY(){
	// assumption, we are in a mode that allows safe transition into SBY mode
	// This mode primarily deals with CU, PM functions
	cmdModeCurrent = MODE_CHANGE_TO_STANDBY;
};
void goSBYfromFIR(){
	// asssumption: we are in FIR mode
	cmdModeCurrent = MODE_CHANGE_TO_STANDBY;
};
void goSBYfromRUN(){
	// assumption: we are in RUN mode
	cmdModeCurrent = MODE_CHANGE_TO_STANDBY;
};
void goSBYfromIDL(){
	// assumption: we are in IDL mode
	cmdModeCurrent = MODE_CHANGE_TO_STANDBY;
};

void goIDL(){
	// assumption, we are in a mode that allows safe transition into IDL mode
	// This mode primarily deals with CU functions
	cmdModeCurrent = MODE_CHANGE_TO_IDLE;
};
void goIDLfromSBY(){
	//assumption: we are in SBY mode
	cmdModeCurrent = MODE_CHANGE_TO_IDLE;
};
void goIDLfromRUN(){
	//assumption: we are in RUN mode
	cmdModeCurrent = MODE_CHANGE_TO_IDLE;
};
void goIDLfromFIR(){
	//assumption: we are in FIR mode
	cmdModeCurrent = MODE_CHANGE_TO_IDLE;
};



void setNewMode(string cmdModeRequest, string cmdModeCurrent){

	//compare cmdModeCurrent and cmdMode, and select a top level function to execute.

	if (cmdModeCurrent  == cmdModeRequest)  {
		//we are in the same mode as requested
		if (cmdMode == MODE_CHANGE_TO_IDLE){
			//from IDL to IDL
			goIDL();
		} else if (cmdMode == MODE_CHANGE_TO_STANDBY){
			//from SBY to SBY
			goSBY();
		} else if (cmdMode == MODE_CHANGE_TO_RUN){
			//from RUN to RUN
			goRUN();
		} else if (cmdMode == MODE_CHANGE_TO_FIRE){
			//from FIR to FIR
			goFIR();
		} else {
			//we have to choose different modes based upon what we are in.
			if (cmdModeRequest == MODE_CHANGE_TO_IDLE){

				//IDL > IDL  already taken care of above

				//SBY > IDL
				goIDLfromSBY();

				//RUN > IDL
				goIDLfromRUN();

				//FIR > IDL
				goIDLfromFIR();

			}else if (cmdModeRequest == MODE_CHANGE_TO_STANDBY) {

				//IDL > SBY
				goSBYfromIDL();

				//SBY > SBY already taken care of above

				//RUN > SBY
				goSBYfromRUN();

				//FIR > SBY
				goSBYfromFIR();

			} else if (cmdModeRequest == MODE_CHANGE_TO_RUN){

				//IDL > RUN
				goRUNfromIDL();

				//SBY > RUN
				goRUNfromSBY();

				//RUN > RUN already taken care of above

				//FIR > RUN
				goRUNfromFIR();

			} else if (cmdModeRequest == MODE_CHANGE_TO_FIRE){

				//IDL > FIR
				goFIRfromIDL();

				//SBY > FIR
				goFIRfromSBY();

				//RUN > FIR
				goFIRfromRUN();

				//FIR > FIR already taken care of above.
			}
		}
	}
};


void disableAll() {
	iprintf("Z");
	SW_TP1.clr(); //Set initial state of SW_TP1 to LOW
	//Pins[PINMC] = NLOW;
	//Pins[PINTP] = LOW;
}

void setDefaults() {
	//reset all params to default Timing components
	iprintf(" ............................ will set defaults now ...\n");
	TSR = TSRD;
	MCHC = MCHCD;
	TPHC = TPHCD;
	TPLC = TPLCD;
	MCLC = MCLCD;
	EOCC = EOCCD;
}

//void doPulses(void *pdata) {
//	//WORD data = * (WORD *) pdata;
//	//iprintf("Data passed to Pulse5(): %d\n",data);
//	int pulses;
//
//	while (1) {
//		OSSemPend(&SemPulse, 1); //wait forever, then countUP
//		pulses = countUP;
//		for (int n = 0; n < pulses; n++) {
//			iprintf("%d", n);
//			//OSTimeDly(TICKS_PER_SECOND); // good to put wait time here.. between pulses.
//			iprintf("\n");
//			//Toggle the output state of Pin J1-17. Hopefully...
//			if (SW_TP1)
//				SW_TP1.clr(); //if high then toggle low
//			else
//				SW_TP1.set(); //if low then toggle high
//
//			//            if (Pins[PINTP])
//			//                Pins[PINTP] = LOW; //if high then toggle low
//			//            else
//			//                Pins[PINTP]; //  toggle high
//		}
//		//XX OSSemPost(&SemCycleComplete);
//	}
//}


void initDMATIMER1() {
	TS1Count = 0; //initalize interrupt counter TS1 (DMATIMER1 Time Slice
	sim2.timer[0].tmr = 0x001A; //system clock divided by 1
	sim2.timer[0].txmr = 0x00;
	sim2.timer[0].ter |= 0x02;
	sim2.timer[0].trr = TSR * 2; //TSR MATLAB
	sim2.timer[0].tcn = 1;


	///from 5270 code set /// DO NOT USE	SetIntc((long) &func_isr, 19, 1, 1);
	SetIntc(0, (long)&func_isr, 32, 1 );

	sim2.timer[0].tmr |= 0x0001; //enable the timer
}

void doSetup() {
	//define the ID string
	strcat(idQ, CU_BUILD_MAJOR);
	strcat(idQ, CU_BUILD_MINOR);
	strcat(idQ, "(");
	strcat(idQ, BUILD_DATE);
	strcat(idQ, "-");
	strcat(idQ, BUILD_TIME);
	strcat(idQ, " by");
	strcat(idQ, CU_AUTHOR);
	strcat(idQ, ")");




	/*
	strcat(idCU, "|");
	strcat(idCU, CU_BUILD_MAJOR);
	strcat(idCU, CU_BUILD_MINOR);
	strcat(idCU, " (");
	strcat(idCU, BUILD_DATE);
	strcat(idCU, ".");
	strcat(idCU, BUILD_TIME);
	strcat(idCU, ")");
	 */
	strcat(verCU, CU_BUILD_MAJOR);
	strcat(verCU, CU_BUILD_MINOR);


	//set up and assign GPIO lines
#ifdef TESTCU
	//define GPIO for TESTCU configuration


	cout << endl << "Setting GPIO lines for TESTCU configuration" <<endl;


	//assign TSW_RUNPMA
	SW_RUNPMA.function(PIN_23_GPIO);
	//assign TSW_TP1
	SW_TP1.function(PIN_12_GPIO);

	//assign TSW_P18L12
	SW_P18L12.function(PIN_16_GPIO);
	//assign TSW_P18H12
	SW_P18H12.function(PIN_25_GPIO);
	//assign TSW_P18L34
	SW_P18L34.function(PIN_49_GPIO);
	//assign TSW_P18H34
	SW_P18H34.function(PIN_50_GPIO);
	//assign I2C_SCL
	//assign I2C_SDA

#else
#ifdef FLTCU
	//define GPIO for FLTCU configuration
	cout << endl <<  "Setting GPIO lines for FLTCU configuration" <<endl;

	//assign SW_RUNPMA
	SW_RUNPMA.function(PIN_23_GPIO);

	//assign SW_TP1
	SW_TP1.function(PIN_31_GPIO);

	//assign SW_P18L1
	SW_P18L1.function(PIN_39_GPIO);

	//assign SW_P18L2
	SW_P18L2.function(PIN_38_GPIO);

	//assign SW_P18L3
	SW_P18L3.function(PIN_37_GPIO);

	//assign SW_P18L4
	SW_P18L4.function(PIN_36_GPIO);

	//assign SW_P18H1
	SW_P18H1.function(PIN_35_GPIO);

	//assign SW_P18H2
	SW_P18H2.function(PIN_34_GPIO);

	//assign SW_P18H3
	SW_P18H3.function(PIN_33_GPIO);

	//assign SW_P18H4
	SW_P18H4.function(PIN_32_GPIO);

	//#else
#endif
#endif
}

void parseCMDPacket (char cmdPacket[I2C_MAX_BUF_SIZE]){

	/*
	 * calls the following helper routine
	 * parseBlockG
	 * parseBlockCU
	 * parseBlockIPD
	 * parseBlockPPU
	 */
	//define
	int currPOS = 0; //marks the current position of the cursor in the string
	string cmdVersion = ""; //length in LEN_MCAT_CMD_PACKET_VERSION
	string cmdBlockG = ""; //length of CU command Block LEN_MCAT_BLOCK_G
	string cmdBlockCU = ""; //length of CU command block LEN_CMD_BLOCK_CU
	string cmdBlockIPD = ""; //length LEN_CMD_BLOCK_IPD
	string cmdBlockPPU = ""; //length LEN_CMD_BLOCK_PPU

	cout << endl << "About to parse Command Packet containing " << strlen((char *) cmdPacket) << " bytes" << endl;
	cout << endl << "The packet contains: [" << cmdPacket << "]" << endl;

	//convert cmdPacket char array to C++ string object
	string strCMD (cmdPacket);

	//extract entire Block of commands for G
	cmdBlockG = strCMD.substr(currPOS, LEN_CMD_BLOCK_G);
	currPOS = currPOS + LEN_CMD_BLOCK_G;
	cout << endl << "G Block: [" << cmdBlockG << "]" << endl;
	parseBlockG(cmdBlockG);

	//extract entire Block of commands for CU
	cmdBlockCU = strCMD.substr(currPOS, LEN_CMD_BLOCK_CU);
	currPOS = currPOS + LEN_CMD_BLOCK_CU;
	cout << endl << "CU Block: [" << cmdBlockCU << "]" << endl;
	parseBlockCU(cmdBlockCU);

	if (cmdMode == MODE_CHANGE_TO_IDLE){
		cout << endl <<  "Mode must be set to IDLE" << endl;
	} else if (cmdMode == MODE_CHANGE_TO_STANDBY) {
		cout << endl << "Mode must be set to STANDBY" << endl;
	} else if (cmdMode == MODE_CHANGE_TO_RUN) {
		cout << endl << "Mode must be set to RUN" << endl;

	} else if (cmdMode == MODE_CHANGE_TO_RUN) {
		cout << endl << "Mode must be set to FIRE" << endl;
	}



	//Block PM support not in present version - skipping

	//extract entire Block IPD
	cmdBlockIPD = strCMD.substr(currPOS, LEN_CMD_BLOCK_IPD);
	currPOS = currPOS + LEN_CMD_BLOCK_IPD;
	cout << endl << "IPD Block: [" << cmdBlockIPD << "]" << endl;
	parseBlockIPD(cmdBlockIPD);


	//extract entire Block PPU
	cmdBlockPPU = strCMD.substr(currPOS, LEN_CMD_BLOCK_PPU);
	currPOS = currPOS + LEN_CMD_BLOCK_PPU;
	cout << endl << "PPU Block: [" << cmdBlockPPU << "]" << endl;
	parseBlockPPU(cmdBlockPPU);

	//Block MNPS support not in present version - skipping

	//Block SBITE support not in present version - skipping

	//we start in idle mode
	if (cmdMode == MODE_CHANGE_TO_IDLE)
	{
		controlPMA(OFF);
		control18Hmanual(1,OFF);
		control18Hmanual(2,OFF);
		control18Hmanual(3,OFF);
		control18Hmanual(4,OFF);
		control18L(1,OFF);
		control18L(2,OFF);
		control18L(3,OFF);
		control18L(4,OFF);
		controlTP1(OFF);

	}

	else if (cmdMode == MODE_CHANGE_TO_STANDBY)
	{
		controlPMA(ON);
		control18Hmanual(1,OFF);
		control18Hmanual(2,OFF);
		control18Hmanual(3,OFF);
		control18Hmanual(4,OFF);
		control18L(1,OFF);
		control18L(2,OFF);
		control18L(3,OFF);
		control18L(4,OFF);
		controlTP1(OFF);
	}

	else if (cmdMode == MODE_CHANGE_TO_RUN)
	{ 	controlPMA(ON);
	control18Hmanual(1,OFF);
	control18Hmanual(2,OFF);
	control18Hmanual(3,OFF);
	control18Hmanual(4,OFF);
	control18L(1,ON);
	control18L(2,ON);
	control18L(3,ON);
	control18L(4,ON);
	setTP1(freqTP1);
	controlTP1(ON);
	}
	else if (cmdMode == MODE_CHANGE_TO_FIRE)
	{
		controlPMA(ON);
		control18L(1,ON);
		control18L(2,ON);
		control18L(3,ON);
		control18L(4,ON);
		setTP1(freqTP1);
		controlTP1(ON);
		OSTimeDly(3*TICKS_PER_SECOND);
		if (cmdP18H1)
			control18Hmanual(1,ON);
		else
			control18Hmanual(1,OFF);

		if (cmdP18H2)
			control18Hmanual(2,ON);
		else
			control18Hmanual(2,OFF);

		if (cmdP18H3)
			control18Hmanual(3,ON);
		else
			control18Hmanual(3,OFF);
		if (cmdP18H4)
			control18Hmanual(4,ON);
		else
			control18Hmanual(4,OFF);
	}


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
	//process s_freqTP1
	s_freqTP1 = BlockIPD.substr(currPOS, LEN_CMD_BLOCK_IPD_TP1);
	freqTP1 = strtol(s_freqTP1.c_str(),&endptr,16);
	currPOS = currPOS + LEN_CMD_BLOCK_IPD_TP1;
	cout << "TP1 string [" << s_freqTP1 << "]" << endl;
	cout << "TP1 integer [" <<  freqTP1 << "]" << endl;
	//process s_countCh1
	s_countCh1 = BlockIPD.substr(currPOS, LEN_CMD_BLOCK_IPD_PCH1);
	countCh1 = strtol(s_countCh1.c_str(),&endptr,16);
	currPOS = currPOS + LEN_CMD_BLOCK_IPD_PCH1;
	cout << "PCH1 [" << s_countCh1 << "]" << endl;
	cout << "PCH1 integer [" <<  countCh1 << "]" << endl;
	//process s_freqTP2
	s_freqTP2 = BlockIPD.substr(currPOS, LEN_CMD_BLOCK_IPD_TP2);
	freqTP2 = strtol(s_freqTP2.c_str(),&endptr,16);
	currPOS = currPOS + LEN_CMD_BLOCK_IPD_TP2;
	cout << "TP2 string [" << s_freqTP2 << "]" << endl;
	cout << "TP2 integer [" <<  freqTP2 << "]" << endl;
	//process s_countCh2
	s_countCh2 = BlockIPD.substr(currPOS, LEN_CMD_BLOCK_IPD_PCH2);
	countCh2 = strtol(s_countCh2.c_str(),&endptr,16);
	currPOS = currPOS + LEN_CMD_BLOCK_IPD_PCH2;
	cout << "PCH2 [" << s_countCh2 << "]" << endl;
	cout << "PCH2 integer [" <<  countCh2 << "]" << endl;
	//process s_freqTP3
	s_freqTP3 = BlockIPD.substr(currPOS, LEN_CMD_BLOCK_IPD_TP3);
	freqTP3 = strtol(s_freqTP3.c_str(),&endptr,16);
	currPOS = currPOS + LEN_CMD_BLOCK_IPD_TP3;
	cout << "TP3 string [" << s_freqTP3 << "]" << endl;
	cout << "TP3 integer [" <<  freqTP3 << "]" << endl;
	//process s_countCh3
	s_countCh3 = BlockIPD.substr(currPOS, LEN_CMD_BLOCK_IPD_PCH3);
	countCh3 = strtol(s_countCh3.c_str(),&endptr,16);
	currPOS = currPOS + LEN_CMD_BLOCK_IPD_PCH3;
	cout << "PCH3 [" << s_countCh3 << "]" << endl;
	cout << "PCH3 integer [" <<  countCh3 << "]" << endl;

	//process s_freqTP4
	s_freqTP4 = BlockIPD.substr(currPOS, LEN_CMD_BLOCK_IPD_TP4);
	freqTP4 = strtol(s_freqTP4.c_str(),&endptr,16);
	currPOS = currPOS + LEN_CMD_BLOCK_IPD_TP4;
	cout << "TP4 string [" << s_freqTP4 << "]" << endl;
	cout << "TP4 integer [" <<  freqTP4 << "]" << endl;
	//process s_countCh4
	s_countCh4 = BlockIPD.substr(currPOS, LEN_CMD_BLOCK_IPD_PCH4);
	countCh4 = strtol(s_countCh4.c_str(),&endptr,16);
	currPOS = currPOS + LEN_CMD_BLOCK_IPD_PCH4;
	cout << "PCH4 [" << s_countCh4 << "]" << endl;
	cout << "PCH4 integer [" <<  countCh4 << "]" << endl;
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
	menuVersion = "6B";
	if (verCU == menuVersion) { //comparing two strings !
		//display menu for 6B
		//cout << "hoooray, it is version 6B" << endl;
		iprintf("\nMCAT Subsystem Test Commands [%s]\r\n",verCU);
		cout << "J. Show the Menu"<< endl;
		cout << "------------ PM Test Routines --------------------------------------" <<endl;
		cout << "P/p. Enable/Disable RUNPMA" << endl;
		cout << "------------ IPD Test Routines -------------------------------------" <<endl;
		cout << "A/a. Set F=1 Hz, enable P18L, TP1/disable TP1" << endl;
		cout << "B/b. Set F=10 Hz, enable P18L, TP1/disable TP1" << endl;
		cout << "C/c. Set F=20 Hz, enable P18L, TP1/disable TP1" << endl;
		cout << "D/d. Set F=30 Hz, enable P18L, TP1/disable TP1" << endl;
		cout << "E/e. Set F=40 Hz, enable P18L, TP1/disable TP1" << endl;
		cout << "F/f. Set F=50 Hz, enable P18L, TP1/disable TP1" << endl;
		cout << "------------ I2C Test Routines -------------------------------------" <<endl;
		cout << "S/s. Master mode send/recieve an message to/from on the I2C bus" << endl;
		cout << "M. Set telemetry test message buffer"<< endl;
		cout << "------------ Power Distribution Test Routines ----------------------" <<endl;
		cout << "I/i. Enable P18L1-4/Disable P18L1-4" << endl;
		cout << "W/w. Enable/Disable P18 for Ch. 4" << endl;
		cout << "X/x. Enable/Disable P18 for Ch. 3" << endl;
		cout << "Y/y. Enable/Disable P18 for Ch. 2" << endl;
		cout << "Z/z. Enable/Disable P18 for Ch. 1" << endl;
	}

	else {
		menuVersion = "6C";
		if (verCU == menuVersion) {


#ifndef HIDDENMENU

			//display menu for version 6C
			//cout << "Version 6C menu goes here" << endl;
			iprintf("\nMCAT Subsystem Test Commands [%s]\r\n",verCU);
			cout << "A/a - Enable/Disable RUN mode F=1 Hz" << endl;
			cout << "B/b - Enable/Disable RUN mode F=10 Hz" << endl;
			cout << "C/c - Enable/Disable RUN mode F=20 Hz" << endl;
			cout << "D/d - Enable/Disable RUN mode F=30 Hz" << endl;
			cout << "E/e - Enable/Disable RUN mode F=40 Hz" << endl;
			cout << "F/f - Enable/Disable RUN mode F=50 Hz" << endl;
			cout << "G/g - I2C Master Send/Receive" <<endl;
			cout << "H/h - Enable/Disable PM" << endl;
			cout << "I/i - Enable/Disable P18L1-4" << endl;
			cout << "J   - Display Menu" << endl;
			cout << "K   - Enable Ch. 1-4" << endl;
#ifdef TESTCU
			cout << "L   - Enable only Ch. 1,2,3" << endl;
			cout << "M   - Enable only Ch. 1,2,4" << endl;
#endif //TESTCU
			cout << "N   - Enable only Ch. 1,2" << endl;
#ifdef TESTCU
			cout << "O   - Enable only Ch. 1,3,4" << endl;
#endif //TESTCU
			cout << "P   - Enable only Ch. 1,3" << endl;
			cout << "Q   - Enable only Ch. 1,4" << endl;
			cout << "R   - Enable only Ch. 1" << endl;
#ifdef TESTCU
			cout << "S   - Enable only Ch. 2,3,4" << endl;
#endif //TESTCU
			cout << "T   - Enable only Ch. 2,3" << endl;
			cout << "U   - Enable only Ch. 2,4" << endl;
			cout << "V   - Enable only Ch. 2" << endl;
			cout << "W   - Enable only Ch. 3,4" << endl;
			cout << "X   - Enable only Ch. 3" << endl;
			cout << "Y   - Enable only Ch. 4" << endl;
			cout << "Z   - Disable Ch. 1-4" << endl;

#ifdef TESTCU
			cout << "!  Force Immediate Reboot of TESTCU" << endl;
			cout << "?  Print Uptime (seconds)" << endl;
#endif //TESTCU


#endif //ifndef HIDDENMENU

		}
		else {
			//display menu for unknown  version
			cout << "Menu for what version ? [" << verCU << "]" << endl;
		}

	};


}


void setNewPulseCount(){
	extern DWORD limitPulseCount;
	startPulseCount = PulseCount; //at start of action, what is the pulse count ?
	if (limitPulseCount > 0) {
		endPulseCount = startPulseCount + limitPulseCount + 1;
	} else {
		endPulseCount = 0;
	}
	debugPrint("Starting Pulse Count");
}

void disablePeripherals(){

	/*
	 * disable peripherals to test power reduction
	 */

	//Power Mgmt Low Register 1
	PERIPH_DISABLE_1_WIRE;
	PERIPH_DISABLE_I2C_2;
	PERIPH_DISABLE_I2C_3;
	PERIPH_DISABLE_I2C_4;
	PERIPH_DISABLE_I2C_5;
	PERIPH_DISABLE_DSPI_2;
	PERIPH_DISABLE_DSPI_3;
	PERIPH_DISABLE_UART_4;
	PERIPH_DISABLE_UART_5;
	PERIPH_DISABLE_UART_6;
	PERIPH_DISABLE_UART_7;
	PERIPH_DISABLE_UART_8;
	PERIPH_DISABLE_UART_9;

	//Power Mgmt High Register 0
	//PERIPH_DISABLE_PIT_0;
	PERIPH_DISABLE_PIT_1;
	PERIPH_DISABLE_PIT_2;
	PERIPH_DISABLE_PIT_3;
	PERIPH_DISABLE_ADC;
	PERIPH_DISABLE_DAC_0;
	PERIPH_DISABLE_USB_OTG;
	PERIPH_DISABLE_USB_HOST;
	PERIPH_DISABLE_MACNET_0;
	PERIPH_DISABLE_MACNET_1;
	PERIPH_DISABLE_ETHERNET_SWITCH_0;
	PERIPH_DISABLE_ETHERNET_SWITCH_1;

	//Power Mgmt Low Register 0
	PERIPH_DISABLE_CAN_0;
	PERIPH_DISABLE_CAN_1;
	PERIPH_DISABLE_UART_2;
	PERIPH_DISABLE_UART_3;



}

// Main task
void UserMain(void *pd) {

	//initialize semaphore structures.
	//	OSSemInit ( &P18H1Sem,0);
	//OSSemInit ( &P18H2Sem,0);
	//OSSemInit ( &P18H3Sem,0);
	//	OSSemInit ( &P18H4Sem,0);
	//
	//	OSSimpleTaskCreate(toggle18H1,Ch1Prio);
	//OSSimpleTaskCreate(toggle18H2,Ch2Prio);
	//OSSimpleTaskCreate(toggle18H3,Ch3Prio);
	//OSSimpleTaskCreate(toggle18H4,Ch4Prio);


	//strcat(idCU = CU_PROJ + ' Subsystem for BRICSAT-p. Version ' + CU_BUILD_MAJOR + CU_BUILD_MINOR + '(' + BUILD_DATE + '.' + BUILD_TIME + ')';



	//InitializeStack();
	//if (EthernetIP == 0)
	//	GetDHCPAddress();
	OSChangePrio(MAIN_PRIO);
	//EnableAutoUpdate();
	//EnableTaskMonitor();
	//EnableSmartTraps();

	doSetup(); //set GPIO pins, idCU strings
	disablePeripherals(); //try to reduce power

	I2CInit(address); // Initialize I2C with entered slave add
	printf("\r\nI2C Address set to %#x\r\n", address);
	cmdModeCurrent = MODE_CHANGE_TO_IDLE;



	disableAll(); //test PPUV8 Ch 3 - should be disabled at startup
	//displayCLIMenu(); ////THIS MENU CAN BE BLANK BUT CANNOT BE  EMPTY


	////////////////////////////////////////////////

	//define the banner header

	strcat(idCU, CU_PROJECT);
	strcat(idCU, "|");
	strcat(idCU,AppName); //TESTCU or FLTCU
	iprintf("\n\n\n%s\nVersion %s", idCU,idQ); //print with handy identifier string defined above.
	menu(); //interactive ground test menu on UART0TX/UARTORX
	while (1) {
		if (charavail()) {
			*buffer = 0x0000;
			gets((char*) buffer);





			menuVersion = "6B";
			if (verCU == menuVersion){
				//debugPrint("parse 6B commands");


				if (buffer[0] == 'S') {


					//cout<< "no Disabled I2C Master Transmit"<<endl;

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
					}
					menu();
				}  // case S
				else if (buffer[0] == 's') {

					//cout<< "not Disabled I2C Master Receive"<<endl;

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
					} else
						iprintf("Failed to read due to error:  %d\r\n", I2CStat);
					menu();
				} // Case s
#ifdef _MULTICHANNELI2C_H
				else if (buffer[0] == 'M') {
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
					menu();
				} // case M
#endif // _MULTICHANNELI2C_H
				else
					if (buffer[0] == 'J'){
						menu();	//do nothing, the menu will be shown.
					}// case J

				//}

					else if (buffer[0] == 'P') {
						controlPMA(ON);
						menu();
						*buffer = 0x0000;

					} //case P
					else if (buffer[0] == 'p') {
						controlPMA(OFF);
						menu();
						*buffer = 0x0000;
					} // case p
					else if (buffer[0] == 'W') {
						//Enable P18H4
						control18Hmanual(4,ON);
						menu();
						*buffer = 0x0000;
					} // case W
					else if (buffer[0] == 'w') {
						//Disable P18H4
						control18Hmanual(4, OFF);
						menu();
						*buffer = 0x0000;
					} // case w
					else if (buffer[0] == 'X') {
						//Enable P18H3
						control18Hmanual(3,ON);
						menu();
						*buffer = 0x0000;
					} //case X
					else if (buffer[0] == 'x') {
						//Disable P18H3
						control18Hmanual(3,OFF);
						menu();
						*buffer = 0x0000;
					} //case x
					else if (buffer[0] == 'Y') {
						//Enable P18H2
						control18Hmanual(2,ON);
						menu();
						*buffer = 0x0000;
					} //case Y
					else if (buffer[0] == 'y') {
						//Disable P18H2
						control18Hmanual(2,OFF);
						menu();
						*buffer = 0x0000;
					} //case y
					else if (buffer[0] == 'Z') {
						//Enable P18H1
						control18Hmanual(1,ON);
						menu();
						*buffer = 0x0000;
					} //case Z

					else if (buffer[0] == 'z') {
						control18Hmanual(1,OFF);
						menu();
						*buffer = 0x0000;
					} //case z
					else if (buffer[0] == 'A'){
						long inputFrequency=1; //sample set to 1 Hz
						//Set Frequency using setTP1
						setTP1(inputFrequency);
						//enable the P18L lines for the IPD section
						control18L(1,ON);
						control18L(2,ON);
						control18L(3,ON);
						control18L(4,ON);
						//enable Trigger pulses for all  controlTP1
						controlTP1(ON);
						//show the menu for sanity
						menu();
						*buffer = 0x0000;
					} // case A

					else if (buffer[0] == 'B'){
						long inputFrequency=10; //sample set to 10 Hz
						//Set Frequency using setTP1
						setTP1(inputFrequency);
						//enable the P18L lines for the IPD section
						control18L(1,ON);
						control18L(2,ON);
						control18L(3,ON);
						control18L(4,ON);
						//enable Trigger pulses for all  controlTP1
						controlTP1(ON);
						//show the menu for sanity
						menu();
						*buffer = 0x0000;
					} //case B


					else if (buffer[0] == 'C'){
						long inputFrequency=20; //sample set to 20 Hz
						//Set Frequency using setTP1
						setTP1(inputFrequency);
						//enable the P18L lines for the IPD section
						control18L(1,ON);
						control18L(2,ON);
						control18L(3,ON);
						control18L(4,ON);
						//enable Trigger pulses for all  controlTP1
						controlTP1(ON);
						//show the menu for sanity
						menu();
						*buffer = 0x0000;
					} //case C
					else if (buffer[0] == 'D'){
						long inputFrequency=30; //sample set to 30 Hz
						//Set Frequency using setTP1
						setTP1(inputFrequency);
						//enable the P18L lines for the IPD section
						control18L(1,ON);
						control18L(2,ON);
						control18L(3,ON);
						control18L(4,ON);
						//enable Trigger pulses for all  controlTP1
						controlTP1(ON);
						//show the menu for sanity
						menu();
						*buffer = 0x0000;
					} //case D

					else if (buffer[0] == 'E'){
						long inputFrequency=40; //sample set to 40 Hz
						//Set Frequency using setTP1
						setTP1(inputFrequency);
						//enable the P18L lines for the IPD section
						control18L(1,ON);
						control18L(2,ON);
						control18L(3,ON);
						control18L(4,ON);
						//enable Trigger pulses for all  controlTP1
						controlTP1(ON);
						//show the menu for sanity
						menu();
						*buffer = 0x0000;
					} //case E
					else if (buffer[0] == 'F'){



						long inputFrequency=50; //sample set to 50 Hz
						//Set Frequency using setTP1
						setTP1(inputFrequency);
						//enable the P18L lines for the IPD section
						control18L(1,ON);
						control18L(2,ON);
						control18L(3,ON);
						control18L(4,ON);
						//enable Trigger pulses for all  controlTP1
						controlTP1(ON);
						//show the menu for sanity
						menu();
						*buffer = 0x0000;
					} // case F
					else if (buffer[0] == 'a' || buffer[0] == 'b' || buffer[0] == 'c' || buffer[0] == 'd' || buffer[0] == 'e' || buffer[0] == 'f'){
						//disable TP1 regardless of the frequency
						control18L(1,OFF);
						control18L(2,OFF);
						control18L(3,OFF);
						control18L(4,OFF);
						controlTP1(OFF);

						menu();
						*buffer = 0x0000;
					} //case a-f
					else if (buffer[0] == 'I'){
						//Enable only the P18L lines for test
						control18L(1,ON);
						control18L(2,ON);
						control18L(3,ON);
						control18L(4,ON);
						menu();
						*buffer = 0x0000;
					} //case I
					else if (buffer[0] == 'i') {
						control18L(1,OFF);
						control18L(2,OFF);
						control18L(3,OFF);
						control18L(4,OFF);
						menu();
						*buffer = 0x0000;
					} //case i
#ifdef TESTCU
					else if (buffer[0] == '!') {
						debugPrint("TESTCU: Issuing ForceReboot command\n");
						ForceReboot();
					} //case !
					else if (buffer[0] == '?') {
						iprintf("Uptime(s): %d / MAC: %02X%02X%02X%02X%02X%02X\r\n",
								Secs, gConfigRec.mac_address[0], gConfigRec.mac_address[1],
								gConfigRec.mac_address[2], gConfigRec.mac_address[3],
								gConfigRec.mac_address[4], gConfigRec.mac_address[5]);
						menu();
						*buffer = 0x0000;
					} //case ?
#endif //TESTCU

			}



			//else {
			menuVersion = "6C";
			if (verCU == menuVersion){
				//	debugPrint("parse 6C commands ---------------------------------------");

				/*		Thruster Channel P18H activation table

					decimal	binary	cmd (on)	cmd (off)
				selection word:	0	0000	N/A	Z	DEFAULT
				[Ch1Ch2Ch3Ch4]	1	0001	Y	y
					2	0010	X	x
					3	0011	W	w
					4	0100	V	v
					5	0101	U	u
					6	0110	T	t
					7	0111	S	s	ignore for Bricsat
					8	1000	R	r
					9	1001	Q	q
					10	1010	P	p
					11	1011	O	o	ignore for Bricsat
					12	1100	N	n
					13	1101	M	m	ignore for Bricsat
					14	1110	L	l	ignore for Bricsat
					15	1111	K	k



				Other Commands selection table
				Command	action		cmd (on)	cmd (off)
				Show Menu	displays menu		J	N/A
				Control P18L	controls P18L1-4		I	i
				Control Power Management	controls PM-A		H	h
				I2C Master Send	multi-master I2C send		G	N/A	ignore for Bricsat
				I2C Master Receive	multi-master I2C test		g	N/A	ignore for Bricsat
				I2C Telemetry Test	telemetry msg send test		j	N/A	ignore for Bricsat
				Set Run Mode to 50 Hz	Set F=50 Hz, enable P18L		F	f
				Set Run Mode to 40 Hz	Set F=40 Hz, enable P18L		E	e
				Set Run Mode to 30 Hz	Set F=30 Hz, enable P18L		D	d
				Set Run Mode to 20 Hz	Set F=20 Hz, enable P18L		C	c
				Set Run Mode to 10 Hz	Set F=10 Hz, enable P18L		B	b
				Set Run Mode to 1 Hz	Set F=1 Hz, enable P18L		A	a
				 */








				if (buffer[0] == 'G') {
					//Multi-master I2C send

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
					}
					menu();
				}  // case G
				else if (buffer[0] == 'g') {

					//cout<< "not Disabled I2C Master Receive"<<endl;

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
					} else
						iprintf("Failed to read due to error:  %d\r\n", I2CStat);
					menu();
				} // Case g
#ifdef _MULTICHANNELI2C_H
				else if (buffer[0] == 'j') {
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
					menu();
				} // case j
#endif // _MULTICHANNELI2C_H


				else if (buffer[0] == 'A'){
					long inputFrequency=1; //sample set to 1 Hz
					//Set Frequency using setTP1
					setTP1(inputFrequency);
					//enable the P18L lines for the IPD section
					control18L(1,ON);
					control18L(2,ON);
					control18L(3,ON);
					control18L(4,ON);
					//enable Trigger pulses for all  controlTP1
					controlTP1(ON);
					//show the menu for sanity
					menu();
					*buffer = 0x0000;
				} // case A

				else if (buffer[0] == 'B'){
					long inputFrequency=10; //sample set to 10 Hz
					//Set Frequency using setTP1
					setTP1(inputFrequency);
					//enable the P18L lines for the IPD section
					control18L(1,ON);
					control18L(2,ON);
					control18L(3,ON);
					control18L(4,ON);
					//enable Trigger pulses for all  controlTP1
					controlTP1(ON);
					//show the menu for sanity
					menu();
					*buffer = 0x0000;
				} //case B


				else if (buffer[0] == 'C'){
					long inputFrequency=20; //sample set to 20 Hz
					//Set Frequency using setTP1
					setTP1(inputFrequency);
					//enable the P18L lines for the IPD section
					control18L(1,ON);
					control18L(2,ON);
					control18L(3,ON);
					control18L(4,ON);
					//enable Trigger pulses for all  controlTP1
					controlTP1(ON);
					//show the menu for sanity
					menu();
					*buffer = 0x0000;
				} //case C
				else if (buffer[0] == 'D'){
					long inputFrequency=30; //sample set to 30 Hz
					//Set Frequency using setTP1
					setTP1(inputFrequency);
					//enable the P18L lines for the IPD section
					control18L(1,ON);
					control18L(2,ON);
					control18L(3,ON);
					control18L(4,ON);
					//enable Trigger pulses for all  controlTP1
					controlTP1(ON);
					//show the menu for sanity
					menu();
					*buffer = 0x0000;
				} //case D

				else if (buffer[0] == 'E'){
					long inputFrequency=40; //sample set to 40 Hz
					//Set Frequency using setTP1
					setTP1(inputFrequency);
					//enable the P18L lines for the IPD section
					control18L(1,ON);
					control18L(2,ON);
					control18L(3,ON);
					control18L(4,ON);
					//enable Trigger pulses for all  controlTP1
					controlTP1(ON);
					//show the menu for sanity
					menu();
					*buffer = 0x0000;
				} //case E
				else if (buffer[0] == 'F'){

					//				/*
					//				 * disable peripherals to test power reduction
					//				 */
					//				PERIPH_DISABLE_1_WIRE;
					//				PERIPH_DISABLE_I2C_2;
					//				PERIPH_DISABLE_I2C_3;
					//				PERIPH_DISABLE_I2C_4;
					//				PERIPH_DISABLE_I2C_5;
					//				PERIPH_DISABLE_DSPI_2;
					//				PERIPH_DISABLE_DSPI_3;
					//				PERIPH_DISABLE_UART_4;
					//				PERIPH_DISABLE_UART_5;
					//				PERIPH_DISABLE_UART_6;
					//				PERIPH_DISABLE_UART_7;
					//				PERIPH_DISABLE_UART_8;
					//				PERIPH_DISABLE_UART_9;

					long inputFrequency=50; //sample set to 50 Hz
					//Set Frequency using setTP1
					setTP1(inputFrequency);
					//enable the P18L lines for the IPD section
					control18L(1,ON);
					control18L(2,ON);
					control18L(3,ON);
					control18L(4,ON);
					//enable Trigger pulses for all  controlTP1
					controlTP1(ON);
					//show the menu for sanity
					menu();
					*buffer = 0x0000;
				} // case F
				else if (buffer[0] == 'a' || buffer[0] == 'b' || buffer[0] == 'c' || buffer[0] == 'd' || buffer[0] == 'e' || buffer[0] == 'f'){
					//disable TP1 regardless of the frequency
					control18L(1,OFF);
					control18L(2,OFF);
					control18L(3,OFF);
					control18L(4,OFF);
					controlTP1(OFF);

					menu();
					*buffer = 0x0000;
				} //case a-f
				else if (buffer[0] == 'H') {
					controlPMA(ON);
					menu();
					*buffer = 0x0000;

				} //case H
				else if (buffer[0] == 'h') {
					controlPMA(OFF);
					menu();
					*buffer = 0x0000;
				} // case h


				else if (buffer[0] == 'I'){
					//Enable only the P18L lines for test
					control18L(1,ON);
					control18L(2,ON);
					control18L(3,ON);
					control18L(4,ON);

					menu();
					*buffer = 0x0000;
				} //case I
				else if (buffer[0] == 'i') {
					control18L(1,OFF);
					control18L(2,OFF);
					control18L(3,OFF);
					control18L(4,OFF);

					menu();
					*buffer = 0x0000;
				} //case i

				else
					if (buffer[0] == 'J'){
						menu();	//do nothing, the menu will be shown.
					}// case J

				/// Thruster Channel P18 activation section
					else if (buffer[0] == 'K') {
						///CH1-4
						control18Hmanual(1,ON);
						control18Hmanual(2,ON);
						control18Hmanual(3,ON);
						control18Hmanual(4,ON);
						setNewPulseCount();
						toggleHFlag=TRUE;
						menu();
						*buffer = 0x0000;
					} //case K


#ifdef TESTCU
					else if (buffer[0] == 'L') {
						control18Hmanual(1,ON);
						control18Hmanual(2,ON);
						control18Hmanual(3,ON);
						control18Hmanual(4,OFF);
						setNewPulseCount();
						toggleHFlag=TRUE;
						menu();
						*buffer = 0x0000;
					} //case L


					else if (buffer[0] == 'M') {
						control18Hmanual(1,ON);
						control18Hmanual(2,ON);
						//control18Hmanual(3,ON);
						control18Hmanual(4,ON);
						setNewPulseCount();
						toggleHFlag=TRUE;
						menu();
						*buffer = 0x0000;
					} //case M
#endif //TESTCU

					else if (buffer[0] == 'N') {
						control18Hmanual(1,ON);
						control18Hmanual(2,ON);
						control18Hmanual(3,OFF);
						control18Hmanual(4,OFF);
						setNewPulseCount();
						toggleHFlag=TRUE;
						menu();
						*buffer = 0x0000;
					} //case N
					else if (buffer[0] == 'O') {
						control18Hmanual(1,ON);
						control18Hmanual(2,OFF);
						control18Hmanual(3,ON);
						control18Hmanual(4,ON);
						setNewPulseCount();
						toggleHFlag=TRUE;
						menu();
						*buffer = 0x0000;
					} //case O
					else if (buffer[0] == 'P') {
						control18Hmanual(1,ON);
						control18Hmanual(2,OFF);
						control18Hmanual(3,ON);
						control18Hmanual(4,OFF);
						setNewPulseCount();
						toggleHFlag=TRUE;
						menu();
						*buffer = 0x0000;
					} //case P
					else if (buffer[0] == 'Q') {
						control18Hmanual(1,ON);
						control18Hmanual(2,OFF);
						control18Hmanual(3,OFF);
						control18Hmanual(4,ON);
						setNewPulseCount();
						toggleHFlag=TRUE;
						menu();
						*buffer = 0x0000;
					} //case Q
					else if (buffer[0] == 'R') {
						control18Hmanual(1,ON);
						control18Hmanual(2,OFF);
						control18Hmanual(3,OFF);
						control18Hmanual(4,OFF);
						setNewPulseCount();
						toggleHFlag=TRUE;
						menu();
						*buffer = 0x0000;
					} //case R
#ifdef TESTCU
					else if (buffer[0] == 'S') {
						control18Hmanual(1,OFF);
						control18Hmanual(2,ON);
						control18Hmanual(3,ON);
						control18Hmanual(4,ON);
						setNewPulseCount();
						toggleHFlag=TRUE;
						menu();
						*buffer = 0x0000;
					} //case S
#endif //TESTCU
					else if (buffer[0] == 'T') {
						control18Hmanual(1,OFF);
						control18Hmanual(2,ON);
						control18Hmanual(3,ON);
						control18Hmanual(4,OFF);
						setNewPulseCount();
						toggleHFlag=TRUE;
						menu();
						*buffer = 0x0000;
					} //case T
					else if (buffer[0] == 'U') {
						control18Hmanual(1,OFF);
						control18Hmanual(2,ON);
						control18Hmanual(3,OFF);
						control18Hmanual(4,ON);
						setNewPulseCount();
						toggleHFlag=TRUE;
						menu();
						*buffer = 0x0000;
					} //case U
					else if (buffer[0] == 'V') {
						control18Hmanual(1,OFF);
						control18Hmanual(2,ON);
						control18Hmanual(3,OFF);
						control18Hmanual(4,OFF);
						setNewPulseCount();
						toggleHFlag=TRUE;
						menu();
						*buffer = 0x0000;
					} //case V
					else if (buffer[0] == 'W') {
						control18Hmanual(1,OFF);
						control18Hmanual(2,OFF);
						control18Hmanual(3,ON);
						control18Hmanual(4,ON);
						setNewPulseCount();
						toggleHFlag=TRUE;
						menu();
						*buffer = 0x0000;
					} //case W
					else if (buffer[0] == 'X') {
						control18Hmanual(1,OFF);
						control18Hmanual(2,OFF);
						control18Hmanual(3,ON);
						control18Hmanual(4,OFF);
						setNewPulseCount();
						toggleHFlag=TRUE;
						menu();
						*buffer = 0x0000;
					} //case X

					else if (buffer[0] == 'Y') {
						control18Hmanual(1,OFF);
						control18Hmanual(2,OFF);
						control18Hmanual(3,OFF);
						control18Hmanual(4,ON);
						setNewPulseCount();
						toggleHFlag=TRUE;

						menu();
						*buffer = 0x0000;
					} //case Y
					else if (buffer[0] == 'Z') {
						control18Hmanual(1,OFF);
						control18Hmanual(2,OFF);
						control18Hmanual(3,OFF);
						control18Hmanual(4,OFF);
						menu();
						*buffer = 0x0000;
					} //case Z

				/// End Thruster Channel P18 activation section
#ifdef TESTCU
					else if (buffer[0] == '!') {
						debugPrint("TESTCU: Issuing ForceReboot command");
						ForceReboot();
					} //case !
#endif //TESTCU
					else if (buffer[0] == '?') {

						//cout << "idQ is: [" << idQ << "]" << "Length: " << strlen(idQ) << endl;

						iprintf("||%s|%02X%02X%02X%02X%02X%02X|%ds|%s||\r\n",
								AppName,
								gConfigRec.mac_address[0], gConfigRec.mac_address[1],
								gConfigRec.mac_address[2], gConfigRec.mac_address[3],
								gConfigRec.mac_address[4], gConfigRec.mac_address[5],Secs,idQ);

						menu();
#ifdef HIDDENMENU
						cout << "[A/a/B/b/C/c/D/d/E/e/F/f/G/g/H/I/i/J/j/K/N/P/Q/R/T/U/V/W/X/Y/Z/?]" << endl;
#endif //HIDDENMENU
						*buffer = 0x0000;

					} //case ?





			}


			//else {
			//debugPrint("Could not figure out which command version to handle input parsing for");
			//}
		}



		////////////////////////////////// end of charavail() selection routine ///////////////////////


		//#ifdef _MULTICHANNELI2C_H
		/*
		 * if (I2CRXAvail()) {
			OSTimeDly(2); // Delay 100 ms to read all input data

			while (I2CRXAvail()) {
				*inbuf++ = I2CGetByte();
			}
			inbuf = I2CInputBuffer;
			printf("must parse Characters found in the I2C Input buffer: [%s]\r\n", inbuf);
			cout << "[" << I2CInputBuffer << "]" <<endl;
			parseCMDPacket(I2CInputBuffer); //parse incoming cmd packet into relevant global variables
			setNewMode(cmdMode, cmdModeCurrent); //compare current mode and set new mode


		}//I2CRXAvail
		*/

		if ((PulseCount >= endPulseCount) && (toggleHFlag))  {
#ifdef GROUNDTESTING
			cout << "Pulse Limit: " << limitPulseCount << " Start: " << startPulseCount << "End: " << endPulseCount << endl;
#endif //GROUNDTESTING
			control18Hmanual(1,OFF);
			control18Hmanual(2,OFF);
			control18Hmanual(3,OFF);
			control18Hmanual(4,OFF);
			toggleHFlag=FALSE;

		}



	}//while loop infinite ..
}

