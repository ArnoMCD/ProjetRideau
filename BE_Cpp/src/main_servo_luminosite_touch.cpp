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
#define MANUEL 1
#define HAUT 1
#define BAS 1
#define FERME 0
#define OUVERT 1

using namespace std;

int lum;
int etat_lum = SOMBRE;
volatile int mode = LUMINOSITE;
int modePrecedent = MANUEL;

int etat_poussoir = 0;
int etat_volet = FERME;


//*******IT HANDLER********
void intrHandler(void *arg)
{
	if (etat_poussoir == 0)
	{
		mode = (mode+1)%2; //mode = 0(LUMINOSITE) ou 1(MANUEL)
		etat_poussoir++;
	}
	else if (etat_poussoir == 1)
		etat_poussoir--;

}

int main(void) {



	mraa_init();

	Servo *monServo = new Servo();
	Capteur *monCapteurLum = new Capteur();
	CapteurNum *monCapteurTouch = new CapteurNum();
	Ecran *monEcran = new Ecran();
	CapteurNum *monCapteurTouchManuel = new CapteurNum();







	/**** INITIALISATION ****/
	monCapteurLum->setPin(1);
	if (!(monCapteurLum->init()))
		cerr << "error : cannot init capteurLum" << endl;

	monCapteurTouch->setPin(3);
	if (!(monCapteurTouch->init()))
		cerr << "error : cannot init capteurTouch" << endl;

	monCapteurTouchManuel->setPin(4);
	if (!(monCapteurTouchManuel->init()))
		cerr << "error : cannot init capteurTouch" << endl;

	monEcran->setPin(0);
	if (!(monEcran->init()))
		cerr << "error : cannot init Ecran" << endl;

	monServo->setPin(5);
	if (!(monServo->init()))
		cerr << "error : cannot init Servo" << endl;


	monCapteurTouch->defineAsInput();
	monCapteurTouch->callIntrHandler(intrHandler);

	monCapteurTouchManuel->defineAsInput();

	monServo->setPeriod(20000);

	//*******LOOOP*******
	while (1) {
		lum = monCapteurLum->readADCValue();
		//cout << monCapteurTouch->readCapteurValue()<< endl;

		switch (mode) {
		case LUMINOSITE:
			monServo->desactiver();
			if (modePrecedent != LUMINOSITE)
				{
				monEcran->afficher("MODE: LUMINOSITE");
				}

			if (etat_lum == SOMBRE && lum > SEUIL_LUM) //on passe de l'ombre � la lumi�re
			{
				etat_lum = LUMINEUX;
				monServo->activer();
				for (int i = 0; i < 5; i++)
					monServo->pulseWidth(1000); //pour le test on consid�re que 5AR = on a mont� le rideau
				monServo->desactiver();
			}
			else if (etat_lum == LUMINEUX && lum < SEUIL_LUM) //on passe de la lumi�re � l'ombre
			{
				etat_lum = SOMBRE;
				monServo->activer();
				for (int i = 0; i < 5; i++)
					monServo->pulseWidth(5000); //pour le test on consid�re que 5AR = on a descendu le rideau
				monServo->desactiver();
			}
			else {
				usleep(100000);
			}
			modePrecedent = LUMINOSITE;
			break;


		case MANUEL:
			if (modePrecedent != MANUEL) monEcran->afficher("MODE: MANUEL");
			modePrecedent = MANUEL;
			if (monCapteurTouchManuel->readCapteurValue())
			{
				if (etat_volet == FERME)
				{
					monServo->activer();
					for (int i = 0; i < 5; i++)
						monServo->allerRetour(); //pour le test on consid�re que 5AR = Ouvrir volet
					monServo->desactiver();
					etat_volet = OUVERT;
				}
				else if (etat_volet == OUVERT)
				{
					monServo->activer();
					for (int i = 0; i < 2; i++)
						monServo->allerRetour(); //pour le test on consid�re que 2AR = Fermer volet
					monServo->desactiver();
					etat_volet = FERME;
				}
			}
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
