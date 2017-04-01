/*
 * Servo.cpp
 *
 *  Created on: 30 mars 2017
 *      Author: florent
 */
#include "../headers/Servo.h"
#include <iostream>

using namespace std;

void Servo::setPeriod(int periode)
{
	period = periode;
}

int Servo::getPeriod()
{
	return period;
}

void Servo::init()
{
	pwmPinNumber = mraa_pwm_init(pin_number);
}

void Servo::afficherCaracteristiques()
{
	cout << "La période du servo est de " << this->getPeriode() << endl;
}
