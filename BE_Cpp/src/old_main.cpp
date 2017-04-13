#include <stdio.h>
#include "mraa.h"
#include <math.h>           // for the log function
#include <string.h>
#include <iostream>

#define SERVO_PIN    3    // ADC pin is 0


using namespace std;

int main2(void) /// RENAME POUR REMETTRE EN MAIN
{
    mraa_pwm_context  pwmPin;

    /* Step1: Initialize the mraa */
    mraa_init();

    /* Step2: Initlaize the ADC pin */
    pwmPin = mraa_pwm_init(SERVO_PIN);

    mraa_pwm_enable(pwmPin, 1);

    mraa_pwm_period_us(pwmPin, 5000);

    /* Step3: Read the ADC value */
    int compteurAR = 0;
    while(compteurAR < 3)
{
    int i = 20;
    //int j = 0;
    while(i<65)
    {
        mraa_pwm_write(pwmPin,i*0.01);
        usleep(5000);
        i++;
    }
    while(i>0)
    {
        mraa_pwm_write(pwmPin,i*0.01);
        usleep(5000);
        i--;
    }
    compteurAR++;
}
    //mraa_pwm_write(0.2);
    //usleep(2

    mraa_pwm_enable(pwmPin, 0);


    return 0;
}
