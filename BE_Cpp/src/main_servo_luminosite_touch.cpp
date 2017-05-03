/*
 * main.cpp
 *
 *  Created on: 30 mars 2017
 *      Author: florent
 */
#include <mraa.h>
#include <iostream>

#include "../headers/Servo.h"
#include "../headers/Ecran.h"
#include "../headers/Capteur.h"
#include "../headers/CapteurNum.h"

#define SEUIL_LUM 500
#define LUMINEUX 1
#define SOMBRE 0
#define LUMINOSITE 0
#define INTERNET 1
#define HAUT 1
#define BAS 1

using namespace std;

int lum;
int etat_lum = SOMBRE;
volatile int mode = LUMINOSITE;
int modePrecedent = INTERNET;
int etat_poussoir = 0;


//*******IT HANDLER********
void intrHandler(void *arg)
{
	if (etat_poussoir == 0)
	{
		mode = (mode+1)%2; //mode = 0(LUMINOSITE) ou 1(INTERNET)
		etat_poussoir++;
	}
	else if (etat_poussoir == 1)
	{
		etat_poussoir--;
	}
}

int main(void) {



	mraa_init();

	Servo *monServo = new Servo();
	Capteur *monCapteurLum = new Capteur();
	CapteurNum *monCapteurTouch = new CapteurNum();
	Ecran *monEcran = new Ecran();







	/**** INITIALISATION ****/
	monCapteurLum->setPin(1);
	if (!(monCapteurLum->init()))
		cerr << "error : cannot init capteurLum" << endl;

	monCapteurTouch->setPin(2);
	if (!(monCapteurTouch->init()))
		cerr << "error : cannot init capteurTouch" << endl;

	monEcran->setPin(0);
	if (!(monEcran->init()))
		cerr << "error : cannot init Ecran" << endl;

	monServo->setPin(3);
	if (!(monServo->init()))
		cerr << "error : cannot init Servo" << endl;

	monCapteurTouch->defineAsInput();
	mraa_gpio_isr(monCapteurTouch->getPoussoirPinNumber(), MRAA_GPIO_EDGE_BOTH, intrHandler, NULL);
	//monCapteurTouch->callIntrHandler(intrHandler); //A FAIRE MARCHER

	//monServo->activer();
	monServo->setPeriod(20000);

	//*******LOOOP*******
	while (1) {
		lum = monCapteurLum->readADCValue();
		cout << monCapteurTouch->readCapteurValue()<< endl;
		switch (mode) {
		case LUMINOSITE:
			if (modePrecedent != LUMINOSITE)
				{
				monEcran->afficher("MODE: LUMINOSITE");
				}

			if (etat_lum == SOMBRE && lum > SEUIL_LUM) //on passe de l'ombre à la lumière
			{
				etat_lum = LUMINEUX;
				monServo->activer();
				for (int i = 0; i < 5; i++)
					monServo->allerRetour(); //pour le test on considère que 5AR = on a monté le rideau
				monServo->desactiver();
			}
			else if (etat_lum == LUMINEUX && lum < SEUIL_LUM) //on passe de la lumière à l'ombre
			{
				etat_lum = SOMBRE;
				monServo->activer();
				for (int i = 0; i < 5; i++)
					monServo->allerRetour(); //pour le test on considère que 5AR = on a descendu le rideau
				monServo->desactiver();
			}
			else {
				usleep(100000);
			}
			modePrecedent = LUMINOSITE;
			break;
		case INTERNET:
			if (modePrecedent != INTERNET) monEcran->afficher("MODE: INTERNET");
			modePrecedent = INTERNET;
			usleep(100000);


			break;
		}

	}

	monCapteurTouch->stopIntrHandler();
	monCapteurTouch->closePin();
	monServo->afficherCaracteristiques();
	monServo->desactiver();
	free(monServo);

	return 0;
}
