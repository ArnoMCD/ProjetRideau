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
	mraa_pwm_context pwmPinNumber;

public:
	virtual void setPeriod(int periode);
	virtual int getPeriod();
	virtual void init();
	virtual void afficherCaracteristiques();

};



#endif /* SERVO_H_ */
