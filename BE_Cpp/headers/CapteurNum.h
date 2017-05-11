/*
 * CapteurNum.h
 *
 *  Created on: 26 avr. 2017
 *      Author: florent
 */

#ifndef HEADERS_CAPTEURNUM_H_
#define HEADERS_CAPTEURNUM_H_
#include "Capteur.h"
#include "mraa.h"

class CapteurNum : public Capteur
{
protected :
	mraa_gpio_context poussoirPinNumber;
public :

	virtual bool init();
	virtual int readCapteurValue();
	virtual void afficherCaracteristiques();
	virtual void defineAsInput();


	virtual void callIntrHandler(void (*ptrHandler)(void*));
	virtual void stopIntrHandler();
	virtual void closePin();

	virtual ~CapteurNum() {};

	virtual mraa_gpio_context getPoussoirPinNumber() const {
		return poussoirPinNumber;
	}
};




#endif /* HEADERS_CAPTEURNUM_H_ */
