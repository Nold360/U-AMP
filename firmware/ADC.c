/*
 * File:   ADC.c
 * Author: Benjamin Todd
 * Editors: nold
 *
 * Created on April 12, 2020, 12:35 AM
 */


#include <xc.h>
#include <stdlib.h>
#include "PICCONFIG_UAMP.h"

unsigned int read_ADC() {
    __delay_ms(5); //sampling time

    ADCON0bits.GOnDONE = 1; //begin ADC
    while (ADCON0bits.GOnDONE); //wait for conversion to complete

    //return (ADRESH >> 3);  //Returns 5-bit result
    return ADRESH; //return upper 5bits
}

int get_adc_volume(int current_vol) {
    // Get a volume out from an analog input, with some hysteresis
    // an_in ranges from 0 to 255
    // current_vol and volume_out range from 0 to 31
    uint8_t an_in = read_ADC();

    // Without hysteresis, we could just divide the an_in value by 8 and
    // round to the nearest integer. Or, equivalently, finding volume_out such
    // that volume_out*8 is within 4 of an_in. To add hysteresis, we just make
    // the that acceptable range wider. A value of 6 should be alright.


    // Check if the current volume level is good enough
    if(abs((current_vol*8 - an_in)) < 6) {
        return current_vol;
    }

    // Otherwise, we'll divide by 8 and round to the nearest int.
    uint8_t out_vol = (an_in + 4)/8;
    if(out_vol > 31) {
        out_vol = 31;
    }
    return out_vol;
 }
