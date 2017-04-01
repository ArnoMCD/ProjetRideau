/*
 * Servo.h
 *
 *  Created on: 30 mars 2017
 *      Author: florent
 */

#ifndef SERVO_H_
#define SERVO_H_
#include "Peripherique.h"

class Servo : public Peripherique {

protected:
	int period;
public:
	virtual void setPeriode(int periode);
	virtual int getPeriode();
	virtual void init();
	virtual void afficherCaracteristiques();
	//virtual int getPin();
	//virtual void setPin(int pin);
};



#endif /* SERVO_H_ */
