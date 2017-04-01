/*
 * main.cpp
 *
 *  Created on: 30 mars 2017
 *      Author: florent
 */

#include "../headers/Servo.h"

int test_servo(void)
{

Servo *monServo = new Servo();
//monServo->init();
monServo->setPin(4);
monServo->setPeriod(120);

monServo->afficherCaracteristiques();

return 0;
}
