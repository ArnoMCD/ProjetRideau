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
	virtual void afficherCaracteristiques();

};



#endif /* SERVO_H_ */
