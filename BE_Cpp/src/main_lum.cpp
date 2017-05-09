#include <mraa/i2c.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <mraa/aio.h>
#include <mraa/gpio.h>

#include "../headers/Ecran.h"
#include "../headers/Capteur.h"


using namespace std;

/* PLAGE CAPTEUR DE LUMINOSITE : 0 (noir complet) -> 770 (sature assez vite) */




int main58(void)
>>>>>>> branch 'master' of https://github.com/ArnoMCD/ProjetRideau.git
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
