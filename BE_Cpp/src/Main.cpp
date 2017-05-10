/*
 * main.cpp
 *
 *  Created on: 30 mars 2017
 *      Author: florent
 */
#include <mraa.h>
#include <iostream>

//****** HEADERS ******
#include "../headers/Servo.h"
#include "../headers/Ecran.h"
#include "../headers/Capteur.h"
#include "../headers/CapteurNum.h"

//****** CONSTANTES ******
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

//****** VARIABLES ******
int lum;
int etat_lum = SOMBRE;
volatile int mode = LUMINOSITE;
int modePrecedent = MANUEL;
int etat_poussoir = 0;
int etat_volet = FERME;


//*******IT HANDLER********
void intrHandler(void *arg)
{
	// Mode s'incrémente sur front montant, i-e à l'appui sur le bouton poussoir.
	if (etat_poussoir == 0)
	{
		mode = (mode+1)%2; //mode = 0(LUMINOSITE) ou 1(MANUEL)
		etat_poussoir++;
	}
	else if (etat_poussoir == 1)
		etat_poussoir--; // <=> Pas de changement de mode sur front descendant !!!
}

//****** MAIN ******
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

	monCapteurTouch->setPin(5);
	if (!(monCapteurTouch->init()))
		cerr << "error : cannot init capteurTouch" << endl;

	monCapteurTouchManuel->setPin(4);
	if (!(monCapteurTouchManuel->init()))
		cerr << "error : cannot init capteurTouch" << endl;

	monEcran->setPin(0);
	if (!(monEcran->init()))
		cerr << "error : cannot init Ecran" << endl;

	monServo->setPin(3);
	if (!(monServo->init()))
		cerr << "error : cannot init Servo" << endl;

	// Definir les boutons poussoirs en tant qu'input
	monCapteurTouch->defineAsInput();
	monCapteurTouchManuel->defineAsInput();

	// Interruption sur appui sur capteur touch
	monCapteurTouch->callIntrHandler(intrHandler);

	// Fixe la période du servo
	monServo->setPeriod(SERVO_PERIOD);

	//*******LOOOP*******
	while (1) {
		lum = monCapteurLum->readADCValue();

		// Switch avec 2 case : mode LUMINOSITE ou MANUEL
		switch (mode) {
		// mode LUMINOSITE : ouvre/ferme en fonction de la luminosité.
		case LUMINOSITE:
			if (modePrecedent != LUMINOSITE)
				{
				monEcran->afficher("MODE: LUMINOSITE");
				}

			if (etat_lum == SOMBRE && lum > SEUIL_LUM) //on passe de l'ombre à la lumière
			{
				etat_lum = LUMINEUX;
				monServo->activer();
				monServo->dutyCycle(MAX_DUTY_CYCLE); //Ouverture volet
				sleep(1);
				monServo->desactiver();
				etat_volet = OUVERT;
			}
			else if (etat_lum == LUMINEUX && lum < SEUIL_LUM) //on passe de la lumière à l'ombre
			{
				etat_lum = SOMBRE;
				monServo->activer();
				monServo->dutyCycle(MIN_DUTY_CYCLE); //Fermeture volet
				sleep(1);
				monServo->desactiver();
				etat_volet = FERME;
			}
			else {
				usleep(100000);
			}
			modePrecedent = LUMINOSITE;
			break;
			// Commande manuelle par l'appui du bouton poussoir(monCapteurTouchManuel)
		case MANUEL:
			if (modePrecedent != MANUEL) monEcran->afficher("MODE: MANUEL");
			modePrecedent = MANUEL;
			if (monCapteurTouchManuel->readCapteurValue())
			{
				if (etat_volet == FERME)
				{
					monServo->activer();
					monServo->dutyCycle(MAX_DUTY_CYCLE); //Ouverture volet
					sleep(1);
					monServo->desactiver();
					etat_volet = OUVERT;
				}
				else if (etat_volet == OUVERT)
				{
					monServo->activer();
					monServo->dutyCycle(MIN_DUTY_CYCLE); //Fermeture volet
					sleep(1);
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
	monServo->desactiver();

	//*** FREE ***
	free(monServo);
	free(monCapteurTouch);
	free(monEcran);
	free(monCapteurLum);
	free(monCapteurTouchManuel);

	return 0;
}
