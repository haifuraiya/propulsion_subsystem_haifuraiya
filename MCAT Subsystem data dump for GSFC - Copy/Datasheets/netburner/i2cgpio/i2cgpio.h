/*
 * i2cgpio.h
 *
 *  Created on: Nov 6, 2012
 *      Author: voyager
 */

#ifndef I2CGPIO_H_
#define I2CGPIO_H_

void GPIOInit(void);

void SetDigitalPin( int, BOOL );

BOOL ReadDigitalPin(int);


#endif /* I2CGPIO_H_ */
