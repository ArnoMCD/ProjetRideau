/*
 * CapteurTemp.cpp
 *
 *  Created on: 1 avr. 2017
 *      Author: florent
 */
#include "../headers/CapteurTemp.h"
#include "mraa.h"
#include <stdio.h>
#include <math.h>

using namespace std;

const int B  = 4275;         // B value for thermistor
const int R0 = 100;          // R0 is 100k ohms

bool CapteurTemp:: init() // si pas int, comment retourner adcPin ? (utilisé dans readADCValue)
{
	adcPin = mraa_aio_init(pin_number);
	return true;
}

float CapteurTemp::readADCValue()
{
	if (init() != 0)
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

float CapteurTemp::calculTemp()
{
	float R;
	if (readADCValue() !=0)
		{
	    	R = 1023.0/((float)adcValue)-1.0;    // Promote to float
	    	R = 100000.0*R;
	    	temperature = 1.0/(log(R/100000.0)/B+1/298.15)-273.15;
	    	return temperature;
		}
	else
	{
		//générer un message d'erreur avec try catch tout ça pour dire d'appeler init() avant calculTemp()
		return 0;
	}
}

