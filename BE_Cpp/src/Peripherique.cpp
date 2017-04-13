/*
 * Peripherique.cpp
 *
 *  Created on: 30 mars 2017
 *      Author: florent
 */
#include "../headers/Peripherique.h"

int Peripherique::getPin()
{
	return pin_number;
}

void Peripherique::setPin(int pin)
{
	this->pin_number = pin;
}

