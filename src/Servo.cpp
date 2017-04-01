/*
 * Servo.cpp
 *
 *  Created on: 30 mars 2017
 *      Author: florent
 */
#include "../headers/Servo.h"
#include <iostream>

using namespace std;

void Servo::setPeriode(int periode)
{
	period = periode;
}

int Servo::getPeriode()
{
	return period;
}

void Servo::init()
{
}

void Servo::afficherCaracteristiques()
{
	cout << "La période du servo est de " << this->getPeriode() << endl;
}
