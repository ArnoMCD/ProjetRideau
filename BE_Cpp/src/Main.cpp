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
#define SEUIL_SOMBRE 400
#define LUMINOSITE 0
#define MANUEL 1
#define MONTANT 0
#define DESCENDANT 1
#define FERME 0
#define OUVERT 1

using namespace std;

//****** VARIABLES ******
int lum = 0;
volatile int mode = LUMINOSITE;
int modePrecedent = MANUEL;
int intr_front = MONTANT;
int etat_volet = FERME;

//*******IT HANDLER********
void intrHandler(void *arg) {
	// Mode s'incr�mente sur front montant, i-e � l'appui sur le bouton poussoir.
	if (intr_front == MONTANT)
		mode = (mode + 1) % 2; //mode = 0(LUMINOSITE) ou 1(MANUEL)
	intr_front ^= 1; //La prochaine lev�e de l'interruption sera sur le front descendant (bouton rel�ch�), on ne changera pas de mode
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

	// Interruption sur appui sur capteur touch, est appel�e sur chaque front montant ET descendant
	monCapteurTouch->callIntrHandler(intrHandler);

	// Fixe la p�riode du servo
	monServo->setPeriod(SERVO_PERIOD);

	//*******LOOP*******
	while (1) {
		lum = monCapteurLum->readADCValue();

		// Switch avec 2 case : mode LUMINOSITE ou MANUEL
		switch (mode) {
		// mode LUMINOSITE : ouvre/ferme en fonction de la luminosit�.
		case LUMINOSITE:
			if (modePrecedent != LUMINOSITE)
				monEcran->afficher("MODE: LUMINOSITE"); //On n'actualise l'affichage sur le LCD qui si le mode a chang�
			modePrecedent = LUMINOSITE;

			if (etat_volet == FERME && lum > SEUIL_LUM) //Si le volet est ferm� et qu'il fait jour...
			{
				monServo->activer();
				monServo->dutyCycle(MAX_DUTY_CYCLE); //...on ouvre le volet
				usleep(500000);
				monServo->desactiver();
				etat_volet = OUVERT;
			} else if (etat_volet == OUVERT && lum < SEUIL_SOMBRE) //Si le volet est ouvert et qu'il fait sombre...
			{
				monServo->activer();
				monServo->dutyCycle(MIN_DUTY_CYCLE); //...on ferme le volet
				usleep(500000);
				monServo->desactiver();
				etat_volet = FERME;
			} else {
				usleep(100000);
			}

			break;

			// Commande manuelle par l'appui du bouton poussoir(monCapteurTouchManuel)
		case MANUEL:
			if (modePrecedent != MANUEL)
				monEcran->afficher("MODE: MANUEL"); //On n'actualise l'affichage sur le LCD qui si le mode a chang�
			modePrecedent = MANUEL;

			if (monCapteurTouchManuel->readCapteurValue()) {
				if (etat_volet == FERME) {
					monServo->activer();
					monServo->dutyCycle(MAX_DUTY_CYCLE); //Ouverture volet
					usleep(500000);
					monServo->desactiver();
					etat_volet = OUVERT;
				} else if (etat_volet == OUVERT) {
					monServo->activer();
					monServo->dutyCycle(MIN_DUTY_CYCLE); //Fermeture volet
					usleep(500000);
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

	//*** DELETE ***
	delete monServo;
	delete monCapteurTouch;
	delete monEcran;
	delete monCapteurLum;
	delete monCapteurTouchManuel;

	return 0;
}
