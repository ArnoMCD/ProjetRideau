/*
 * CapteurTemp.cpp
 *
 *  Created on: 1 avr. 2017
 *      Author: florent
 */
#include "mraa.h"
#include <stdio.h>
#include <math.h>
#include "../headers/CapteurTemp.h"

using namespace std;

const int B  = 4275;         // B value for thermistor
const int R0 = 100;          // R0 is 100k ohms

// Clacule la temp�rature
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
		//g�n�rer un message d'erreur avec try catch tout �a pour dire d'appeler init() avant calculTemp()
		return 0;
	}
}

