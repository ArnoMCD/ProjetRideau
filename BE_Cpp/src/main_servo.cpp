/*
 * main.cpp
 *
 *  Created on: 30 mars 2017
 *      Author: florent
 */

#include "../headers/Servo.h"
#include <mraa.h>
#include <iostream>

using namespace std;

int main12(void) {
	int compteurAR = 0;
	//int i = 20;

	mraa_init();

	Servo *monServo = new Servo();

	monServo->setPin(3);

	if (monServo->init())
	{
		monServo->activer();
		monServo->setPeriod(20000);

		while (compteurAR < 1)
		{
			monServo->allerRetour();
			compteurAR++;
		}
		//usleep(1000000);
		monServo->afficherCaracteristiques();
		monServo->desactiver();
		free(monServo);
		// Marche pas
		//mraa_pwm_enable(monServo->pwmPinNumber, 0); // Ne marche pas non plus
	}

	else
	{
		cerr << "error : cannot init servo" << endl;
	}

	return 0;
}
