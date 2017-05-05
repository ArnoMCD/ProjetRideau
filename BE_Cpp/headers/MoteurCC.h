/*
 * Ecran.h
 *
 *  Created on: 2 avr. 2017
 *      Author: florent
 */

#ifndef HEADERS_MOTEURCC_H_
#define HEADERS_MOTEURCC_H_
#include "Peripherique.h"

#include <unistd.h>
#include <iostream>
#include <string>
#include <mraa/i2c.h>
#include <mraa/aio.h>
#include <mraa/gpio.h>

class MoteurCC : public Peripherique
{
protected:
	 mraa_i2c_context m_i2c_motor_control;
public:
	virtual bool init();
	virtual void afficherCaracteristiques();
	virtual void arreter();
	virtual int dutyCycle(float duty);
};



#endif /* HEADERS_MOTEURCC_H_ */
