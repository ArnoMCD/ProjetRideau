#include <stdio.h>
#include <mraa.h>
#include <math.h>           // for the log function

const int B  = 4275;         // B value for thermistor
const int R0 = 100;          // R0 is 100k ohms

#define TEMP_ADC_PIN    0    // ADC pin is 0

float getTemperature(void)
{
    mraa_aio_context   adcPin;           // used as AIO context
    float              adcValue;         // ADC value read into this variable
    float              R, temperature;   // Used in calculations

    /* Step1: Initialize the mraa */
    mraa_init();

    /* Step2: Initlaize the ADC pin */
    adcPin = mraa_aio_init(TEMP_ADC_PIN);

    /* Step3: Read the ADC value */
    adcValue = mraa_aio_read(adcPin);

    /* Step2: Apply the transformation */
    R = 1023.0/((float)adcValue)-1.0;    // Promote to float
    R = 100000.0*R;

    temperature = 1.0/(log(R/100000.0)/B+1/298.15)-273.15;


    return temperature;
}
