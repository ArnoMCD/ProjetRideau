/*
 * CapteurNum.cpp
 *
 *  Created on: 26 avr. 2017
 *      Author: florent
 */
#include "mraa.h"
#include <stdio.h>
#include <math.h>
#include "../headers/CapteurNum.h"
#include <iostream>


using namespace std;


//Initialisation
bool CapteurNum::init()
{
	poussoirPinNumber = mraa_gpio_init(pin_number);
	if (poussoirPinNumber != NULL) return true;
	else return false;
}

// Pin = Input
void CapteurNum::defineAsInput()
{
	mraa_gpio_dir(poussoirPinNumber, MRAA_GPIO_IN);
}

// Lit la valeur du bouton poussoir;
int CapteurNum::readCapteurValue()
{
	return mraa_gpio_read(poussoirPinNumber);
}

// Affiche état du bouton poussoir
void CapteurNum::afficherCaracteristiques()
{
	if (this->readCapteurValue() != 0)
			cout << "The button is being pushed" << endl;
	else cout << "The button is not being pushed" << endl;
}

// Appelle le handler quand la pin du bouton poussoir passe de 0 à 1
void CapteurNum:: callIntrHandler(void (*ptrHandler)(void*))
{
	mraa_gpio_isr(poussoirPinNumber, MRAA_GPIO_EDGE_BOTH, ptrHandler, NULL);
}

// si mode = 0 alors mode = 1 / si mode = 1 alors mode = 0
//int CapteurNum:: intrHandler(void *arg)
//{
//	mode = (mode+1)%2;
//	return mode;
//}

//Stop the interruption handler
void CapteurNum:: stopIntrHandler()
{
	mraa_gpio_isr_exit(poussoirPinNumber);
}

// Exit
void CapteurNum:: closePin()
{
	mraa_gpio_close(poussoirPinNumber);
}

// Affiche le mode
void CapteurNum:: printMode(int mode)
{
	cout << mode;
}

