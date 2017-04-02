/*
 * CapteurTemp.h
 *
 *  Created on: 1 avr. 2017
 *      Author: florent
 */

#ifndef HEADERS_CAPTEURTEMP_H_
#define HEADERS_CAPTEURTEMP_H_
#include "Peripherique.h"
#include "mraa.h"


class CapteurTemp : public Peripherique
{
protected:
	float adcValue;    // ADC value read into this variable
	float r;           // Resistance
	float temperature; //
	mraa_aio_context adcPin;

public :
	virtual bool init();
	virtual float calculTemp();
	virtual float readADCValue();
};





#endif /* HEADERS_CAPTEURTEMP_H_ */
