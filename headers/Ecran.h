/*
 * Ecran.h
 *
 *  Created on: 2 avr. 2017
 *      Author: florent
 */

#ifndef HEADERS_ECRAN_H_
#define HEADERS_ECRAN_H_
#include "Peripherique.h"
#include <mraa/i2c.h>
#include <mraa/aio.h>
#include <mraa/gpio.h>

class Ecran
{
protected:
	 mraa_i2c_context m_i2c_lcd_control, m_i2c_lcd_rgb;
public:
	virtual bool init();
	virtual int afficheTemp(float temperature);
};



#endif /* HEADERS_ECRAN_H_ */
