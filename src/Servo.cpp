/*
 * Servo.cpp
 *
 *  Created on: 30 mars 2017
 *      Author: florent
 */
#include "../headers/Servo.h"
#include <iostream>

using namespace std;

void Servo::setPeriod(int periode) {
	if (this->init()) {
		mraa_pwm_period_us(pwmPinNumber, periode);
		period = periode;
	} else {
		//g�n�rer un message d'erreur avec try catch tout �a pour dire d'appeler init() avant setPeriod()
	}
}

int Servo::getPeriod() {
	return period;
}

bool Servo::init() {
	pwmPinNumber = mraa_pwm_init(pin_number);
	if (pwmPinNumber != NULL)
		return true;
	else
		return false;
}

void Servo::activer() {
	if (pwmPinNumber != NULL) {
		mraa_pwm_enable(pwmPinNumber, 1);
	} else {
		//g�n�rer un message d'erreur avec try catch tout �a pour dire d'appeler init() avant activer()
	}
}

void Servo::desactiver() {
	if (pwmPinNumber != NULL) {
		mraa_pwm_enable(pwmPinNumber, 0);
	} else {
		//g�n�rer un message d'erreur avec try catch tout �a pour dire d'appeler init() avant desactiver()
	}
}

void Servo::dutyCycle(float pourcentage) {
	if (pwmPinNumber != NULL) {
		mraa_pwm_write(pwmPinNumber, pourcentage);
	} else {
		//g�n�rer un message d'erreur avec try catch tout �a pour dire d'appeler init() avant desactiver()
	}
}

void Servo::afficherCaracteristiques() {
	cout << "La p�riode du servo est de " << this->getPeriod() << endl;
}
