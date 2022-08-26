/*
 * i2cgpio.cpp
 *
 *  Created on: Nov 6, 2012
 *      Author: voyager
 */
#include <stdio.h>
#include <ctype.h>
#include <sim.h>
#include <i2cmaster.h>
#include <pins.h>

#define BASEADDRESS 0xA0000000

static DWORD PCA_Dir;	// Direction of GPIO;
static DWORD PCA_Drive;	// Drive value for outputs;

bool bGPIOInit;			// Boolean to catch whether the module has been initialized;

#define CHECK_INIT() if(!bGPIOInit) GPIOInit();

void GPIOInit (void)
{
	I2CInit();

	PCA_Dir = 0;
	PCA_Drive = 0xFFFF;

	bGPIOInit = TRUE;
}

/*
SetDigitalPin
Sets an output of the I2C module to a boolean value
*/
void SetDigitalPin( int pin, BOOL val )
{
   BYTE Buffer[3];

   DWORD new_drive = PCA_Drive;

   //Set the value of the new_drive value to the appropriate level
   if ( val )
      new_drive |= ( 1 << pin );
   else
      new_drive &= ~( 1 << pin );

   //If there is a mismatch between the new_drive value and the current one
   //Reset the Drive value, and send the message as follows
   if ( new_drive != PCA_Drive )
   {
      PCA_Drive = new_drive;
      Buffer[0] = 0x02;
      Buffer[1] = ( PCA_Drive & 0xFF );
      Buffer[2] = ( PCA_Drive >> 8 ) & 0xFF;;
      I2CSendBuf( 0x74, Buffer, 3 );		//In this instance the address is 0x74,
      	  	  	  	  	  	  	  	  	  //if additional modules were used, this should be changed.
   }
  

   DWORD new_dir = PCA_Dir;
   new_dir |= ( 1 << pin );
   if ( new_dir != PCA_Dir )
   {
      PCA_Dir = new_dir;
      Buffer[0] = 0x06;
      Buffer[1] = ~( ( PCA_Dir & 0xFF ) );
      Buffer[2] = ~( ( PCA_Dir >> 8 ) & 0xFF );
      I2CSendBuf( 0x74, Buffer, 3 );
   }


}

/*
ReadDigitalPin
Returns the state high or low of an input pin in the form of a boolean
*/
BOOL ReadDigitalPin( int pin )
{
   BYTE Buffer[3];
   DWORD new_dir = PCA_Dir;
   new_dir &= ~( 1 << pin );
   if ( new_dir != PCA_Dir )
   {
      PCA_Dir = new_dir;
      Buffer[0] = 0x06;
      Buffer[1] = ~( ( PCA_Dir & 0xFF ) );
      Buffer[2] = ~( ( PCA_Dir >> 8 ) & 0xFF );
      I2CSendBuf( 0x74, Buffer, 3 );
   }

   Buffer[0] = 0;
   I2CSendBuf( 0x74, Buffer, 1 );
   I2CReadBuf( 0x74, Buffer, 2 );

   
   if ( pin < 8 )
   {
      BYTE mask = ( 1 << ( pin ) );
      return ( ( Buffer[0] & mask ) != 0 );
   }
   else
   {
      BYTE mask = ( 1 << ( pin - 8 ) );
      return ( ( Buffer[1] & mask ) != 0 );
   }

   return FALSE;
}
