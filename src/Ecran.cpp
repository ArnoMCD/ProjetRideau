/*
 * Ecran.cpp
 *
 *  Created on: 2 avr. 2017
 *      Author: florent
 */
#include "Ecran.h"

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

int m_bus=0;
int m_lcd_control_address=0x3E; // A voir où on les définit ???
int m_rgb_control_address=0x62;

bool Ecran::init()
{
    m_i2c_lcd_control = mraa_i2c_init(m_bus);
    mraa_i2c_address(m_i2c_lcd_control, m_lcd_control_address);

    m_i2c_lcd_rgb = mraa_i2c_init(m_bus);
    mraa_i2c_address(m_i2c_lcd_rgb, m_rgb_control_address);
    usleep(50000);
    i2Cmd (m_i2c_lcd_control, LCD_FUNCTIONSET | LCD_2LINE);
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

int Ecran::AfficheTemp(float temperature)
{
	if (init())
	{
	    int row=1, column=2;
	    int row_addr[] = { 0x80, 0xc0, 0x14, 0x54};
	    uint8_t offset = ((column % 16) + row_addr[row]);
	    i2Cmd (m_i2c_lcd_control, offset);

	    while (1)
		{
	    	i2Cmd (m_i2c_lcd_control, LCD_CLEARDISPLAY);
	    	    std::string strTemperature = std::to_string(temperature);
	    	    strTemperature = strTemperature.substr(0,4);
	    	    std::string msg= "Temp : "+ strTemperature +" C" ;
	    	    usleep(1000);
	    	    for (std::string::size_type i = 0; i < msg.size(); ++i) {
	    	      i2cData (m_i2c_lcd_control, msg[i]);
	    	    }
	    	    //usleep(100000);
	    }
		sleep(3);
		mraa_i2c_stop(m_i2c_lcd_control);
		return 0;
	}
	else
	{
		// Message avec try / catch .. init avant
		return 1234;
	}
}



