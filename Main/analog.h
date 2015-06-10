/* 
 * File:   analog.h
 * Author: bn
 *
 * Created on 26 mei 2014, 9:42
 */

#ifndef ANALOG_H
#define	ANALOG_H

#ifdef	__cplusplus
extern "C" {
#endif
    // Define setup parameters for OpenADC10 function
    // Turn module on | Ouput in integer format | Trigger mode auto | Enable autosample
#define config1     ADC_FORMAT_INTG | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON
    // ADC ref external | Disable offset test | Disable scan mode | Perform 2 samples | Use dual buffers | Use alternate mode
#define config2     ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_OFF | ADC_SAMPLES_PER_INT_2 | ADC_ALT_BUF_ON | ADC_ALT_INPUT_ON
    // Use ADC internal clock | Set sample time
#define config3     ADC_CONV_CLK_INTERNAL_RC | ADC_SAMPLE_TIME_15
    // Do not assign channels to scan
#define configscan  SKIP_SCAN_ALL

#define configport  ENABLE_AN2_ANA


void getAnalogInputInString(char * string);
void getAnalogValue(void);

#ifdef	__cplusplus
}
#endif

#endif	/* ANALOG_H */

