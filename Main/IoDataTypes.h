/* 
 * File:   IoDataTypes.h
 * Author: bn
 *
 * Created on 28 november 2014, 8:45
 */

#ifndef IODATATYPES_H
#define	IODATATYPES_H

#include "os_port.h"

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct Input {
        char Name[64];
        bool_t Status;
    } Input_t;

    typedef struct Relay {
        char Name[64];
        bool_t Status;
        bool_t EnablePulse;
        int PulseTime;
    } Relay_t;

    typedef struct Analog {
        char Name[64];
        double Value;
        int MaxValue;
        int MinValue;
        int AlarmValue;
    } Analog_t;


#ifdef	__cplusplus
}
#endif

#endif	/* IODATATYPES_H */

