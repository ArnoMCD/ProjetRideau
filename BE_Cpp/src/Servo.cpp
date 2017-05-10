/*
 * Servo.cpp
 *
 *  Created on: 30 mars 2017
 *      Author: florent
 */
#include "../headers/Servo.h"
#include <iostream>

using namespace std;

// Fixe la période du servo
void Servo::setPeriod(int periode) {
	if (pwmPinNumber != NULL) {
		mraa_pwm_period_us(pwmPinNumber, periode);
		period = periode;
	} else {
		//générer un message d'erreur avec try catch tout ça pour dire d'appeler init() avant setPeriod()
		cerr << "error : pwmPinNumber is NULL, can't setPeriod" << endl;
	}
}

// Retourne la période du servo
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
		//générer un message d'erreur avec try catch tout ça pour dire d'appeler init() avant activer()
		cerr << "error : pwmPinNumber is NULL, cant activer" << endl;
	}
}

void Servo::desactiver() {
	if (pwmPinNumber != NULL) {
		mraa_pwm_enable(pwmPinNumber, 0);
	} else {
		//générer un message d'erreur avec try catch tout ça pour dire d'appeler init() avant desactiver()
		cerr << "error : pwmPinNumber is NULL, cant desactiver" << endl;
	}
}

// Fonctionnement avec duty cycle -> on préfèrera utiliser pulsewidth, voir plus bas
void Servo::dutyCycle(float pourcentage) {
	if (pwmPinNumber != NULL) {
		mraa_pwm_write(pwmPinNumber, pourcentage);
	} else {
		//générer un message d'erreur avec try catch tout ça pour dire d'appeler init() avant desactiver()
		cerr << "error : pwmPinNumber is NULL, cant dutyCycle" << endl;
	}
}

void Servo::pulseWidth(float us) {
	if (pwmPinNumber != NULL) {
		mraa_pwm_pulsewidth_us(pwmPinNumber, us);
	} else {
		cerr << "error : pwmPinNumber is NULL, cant pulseWidth" << endl;
	}
}

// Affiche la pin et la période du servo
void Servo::afficherCaracteristiques() {
	cout << "La période du servo est de " << this->getPeriod() << endl;
	cout << "Le numero de PIN est " << this->getPin()<< endl;
}

// Effectue un aller-retour complet
void Servo::allerRetour() {
	this->dutyCycle(MAX_DUTY_CYCLE);
	sleep(1);
	this->dutyCycle(MIN_DUTY_CYCLE);
	sleep(1);
}




