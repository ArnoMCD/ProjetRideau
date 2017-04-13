/*
 * main.cpp
 *
 *  Created on: 30 mars 2017
 *      Author: florent
 */

#include "../headers/Servo.h"
#include <mraa.h>


int main1(void) {
	int compteurAR = 0;
	int i = 20;

	mraa_init();

	Servo *monServo = new Servo();

	monServo->setPin(3);

	if (monServo->init())
	{
		monServo->activer();
		monServo->setPeriod(20000);

		while (compteurAR < 4)
		{
			i = 20;
			while (i<55)
			{
				monServo->dutyCycle(i*0.01);
				usleep(5000);
				i++;
			}

			while(i>20)
			{
				monServo->dutyCycle(i*0.01);
				usleep(5000);
				i--;
			}

			compteurAR++;
		}
		usleep(1000000);
		monServo->afficherCaracteristiques();
		monServo->desactiver();
		free(monServo);
		// Marche pas
		//mraa_pwm_enable(monServo->pwmPinNumber, 0); // Ne marche pas non plus
	}

	return 0;
}
