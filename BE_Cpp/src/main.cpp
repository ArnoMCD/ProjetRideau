/*
 * main.cpp
 *
 *  Created on: 30 mars 2017
 *      Author: florent
 */
#include "../headers/Capteur.h"
#include "../headers/Servo.h"
#include <mraa.h>

int main1(void) {
	int compteurAR = 0;
	int i = 20;

	mraa_init();

	Capteur *monCapteurLum = new Capteur();
	monCapteurLum->setPin(1);
	if (monCapteurLum->init()) {

		Servo *monServo = new Servo();
		monServo->setPin(3);

		if (monServo->init()) {
			monServo->activer();
			monServo->setPeriod(20000);

			monServo->dutyCycle(0.01);

			sleep(3);
			monServo->afficherCaracteristiques();
			monServo->desactiver();
			free(monServo);
			// Marche pas
			//mraa_pwm_enable(monServo->pwmPinNumber, 0); // Ne marche pas non plus
		}

	}
	return 0;
}
