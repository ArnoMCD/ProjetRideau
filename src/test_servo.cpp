/*
 * main.cpp
 *
 *  Created on: 30 mars 2017
 *      Author: florent
 */

#include "../headers/Servo.h"
#include <mraa.h>

int test_servo(void) {
	int compteurAR = 0;
	int i = 20;

	mraa_init();

	Servo *monServo = new Servo();

	monServo->setPin(3);

	if (monServo->init())
	{
		monServo->activer();
		monServo->setPeriod(5000);

		while (compteurAR < 3)
		{
			i = 20;
			while (i<65)
			{
				monServo->dutyCycle(i*0.01);
				usleep(5000);
				i++;
			}

			while(i>0)
			{
				monServo->dutyCycle(i*0.01);
				usleep(5000);
				i--;
			}

			compteurAR++;
		}

		monServo->desactiver();
	}

	monServo->afficherCaracteristiques();

	return 0;
}
