3/24/2015 Samudra Haque samudra@gwu.edu GWU MAE MpNL
This codebase requires Netburner NANO54415 network development kit (NNDK).
It depends upon the Netburner RTOS and libraries obtained through the typical free developer license, which depends upon the use of an unmodified netburner module, hence the use of a daughter board approach for the Control Unit in a Mini-PCI Express connector/latch.

www.netburner.com

The codebase is 6C. Developed for the BRICSAT-P platform originally (Oct, 2015). Any .s19 extension file is a hex binary to be downloaded to a netburner NANO54415 target. GROUNDTESTING and FLIGHT modes enable/disable verbosity.

Choose the configuration you need to compile for, from the NBECLIPSE project properties page. 

Future versions:
(from e-mail to CANYVAL-X GSFC/GWU team of 3/16/2015) 

3. For the next few steps, leading to the Month of April, with Azimi's help from GSFC I propose to send Yonsei team (or Phil@Yonsei) my planned software mods are as follows:

2A. 3/15/2015 - COMPLETED - Initial load of MCAT canyval will be the 6C flight code of BRICSAT. No Changes. Command Set 6C. No I2C. Serial Comms only.

2B.3/16/2015 - Version 6D - Modification of low-level timing trigger pulse duration to accomodate Canyval IES (Inductive Energy Storage) specs instead of Bricsat IES specs. This will increase slightly increase the on-time of the IGBT in clamped inductive storage operation, No other changes. No I2C. Serial Comms only. Adjustment of command set for firing rates in five segments A...F to represent likely conops. Currently, this is 1/10/20/30/40/50 Hz. Is this sufficient ?

4. The following steps will be done when practical .... between GWU/GSFC collaboration. (Requires use of a backup MCAT Canyval subsystem or the MCAT Bricsat subsystem, and Azimi Benham's GOMSPACE I2C).

2C.  Version 6E - Addition of I2C comms with interface between Serial Command Buffer / I2C RX, and Telemetry Buffer / I2C TX modules. Commands will be programmed and tested from a GOMSPACE (or any other compatible multi-master I2C device at 400 kHz baud rate) to demo  I2C functions. No changes to command set 6C, unless minor and requested by CANYVAL flight team and approved by Phil.

2D. Version 6F - Addition of current sensor functionality, storage of sensor events, transfer of sensor events to I2C telemetry buffer, testing of Polling feature of sensor events via Telemetry buffer on the I2C bus.


Brief Explanation of the low-level timing routines:
This system uses a hardware DMA timer (could be any hardware timer) that is programmable and executes an interrupt-service routine that inspects the value of the time slice counter. Depending upon the hardware timer values, and the programmed counts, different low-level events can be actuated via the GPIO pins of the Control Unit. This behavior is intended to be implemented as several timing sources, allowing variable pulse repetition rate of different thruster channels, and event triggers, but in this implementation is limited to a single source of timing. That said, for a more complex treatment of the options available, refer to US Patent Appl. 14/462,127 and See Note 4 of Schematic MCAT-CANYVAL-BPL-5X1.pdf document.
 

Actual timing figures are generated using MATLAB DMATIMERV4 script, so ask the technical contact at GWU for proper use. 
