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
	if (pwmPinNumber != NULL) {
		mraa_pwm_period_us(pwmPinNumber, periode);
		period = periode;
	} else {
		//g�n�rer un message d'erreur avec try catch tout �a pour dire d'appeler init() avant setPeriod()
		cerr << "error : pwmPinNumber is NULL, can't setPeriod" << endl;
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
		cerr << "error : pwmPinNumber is NULL, cant activer" << endl;
	}
}

void Servo::desactiver() {
	if (pwmPinNumber != NULL) {
		mraa_pwm_enable(pwmPinNumber, 0);
	} else {
		//g�n�rer un message d'erreur avec try catch tout �a pour dire d'appeler init() avant desactiver()
		cerr << "error : pwmPinNumber is NULL, cant desactiver" << endl;
	}
}

void Servo::
dutyCycle(float pourcentage) {
	if (pwmPinNumber != NULL) {
		mraa_pwm_write(pwmPinNumber, pourcentage);
	} else {
		//g�n�rer un message d'erreur avec try catch tout �a pour dire d'appeler init() avant desactiver()
		cerr << "error : pwmPinNumber is NULL, cant dutyCycle" << endl;
	}
}

void Servo::pulseWidth(float us) {
	if (pwmPinNumber != NULL) {
		mraa_pwm_pulsewidth_us(pwmPinNumber, us);
	} else {
		//g�n�rer un message d'erreur avec try catch tout �a pour dire d'appeler init() avant desactiver()
		cerr << "error : pwmPinNumber is NULL, cant pulseWidth" << endl;
	}
}

void Servo::afficherCaracteristiques() {
	cout << "La p�riode du servo est de " << this->getPeriod() << endl;
	cout << "Le numero de PIN est " << this->getPin()<< endl;
}

void Servo::allerRetour() {

	int i = 20;
	while (i<65)
	{
		this->dutyCycle(i*0.01);
		usleep(2500);
		i++;
	}

	while(i>20)
	{
		this->dutyCycle(i*0.01);
		usleep(2500);
		i--;
	}
}
