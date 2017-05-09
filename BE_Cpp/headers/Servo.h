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

public: // Public --> Juste pour tester en désactivant sans passer ar désactiver
	int period; //Periode en us
	mraa_pwm_context pwmPinNumber;

public:
	virtual void setPeriod(int periode);
	virtual int getPeriod();
	virtual bool init();
	virtual void activer();
	virtual void desactiver();
	virtual void dutyCycle(float pourcentage);
	virtual void pulseWidth(float us);
	virtual void afficherCaracteristiques();
	virtual void allerRetour();


};



#endif /* SERVO_H_ */
