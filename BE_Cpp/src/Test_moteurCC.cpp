/*
 * main_moteur.cpp
 *
 *  Created on: 3 mai 2017
 *      Author: Arno
 */
#include <mraa/i2c.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <mraa/aio.h>
#include <mraa/gpio.h>

#include "../headers/MoteurCC.h"
#include "../headers/Capteur.h"


using namespace std;

// ********** TEST DU MOTEUR CC SEUL *************
// ----------- DRIVER NON COMPATIBLE AVEC LA GALILEO -----------
// ********** PROGRAMME NON FONCTIONNEL *************

int mainm_moteurCC(void)

{
	mraa_init();

	MoteurCC *monMoteur = new MoteurCC();

	monMoteur -> setPin(0);
	monMoteur -> init();

	while(1)
	{
	monMoteur->dutyCycle(50);
	}

	free(monMoteur);

	return 0;

}




