/*********************************************************************
 *
 *               External serial data EEPROM Access Defs. for MAC address
 *
 *********************************************************************
 * FileName:        SPIMACEEPROM.h
 * Dependencies:    None
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Compiler:        Microchip C32 v1.05 or higher
 *					Microchip C30 v3.12 or higher
 *					Microchip C18 v3.30 or higher
 *					HI-TECH PICC-18 PRO 9.63PL2 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (C) 2002-2009 Microchip Technology Inc.  All rights
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
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Nilesh Rajbharti     5/20/02     Original (Rev. 1.0)
********************************************************************/
#ifndef __SPIMACEEPROM_H
#define __SPIMACEEPROM_H

#include "GenericTypeDefs.h"
#include "EEPROM.h"
typedef BOOL SPIMACEE_RESULT;
#define SPIMACEE_SUCCESS FALSE

#if defined(MAC_EEPROM_CS_TRIS)	
	void SPIMACEEInit(void);
	SPIMACEE_RESULT SPIMACEEBeginWrite(BYTE address);
	SPIMACEE_RESULT SPIMACEEWrite(BYTE val);
	void SPIMACEEWriteArray(BYTE *val, WORD wLen);
	SPIMACEE_RESULT SPIMACEEEndWrite(void);
	SPIMACEE_RESULT SPIMACEEBeginRead(BYTE address);
	BYTE SPIMACEERead(void);
	SPIMACEE_RESULT SPIMACEEReadArray(BYTE address, BYTE *buffer, WORD length);
	SPIMACEE_RESULT SPIMACEEEndRead(void);
	BOOL SPIMACEEIsBusy(void);
#else
	// If you get any of these linker errors, it means that you either have an 
	// error in your HardwareProfile.h  The code 
	// is attempting to call a function that can't possibly work because you 
	// have not specified what pins and SPI module the physical SPI EEPROM chip 
	// is connected to.
  	void 		You_cannot_call_the_SPIMACEEInit_function_without_defining_MAC_EEPROM_CS_TRIS_in_HardwareProfile_h_first(void);
	XEE_RESULT	You_cannot_call_the_SPIMACEEBeginWrite_function_without_defining_MAC_EEPROM_CS_TRIS_in_HardwareProfile_h_first(void);
	XEE_RESULT	You_cannot_call_the_SPIMACEEWrite_function_without_defining_MAC_EEPROM_CS_TRIS_in_HardwareProfile_h_first(void);
	void 		You_cannot_call_the_SPIMACEEWriteArray_function_without_defining_MAC_EEPROM_CS_TRIS_in_HardwareProfile_h_first(void);
	XEE_RESULT	You_cannot_call_the_SPIMACEEEndWrite_function_without_defining_MAC_EEPROM_CS_TRIS_in_HardwareProfile_h_first(void);
	XEE_RESULT	You_cannot_call_the_SPIMACEEBeginRead_function_without_defining_MAC_EEPROM_CS_TRIS_in_HardwareProfile_h_first(void);
	BYTE 		You_cannot_call_the_SPIMACEERead_function_without_defining_MAC_EEPROM_CS_TRIS_in_HardwareProfile_h_first(void);
	XEE_RESULT	You_cannot_call_the_SPIMACEEReadArray_function_without_defining_MAC_EEPROM_CS_TRIS_in_HardwareProfile_h_first(void);
	XEE_RESULT	You_cannot_call_the_SPIMACEEEndRead_function_without_defining_MAC_EEPROM_CS_TRIS_in_HardwareProfile_h_first(void);
	BOOL 		You_cannot_call_the_SPIMACEEIsBusy_function_without_defining_MAC_EEPROM_CS_TRIS_in_HardwareProfile_h_first(void);
	#define SPIMACEEInit()				You_cannot_call_the_XEEInit_function_without_defining_MAC_EEPROM_CS_TRIS_in_HardwareProfile_h_first()
	#define SPIMACEEBeginWrite(a) 		You_cannot_call_the_XEEBeginWrite_function_without_defining_MAC_EEPROM_CS_TRIS_in_HardwareProfile_h_first()
	#define SPIMACEEWrite(a)			You_cannot_call_the_XEEWrite_function_without_defining_MAC_EEPROM_CS_TRIS_in_HardwareProfile_h_first()
	#define SPIMACEEWriteArray(a,b)		You_cannot_call_the_XEEWriteArray_function_without_defining_MAC_EEPROM_CS_TRIS_in_HardwareProfile_h_first()
	#define SPIMACEEEndWrite()			You_cannot_call_the_XEEEndWrite_function_without_defining_MAC_EEPROM_CS_TRIS_in_HardwareProfile_h_first()
	#define SPIMACEEBeginRead(a)		You_cannot_call_the_XEEBeginRead_function_without_defining_MAC_EEPROM_CS_TRIS_in_HardwareProfile_h_first()
	#define SPIMACEERead(a)				You_cannot_call_the_XEERead_function_without_defining_MAC_EEPROM_CS_TRIS_in_HardwareProfile_h_first()
	#define SPIMACEEReadArray(a, b, c)	You_cannot_call_the_XEEReadArray_function_without_defining_MAC_EEPROM_CS_TRIS_in_HardwareProfile_h_first()
	#define SPIMACEEEndRead()			You_cannot_call_the_XEEEndRead_function_without_defining_MAC_EEPROM_CS_TRIS_in_HardwareProfile_h_first()
	#define SPIMACEEIsBusy()			You_cannot_call_the_SPIMACEEIsBusy_function_without_defining_MAC_EEPROM_CS_TRIS_in_HardwareProfile_h_first()
#endif

#endif
