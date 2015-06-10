/*********************************************************************
 *
 *	Hardware specific definitions
 *
 *********************************************************************
 * FileName:        HardwareProfile.h
 * Dependencies:    None
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Compiler:        Microchip C32 v1.10 or higher
 *					Microchip C30 v3.12 or higher
 *					Microchip C18 v3.34 or higher
 *					HI-TECH PICC-18 PRO 9.63PL2 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (C) 2002-2010 Microchip Technology Inc.  All rights
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and
 * distribute:
 * (i)  the Software when embedded on a Microchip microcontroller or
 *      digital signal controller product ("Device") which is
 *      integrated into Licensee's product; or
 * (ii) ONLY the Software driver source files ENC28J60.c, ENC28J60.h,
 *		ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device
 *		used in conjunction with a Microchip ethernet controller for
 *		the sole purpose of interfacing with the ethernet controller.
 *
 * You should refer to the license agreement accompanying this
 * Software for additional information regarding your rights and
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 *
 * Author               Date		Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Howard Schlunder		10/03/06	Original, copied from Compiler.h
 * Ken Hesky            01/xx/10    Added MRF24WB0M-specific features
 ********************************************************************/
#ifndef __HARDWARE_PROFILE_H
#define __HARDWARE_PROFILE_H

#include "GenericTypeDefs.h"
#include "Compiler.h"

#define PIC32_ENET_SK_DM320004		// PIC32MX795F512L Ethernet Starter Kit board with embedded Ethernet controller

// If no hardware profiles are defined, assume that we are using 
// a Microchip demo board and try to auto-select the correct profile
// based on processor selected in MPLAB
//#if !defined(PICDEMNET2) && !defined(PIC18_EXPLORER) && !defined(HPC_EXPLORER) && !defined(EXPLORER_16) && !defined(PIC24FJ64GA004_PIM) && !defined(DSPICDEM11) && !defined(PICDEMNET2) && !defined(INTERNET_RADIO) && !defined(YOUR_BOARD) && !defined(__PIC24FJ128GA006__) && !defined(PIC32_GP_SK_DM320001) && !defined(PIC32_USB_DM320003_1) && !defined(PIC32_USB_SK_DM320003_2) && !defined(PIC32_ENET_SK_DM320004) && !defined(PIC24FJ256DA210_DEV_BOARD)
//	#if defined(__18F97J60) || defined(_18F97J60)
//		#define PICDEMNET2
//	#elif defined(__18F67J60) || defined(_18F67J60)
//		#define INTERNET_RADIO
//	#elif defined(__18F8722) || defined(__18F87J10) || defined(_18F8722) || defined(_18F87J10) || defined(__18F87J11) || defined(_18F87J11)|| defined(__18F87J50) || defined(_18F87J50)
//		#define PIC18_EXPLORER
//		//#define HPC_EXPLORER
//	#elif defined(__PIC24FJ64GA004__)
//		#define PIC24FJ64GA004_PIM
//	#elif defined(__PIC24FJ256DA210__)
//		#define PIC24FJ256DA210_DEV_BOARD
//	#elif defined(__PIC24F__) || defined(__PIC24H__) || defined(__dsPIC33F__) || defined(__PIC32MX__)
//		#define EXPLORER_16
//	#elif defined(__dsPIC30F__)
//		#define DSPICDEM11
//	#endif
//#endif
//
// Set configuration fuses (but only once)
#if defined(THIS_IS_STACK_APPLICATION)
#if defined(__18CXX)
#if defined(__EXTENDED18__)
#pragma config XINST=ON
#elif !defined(HI_TECH_C)
#pragma config XINST=OFF
#endif

#if defined(__18F8722) && !defined(HI_TECH_C)
// PICDEM HPC Explorer or PIC18 Explorer board
#pragma config OSC=HSPLL, FCMEN=OFF, IESO=OFF, PWRT=OFF, WDT=OFF, LVP=OFF
#elif defined(_18F8722)	// HI-TECH PICC-18 compiler
// PICDEM HPC Explorer or PIC18 Explorer board with HI-TECH PICC-18 compiler
__CONFIG(1, HSPLL);
__CONFIG(2, WDTDIS);
__CONFIG(3, MCLREN);
__CONFIG(4, XINSTDIS & LVPDIS);
#elif defined(__18F87J10) && !defined(HI_TECH_C)
// PICDEM HPC Explorer or PIC18 Explorer board
#pragma config WDTEN=OFF, FOSC2=ON, FOSC=HSPLL
#elif defined(__18F87J11) && !defined(HI_TECH_C)
// PICDEM HPC Explorer or PIC18 Explorer board
#pragma config WDTEN=OFF, FOSC=HSPLL
#elif defined(__18F87J50) && !defined(HI_TECH_C)
// PICDEM HPC Explorer or PIC18 Explorer board
#pragma config WDTEN=OFF, FOSC=HSPLL, PLLDIV=3, CPUDIV=OSC1
#elif (defined(__18F97J60) || defined(__18F96J65) || defined(__18F96J60) || defined(__18F87J60) || defined(__18F86J65) || defined(__18F86J60) || defined(__18F67J60) || defined(__18F66J65) || defined(__18F66J60)) && !defined(HI_TECH_C)
// PICDEM.net 2 or any other PIC18F97J60 family device
#pragma config WDT=OFF, FOSC2=ON, FOSC=HSPLL, ETHLED=ON
#elif defined(_18F97J60) || defined(_18F96J65) || defined(_18F96J60) || defined(_18F87J60) || defined(_18F86J65) || defined(_18F86J60) || defined(_18F67J60) || defined(_18F66J65) || defined(_18F66J60)
// PICDEM.net 2 board with HI-TECH PICC-18 compiler
__CONFIG(1, WDTDIS & XINSTDIS);
__CONFIG(2, HSPLL);
__CONFIG(3, ETHLEDEN);
#elif defined(__18F4620) && !defined(HI_TECH_C)
#pragma config OSC=HSPLL, WDT=OFF, MCLRE=ON, PBADEN=OFF, LVP=OFF
#endif
#elif defined(__PIC24FJ256DA210__) || defined(__PIC24FJ256GB210__)
// PIC24FJ256DA210 Development Board (Graphics) or PIC24FJ256GB210 PIM on Explorer 16
_CONFIG3(ALTPMP_ALPMPDIS & SOSCSEL_EC); // PMP in default location, disable Timer1 oscillator so that RC13 can be used as a GPIO
_CONFIG2(FNOSC_PRIPLL & POSCMOD_XT & IOL1WAY_OFF & PLL96MHZ_ON & PLLDIV_DIV2); // Primary XT OSC with 96MHz PLL (8MHz crystal input), IOLOCK can be set and cleared
_CONFIG1(FWDTEN_OFF & ICS_PGx2 & JTAGEN_OFF & ALTVREF_ALTVREDIS); // Watchdog timer off, ICD debugging on PGEC2/PGED2 pins, JTAG off, AVREF and CVREF in default locations
#elif defined(__PIC24FJ256GB110__)
// PIC24FJ256GB110 PIM on Explorer 16
_CONFIG2(PLLDIV_DIV2 & PLL_96MHZ_ON & FNOSC_PRIPLL & IOL1WAY_OFF & POSCMOD_XT); // Primary XT OSC with 96MHz PLL (8MHz crystal input), IOLOCK can be set and cleared
_CONFIG1(JTAGEN_OFF & ICS_PGx2 & FWDTEN_OFF); // Watchdog timer off, ICD debugging on PGEC2/PGED2 pins, JTAG off
#elif defined(__PIC24FJ256GA110__)
// PIC24FJ256GA110 PIM on Explorer 16
_CONFIG2(FNOSC_PRIPLL & IOL1WAY_OFF & POSCMOD_XT); // Primary XT OSC with PLL, IOLOCK can be set and cleared
_CONFIG1(JTAGEN_OFF & ICS_PGx2 & FWDTEN_OFF); // Watchdog timer off, ICD debugging on PGEC2/PGED2 pins, JTAG off
#elif defined(__PIC24F__)
// Explorer 16 board
_CONFIG2(FNOSC_PRIPLL & POSCMOD_XT) // Primary XT OSC with 4x PLL
_CONFIG1(JTAGEN_OFF & FWDTEN_OFF) // JTAG off, watchdog timer off
#elif defined(__dsPIC33F__) || defined(__PIC24H__)
// Explorer 16 board
_FOSCSEL(FNOSC_PRIPLL) // PLL enabled
_FOSC(OSCIOFNC_OFF & POSCMD_XT) // XT Osc
_FWDT(FWDTEN_OFF) // Disable Watchdog timer
// JTAG should be disabled as well
#elif defined(__dsPIC30F__)
// dsPICDEM 1.1 board
_FOSC(XT_PLL16) // XT Osc + 16X PLL
_FWDT(WDT_OFF) // Disable Watchdog timer
_FBORPOR(MCLR_EN & PBOR_OFF & PWRT_OFF)
#elif defined(__PIC32MX__)
#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF, FPBDIV = DIV_1, POSCMOD = XT, FNOSC = PRIPLL, CP = OFF
#if defined(PIC32_ENET_SK_DM320004)
#pragma config FMIIEN = OFF, FETHIO = OFF	// external PHY in RMII/alternate configuration
#endif
#endif
#endif // Prevent more than one set of config fuse definitions

// Clock frequency value.
// This value is used to calculate Tick Counter value
#if defined(__18CXX)
// All PIC18 processors
#if defined(PICDEMNET2) || defined(INTERNET_RADIO)
#define GetSystemClock()		(41666667ul)      // Hz
#define GetInstructionClock()	(GetSystemClock()/4)
#define GetPeripheralClock()	GetInstructionClock()
#elif defined(__18F87J50) || defined(_18F87J50)
#define GetSystemClock()		(48000000ul)      // Hz
#define GetInstructionClock()	(GetSystemClock()/4)
#define GetPeripheralClock()	GetInstructionClock()
#else
#define GetSystemClock()		(40000000ul)      // Hz
#define GetInstructionClock()	(GetSystemClock()/4)
#define GetPeripheralClock()	GetInstructionClock()
#endif
#elif defined(__PIC24F__) || defined(__PIC24FK__)
// PIC24F processor
#define GetSystemClock()		(32000000ul)      // Hz
#define GetInstructionClock()	(GetSystemClock()/2)
#define GetPeripheralClock()	GetInstructionClock()
#elif defined(__PIC24H__)
// PIC24H processor
#define GetSystemClock()		(80000000ul)      // Hz
#define GetInstructionClock()	(GetSystemClock()/2)
#define GetPeripheralClock()	GetInstructionClock()
#elif defined(__dsPIC33F__)
// dsPIC33F processor
#define GetSystemClock()		(80000000ul)      // Hz
#define GetInstructionClock()	(GetSystemClock()/2)
#define GetPeripheralClock()	GetInstructionClock()
#elif defined(__dsPIC30F__)
// dsPIC30F processor
#define GetSystemClock()		(117920000ul)      // Hz
#define GetInstructionClock()	(GetSystemClock()/4)
#define GetPeripheralClock()	GetInstructionClock()
#elif defined(__PIC32MX__)
// PIC32MX processor
#define GetSystemClock()		(80000000ul)      // Hz
#define GetInstructionClock()	(GetSystemClock()/1)
#define GetPeripheralClock()	(GetInstructionClock()/1)	// Set your divider according to your Peripheral Bus Frequency configuration fuse setting
#endif

// Hardware mappings
#if defined(PIC18_EXPLORER) && !defined(HI_TECH_C)
// PIC18 Explorer + Fast 100Mbps Ethernet PICtail Plus or Ethernet PICtail
// I/O pins
#define LED0_TRIS			(TRISDbits.TRISD0)
#define LED0_IO				(LATDbits.LATD0)
#define LED1_TRIS			(TRISDbits.TRISD1)
#define LED1_IO				(LATDbits.LATD1)
#define LED2_TRIS			(TRISDbits.TRISD2)
#define LED2_IO				(LATDbits.LATD2)
#define LED3_TRIS			(TRISDbits.TRISD3)
#define LED3_IO				(LATDbits.LATD3)
#define LED4_TRIS			(TRISDbits.TRISD4)
#define LED4_IO				(LATDbits.LATD4)
#define LED5_TRIS			(TRISDbits.TRISD5)
#define LED5_IO				(LATDbits.LATD5)
#define LED6_TRIS			(TRISDbits.TRISD6)
#define LED6_IO				(LATDbits.LATD6)
#define LED7_TRIS			(TRISDbits.TRISD7)
#define LED7_IO				(LATDbits.LATD7)
#define LED_GET()			(LATD)
#define LED_PUT(a)			(LATD = (a))

#define BUTTON0_TRIS		(TRISAbits.TRISA5)
#define	BUTTON0_IO			(PORTAbits.RA5)
#define BUTTON1_TRIS		(TRISBbits.TRISB0)
#define	BUTTON1_IO			(PORTBbits.RB0)
#define BUTTON2_TRIS		(PRODL)				// No Button2 on this board
#define	BUTTON2_IO			(1u)
#define BUTTON3_TRIS		(PRODL)				// No Button3 on this board
#define	BUTTON3_IO			(1u)


// Register name fix up for certain processors
#define SPBRGH				SPBRGH1
#if defined(__18F87J50) || defined(_18F87J50) || defined(__18F87J11) || defined(_18F87J11)
#define ADCON2		ADCON1
#endif

#elif defined(PIC18_EXPLORER) && defined(HI_TECH_C)
// PIC18 Explorer + Fast 100Mbps Ethernet PICtail Plus or Ethernet PICtail + HI-TECH PICC-18 compiler
// I/O pins
#define LED0_TRIS			(TRISD0)
#define LED0_IO				(LATD0)
#define LED1_TRIS			(TRISD1)
#define LED1_IO				(LATD1)
#define LED2_TRIS			(TRISD2)
#define LED2_IO				(LATD2)
#define LED3_TRIS			(TRISD3)
#define LED3_IO				(LATD3)
#define LED4_TRIS			(TRISD4)
#define LED4_IO				(LATD4)
#define LED5_TRIS			(TRISD5)
#define LED5_IO				(LATD5)
#define LED6_TRIS			(TRISD6)
#define LED6_IO				(LATD6)
#define LED7_TRIS			(TRISD7)
#define LED7_IO				(LATD7)
#define LED_GET()			(LATD)
#define LED_PUT(a)			(LATD = (a))

#define BUTTON0_TRIS		(TRISA5)
#define	BUTTON0_IO			(RA5)
#define BUTTON1_TRIS		(TRISB0)
#define	BUTTON1_IO			(RB0)
#define BUTTON2_TRIS		(PRODL)				// No Button2 on this board
#define	BUTTON2_IO			(1u)
#define BUTTON3_TRIS		(PRODL)				// No Button3 on this board
#define	BUTTON3_IO			(1u)

// LCD I/O pins
// TODO: Need to add support for LCD behind MCP23S17 I/O expander.  This 
// requires code that isn't in the TCP/IP stack, not just a hardware 
// profile change.

// Register name fix up for certain processors
#define SPBRGH				SPBRGH1
#define TXSTAbits			TXSTA1bits
#define RCSTAbits			RCSTA1bits
#define BAUDCONbits			BAUDCON1bits
#define GO					GODONE
#if defined(__18F87J50) || defined(_18F87J50) || defined(__18F87J11) || defined(_18F87J11)
#define ADCON2		ADCON1
#endif

#elif defined(HPC_EXPLORER) && !defined(HI_TECH_C)
// PICDEM HPC Explorer + Fast 100Mbps Ethernet PICtail Plus or Ethernet PICtail
// I/O pins
#define LED0_TRIS			(TRISDbits.TRISD0)
#define LED0_IO				(LATDbits.LATD0)
#define LED1_TRIS			(TRISDbits.TRISD1)
#define LED1_IO				(LATDbits.LATD1)
#define LED2_TRIS			(TRISDbits.TRISD2)
#define LED2_IO				(LATDbits.LATD2)
#define LED3_TRIS			(TRISDbits.TRISD3)
#define LED3_IO				(LATDbits.LATD3)
#define LED4_TRIS			(TRISDbits.TRISD4)
#define LED4_IO				(LATDbits.LATD4)
#define LED5_TRIS			(TRISDbits.TRISD5)
#define LED5_IO				(LATDbits.LATD5)
#define LED6_TRIS			(TRISDbits.TRISD6)
#define LED6_IO				(LATDbits.LATD6)
#define LED7_TRIS			(TRISDbits.TRISD7)
#define LED7_IO				(LATDbits.LATD7)
#define LED_GET()			(LATD)
#define LED_PUT(a)			(LATD = (a))


#define BUTTON0_TRIS		(TRISBbits.TRISB0)
#define	BUTTON0_IO			(PORTBbits.RB0)
#define BUTTON1_TRIS		(TRISBbits.TRISB0)	// No Button1 on this board, remap to Button0
#define	BUTTON1_IO			(PORTBbits.RB0)
#define BUTTON2_TRIS		(TRISBbits.TRISB0)	// No Button2 on this board, remap to Button0
#define	BUTTON2_IO			(PORTBbits.RB0)
#define BUTTON3_TRIS		(TRISBbits.TRISB0)	// No Button3 on this board, remap to Button0
#define	BUTTON3_IO			(PORTBbits.RB0)

// Register name fix up for certain processors
#define SPBRGH				SPBRGH1
#if defined(__18F87J50) || defined(_18F87J50) || defined(__18F87J11) || defined(_18F87J11)
#define ADCON2		ADCON1
#endif

#elif defined(HPC_EXPLORER) && defined(HI_TECH_C)
// PICDEM HPC Explorer + Ethernet PICtail
#define TXSTA				TXSTA1
#define RCSTA				RCSTA1
#define SPBRG				SPBRG1
#define SPBRGH				SPBRGH1
#define RCREG				RCREG1
#define TXREG				TXREG1

// I/O pins
#define LED0_TRIS			(TRISD0)
#define LED0_IO				(LATD0)
#define LED1_TRIS			(TRISD1)
#define LED1_IO				(LATD1)
#define LED2_TRIS			(TRISD2)
#define LED2_IO				(LATD2)
#define LED3_TRIS			(TRISD3)
#define LED3_IO				(LATD3)
#define LED4_TRIS			(TRISD4)
#define LED4_IO				(LATD4)
#define LED5_TRIS			(TRISD5)
#define LED5_IO				(LATD5)
#define LED6_TRIS			(TRISD6)
#define LED6_IO				(LATD6)
#define LED7_TRIS			(TRISD7)
#define LED7_IO				(LATD7)
#define LED_GET()			(LATD)
#define LED_PUT(a)			(LATD = (a))

#define BUTTON0_TRIS		(TRISB0)
#define	BUTTON0_IO			(RB0)
#define BUTTON1_TRIS		(TRISB0)	// No Button1 on this board, remap to Button0
#define	BUTTON1_IO			(RB0)
#define BUTTON2_TRIS		(TRISB0)	// No Button2 on this board, remap to Button0
#define	BUTTON2_IO			(RB0)
#define BUTTON3_TRIS		(TRISB0)	// No Button3 on this board, remap to Button0
#define	BUTTON3_IO			(RB0)

#elif defined(PIC24FJ64GA004_PIM)
// Explorer 16 + PIC24FJ64GA004 PIM + Ethernet PICtail Plus

// Push Button I/O pins
#define BUTTON3_TRIS		TRISAbits.TRISA10		// Mutliplexed with LED0
#define BUTTON3_IO			PORTAbits.RA10
#define BUTTON2_TRIS		TRISAbits.TRISA9		// Multiplexed with LED4
#define BUTTON2_IO			PORTAbits.RA9
#define BUTTON1_TRIS		TRISCbits.TRISC6		// Multiplexed with LED7
#define BUTTON1_IO			PORTCbits.RC6
#define BUTTON0_TRIS		TRISAbits.TRISA7		// Multiplexed with LED1
#define BUTTON0_IO			PORTAbits.RA7

// LED I/O pins
#define LED0_TRIS			TRISAbits.TRISA10		// Multiplexed with BUTTON3
#define LED0_IO				LATAbits.LATA10
#define LED1_TRIS			TRISAbits.TRISA7		// Multiplexed with BUTTON0
#define LED1_IO				LATAbits.LATA7
#define LED2_TRIS			TRISBbits.TRISB8		// Multiplexed with LCD_DATA4
#define LED2_IO				LATBbits.LATB8
#define LED3_TRIS			TRISBbits.TRISB9		// Multiplexed with LCD_DATA3
#define LED3_IO				LATBbits.LATB9
#define LED4_TRIS			TRISAbits.TRISA9		// Multiplexed with BUTTON2
#define LED4_IO				LATAbits.LATA9
#define LED5_TRIS			TRISAbits.TRISA8		// Multiplexed with EEPROM_CS
#define LED5_IO				LATAbits.LATA8
#define LED6_TRIS			TRISBbits.TRISB12		// Multiplexed with LCD_DATA0
#define LED6_IO				LATBbits.LATB12
#define LED7_TRIS			TRISCbits.TRISC6		// Multiplexed with BUTTON1
#define LED7_IO				LATCbits.LATC6
#define LED_GET()			(0u)
#define LED_PUT(a)

// UART I/O Mapping
#define UARTTX_TRIS			(TRISCbits.TRISC9)
#define UARTTX_IO			(PORTCbits.RC9)
#define UARTRX_TRIS			(TRISCbits.TRISC3)
#define UARTRX_IO			(PORTCbits.RC3)

// LCD Module I/O pins
#define LCD_DATA0_TRIS		(TRISBbits.TRISB12)		// Multiplexed with LED6
#define LCD_DATA0_IO		(LATBbits.LATB12)
#define LCD_DATA1_TRIS		(TRISBbits.TRISB11)
#define LCD_DATA1_IO		(LATBbits.LATB11)
#define LCD_DATA2_TRIS		(TRISBbits.TRISB10)
#define LCD_DATA2_IO		(LATBbits.LATB10)
#define LCD_DATA3_TRIS		(TRISBbits.TRISB9)		// Multiplexed with LED3
#define LCD_DATA3_IO		(LATBbits.LATB9)
#define LCD_DATA4_TRIS		(TRISBbits.TRISB8)		// Multiplexed with LED2
#define LCD_DATA4_IO		(LATBbits.LATB8)
#define LCD_DATA5_TRIS		(TRISBbits.TRISB7)
#define LCD_DATA5_IO		(LATBbits.LATB7)
#define LCD_DATA6_TRIS		(TRISBbits.TRISB6)
#define LCD_DATA6_IO		(LATBbits.LATB6)
#define LCD_DATA7_TRIS		(TRISBbits.TRISB5)
#define LCD_DATA7_IO		(LATBbits.LATB5)
#define LCD_RD_WR_TRIS		(TRISBbits.TRISB13)
#define LCD_RD_WR_IO		(LATBbits.LATB13)
#define LCD_RS_TRIS			(TRISCbits.TRISC7)
#define LCD_RS_IO			(LATCbits.LATC7)
#define LCD_E_TRIS			(TRISBbits.TRISB14)
#define LCD_E_IO			(LATBbits.LATB14)

// Peripheral Pin Select Outputs
#define NULL_IO		0
#define C1OUT_IO	1
#define C2OUT_IO	2
#define U1TX_IO		3
#define U1RTS_IO	4
#define U2TX_IO		5
#define U2RTS_IO	6
#define SDO1_IO		7
#define SCK1OUT_IO	8
#define SS1OUT_IO	9
#define SDO2_IO		10
#define SCK2OUT_IO	11
#define SS2OUT_IO	12
#define OC1_IO		18
#define OC2_IO		19
#define OC3_IO		20
#define OC4_IO		21
#define OC5_IO		22

#elif defined(EXPLORER_16)
// Explorer 16 + PIC24FJ128GA010/PIC24HJ256GP610/dsPIC33FJ256GP710/
//				 PIC32MX460F512L/PIC32MX360F512L/PIC32MX795F512L PIM + 
//               Fast 100Mbps Ethernet PICtail Plus or Ethernet PICtail Plus or MRF24WB0M WiFi PICtail Plus

#define LED0_TRIS			(TRISAbits.TRISA0)	// Ref D3
#define LED0_IO				(LATAbits.LATA0)
#define LED1_TRIS			(TRISAbits.TRISA1)	// Ref D4
#define LED1_IO				(LATAbits.LATA1)
#define LED2_TRIS			(TRISAbits.TRISA2)	// Ref D5
#define LED2_IO				(LATAbits.LATA2)
#define LED3_TRIS			(TRISAbits.TRISA3)	// Ref D6
#define LED3_IO				(LATAbits.LATA3)
#define LED4_TRIS			(TRISAbits.TRISA4)	// Ref D7
#define LED4_IO				(LATAbits.LATA4)
#define LED5_TRIS			(TRISAbits.TRISA5)	// Ref D8
#define LED5_IO				(LATAbits.LATA5)
#define LED6_TRIS			(TRISAbits.TRISA6)	// Ref D9
#define LED6_IO				(LATAbits.LATA6)
#define LED7_TRIS			(TRISAbits.TRISA7)	// Ref D10	// Note: This is multiplexed with BUTTON1
#define LED7_IO				(LATAbits.LATA7)
#define LED_GET()			(*((volatile unsigned char*)(&LATA)))
#define LED_PUT(a)			(*((volatile unsigned char*)(&LATA)) = (a))


#define BUTTON0_TRIS		(TRISDbits.TRISD13)	// Ref S4
#define	BUTTON0_IO			(PORTDbits.RD13)
#define BUTTON1_TRIS		(TRISAbits.TRISA7)	// Ref S5	// Note: This is multiplexed with LED7
#define	BUTTON1_IO			(PORTAbits.RA7)
#define BUTTON2_TRIS		(TRISDbits.TRISD7)	// Ref S6
#define	BUTTON2_IO			(PORTDbits.RD7)
#define BUTTON3_TRIS		(TRISDbits.TRISD6)	// Ref S3
#define	BUTTON3_IO			(PORTDbits.RD6)

#define UARTTX_TRIS			(TRISFbits.TRISF5)
#define UARTTX_IO			(PORTFbits.RF5)
#define UARTRX_TRIS			(TRISFbits.TRISF4)
#define UARTRX_IO			(PORTFbits.RF4)

// LCD Module I/O pins.  NOTE: On the Explorer 16, the LCD is wired to the 
// same PMP lines required to communicate with an ENCX24J600 in parallel 
// mode.  Since the LCD does not have a chip select wire, if you are using 
// the ENC424J600/624J600 in parallel mode, the LCD cannot be used.
#if !defined(ENC100_INTERFACE_MODE) || (ENC100_INTERFACE_MODE == 0)	// SPI only
#define LCD_DATA_TRIS		(*((volatile BYTE*)&TRISE))
#define LCD_DATA_IO			(*((volatile BYTE*)&LATE))
#define LCD_RD_WR_TRIS		(TRISDbits.TRISD5)
#define LCD_RD_WR_IO		(LATDbits.LATD5)
#define LCD_RS_TRIS			(TRISBbits.TRISB15)
#define LCD_RS_IO			(LATBbits.LATB15)
#define LCD_E_TRIS			(TRISDbits.TRISD4)
#define LCD_E_IO			(LATDbits.LATD4)
#endif


#elif defined(DSPICDEM11)
// dsPICDEM 1.1 Development Board + Ethernet PICtail airwired. There 
// is no PICtail header on this development board.  The following 
// airwires must be made:
// 1. dsPICDEM GND <-> PICtail GND (PICtail pin 27)
// 2. dsPICDEM Vdd <- PICtail VPIC (PICtail pin 25)
// 3. dsPICDEM RG2 -> PICtail ENC28J60 CS (PICtail pin 22)
// 4. dsPICDEM RF6 -> PICtail SCK (PICtail pin 11)
// 5. dsPICDEM RF7 <- PICtail SDI (PICtail pin 9)
// 6. dsPICDEM RF8 -> PICtail SDO (PICtail pin 7)
// 7. dsPICDEM RG3 -> PICtail 25LC256 CS (PICtail pin 20)

#define LED0_TRIS			(TRISDbits.TRISD3)	// Ref LED4
#define LED0_IO				(PORTDbits.RD3)
#define LED1_TRIS			(TRISDbits.TRISD2)	// Ref LED3
#define LED1_IO				(PORTDbits.RD2)
#define LED2_TRIS			(TRISDbits.TRISD1)	// Ref LED2
#define LED2_IO				(PORTDbits.RD1)
#define LED3_TRIS			(TRISDbits.TRISD0)	// Ref LED1
#define LED3_IO				(PORTDbits.RD0)
#define LED4_TRIS			(TRISDbits.TRISD3)	// No LED, Remapped to Ref LED4
#define LED4_IO				(PORTDbits.RD3)
#define LED5_TRIS			(TRISDbits.TRISD2)	// No LED, Remapped to Ref LED3
#define LED5_IO				(PORTDbits.RD2)
#define LED6_TRIS			(TRISDbits.TRISD1)	// No LED, Remapped to Ref LED2
#define LED6_IO				(PORTDbits.RD1)
#define LED7_TRIS			(TRISDbits.TRISD0)	// No LED, Remapped to Ref LED1
#define LED7_IO				(PORTDbits.RD0)
#define LED_GET()			((LED3_IO<<3) | (LED2_IO<<2) | (LED1_IO<<1) | LED0_IO)
#define LED_PUT(a)			do{BYTE vTemp = (a); LED0_IO = vTemp&0x1; LED1_IO = vTemp&0x2; LED2_IO = vTemp&0x4; LED3_IO = vTemp&0x8;} while(0)

#define BUTTON0_TRIS		(TRISAbits.TRISA15)	// Ref SW4
#define	BUTTON0_IO			(PORTAbits.RA15)
#define BUTTON1_TRIS		(TRISAbits.TRISA14)	// Ref SW3
#define	BUTTON1_IO			(PORTAbits.RA14)
#define BUTTON2_TRIS		(TRISAbits.TRISA13)	// Ref SW2
#define	BUTTON2_IO			(PORTAbits.RA13)
#define BUTTON3_TRIS		(TRISAbits.TRISA12)	// Ref SW1
#define	BUTTON3_IO			(PORTAbits.RA12)

#define UARTTX_TRIS			(TRISFbits.TRISF3)
#define UARTTX_IO			(PORTFbits.RF3)
#define UARTRX_TRIS			(TRISFbits.TRISF2)
#define UARTRX_IO			(PORTFbits.RF2)

// SI3000 codec pins
#define CODEC_RST_TRIS		(TRISFbits.TRISF6)
#define CODEC_RST_IO		(PORTFbits.RF6)

// PIC18F252 LCD Controller
#define LCDCTRL_CS_TRIS		(TRISGbits.TRISG9)
#define LCDCTRL_CS_IO		(PORTGbits.RG9)

#elif defined(PICDEMNET2) && !defined(HI_TECH_C)
// PICDEM.net 2 (PIC18F97J60 + ENC28J60 or ENC624J600)

// I/O pins
#define LED0_TRIS			(TRISJbits.TRISJ0)
#define LED0_IO				(LATJbits.LATJ0)
#define LED1_TRIS			(TRISJbits.TRISJ1)
#define LED1_IO				(LATJbits.LATJ1)
#define LED2_TRIS			(TRISJbits.TRISJ2)
#define LED2_IO				(LATJbits.LATJ2)
#define LED3_TRIS			(TRISJbits.TRISJ3)
#define LED3_IO				(LATJbits.LATJ3)
#define LED4_TRIS			(TRISJbits.TRISJ4)
#define LED4_IO				(LATJbits.LATJ4)
#define LED5_TRIS			(TRISJbits.TRISJ5)
#define LED5_IO				(LATJbits.LATJ5)
#define LED6_TRIS			(TRISJbits.TRISJ6)
#define LED6_IO				(LATJbits.LATJ6)
#define LED7_TRIS			(TRISJbits.TRISJ7)
#define LED7_IO				(LATJbits.LATJ7)
#define LED_GET()			(LATJ)
#define LED_PUT(a)			(LATJ = (a))

#define BUTTON0_TRIS		(TRISBbits.TRISB3)
#define	BUTTON0_IO			(PORTBbits.RB3)
#define BUTTON1_TRIS		(TRISBbits.TRISB2)
#define	BUTTON1_IO			(PORTBbits.RB2)
#define BUTTON2_TRIS		(TRISBbits.TRISB1)
#define	BUTTON2_IO			(PORTBbits.RB1)
#define BUTTON3_TRIS		(TRISBbits.TRISB0)
#define	BUTTON3_IO			(PORTBbits.RB0)

// LCD I/O pins
#define LCD_DATA_TRIS		(TRISE)
#define LCD_DATA_IO			(LATE)
#define LCD_RD_WR_TRIS		(TRISHbits.TRISH1)
#define LCD_RD_WR_IO		(LATHbits.LATH1)
#define LCD_RS_TRIS			(TRISHbits.TRISH2)
#define LCD_RS_IO			(LATHbits.LATH2)
#define LCD_E_TRIS			(TRISHbits.TRISH0)
#define LCD_E_IO			(LATHbits.LATH0)

#elif defined(PICDEMNET2) && defined(HI_TECH_C)
// PICDEM.net 2 (PIC18F97J60 + ENC28J60) + HI-TECH PICC-18 compiler
// Optionally may use Fast 100Mbps Ethernet PICtail Plus (ENC624J600)
// I/O pins
#define LED0_TRIS			(TRISJ0)
#define LED0_IO				(LATJ0)
#define LED1_TRIS			(TRISJ1)
#define LED1_IO				(LATJ1)
#define LED2_TRIS			(TRISJ2)
#define LED2_IO				(LATJ2)
#define LED3_TRIS			(TRISJ3)
#define LED3_IO				(LATJ3)
#define LED4_TRIS			(TRISJ4)
#define LED4_IO				(LATJ4)
#define LED5_TRIS			(TRISJ5)
#define LED5_IO				(LATJ5)
#define LED6_TRIS			(TRISJ6)
#define LED6_IO				(LATJ6)
#define LED7_TRIS			(TRISJ7)
#define LED7_IO				(LATJ7)
#define LED_GET()			(LATJ)
#define LED_PUT(a)			(LATJ = (a))

#define BUTTON0_TRIS		(TRISB3)
#define	BUTTON0_IO			(RB3)
#define BUTTON1_TRIS		(TRISB2)
#define	BUTTON1_IO			(RB2)
#define BUTTON2_TRIS		(TRISB1)
#define	BUTTON2_IO			(RB1)
#define BUTTON3_TRIS		(TRISB0)
#define	BUTTON3_IO			(RB0)

// LCD I/O pins
#define LCD_DATA_TRIS		(TRISE)
#define LCD_DATA_IO			(LATE)
#define LCD_RD_WR_TRIS		(TRISH1)
#define LCD_RD_WR_IO		(LATH1)
#define LCD_RS_TRIS			(TRISH2)
#define LCD_RS_IO			(LATH2)
#define LCD_E_TRIS			(TRISH0)
#define LCD_E_IO			(LATH0)

// Register name fixup for certain processors
#define SPBRGH				SPBRGH1
#define TXSTAbits			TXSTA1bits
#define RCSTAbits			RCSTA1bits
#define BAUDCONbits			BAUDCON1bits
#define GO					GODONE

#elif defined(INTERNET_RADIO) // Internet Radio board
// Internet Radio board (05-60142)
// I/O pins
#define LED0_TRIS			(TRISCbits.TRISC2)
#define LED0_IO				(LATCbits.LATC2)
#define LED1_TRIS			(PRODL)				// No LED1 on this board
#define LED1_IO				(PRODL)
#define LED2_TRIS			(PRODL)				// No LED2 on this board
#define LED2_IO				(PRODL)
#define LED3_TRIS			(PRODL)				// No LED3 on this board
#define LED3_IO				(PRODL)
#define LED4_TRIS			(PRODL)				// No LED4 on this board
#define LED4_IO				(PRODL)
#define LED5_TRIS			(PRODL)				// No LED5 on this board
#define LED5_IO				(PRODL)
#define LED6_TRIS			(PRODL)				// No LED6 on this board
#define LED6_IO				(PRODL)
#define LED7_TRIS			(PRODL)				// No LED7 on this board
#define LED7_IO				(PRODL)
#define LED_GET()			(LED0_IO)
#define LED_PUT(a)			(LED0_IO = (a))

#define BUTTON0_TRIS		(TRISBbits.TRISB5)
#define	BUTTON0_IO			(PORTBbits.RB5)
#define BUTTON1_TRIS		(TRISFbits.TRISF1)
#define	BUTTON1_IO			(PORTFbits.RF1)
#define BUTTON2_TRIS		(TRISBbits.TRISB4)
#define	BUTTON2_IO			(PORTBbits.RB4)
#define BUTTON3_TRIS		(PRODL)				// No BUTTON3 on this board
#define	BUTTON3_IO			(PRODL)

// Serial SRAM
#define SPIRAM_CS_TRIS			(TRISEbits.TRISE4)
#define SPIRAM_CS_IO			(LATEbits.LATE4)
#define SPIRAM_SCK_TRIS			(TRISCbits.TRISC3)
#define SPIRAM_SDI_TRIS			(TRISCbits.TRISC4)
#define SPIRAM_SDO_TRIS			(TRISCbits.TRISC5)
#define SPIRAM_SPI_IF			(PIR1bits.SSPIF)
#define SPIRAM_SSPBUF			(SSP1BUF)
#define SPIRAM_SPICON1			(SSP1CON1)
#define SPIRAM_SPICON1bits		(SSP1CON1bits)
#define SPIRAM_SPICON2			(SSP1CON2)
#define SPIRAM_SPISTAT			(SSP1STAT)
#define SPIRAM_SPISTATbits		(SSP1STATbits)
#define SPIRAM2_CS_TRIS			(TRISEbits.TRISE5)
#define SPIRAM2_CS_IO			(LATEbits.LATE5)
#define SPIRAM2_SCK_TRIS		(TRISCbits.TRISC3)
#define SPIRAM2_SDI_TRIS		(TRISCbits.TRISC4)
#define SPIRAM2_SDO_TRIS		(TRISCbits.TRISC5)
#define SPIRAM2_SPI_IF			(PIR1bits.SSPIF)
#define SPIRAM2_SSPBUF			(SSP1BUF)
#define SPIRAM2_SPICON1			(SSP1CON1)
#define SPIRAM2_SPICON1bits		(SSP1CON1bits)
#define SPIRAM2_SPICON2			(SSP1CON2)
#define SPIRAM2_SPISTAT			(SSP1STAT)
#define SPIRAM2_SPISTATbits		(SSP1STATbits)

// VLSI VS1011/VS1053 audio encoder/decoder and DAC
#define MP3_DREQ_TRIS			(TRISBbits.TRISB0)	// Data Request
#define MP3_DREQ_IO 			(PORTBbits.RB0)
#define MP3_XRESET_TRIS			(TRISDbits.TRISD0)	// Reset, active low
#define MP3_XRESET_IO			(LATDbits.LATD0)
#define MP3_XDCS_TRIS			(TRISBbits.TRISB1)	// Data Chip Select
#define MP3_XDCS_IO				(LATBbits.LATB1)
#define MP3_XCS_TRIS			(TRISBbits.TRISB2)	// Control Chip Select
#define MP3_XCS_IO				(LATBbits.LATB2)
#define MP3_SCK_TRIS			(TRISCbits.TRISC3)
#define MP3_SDI_TRIS			(TRISCbits.TRISC4)
#define MP3_SDO_TRIS			(TRISCbits.TRISC5)
#define MP3_SPI_IF				(PIR1bits.SSP1IF)
#define MP3_SSPBUF				(SSP1BUF)
#define MP3_SPICON1				(SSP1CON1)
#define MP3_SPICON1bits			(SSP1CON1bits)
#define MP3_SPICON2				(SSP1CON2)
#define MP3_SPISTAT				(SSP1STAT)
#define MP3_SPISTATbits			(SSP1STATbits)

// OLED Display
#define oledWR                  (PORTAbits.RA3)
#define oledWR_TRIS             (TRISAbits.TRISA3)
#define oledRD                  (PORTAbits.RA4)
#define oledRD_TRIS             (TRISAbits.TRISA4)
#define oledCS                  (PORTAbits.RA5)
#define oledCS_TRIS             (TRISAbits.TRISA5)
#define oledRESET               (PORTDbits.RD1)
#define oledRESET_TRIS          (TRISDbits.TRISD1)
#define oledD_C                 (PORTGbits.RG4)
#define oledD_C_TRIS            (TRISGbits.TRISG4)


#elif defined(PIC32_GP_SK_DM320001) || defined(PIC32_USB_DM320003_1) || defined(PIC32_USB_SK_DM320003_2)
// PIC32 (General Purpose) Starter Kit (02-02002) with PIC32MX360F512L processor, 
// PIC32 USB Starter Board (02-02030) with PIC32MX460F512L processor, or
// PIC32 USB Starter Kit II (02-02148) with PIC32MX795F512L processor +
// PIC32 I/O Expansion Board (05-02029) +
// Ethernet PICtail Plus, Fast 100Mbps Ethernet PICtail Plus, or 
// MRF24WB0M 802.11 WiFi PICtail Plus

// Specify which SPI to use for the ENC28J60 or ENC624J600.  SPI1 is 
// the topmost slot with pin 1 on it.  SPI2 is the middle slot 
// starting on pin 33.
#define ENC_IN_SPI1
//#define ENC_IN_SPI2

// Note that SPI1 cannot be used when using the PIC32 USB Starter 
// Board or PIC32 USB Starter Kit II due to the USB peripheral pins 
// mapping on top of the ordinary SPI1 pinout.  
#if defined(ENC_IN_SPI1) && (defined(__32MX460F512L__) || defined(__32MX795F512L__))
#undef ENC_IN_SPI1
#define ENC_IN_SPI2
#endif


// Hardware mappings
#define LED0_TRIS			(TRISDbits.TRISD0)	// Ref LED1
#define LED0_IO				(LATDbits.LATD0)
#define LED1_TRIS			(TRISDbits.TRISD1)	// Ref LED2
#define LED1_IO				(LATDbits.LATD1)
#define LED2_TRIS			(TRISDbits.TRISD2)	// Ref LED3
#define LED2_IO				(LATDbits.LATD2)
#define LED3_TRIS			(LED2_TRIS)			// No such LED
#define LED3_IO				(LATDbits.LATD6)
#define LED4_TRIS			(LED2_TRIS)			// No such LED
#define LED4_IO				(LATDbits.LATD6)
#define LED5_TRIS			(LED2_TRIS)			// No such LED
#define LED5_IO				(LATDbits.LATD6)
#define LED6_TRIS			(LED2_TRIS)			// No such LED
#define LED6_IO				(LATDbits.LATD6)
#define LED7_TRIS			(LED2_TRIS)			// No such LED
#define LED7_IO				(LATDbits.LATD6)

#define LED_GET()			((BYTE)LATD & 0x07)
#define LED_PUT(a)			do{LATD = (LATD & 0xFFF8) | ((a)&0x07);}while(0)

#define BUTTON0_TRIS		(TRISDbits.TRISD6)	// Ref SW1
#define	BUTTON0_IO			(PORTDbits.RD6)
#define BUTTON1_TRIS		(TRISDbits.TRISD7)	// Ref SW2
#define	BUTTON1_IO			(PORTDbits.RD7)
#define BUTTON2_TRIS		(TRISDbits.TRISD13)	// Ref SW3
#define	BUTTON2_IO			(PORTDbits.RD13)
#define BUTTON3_TRIS		(TRISDbits.TRISD13)	// No BUTTON3 on this board
#define	BUTTON3_IO			(1)

// UART configuration (not too important since we don't have a UART 
// connector attached normally, but needed to compile if the STACK_USE_UART 
// or STACK_USE_UART2TCP_BRIDGE features are enabled.
#define UARTTX_TRIS			(TRISFbits.TRISF3)
#define UARTRX_TRIS			(TRISFbits.TRISF2)

#elif defined(PIC32_ENET_SK_DM320004)
// PIC32 Ethernet Starter Kit (04-02146) with PIC32MX795F512L processor and National DP83848 10/100 PHY
// External SMSC PHY configuration
#define	PHY_RMII				// external PHY runs in RMII mode
#define	PHY_CONFIG_ALTERNATE	// alternate configuration used
#define	PHY_ADDRESS			0x1	// the address of the National DP83848 PHY

// Hardware mapping

#define SPIFLASH_CS_TRIS		(TRISGbits.TRISG9)
#define SPIFLASH_CS_IO			(LATGbits.LATG9)
#define SPIFLASH_SCK_TRIS		(TRISGbits.TRISG6)
#define SPIFLASH_SDI_TRIS		(TRISGbits.TRISG7)
#define SPIFLASH_SDI_IO			(PORTGbits.RG7)
#define SPIFLASH_SDO_TRIS		(TRISGbits.TRISG8)
#define SPIFLASH_SPI_IF			(IFS0bits.SPI2IF)
#define SPIFLASH_SSPBUF			(SPI2BUF)
#define SPIFLASH_SPICON1		(SPI2CON)
#define SPIFLASH_SPICON1bits	(SPI1CONbits)
#define SPIFLASH_SPICON2		(SPI2CON)
#define SPIFLASH_SPICON2bits		(SPI2CONbits)
#define SPIFLASH_SPISTAT		(SPI2STAT)
#define SPIFLASH_SPISTATbits	(SPI2STATbits)


// Note, it is not possible to use a MRF24WB0M 802.11 WiFi PICtail 
// Plus card with this starter kit.  The required interrupt signal, among 
// possibly other I/O pins aren't available on the Starter Kit board.  

#elif defined(PIC24FJ256DA210_DEV_BOARD)
// PIC24FJ256DA210 Development Board (Graphics) + 
//   Fast 100Mbps Ethernet PICtail Plus or Ethernet PICtail Plus or MRF24WB0M WiFi PICtail Plus

#define LED0_TRIS			(TRISAbits.TRISA7)		// Ref D4: Jumper JP11 must have a shunt shorting pins 1 and 2 together
#define LED0_IO				(LATAbits.LATA7)
#define LED1_TRIS			(((BYTE*)&NVMKEY)[1])	// No such LED, map to dummy register.  D3 is the natural choice for LED0, but the D3 pin (RB5) is multiplexed with R3 potentiometer and MDIX signal on Fast 100Mbps Ethernet PICtail Plus, so it cannot be used
#define LED1_IO				(((BYTE*)&NVMKEY)[1])
#define LED2_TRIS			(TRISEbits.TRISE9)		// Ref D2.  NOTE: When using the PSP interface, this RE9 signal also controls the POR (SHDN) signal on the Fast 100Mbps Ethernet PICtail Plus.
#define LED2_IO				(LATEbits.LATE9)
#define LED3_TRIS			(TRISGbits.TRISG8)		// Ref D1.  NOTE: When using the PSP interface, this RG8 signal also controls the CS signal on the Fast 100Mbps Ethernet PICtail Plus.
#define LED3_IO				(LATGbits.LATG8)
#define LED4_TRIS			(((BYTE*)&NVMKEY)[1])	// No such LED, map to dummy register
#define LED4_IO				(((BYTE*)&NVMKEY)[1])
#define LED5_TRIS			(((BYTE*)&NVMKEY)[1])	// No such LED, map to dummy register
#define LED5_IO				(((BYTE*)&NVMKEY)[1])
#define LED6_TRIS			(((BYTE*)&NVMKEY)[1])	// No such LED, map to dummy register
#define LED6_IO				(((BYTE*)&NVMKEY)[1])
#define LED7_TRIS			(((BYTE*)&NVMKEY)[1])	// No such LED, map to dummy register
#define LED7_IO				(((BYTE*)&NVMKEY)[1])
#define LED_GET()			((LATGbits.LATG8<<3) | (LATEbits.LATE9<<2) | LATAbits.LATA7)
#define LED_PUT(a)			do{BYTE vTemp = (a); LED0_IO = vTemp&0x1; LED2_IO = vTemp&0x4; LED3_IO = vTemp&0x8;} while(0)


#define BUTTON0_TRIS		(((BYTE*)&NVMKEY)[1])	// Ref S3: NOTE: This pin is multiplexed with D3 and cannot be used simulatneously.  Therefore, we will pretend there is no such button.
#define	BUTTON0_IO			(1)
#define BUTTON1_TRIS		(((BYTE*)&NVMKEY)[1])	// Ref S2: NOTE: This pin is multiplexed with D2 and cannot be used simulatneously.  Therefore, we will pretend there is no such button.
#define	BUTTON1_IO			(1)
#define BUTTON2_TRIS		(((BYTE*)&NVMKEY)[1])	// Ref S1: NOTE: This pin is multiplexed with D1 and cannot be used simulatneously.  Therefore, we will pretend there is no such button.
#define	BUTTON2_IO			(1)
#define BUTTON3_TRIS		(((BYTE*)&NVMKEY)[1])	// No such button
#define	BUTTON3_IO			(1)


#define UARTTX_TRIS			(TRISFbits.TRISF3)
#define UARTTX_IO			(PORTFbits.RF3)
#define UARTRX_TRIS			(TRISDbits.TRISD0)
#define UARTRX_IO			(PORTDbits.RD0)


// NOTE: You must also set SPIFlash.h file to define SPI_FLASH_SST, define 
//       SPI_FLASH_SECTOR_SIZE as 4096, and define SPI_FLASH_PAGE_SIZE as 0.  
//       Jumper JP23 must have a shunt shorting pins 2-3 (not the default).
// SST SST25VF016B (16Mbit/2Mbyte)
#define SPIFLASH_CS_TRIS		(TRISAbits.TRISA14)
#define SPIFLASH_CS_IO			(LATAbits.LATA14)
#define SPIFLASH_SCK_TRIS		(TRISDbits.TRISD8)
#define SPIFLASH_SDI_TRIS		(TRISBbits.TRISB0)
#define SPIFLASH_SDI_IO			(PORTBbits.RB0)
#define SPIFLASH_SDO_TRIS		(TRISBbits.TRISB1)
#define SPIFLASH_SPI_IF			(IFS0bits.SPI1IF)
#define SPIFLASH_SSPBUF			(SPI1BUF)
#define SPIFLASH_SPICON1		(SPI1CON1)
#define SPIFLASH_SPICON1bits	(SPI1CON1bits)
#define SPIFLASH_SPICON2		(SPI1CON2)
#define SPIFLASH_SPISTAT		(SPI1STAT)
#define SPIFLASH_SPISTATbits	(SPI1STATbits)


#elif defined(YOUR_BOARD)


#else
#error "Hardware profile not defined.  See available profiles in HardwareProfile.h and modify or create one."
#endif


#if defined(__18CXX)	// PIC18
// UART mapping functions for consistent API names across 8-bit and 16 or 
// 32 bit compilers.  For simplicity, everything will use "UART" instead 
// of USART/EUSART/etc.
#define BusyUART()				BusyUSART()
#define CloseUART()				CloseUSART()
#define ConfigIntUART(a)		ConfigIntUSART(a)
#define DataRdyUART()			DataRdyUSART()
#define OpenUART(a,b,c)			OpenUSART(a,b,c)
#define ReadUART()				ReadUSART()
#define WriteUART(a)			WriteUSART(a)
#define getsUART(a,b,c)			getsUSART(b,a)
#define putsUART(a)				putsUSART(a)
#define getcUART()				ReadUSART()
#define putcUART(a)				WriteUSART(a)
#define putrsUART(a)			putrsUSART((far rom char*)a)

#else	 // PIC24F, PIC24H, dsPIC30, dsPIC33, PIC32
// Some A/D converter registers on dsPIC30s are named slightly differently 
// on other procesors, so we need to rename them.
#if defined(__dsPIC30F__)
#define ADC1BUF0			ADCBUF0
#define AD1CHS				ADCHS
#define	AD1CON1				ADCON1
#define AD1CON2				ADCON2
#define AD1CON3				ADCON3
#define AD1PCFGbits			ADPCFGbits
#define AD1CSSL				ADCSSL
#define AD1IF				ADIF
#define AD1IE				ADIE
#define _ADC1Interrupt		_ADCInterrupt
#endif

// Select which UART the STACK_USE_UART and STACK_USE_UART2TCP_BRIDGE 
// options will use.  You can change these to U1BRG, U1MODE, etc. if you 
// want to use the UART1 module instead of UART2.
#define UBRG					U2BRG
#define UMODE					U2MODE
#define USTA					U2STA
#define BusyUART()				BusyUART2()
#define CloseUART()				CloseUART2()
#define ConfigIntUART(a)		ConfigIntUART2(a)
#define DataRdyUART()			DataRdyUART2()
#define OpenUART(a,b,c)			OpenUART2(a,b,c)
#define ReadUART()				ReadUART2()
#define WriteUART(a)			WriteUART2(a)
#define getsUART(a,b,c)			getsUART2(a,b,c)
#if defined(__C32__)
#define putsUART(a)			putsUART2(a)
#else
#define putsUART(a)			putsUART2((unsigned int*)a)
#endif
#define getcUART()				getcUART2()
#define putcUART(a)				do{while(BusyUART()); WriteUART(a); while(BusyUART()); }while(0)
#define putrsUART(a)			putrsUART2(a)
#endif


#endif
