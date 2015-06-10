/**
 * @file relay.c
 * @brief Embedded resource management
 *
 * @section License
 *
 * Copyright (C) 2014 Velleman nv. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @author Velleman nv (www.velleman.eu)
 * @version 1.0.0
 **/

#include "analog.h"
#include <p32xxxx.h>
#include "shared.h"

void initAnalog() {
    AD1PCFG = 0xFFFB; // all PORTB = Digital but RB2 = analog
    AD1CON1 = 0x0000; // ASAM bit = 1 implies acquisition
    // starts immediately after last
    // conversion is done
    AD1CHS = 0x00020000; // Connect RB2/AN2 as CH0 input
    // in this example RB7/AN7 is the input
    AD1CSSL = 0;
    AD1CON3 = 0x0002; // Sample time manual, TAD = internal 6 TPB
    AD1CON2 = 0;

    AD1CON1SET = 0x8000; // turn ON the ADC
}

void getAnalogValue(void) {

    AD1CON1SET = 0x0002; // start sampling ...
    osDelayTask(100); // for 100 ms
    AD1CON1CLR = 0x0002; // start Converting
    while (!(AD1CON1 & 0x0001)); // conversion done?
    appSettings.IoSettings.analog.Value = ADC1BUF0; // yes then get ADC value
    Nop();
}
void ftoa(float value, char *string)
 {
     if (value < 0) {
         *string++ = '-';
         value = -value;
     }
     sprintf(string, "%lu.%02u",(long) value,(int) ((value - (long) value) * 1000. + 0.5));
 }

void getAnalogInputInString(char * string)
{
    //Mail contents
   float fvalue =appSettings.IoSettings.analog.Value;
   fvalue /= 1023;
   fvalue *=3.3;
   fvalue *=2;
   ftoa(fvalue,string);
}

int getAnalogInputInInteger()
{
    //Mail contents
   float fvalue =appSettings.IoSettings.analog.Value;
   fvalue /= 1023;
   fvalue *=3.3;
   fvalue *=2;
   return fvalue;
}

