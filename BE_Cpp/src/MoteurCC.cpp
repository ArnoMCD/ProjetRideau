/*
 * MoteurCC.cpp
 *
 *  Created on: 2 avr. 2017
 *      Author: florent
 */
#include "../headers/MoteurCC.h"

#include <mraa/i2c.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <mraa/aio.h>
#include <mraa/gpio.h>

#define LCD_CLEARDISPLAY 0x01
#define LCD_ENTRYMODESET 0x04
#define LCD_FUNCTIONSET 0x20
#define LCD_DATA 0x40
#define LCD_CMD 0x80
#define LCD_DISPLAYCONTROL 0x08
#define LCD_DISPLAYON 0x04

// flags for display entry mode
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTDECREMENT 0x00

#define LCD_2LINE 0x08

using namespace std;

//int m_bus=0;
int m_motor_control_address=0x0f;

mraa_result_t i2cData2 (mraa_i2c_context ctx, uint8_t value) {
    mraa_result_t error = MRAA_SUCCESS;

    uint8_t data[2] = { LCD_DATA, value };
    error = mraa_i2c_address (ctx, m_motor_control_address);
    error = mraa_i2c_write (ctx, data, 2);

    return error;
}



mraa_result_t i2Cmd2 (mraa_i2c_context ctx, uint8_t value) {
    mraa_result_t error = MRAA_SUCCESS;

    uint8_t data[2] = { LCD_CMD, value };
    error = mraa_i2c_address (ctx, m_motor_control_address);
    error = mraa_i2c_write (ctx, data, 2);

    return error;
}

mraa_result_t i2cReg2 (mraa_i2c_context ctx, int deviceAdress, int addr, uint8_t value) {
    mraa_result_t error = MRAA_SUCCESS;

    uint8_t data[2] = { addr, value };
    error = mraa_i2c_address (ctx, deviceAdress);
    error = mraa_i2c_write (ctx, data, 2);

    return error;
}

void MoteurCC::afficherCaracteristiques()
{

}

void MoteurCC::arreter()
{
	mraa_i2c_stop(m_i2c_motor_control);
}

bool MoteurCC::init()
{
    m_i2c_motor_control = mraa_i2c_init(pin_number);
    mraa_i2c_address(m_i2c_motor_control, m_motor_control_address);

    return true;
}

int MoteurCC::dutyCycle(float duty)
{
	if (m_i2c_motor_control != NULL)
	{
	    //i2Cmd2 (m_i2c_motor_control, offset);
		return 1;
	}

	else
	{
		// Message avec try / catch .. init avant
		return -1;
	}
}

