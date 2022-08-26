/*
 * main.cpp for MCAT-2CU-PS3-OLD
 * for M-CAT 1-ch thruster control unit (Netburner MOD5270B with MOD-DEV-70 eval board)
 * Author: Samudra Haque N3RDX (samudra@gwu.edu)
 */

//////////////////////////////////////////////////// Pin Assignment
/*
 * updated 8/21/2013 SH
 * MOD5270B Pin-Outs with MOD-DEV-70 Board
 * J2-34; SW3 controlling P15H to Ch. 3 PPU V7x
 * J2-36; SW1 controlling P15H to Ch. 1 PPU V7x
 * J2-37; TP  common trigger to all PPU (to be modified later).
 * J2-38; SW2 controlling P15H to Ch. 2 PPU V7x
 */

//////////////////////////////////////////////////// Version History
/*
 * Rev 4G 201308211226 inverted sense of logic for RLY SW 1-3 (Ch. 1 - 3)
 * Rev 4F 201308211003 JD SH with 3 channel and 5 Frequency options
 * Rev 4E 201307251254 testin PPUV8 (FAN3227TMX) timing with 200 uS TP pos width, 200 uS Pre-TP MCH, 200 uS Post-TP MCL
 * Rev 4D 201306111639 testing J2-36 signaling with optocoupler and relay switch
 * Rev 4C 201306091527 tested J2-37 signaling with optocoupler and relay switch
 * Rev 4B 201304011845 general 3V/5V level transl. testing for MCAT-1CU
 * Rev 4A 201304011100 used J2[37] with 74LVX4245 3V/5V level transl. cct.
 * Rev 37C 201303132319 testing GPIO functions w/ disabled DMA timer on MOD-DEV-70
 * Software version continued from GPIOTest application (C6 201208042244)
 * Code includes segments of GPIOTest and test-NB-Semaphore (201208011503)
 *
 * Aug 12 . Julie added pin J2[34] to command PPU number 3
 *
 */

///////////////////////////////////////////////////// Version Block
#define BUILD_MAJOR "4"  // numeric
#define BUILD_MINOR "G" // alpha only
#define BUILD_TIMESTAMP "201308211226"
#define BUILD_APP_TASKMON "M2CU-4G"
#define BUILD_APP_TITLE "Micro-Cathode Arc Thruster 2-Ch Control Unit - Remote Test Program"
#define VERSION_LEN 30
//#define NTP_SERVER_IP "199.241.31.96" //  WARNING Need to select correct time server
#define NTP_SERVER_POOL "0.pool.ntp.org"

////////////////////////////////////////////////////// INCLUDES v
#include "predef.h" //NB template
#include <stdio.h> //NB template
#include <ctype.h> //NB template
#include <startnet.h> //NB template
#include <autoupdate.h> //NB template
#include <dhcpclient.h> //NB template
#include <taskmon.h> //NB template
#include <nbtime.h> /* Include for NTP functions*/
#include <udp.h>
#include <time.h>
#include <string.h>
#include <string>
#include <iosys.h>
#include <utils.h>
/*include for TCP stuff*/
#include <ip.h>
#include <dns.h>
#include <tcp.h>
//#include "clientweb.h"
#include <htmlfiles.h>
#include <ucos.h>
//#include <iostream.h>
//#include <iostream>
#include <pins.h>
#include <sim5270.h> // reqd for ISR
#include <cfinter.h>
#include <math.h>

// Disable SmartTraps when in debug mode
//#ifdef _DEBUG
//#include <NetworkDebug.h>
//#else
//#include <smarttrap.h>
//#endif
#include <smarttrap.h>
using namespace std;

/////////////////////////////////////////////////////////// INCLUDES ^

extern "C" {
    void UserMain(void * pd);
    void displayCLIMenu();
    void displayConfig();
    void doPulses(void *pdata);
    void stopPulses(void *pdata);
    //    void doTP(void *pdata);
    void initDMATIMER1();

    void SetIntc(long func, int vector, int level, int prio); //sets up the 5270 interrupt controller
    void tzsetchar(char * tzenv);
    void ShowLocalIPAddr(int sock, PCSTR url);
    void ShowRemoteIPAddr(int sock, PCSTR url);
    void ShowAppRevision(int sock, PCSTR url);
    void ShowImpulseComponentEvents(int sock, PCSTR url);
    void PrintTimeStruct(struct tm&bt);
    void pollNTPServer();
    void writeTimeStampUTC();
    void htmlDisplayUTCClock(int sock, PCSTR url);
    void setDefaults();
    void disableAll();
}

///////////////////////////////////////////////////////////// GLOBALS

const char * AppName = BUILD_APP_TASKMON;
const char * testString = "Hello World!";
const char
*dow_str[] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT", "\0" };

char testArrayChars[50] = "Hi, There!";
char gPostBuf[1000]; /// HTML form processing ?

DWORD doPulseStack[USER_TASK_STK_SIZE];
//DWORD doTPStack[USER_TASK_STK_SIZE];
DWORD uint32_counter = 0; //Initalize interrupt counter
DWORD PulseCount = 0; //Initialize whole pulse count
DWORD MaxCount = 1; //Initalize SPC/SPN

IPADDR ntp_srvr_addr; //placeholder for NTP server Ip address (from DNS lookup)

int TS1Count = 0; //DMA TIMER1 Time Step Count
int testVar = { 0 }; // for HTML output
string lastActivityHTML;

bool AssignedDHCP = FALSE; // if DHCP failed.. use static IP addr ?
bool Continuous = FALSE; // variable for SPC=C (HTML UI) condition.

// Semaphore definitions
OS_SEM SemPulse;
OS_SEM SemTP;

// Timing Defaults
//All timing units (IRQCount) are based upon TSR (based upon REFVAL) derived from DMATIMERCALC2.m
//int REFVAL = 67091 for 1.8 mS, 367 for 10 uS;
int TSRD = 367; //Timebase in REFVAL units (TS)
int TSR = TSRD;

/*
 *  * Original source of timing sequence (DMATIMERV2.m) from Taisen Zhuang, 2010-2011
 *


 // TSR timing for each event in sequence
 int MCHCD = 0; //assumed that EMH is turned on at initial, count t=0
 int TPHCD = 182; //Turn on Trigger Pulse at TSR ####
 int TPLCD = 364; //Turn off Trigger Pulse at TSR ####
 int MCLCD = 564; //Turn of Magnetic Coil ####
 int EOCCD = 568; //End of Cycle value - Default 1 Hz
 */

//Following timing block for PPUV7 Hybrid V8 - Samudra 2013 7/30
int MCHCD = 0;
int TPHCD = 30;
int TPLCD = 40;
int MCLCD = 70;
int EOCCD = 99928; // system default F=1 Hz, with the following parameters.

/*Events (inclusive of rise/fall times):
 MCH 0 mS
 TPH 0.3008 mS
 TPL 0.4016 mS
 MCL 0.7024 mS
 EOC 0.710732 mS
 Checking Total time period for 1407 full cycles is: 1 seconds

 [MCF5270 DMA TIMER and Interrupt Count Values]

 Time Step (TSR): 10 uS
 REFVAL: 367
 DIVIDER:1
 PRESCALER:1

 [TS Counter Values (MCHC, TPHC, TPLC, MCLC, EOCC)]
 in ascending order of event time

 0         0
 0.0003   30.0000
 0.0004   40.0000
 0.0007   70.0000
 0.0007   71.0000

 [Table of Frequency vs td (TS Counts)]
 1       99928*/





//Timing components
int MCHC = MCHCD;
int TPHC = TPHCD;
int TPLC = TPLCD;
int MCLC = MCLCD;
int EOCC = EOCCD;

//matching variables for actual time (mS) display through HTML.
double MCHCT = 0;
double TPHCT = 0;
double TPLCT = 0;
double MCLCT = 0;
double EOCCT = 0;
char MCHCTS[5]; //string to hold the value of MCHCTS in X.XX format
char TPHCTS[5];
char TPLCTS[5];
char MCLCTS[5];
char EOCCTS[5];
int DIVIDER = 1;
int PRESCALER = 1;
double INTSYSCLK = 147456000;
double CLOCKFREQ = INTSYSCLK / 2;

// Logic definitions
int HIGH = 1; int NHIGH = 0;
int LOW = 0; int NLOW = 1;

// Pin Selection for SB70LC unused in MOD5270B
//int PINMC = 15; //PTIMER7 //BJT Inverter - could be any pin (SB70LC, JP1-1 to JP1-17)
//int PINTP = 16; //PFECI2C0 //non-inverted be any pin (SB70LC, JP1-1 to JP1-17)
//int PINTP=17; //actually could be any pin (SB70LC, JP1-1 to JP1-17)

int countUP; //interrupt cycle

INTERRUPT(func_isr, 0x2600)
{
    sim.timer[0].ter |= 0x02; //Clear the DTIM0 ref event flag
    // we acknowledge the INTERRUPT, but check first if our PulseCount has exceeded MaxCount
    // meanwhile, the ISR is still running, and can do other functions, the program will not output signals
    // unless desired
    if ((PulseCount < MaxCount) || (Continuous == TRUE)) {
        if (TS1Count == MCHC) {
            //we must activate magnetic coil here MCH
            //Pins[PINMC] = NHIGH; //(inverted) activate magnetic coil
            iprintf("U");
            TS1Count++;
        } else {
            if (TS1Count == TPHC) {
                //Pins[PINTP] = HIGH; //activate trigger pulse
                //Pins[PINTP] = HIGH; //activate trigger pulse
                J2[37].clr(); // inverted due to PPUV7x/V8 hybrid
                ////// test 3V > 5V level transl. - signal TP1 ON
                TS1Count++;
            } else {
                {
                    if (TS1Count == TPLC) {
                        //Pins[PINTP] = LOW; //deactivate trigger pulse
                        //Pins[PINTP] = LOW; //deactivate trigger pulse
                        J2[37].set();
                        //inverted due to PPUV7x/V8 hybrid
                        ////// test 3V > 5V level transl. - signal TP1 OFF
                        TS1Count++;
                    } else {
                        if (TS1Count == MCLC) {
                            //we must deactivate magnetic coil here MCL
                            //Pins[PINMC] = NLOW; //(inverted) deactivate magnetic coil
                            iprintf("D");
                            TS1Count++;
                        } else {

                            if (TS1Count == EOCC) { // end cycle after delay
                                TS1Count = 0; //restart
                                PulseCount++;
                                iprintf(" %d ",PulseCount);
                            } else
                                TS1Count++; //go to next cycle
                        }
                    }
                }
            }
        }
    }
}

void disableAll() {
    iprintf("Z");
    J2[37].clr(); //Set initial state of J2[37] to LOW
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

void doPulses(void *pdata) {
    //WORD data = * (WORD *) pdata;
    //iprintf("Data passed to Pulse5(): %d\n",data);
    int pulses;

    while (1) {
        OSSemPend(&SemPulse, 1); //wait forever, then countUP
        pulses = countUP;
        for (int n = 0; n < pulses; n++) {
            iprintf("%d", n);
            //OSTimeDly(TICKS_PER_SECOND); // good to put wait time here.. between pulses.
            iprintf("\n");
            //Toggle the output state of Pin J1-17. Hopefully...
            if (J2[37])
                J2[37].clr(); //if high then toggle low
            else
                J2[37].set(); //if low then toggle high

            //            if (Pins[PINTP])
            //                Pins[PINTP] = LOW; //if high then toggle low
            //            else
            //                Pins[PINTP]; //  toggle high
        }
        //XX OSSemPost(&SemCycleComplete);
    }
}

void displayCLIMenu() {
    iprintf("\r\n--- %s Remote Test Program ---\r\n", BUILD_APP_TASKMON);
    iprintf("--- Micro-Cathode Arc Thruster PhoneSat Experiment/MAPERS [GWU/NASA ARC]\n");
    //pollNTPServer();
    writeTimeStampUTC();
    iprintf("0. Show %s Version\r\n", BUILD_APP_TASKMON);
    iprintf("1. Set F=1 Hz (continuous)\r\n");
    iprintf("2. Set F=2 Hz (continuous)\r\n");
    iprintf("3. Set F=5 Hz (continuous) -- not enabled yet in code \r\n");
    iprintf("4. Set F=7 Hz (continuous) -- not enabled yet in code \r\n");
    iprintf("5. Set F=10 Hz (continuous) -- not enabled yet in code \r\n");
    //iprintf("4. Pulse HIGH/LOW (50%% duty cycle, 1000 times)\r\n");
    iprintf("6. ENABLE MCAT pulse train\r\n");
    iprintf("7. Disable o/p signals\r\n");
    iprintf("8. DISABLE MCAT pulse train\r\n");
    iprintf("9. Restart\r\n");
    iprintf("F. ACTIVATE LED8 & TP1\r\n");
    iprintf("G. DEACTIVATE LED8 & TP1\r\n");
    iprintf("H. ACTIVATE LED1\r\n");
    iprintf("J. DEACTIVATE LED1\r\n");
    iprintf("Z/z. ENABLE/DISABLE uCAT Ch. 1\r\n");
    iprintf("Y/y. ENABLE/DISABLE uCAT Ch. 2\r\n");
    // added by Julie on aug 12
    iprintf("X/x. ENABLE/DISABLE uCAT Ch. 3\r\n");
    iprintf("\n");
}

void displayConfig() {
    iprintf("\r\n%s\n%s (%s.%s) Build (%s)\n", BUILD_APP_TITLE,
            BUILD_APP_TASKMON, BUILD_MAJOR, BUILD_MINOR, BUILD_TIMESTAMP);
    iprintf("Local IP: ");
    ShowIP(EthernetIP);
    iprintf("\n");
}

void initDMATIMER1() {
    TS1Count = 0; //initalize interrupt counter TS1 (DMATIMER1 Time Slice
    sim.timer[0].tmr = 0x001A; //system clock divided by 1
    sim.timer[0].txmr = 0x00;
    sim.timer[0].ter |= 0x02;
    sim.timer[0].trr = TSR * 2; //TSR MATLAB
    sim.timer[0].tcn = 1;
    SetIntc((long) &func_isr, 19, 1, 1);
    sim.timer[0].tmr |= 0x0001; //enable the timer
}

// PrintTimeStruct - Print the time to stdout, which is the debug serial port by default.
void PrintTimeStruct(struct tm &bt) {
    //extern const char * testString;
    iprintf("%d/%d/%d day: %d (%s) %02d:%02d:%02D", bt.tm_mon + 1, bt.tm_mday,
            bt.tm_year + 1900, bt.tm_yday, dow_str[bt.tm_wday], bt.tm_hour,
            bt.tm_min, bt.tm_sec);
}
void writeTimeStampUTC() {
    time_t currentTime;
    struct tm *TIMESTAMP;
    currentTime = time(NULL); //placeholder current sysclock
    TIMESTAMP = gmtime(&currentTime);
    iprintf("Timestamp (UTC): %s\n", asctime(TIMESTAMP));
}
//iprintf(">>>>>>>>>>> %d <<<<<<<<<<<<", TIMESTAMP->tm_year + 1900);

void htmlDisplayUTCClock(int sock, PCSTR url) {
    time_t currentTime;
    struct tm *TIMESTAMP;
    char htmlUTCClock[80];
    // timestamp variables
    int TIMESTAMP_year;
    int TIMESTAMP_mon;
    int TIMESTAMP_day;
    int TIMESTAMP_hour;
    int TIMESTAMP_min;
    int TIMESTAMP_sec;

    currentTime = time(NULL); //placeholder current sysclock
    TIMESTAMP = gmtime(&currentTime);

    TIMESTAMP_year = TIMESTAMP->tm_year + 1900;
    TIMESTAMP_mon = TIMESTAMP->tm_mon + 1;
    TIMESTAMP_day = TIMESTAMP->tm_mday;
    TIMESTAMP_hour = TIMESTAMP->tm_hour;
    TIMESTAMP_min = TIMESTAMP->tm_min;
    TIMESTAMP_sec = TIMESTAMP->tm_sec;
    sprintf(htmlUTCClock, "%d/%d/%d-%d:%d:%d<BR>%s", TIMESTAMP_year,
            TIMESTAMP_mon, TIMESTAMP_day, TIMESTAMP_hour, TIMESTAMP_min,
            TIMESTAMP_sec, BUILD_APP_TASKMON);
    writestring(sock, htmlUTCClock);

}
// IPtoString - Convert IP addr to a string from Pg 74 of NNDK Netburner Programmers Guide
void IPtoString(IPADDR ia, char *s) {
    PBYTE ipb = (PBYTE) &ia;
    siprintf(s, "%d.%d.%d.%d", (int) ipb[0], (int) ipb[1], (int) ipb[2],
             (int) ipb[3]);
}

// Show LocalIPAddr - Simple routine for user comfort when using Web Interface
void ShowLocalIPAddr(int sock, PCSTR url) {
    char buf[80];
    IPtoString(GetSocketLocalAddr(sock), buf);
    writestring(sock, buf);
}

// Display program details on the HTML webpage.
void ShowAppRevision(int sock, PCSTR url) {
    char buf[VERSION_LEN]; //VERSION_LEN = 20 bytes only ! the program will crash if buffer is overrun
    siprintf(buf, "VER: %s(%s)<p> %s", BUILD_MAJOR, BUILD_MINOR,
             BUILD_TIMESTAMP);
    writestring(sock, buf);
}

void ShowRemoteIPAddr(int sock, PCSTR url) {
    char buf[80];
    IPtoString(GetSocketRemoteAddr(sock), buf);
    writestring(sock, buf);
}

// Convert Impulse Component Timing Values in TS to uS.
void ShowImpulseComponentEvents(int sock, PCSTR url) {
    /*
     *
     char buf[VERSION_LEN]; //VERSION_LEN = 20 bytes only ! the program will crash if buffer is overrun
     siprintf(buf, "VER: %s(%s)<p> %s", BUILD_MAJOR, BUILD_MINOR,
     BUILD_TIMESTAMP);
     writestring(sock, buf);
     */

    //refer to MCF5270 DMA TIMER GUIDE
    MCHCT = (MCHC + 1) * (DIVIDER / CLOCKFREQ) * (PRESCALER + 1);
    TPHCT = (TPHC + 1) * (DIVIDER / CLOCKFREQ) * (PRESCALER + 1);
    TPLCT = (TPLC + 1) * (DIVIDER / CLOCKFREQ) * (PRESCALER + 1);
    MCLCT = (MCLC + 1) * (DIVIDER / CLOCKFREQ) * (PRESCALER + 1);
    EOCCT = (EOCC + 1) * (DIVIDER / CLOCKFREQ) * (PRESCALER + 1);
    sprintf(MCHCTS, "%f", MCHCT); //useful for HTML UI
    sprintf(TPHCTS, "%f", TPHCT); //useful for HTML UI
    sprintf(TPLCTS, "%f", TPLCT); //useful for HTML UI
    sprintf(MCLCTS, "%f", MCLCT); //useful for HTML UI
    sprintf(EOCCTS, "%f", EOCCT); //useful for HTML UI
    //printf("DEBUG: Value of MCHC is %f (%g)",MCHCT,MCHCT);
}

void pollNTPServer() {
    /*-------------------------------------------------------------------
     A simple NTP Client example that will get the time from a NTP
     server and display the UTC and PDT time through the debug serial
     port. Use MTTTY to monitor the output.

     For this example to function, your NetBurner device must have
     access to the Internet, with a working configuration for the
     IP address, mask and gateway.
     --------------------------------------------------------------------*/
    DWORD tv = time(NULL);
    struct tm tm_struct;

    struct tm *gmtime_r(const time_t *clock, struct tm *result);
    /*
     Converts a time in seconds since the Epoch (00:00:00 UTC,
     January 1, 1970) into a broken-down time, expressed as
     Coordinated Universal Time (UTC).

     clock  = The time to be converted
     result = Points to the structure where the converted time is to be stored

     On success, gmtime_r() return result. On error, it returns NULL
     */

    gmtime_r((const time_t *) &tv, &tm_struct);
    iprintf("UTC time = ");
    PrintTimeStruct(tm_struct);

    tzsetchar("EST5EDT4,M3.2.0/01:00:00,M11.1.0/02:00:00");

    localtime_r((const time_t *) &tv, &tm_struct);
    iprintf("\r\n%s time = ", _tzname[0]);
    PrintTimeStruct(tm_struct);
    iprintf("\r\n\r\n");

    testVar++; //increment counter to display on HTML webpage.
}

void UserMain(void * pd) {


/*    //Samudra // Oriol
    J2[24].function(PINJ2_PD_GPIO); // simulate Thruster 8 with LED8 MOD-DEV-70
    J2[15].function(PINJ2_PD_GPIO); // simulate Thruster 1 with LED1 MOD-DEV-70
    J2[37].function(PINJ2_37_GPIO); // test signal for 3V > 5V logic transl. (M1CU/TP1)
    J2[37].clr(); // ensure PPUV8 Ch 3 signal line is low at startup
    J2[36].function(PINJ2_36_GPIO); //SW1 signal line for uCAT Ch. 1
    J2[36].clr();
    J2[38].function(PINJ2_38_GPIO); //SW2 signal line for uCAT Ch. 2
    J2[38].clr();

    // added Aug 12 by Julie
    J2[34].function(PINJ2_34_GPIO); //SW1 signal line for uCAT Ch. 3
    J2[34].clr();*/




    //revised 21AUG13 pin definition block by SH to reflect MCAT-3CU-PS3 ARC1 configuration
      J2[24].function(PINJ2_PD_GPIO); // simulate Thruster 8 with LED8 MOD-DEV-70
      J2[15].function(PINJ2_PD_GPIO); // simulate Thruster 1 with LED1 MOD-DEV-70
      J2[37].function(PINJ2_37_GPIO); // Trigger Pulse TP
      J2[37].clr(); // ensure TP is low at startup.
      J2[36].function(PINJ2_36_GPIO); //SW1 signal line for uCAT Ch. 1
      J2[36].set(); //was clr() in version 4F
      J2[38].function(PINJ2_38_GPIO); //SW2 signal line for uCAT Ch. 2
      J2[38].set(); //was clr() in version 4F

      // added Aug 12 by Julie
      J2[34].function(PINJ2_34_GPIO); //SW1 signal line for uCAT Ch. 3
      J2[34].set(); //was clr() in version 4F


    InitializeStack();
    if (EthernetIP == 0)
        GetDHCPAddress();
    OSChangePrio(MAIN_PRIO);
    EnableAutoUpdate();
    //StartHTTP();
    EnableTaskMonitor();
    //#ifndef _DEBUG
    //EnableSmartTraps();
    //#endif

    // Set the time using NTP
    //    BOOL result = FALSE;
    //    while (!result) {
    //        // Set the NTP time
    //        result = SetNTPTime(AsciiToIp(NTP_SERVER_IP));
    //        if (!result) {
    //            iprintf("SetNTPTime() failed, waiting 30 seconds to try again\r\n");
    //            OSTimeDly(TICKS_PER_SECOND * 30);
    //        } else {
    //            iprintf("NTP Time has been set ...\n");
    //        }
    //    }


    if (GetHostByName(NTP_SERVER_POOL,&ntp_srvr_addr,0,TICKS_PER_SECOND*10)==DNS_OK)
    {
        iprintf("Got NTP Server IP = ");
        ShowIP(ntp_srvr_addr);
        printf("\r\n");

        // Set the time using NTP
        BOOL result = FALSE;
        result = SetNTPTime(ntp_srvr_addr);
        if (!result) {
            iprintf("SetNTPTime() failed, waiting 5 seconds to try again\r\n");
            OSTimeDly(TICKS_PER_SECOND * 5);
        } else {
            iprintf("NTP Time has been set ...\n");
        }


    }
    else
    {
        iprintf("Failed to get NTP Server IP Address\n");
    }

    iprintf("*********************************************************************************\n");
    iprintf("Micro-Cathode Arc Thruster (uCAT) PhoneSat Experiment/MAPERS [GWU/NASA ARC]\n");
    iprintf("For a 3-channel interface control board");
    iprintf("(c) 2013 George Washington University\n");
    iprintf("\nAuthor: Samudra Haque, Ph.D Student\n");
    iprintf("Dept. of Mechanical and Aeropace Engineering\n");
    iprintf("801 22nd St NW\n");
    iprintf("Washington, DC 20052\n\n");
    displayConfig();
    iprintf("*********************************************************************************\n\n");

    // Test 718
    // ???? Drive Strength Control Register Ð Set a high output drive
    // strength (writing to bit 0 affects all ??? pins configured for
    // GPIO).
    sim.gpio.dscr_feci2c |= 0x01;

    ///// NOT REQUIRED? V
    if (OSTaskCreate(doPulses, NULL,
                     (void *) &doPulseStack[USER_TASK_STK_SIZE], (void *) doPulseStack,
                     MAIN_PRIO + 1) != OS_NO_ERR) {
        iprintf("**** Error creating doPulse task \n)");
    }
    OSSemInit(&SemPulse, 0);
    ///// NOT REQUIRED? ^

    disableAll(); //test PPUV8 Ch 3 - should be disabled at startup
    displayCLIMenu(); ////THIS MENU CAN BE BLANK BUT CANNOT BE  EMPTY
    //RegisterPost(); ///////////////////// important to enable HTML <-> App connectivity

    while (1) {
        char c = getchar();
        switch (c) {
            case '0': {
                displayConfig();
                displayCLIMenu();
                break;
            }
              //1,6,7,2,6,7
            case '1': {
                //EOCC = 568; //End of Cycle Count - for f=176 Hz (MATLAB DMATIMERV2 w/1.8mS TP)
                EOCC = 99928; // F=1Hz for PPUv7/V8 hybrid F=1 Hz 1AUG13 (PPU V7x/V8, MATLAB)
                iprintf(">> Impulse frequency set to 1 Hz, (EOCC = %d)\n", EOCC);
                displayCLIMenu();
                break;

            }
            case '2': {
                // EOCC = 99434; // End of Cycle Count F=1 Hz (PPU V5, Matlab, DMATIMERV2 w/1.8mS TP)
                EOCC = 49928; // End of Cycle Count F=2 Hz 1AUG13 SEH (PPU V7x/V8, MATLAB)
                iprintf(">> Impulse Frequency set to 2 Hz, (EOCC = %d)\n", EOCC);
                displayCLIMenu();
                break;
            }

/*
            case '3': {
            	// put correct EOCC from Samudra's file to have F=5Hz
                           //EOCC = ; End of Cycle Count F=5 Hz 1AUG13 SEH (PPU V7x/V8, MATLAB)
                           iprintf(">> Impulse frequency set to 5 Hz, (EOCC = %d)\n", EOCC);
                           displayCLIMenu();
                           break;

           }
             case '4': {
            	 // put correct EOCC from Samudra's file to have F=7Hz
                           //EOCC = ; // End of Cycle Count F=7 Hz 1AUG13 SEH (PPU V7x/V8, MATLAB)
                           iprintf(">> Impulse Frequency set to 7 Hz, (EOCC = %d)\n", EOCC);
                           displayCLIMenu();
                           break;
           }

             case '5': {
            	 // put correct EOCC from Samudra's file to have F=10Hz
                      //     EOCC = ; // End of Cycle Count F=10 Hz 1AUG13 SEH (PPU V7x/V8, MATLAB)
                           iprintf(">> Impulse Frequency set to 10 Hz, (EOCC = %d)\n", EOCC);
                           displayCLIMenu();
                           break;
           }
*/

            case '6': {
                iprintf("Starting DMATIMER1 ISR (EOCC: %d)\n", EOCC);
                Continuous = TRUE;
                initDMATIMER1();
                //displayCLIMenu();
                break;
            }
                //SEH: 7/28/13 not sure here why I left this code
            case '7': {
                iprintf("Z");
                disableAll();
                // note the absence of a 'break;' statement here !
            }
            case '8': {
                Continuous = FALSE;
                sim.timer[0].tmr = 0x001A; //disable timer 0?
                //Pins[PINMC] = HIGH;
                //Pins[PINTP] = LOW; //inverted due BJT inverter application
                J2[37].clr(); ////// test 3V > 5V level transl. - signal TP1 OFF
                iprintf("\n>>Stopping MCAT pulse train after (%d) pulses\r\n",
                        PulseCount);
                PulseCount = 0;
                displayCLIMenu();
                break;
            }
            case '9': {
                // Stop pulse train
                iprintf("Ok, Reverting to Main Menu");
                break;
            }
                //ORIOL + SAMUDRA test for MOD-DEV-70/MOD-5270 Logic
            case 'F': {
                // Simulated command to fire thruster for N pulses (N not defined)
                iprintf("LED8[ON]\n");
                J2[24].clr();
                //J2[37].set(); ////// test 3V > 5V level transl. - signal TP1 ON
                //XX demoPulse(stopFlag);
                //XX OSSemPost(&SemCycleComplete);
                break;
            }
                //ORIOL + SAMUDRA test for MOD-DEV-70/MOD-5270 Logic
            case 'G': {
                // Simulated command to fire thruster for N pulses (N not defined)
                iprintf("LED8[OFF]\n");
                J2[24].set();
                //J2[37].clr(); ////// test 3V > 5V level transl. -- signal TP1 OFF
                break;
            }
                //ORIOL + SAMUDRA test for MOD-DEV-70/MOD-5270 Logic
            case 'H': {
                // Simulated command to fire thruster for N pulses (N not defined)
                iprintf("LED1[ON]\n");
                J2[15].clr();
                break;
            }
                //ORIOL + SAMUDRA test for MOD-DEV-70/MOD-5270 Logic
            case 'J': {
                // Simulated command to fire thruster for N pulses (N not defined)
                iprintf("LED1[OFF]\n");
                J2[15].set();
                break;
            }
                //PPUV8 Track 2 Ch 1
            case 'Z': {
                // enable Ch. 1 power switch SW1
                J2[36].clr(); //was set() in 4F
                iprintf("... EN1 ...\r\n");
                break;
            }
                //PPUV8 Track 2 Ch 1
            case 'z': {
                // disable Ch. 1 power switch SW1
                iprintf("...Disabled Ch. 1\r\n");
                J2[36].set(); //was clr() in 4F
                break;
            }
                //PPUV8 Track 2 Ch 2
            case 'Y': {
                // enable Ch. 2 power switch SW1
                J2[38].clr(); //was set() in 4F
                iprintf("... EN2 ...\r\n");
                break;
            }
                //PPUV8 Track 2 Ch 2
            case 'y': {
                // disable Ch. 2 power switch SW1
                iprintf("...Disabled Ch. 2\r\n");
                J2[38].set(); //was clr() in 4F
                break;
            }
            case 'X': {
                 // enable Ch. 3 power switch SW1
                 J2[34].clr(); //was set() in 4F
                 iprintf("... EN3 ...\r\n");
                 break;
            }
                 //PPUV8 Track 2 Ch 2
            case 'x': {
                 // disable Ch. 3 power switch SW1
                 iprintf("...Disabled Ch. 3\r\n");
                 J2[34].set(); //was clr() in 4F
                 break;
            }
            default: {
                displayCLIMenu();
            }

        }
    }

}
