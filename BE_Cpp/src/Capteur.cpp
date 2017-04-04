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

bool Capteur:: init() // si pas int, comment retourner adcPin ? (utilisé dans readADCValue)
					  // ARNO : adcPin est un attribut de Capteur donc pas besoin de return il est modifié direct :)
					  // Ah mais oui ! thanks
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
		//générer un message d'erreur avec try catch tout ça pour dire d'appeler init() avant readADCValue()
		return 0;
	}
}

void Capteur::afficherCaracteristiques(){

}
