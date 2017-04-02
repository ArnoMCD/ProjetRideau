/*
 * Capteur.h
 *
 *  Created on: 1 avr. 2017
 *      Author: florent
 */

#ifndef HEADERS_CAPTEUR_H_
#define HEADERS_CAPTEUR_H_
#include "Peripherique.h"
#include "mraa.h"


class Capteur : public Peripherique
{
protected:
	float adcValue;    // ADC value read into this variable
	mraa_aio_context adcPin;

public :
	virtual bool init();
	virtual float readADCValue();
};





#endif /* HEADERS_CAPTEUR_H_ */
