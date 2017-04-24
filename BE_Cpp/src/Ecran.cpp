/*
 * Ecran.cpp
 *
 *  Created on: 2 avr. 2017
 *      Author: florent
 */
#include "../headers/Ecran.h"

#include <mraa/i2c.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <mraa/aio.h>
#include <mraa/gpio.h>

#define LCD_CLEARDISPLAY 0x01
#define LCD_ENTRYMODESET 0x04 // Autant définir constantes là, main + clair
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

int m_bus=0;
int m_lcd_control_address=0x3E; // A voir où on les définit ???
int m_rgb_control_address=0x62;

mraa_result_t i2cData (mraa_i2c_context ctx, uint8_t value) {
    mraa_result_t error = MRAA_SUCCESS;

    uint8_t data[2] = { LCD_DATA, value };
    error = mraa_i2c_address (ctx, m_lcd_control_address);
    error = mraa_i2c_write (ctx, data, 2);

    return error;
}



mraa_result_t i2Cmd (mraa_i2c_context ctx, uint8_t value) {
    mraa_result_t error = MRAA_SUCCESS;

    uint8_t data[2] = { LCD_CMD, value };
    error = mraa_i2c_address (ctx, m_lcd_control_address);
    error = mraa_i2c_write (ctx, data, 2);

    return error;
}

mraa_result_t i2cReg (mraa_i2c_context ctx, int deviceAdress, int addr, uint8_t value) {
    mraa_result_t error = MRAA_SUCCESS;

    uint8_t data[2] = { addr, value };
    error = mraa_i2c_address (ctx, deviceAdress);
    error = mraa_i2c_write (ctx, data, 2);

    return error;
}

void Ecran::afficherCaracteristiques()
{

}

void Ecran::arreter()
{
	mraa_i2c_stop(m_i2c_lcd_control);
}

bool Ecran::init()
{
    m_i2c_lcd_control = mraa_i2c_init(pin_number);
    mraa_i2c_address(m_i2c_lcd_control, m_lcd_control_address);

    m_i2c_lcd_rgb = mraa_i2c_init(m_bus);
    mraa_i2c_address(m_i2c_lcd_rgb, m_rgb_control_address);
    usleep(50000);
    i2Cmd(m_i2c_lcd_control, LCD_FUNCTIONSET | LCD_2LINE);
    usleep(4500);
    i2Cmd (m_i2c_lcd_control, LCD_FUNCTIONSET | LCD_2LINE);
    usleep(4500);
    i2Cmd (m_i2c_lcd_control, LCD_FUNCTIONSET | LCD_2LINE);
    usleep(4500);
    i2Cmd (m_i2c_lcd_control, LCD_FUNCTIONSET | LCD_2LINE);
    i2Cmd (m_i2c_lcd_control, LCD_DISPLAYCONTROL | LCD_DISPLAYON);
    i2Cmd (m_i2c_lcd_control, LCD_CLEARDISPLAY);
    usleep(4500);
    i2Cmd (m_i2c_lcd_control, LCD_ENTRYMODESET |
           LCD_ENTRYLEFT |
           LCD_ENTRYSHIFTDECREMENT);
    i2cReg (m_i2c_lcd_rgb, m_rgb_control_address, 0, 0);
    i2cReg (m_i2c_lcd_rgb, m_rgb_control_address, 1, 0);
    i2cReg (m_i2c_lcd_rgb, m_rgb_control_address, 0x08, 0xAA);

    i2cReg (m_i2c_lcd_rgb, m_rgb_control_address, 0x04, 255);
    i2cReg (m_i2c_lcd_rgb, m_rgb_control_address, 0x03, 255);
    i2cReg (m_i2c_lcd_rgb, m_rgb_control_address, 0x02, 255);

    return true;
}

#include <sstream>
std::string Convert (float number){
    std::ostringstream buff;
    buff<<number;
    return buff.str();
}

int Ecran::afficherTemp(float temperature)
{
	if (m_i2c_lcd_control != NULL)
	{
	    int row=1, column=2;
	    int row_addr[] = { 0x80, 0xc0, 0x14, 0x54};
	    uint8_t offset = ((column % 16) + row_addr[row]);
	    i2Cmd (m_i2c_lcd_control, offset);
		i2Cmd (m_i2c_lcd_control, LCD_CLEARDISPLAY);
	    std::string strTemperature = Convert(temperature);
		// std::string strTemperature = to_string(temperature); // Ne marche plus ?
	    														// ARNO : si mais faut ajouter lstdc++ au compilateur :)
		strTemperature = strTemperature.substr(0,4);
		std::string msg= "Temp : "+ strTemperature +" C" ;
		usleep(30000);

		for (std::string::size_type i = 0; i < msg.size(); ++i) {
		i2cData (m_i2c_lcd_control, msg[i]);


		//usleep(100000);

	    }
		return 1;
	}
	else
	{
		// Message avec try / catch .. init avant
		return -1;
	}
}

int Ecran::afficher(float x)
{
	if (m_i2c_lcd_control != NULL)
	{
	    int row=1, column=2;
	    int row_addr[] = { 0x80, 0xc0, 0x14, 0x54};
	    uint8_t offset = ((column % 16) + row_addr[row]);
	    i2Cmd (m_i2c_lcd_control, offset);
		i2Cmd (m_i2c_lcd_control, LCD_CLEARDISPLAY);
	    std::string strX = Convert(x);

		usleep(30000);

		for (std::string::size_type i = 0; i < strX.size(); ++i) {
		i2cData (m_i2c_lcd_control, strX[i]);


		//usleep(100000);

	    }
		return 1;
	}
	else
	{
		// Message avec try / catch .. init avant
		return -1;
	}
}

int Ecran::afficher(std::string msg)
{
	if (m_i2c_lcd_control != NULL)
	{
	    int row=1, column=2;
	    int row_addr[] = { 0x80, 0xc0, 0x14, 0x54};
	    uint8_t offset = ((column % 16) + row_addr[row]);
	    i2Cmd (m_i2c_lcd_control, offset);
		i2Cmd (m_i2c_lcd_control, LCD_CLEARDISPLAY);
	    //std::string strMsg(msg);

		usleep(30000);

		for (std::string::size_type i = 0; i < msg.size(); ++i) {
		i2cData (m_i2c_lcd_control, msg[i]);


		//usleep(100000);

	    }
		return 1;
	}
	else
	{
		// Message avec try / catch .. init avant
		return -1;
	}
}

