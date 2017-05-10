/*
 * Capteur.cpp
 *
 *  Created on: 1 avr. 2017
 *      Author: florent
 */
#include "mraa.h"
#include <stdio.h>
#include <math.h>
#include "../headers/Capteur.h"

using namespace std;

bool Capteur:: init()
{
	adcPin = mraa_aio_init(pin_number);
	if (adcPin != NULL) return true;
	else return false;
}

float Capteur::readADCValue()
{
	if (adcPin != NULL)
	{
		adcValue = mraa_aio_read(adcPin);
		return adcValue;
	}
	else
	{
		return -1;
	}
}

void Capteur::afficherCaracteristiques(){

}
