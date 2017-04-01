/*
 * Servo.h
 *
 *  Created on: 30 mars 2017
 *      Author: florent
 */

#ifndef SERVO_H_
#define SERVO_H_
#include "Peripherique.h"
#include "mraa.h"

class Servo : public Peripherique {

protected:
	int period; //Periode en us
	mraa_pwm_context pwmPinNumber;

public:
	virtual void setPeriod(int periode);
	virtual int getPeriod();
	virtual void init();
	virtual void activer();
	virtual void desactiver();
	virtual void afficherCaracteristiques();

};



#endif /* SERVO_H_ */
