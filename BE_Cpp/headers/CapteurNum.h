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
	mraa_aio_context poussoirPinNumber;
	int mode;
public :
	virtual bool init();
	virtual int readCapteurValue();
	virtual void afficherCaracteristiques();
	virtual void defineAsInput();

	virtual void callIntrHandler();
	virtual int intrHandler();
	virtual void stopIntrHandler();
	virtual void closePin();

	virtual void printCounter(int compteur);
	virtual void printMode(int mode);
};




#endif /* HEADERS_CAPTEURNUM_H_ */
