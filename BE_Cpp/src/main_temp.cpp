#include <mraa/i2c.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <mraa/aio.h>
#include <mraa/gpio.h>

#include "../headers/Ecran.h"
#include "../headers/CapteurTemp.h"


using namespace std;




int main(void)
{
	mraa_init();

	CapteurTemp *monCapteurTemp = new CapteurTemp();
	Ecran *monEcran = new Ecran();

	monCapteurTemp->setPin(0);
	monCapteurTemp->init();

	monEcran -> setPin(0);
	monEcran -> init();
	int compteur_seconde(0);

	while (compteur_seconde < 100)
	{
		monEcran -> afficheTemp(monCapteurTemp->calculTemp());
		++compteur_seconde;
	}
	mraa_i2c_stop(monEcran->m_i2c_lcd_control);

	return 0;

}
