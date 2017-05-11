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

#define SERVO_PERIOD 5000
#define MAX_DUTY_CYCLE 0.51
#define MIN_DUTY_CYCLE 0.15

class Servo : public Peripherique {

protected: //
	int period; //Periode en us
	mraa_pwm_context pwmPinNumber;

public:
	// Toutes les méthodes utilisées par un servo
	virtual void setPeriod(int periode);
	virtual int getPeriod();
	virtual bool init();
	virtual void activer();
	virtual void desactiver();
	virtual void dutyCycle(float pourcentage);
	virtual void pulseWidth(float us);
	virtual void afficherCaracteristiques();
	virtual void allerRetour();

	virtual ~Servo() {};


};



#endif /* SERVO_H_ */
