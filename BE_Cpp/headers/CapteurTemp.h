/*
 * CapteurTemp.h
 *
 *  Created on: 1 avr. 2017
 *      Author: florent
 */

#ifndef HEADERS_CAPTEURTEMP_H_
#define HEADERS_CAPTEURTEMP_H_
#include "Capteur.h"
#include "mraa.h"


class CapteurTemp : public Capteur
{
protected:
	//float R;           // Resistance
	float temperature;

public :
	virtual float calculTemp();
	virtual ~CapteurTemp() {};
};

#endif /* HEADERS_CAPTEURTEMP_H_ */
