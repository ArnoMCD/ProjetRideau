/*
 * Peripherique.h
 *
 *  Created on: 30 mars 2017
 *      Author: florent
 */

#ifndef PERIPHERIQUE_H_
#define PERIPHERIQUE_H_

class Peripherique
{
protected :
	int pin_number;
public :
	virtual int getPin();
	virtual void setPin(int pin);
	virtual bool init() = 0;
	virtual void afficherCaracteristiques() = 0;
};

#endif /* PERIPHERIQUE_H_ */
