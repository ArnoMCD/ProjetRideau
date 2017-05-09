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

/******I2C command definitions*************/
#define MotorSpeedSet             0x82
#define PWMFrequenceSet           0x84
#define DirectionSet              0xaa
#define MotorSetA                 0xa1
#define MotorSetB                 0xa5
#define Nothing                   0x01
/**************Motor ID**********************/
#define MOTOR1 			          1
#define MOTOR2 			          2
/**************Motor Direction***************/
#define BothClockWise             0x0a
#define BothAntiClockWise         0x05
#define M1CWM2ACW                 0x06
#define M1ACWM2CW                 0x09
/**************Motor Direction***************/
#define ClockWise                 0x0a
#define AntiClockWise             0x05
/**************Prescaler Frequence***********/
#define F_31372Hz                 0x01
#define F_3921Hz                  0x02
#define F_490Hz                   0x03
#define F_122Hz                   0x04
#define F_30Hz                    0x05

using namespace std;

//int m_bus=0;
const int m_motor_control_address=0x0f;
/*
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
*/
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
		uint8_t data[3] = { 0xAA, 0xFF, 0xFF};
		mraa_i2c_address (m_i2c_motor_control, m_motor_control_address);
		mraa_i2c_write (m_i2c_motor_control, data, 3);

		data[0] = 0x82;
		mraa_i2c_address (m_i2c_motor_control, m_motor_control_address);
		mraa_i2c_write (m_i2c_motor_control, data, 3);


		data[0] = 0xA1;
		mraa_i2c_address (m_i2c_motor_control, m_motor_control_address);
		mraa_i2c_write (m_i2c_motor_control, data, 3);

		data[0] = 0xA5;
		mraa_i2c_address (m_i2c_motor_control, m_motor_control_address);
		mraa_i2c_write (m_i2c_motor_control, data, 3);

		data[0] = 0x84;
		mraa_i2c_address (m_i2c_motor_control, m_motor_control_address);
		mraa_i2c_write (m_i2c_motor_control, data, 3	 );
		return 1;


		/*uint8_t data[5] = { 0x55, 0xAA, 0xB1, 0x1, 0x00};
	    data[4] = (data[0]+data[1]+data[2]+data[3]) & 0xFF;
	    mraa_i2c_write (m_i2c_motor_control, data, 5);

	    data[2] = 0xC1;
	    data[3] = 0xFF;
	    data[4] = (data[0]+data[1]+data[2]+data[3]) & 0xFF;
		//error = mraa_i2c_address (m_i2c_motor_control, m_motor_control_address);
		mraa_i2c_write (m_i2c_motor_control, data, 5);*/

	}

	else
	{
		// Message avec try / catch .. init avant
		return -1;
	}
}

