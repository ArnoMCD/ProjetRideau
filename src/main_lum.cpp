#include <mraa/i2c.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <mraa/aio.h>
#include <mraa/gpio.h>

#include "../headers/Ecran.h"
#include "../headers/Capteur.h"


using namespace std;




int main4(void)
{
	mraa_init();

	Capteur *monCapteurLum = new Capteur();
	Ecran *monEcran = new Ecran();

	monCapteurLum->setPin(1);
	monCapteurLum->init();

	monEcran -> setPin(0);
	monEcran -> init();
	int compteur_seconde(0);

	while (compteur_seconde < 10)
	{
		monEcran -> afficher(monCapteurLum->readADCValue());
		sleep(1);
		++compteur_seconde;
	}

	monEcran->arreter();

	free(monEcran);
	free(monCapteurLum);

	return 0;

}
