/*
 * File:   relays.h
 * Author: bn
 *
 * Created on 26 mei 2014, 9:42
 */

#ifndef RELAYS_H
#define	RELAYS_H

#ifdef	__cplusplus
extern "C" {
#endif

    //Relays
#define RY1_MASK (1 << 2)
#define RY2_MASK (1 << 3)
#define RY3_MASK (1 << 4)
#define RY4_MASK (1 << 5)

#define RY1 LATDbits.LATD2
#define RY2 LATDbits.LATD3
#define RY3 LATDbits.LATD4
#define RY4 LATDbits.LATD5

#define READRY1 PORTDbits.RD2
#define READRY2 PORTDbits.RD3
#define READRY3 PORTDbits.RD4
#define READRY4 PORTDbits.RD5

#define RELAYS_STATUS_ADR_LOC 0x00
#define REMEMBER_RELAYS ENABLED





int getRelayValue(int relay);
void setRelayValue(int relay, int status);
void saveRelays(void);



#ifdef	__cplusplus
}
#endif

#endif	/* RELAYS_H */

