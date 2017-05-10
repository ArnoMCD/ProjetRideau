#include <mraa/i2c.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <mraa/aio.h>
#include <mraa/gpio.h>

#include "../headers/Ecran.h"
#include "../headers/CapteurTemp.h"


using namespace std;

// ********** TEST DU CAPTEUR DE TEMPERATURE SEUL *************


int main_temp(void)
{
	mraa_init();

	CapteurTemp *monCapteurTemp = new CapteurTemp();
	Ecran *monEcran = new Ecran();

	monCapteurTemp->setPin(0);
	monCapteurTemp->init();

	monEcran -> setPin(0);
	monEcran -> init();
	int compteur_seconde(0);

	while (compteur_seconde < 10)
	{
		monEcran -> afficherTemp(monCapteurTemp->calculTemp());
		sleep(1);
		++compteur_seconde;
	}

	monEcran->arreter();

	free(monEcran);
	free(monCapteurTemp);

	return 0;

}
