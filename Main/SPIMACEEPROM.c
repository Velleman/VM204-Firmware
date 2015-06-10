/*********************************************************************
 *
 *               Data SPI EEPROM Access Routines for MAC address
 *
 *********************************************************************
 * FileName:        SPIMACEEPROM.c
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
 * Howard Schlunder     9/01/04     Rewritten for SPI EEPROMs
 * Howard Schlunder     8/10/06     Modified to control SPI module
 *                                  frequency whenever EEPROM accessed
 *                                  to allow bus sharing with different
 *                                  frequencies.
********************************************************************/
#define __SPIMACEEPROM_C


#include "SPIMACEEPROM.h"
#include <spi.h>
#include "EEPROM.h"
// If the CS line is not defined, SPIMACEEPROM.c's content will not be compiled.  
// If you are using a serial EEPROM please define the CS pin as MAC_EEPROM_CS_TRIS 
// in HardwareProfile.h
#if defined(MAC_EEPROM_CS_TRIS)

//#include "TCPIP Stack/TCPIP.h"

// IMPORTANT SPI NOTE: The code in this file expects that the SPI interrupt
//      flag (MAC_EEPROM_SPI_IF) be clear at all times.  If the SPI is shared with
//      other hardware, the other code should clear the EEPROM_SPI_IF when it is
//      done using the SPI.

// SPI Serial EEPROM buffer size.  To enhance performance while
// cooperatively sharing the SPI bus with other peripherals, bytes
// read and written to the memory are locally buffered. Legal
// sizes are 1 to the EEPROM page size.
#define MAC_EEPROM_BUFFER_SIZE		(16)

// Must be the EEPROM write page size, or any binary power of 2 divisor.  If 
// using a smaller number, make sure it is at least EEPROM_BUFFER_SIZE big for 
// max performance.  Microchip 25AA02E48 uses 16 byte page size 
#define MAC_EEPROM_PAGE_SIZE		(16)

// EEPROM SPI opcodes
#define OPCODE_READ    0x03    // Read data from memory array beginning at selected address
#define OPCODE_WRITE   0x02    // Write data to memory array beginning at selected address
#define OPCODE_WRDI    0x04    // Reset the write enable latch (disable write operations)
#define OPCODE_WREN    0x06    // Set the write enable latch (enable write operations)
#define OPCODE_RDSR    0x05    // Read Status register
#define OPCODE_WRSR    0x01    // Write Status register

#define MAC_EEPROM_MAX_SPI_FREQ		(5000000ul)    // Hz

#if defined (__18CXX)
    #define ClearSPIDoneFlag()  {MAC_EEPROM_SPI_IF = 0;}
    #define WaitForDataByte()   {while(!MAC_EEPROM_SPI_IF); MAC_EEPROM_SPI_IF = 0;}
    #define SPI_ON_BIT          (MAC_EEPROM_SPICON1bits.SSPEN)
#elif defined(__C30__)
    #define ClearSPIDoneFlag()
    static inline __attribute__((__always_inline__)) void WaitForDataByte( void )
    {
        while ((MAC_EEPROM_SPISTATbits.SPITBF == 1) || (MAC_EEPROM_SPISTATbits.SPIRBF == 0));
    }

    #define SPI_ON_BIT          (MAC_EEPROM_SPISTATbits.SPIEN)
#elif defined( __PIC32MX__ )
    #define ClearSPIDoneFlag()
    static inline __attribute__((__always_inline__)) void WaitForDataByte( void )
    {
        while (!MAC_EEPROM_SPISTATbits.SPITBE || !MAC_EEPROM_SPISTATbits.SPIRBF);
    }

    #define SPI_ON_BIT          (MAC_EEPROM_SPICON1bits.ON)
#else
    #error Determine SPI flag mechanism
#endif

static void DoWrite(void);

static BYTE MACEEPROMAddress;
static BYTE MACEEPROMBuffer[MAC_EEPROM_BUFFER_SIZE];
static BYTE vBytesInBuffer;

/*********************************************************************
 * Function:        void MACEEInit(unsigned char speed)
 *
 * PreCondition:    None
 *
 * Input:           speed - not used (included for compatibility only)
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Initialize SPI module to communicate to serial
 *                  EEPROM.
 *
 * Note:            Code sets SPI clock to Fosc/16.
 ********************************************************************/
#if (defined(HPC_EXPLORER) || defined(PIC18_EXPLORER)) && !defined(__18F87J10) && !defined(__18F87J11) && !defined(__18F87J50)
    #define PROPER_SPICON1  (0x20)      /* SSPEN bit is set, SPI in master mode, FOSC/4, IDLE state is low level */
#elif defined(__PIC24F__) || defined(__PIC24FK__)
    #define PROPER_SPICON1  (0x0013 | 0x0120)   /* 1:1 primary prescale, 4:1 secondary prescale, CKE=1, MASTER mode */
#elif defined(__dsPIC30F__)
    #define PROPER_SPICON1  (0x0017 | 0x0120)   /* 1:1 primary prescale, 3:1 secondary prescale, CKE=1, MASTER mode */
#elif defined(__dsPIC33F__) || defined(__PIC24H__)
    #define PROPER_SPICON1  (0x0003 | 0x0120)   /* 1:1 primary prescale, 8:1 secondary prescale, CKE=1, MASTER mode */
#elif defined(__PIC32MX__)
    //#define PROPER_SPICON1  (_SPI1CON_ON_MASK  | _SPI1CON_CKE_MASK | _SPI1CON_MSTEN_MASK)
    #define PROPER_SPICON2  (_SPI2CON_ON_MASK | _SPI2CON_CKE_MASK | _SPI2CON_MSTEN_MASK)
#else
    #define PROPER_SPICON1  (0x21)      /* SSPEN bit is set, SPI in master mode, FOSC/16, IDLE state is low level */
#endif

void SPIMACEEInit(void)
{
    
    MAC_EEPROM_CS_TRIS = 0;     // Drive SPI MAC EEPROM chip select pin
    MAC_EEPROM_CS_IO = 0;

    MAC_EEPROM_SCK_TRIS = 0;    // Set SCK pin as an output
    LATGbits.LATG6 = 0;
    MAC_EEPROM_SDI_TRIS = 1;    // Make sure SDI pin is an input
    MAC_EEPROM_SDO_TRIS = 0;    // Set SDO pin as an output

    ClearSPIDoneFlag();
    #if defined(__C30__)
        MAC_EEPROM_SPICON1 = PROPER_SPICON1; // See PROPER_SPICON1 definition above
        MAC_EEPROM_SPICON2 = 0;
        MAC_EEPROM_SPISTAT = 0;    // clear SPI
        MAC_EEPROM_SPISTATbits.SPIEN = 1;
    #elif defined(__C32__)
        MAC_EEPROM_SPIBRG = (40000000-1ul)/2ul/MAC_EEPROM_MAX_SPI_FREQ;
        MAC_EEPROM_SPICON2 = PROPER_SPICON2;
    #elif defined(__18CXX)
        MAC_EEPROM_SPICON1 = PROPER_SPICON1; // See PROPER_SPICON1 definition above
        MAC_EEPROM_SPISTATbits.CKE = 1;     // Transmit data on rising edge of clock
        MAC_EEPROM_SPISTATbits.SMP = 0;     // Input sampled at middle of data output time
    #endif
}

void SPIMACEEDeInit(void)
{
    ClearSPIDoneFlag();
   // MAC_EEPROM_SPICON1 |=
    //MAC_EEPROM_CS_IO = 1;
    
}


/*********************************************************************
 * Function:        SPIMACEE_RESULT MACEEBeginRead(BYTE address)
 *
 * PreCondition:    None
 *
 * Input:           address - Address at which read is to be performed.
 *
 * Output:          SPIMACEE_SUCCESS
 *
 * Side Effects:    None
 *
 * Overview:        Sets internal address counter to given address.
 *
 * Note:            None
 ********************************************************************/
SPIMACEE_RESULT	SPIMACEEBeginRead(BYTE address)
{
    // Save the address and empty the contents of our local buffer
    MACEEPROMAddress = address;
    vBytesInBuffer = 0;
    return SPIMACEE_SUCCESS;
}


/*********************************************************************
 * Function:        BYTE SPIMACEERead(void)
 *
 * PreCondition:    SPIMACEEInit() && PSIMACEEBeginRead() are already called.
 *
 * Input:           None
 *
 * Output:          BYTE that was read
 *
 * Side Effects:    None
 *
 * Overview:        Reads next byte from EEPROM; internal address
 *                  is incremented by one.
 *
 * Note:            None
 ********************************************************************/
BYTE SPIMACEERead(void)
{
    // Check if no more bytes are left in our local buffer
    if(vBytesInBuffer == 0u)
    {
        // Get a new set of bytes
        SPIMACEEReadArray(MACEEPROMAddress, MACEEPROMBuffer, MAC_EEPROM_BUFFER_SIZE);
        MACEEPROMAddress += MAC_EEPROM_BUFFER_SIZE;
        vBytesInBuffer = MAC_EEPROM_BUFFER_SIZE;
    }

    // Return a byte from our local buffer
    return MACEEPROMBuffer[MAC_EEPROM_BUFFER_SIZE - vBytesInBuffer--];
}

/*********************************************************************
 * Function:        SPIMACEE_RESULT SPIMACEEEndRead(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          SPIMACEE_SUCCESS
 *
 * Side Effects:    None
 *
 * Overview:        This function does nothing.
 *
 * Note:            Function is used for backwards compatability with
 *                  I2C EEPROM module.
 ********************************************************************/
SPIMACEE_RESULT SPIMACEEEndRead(void)
{
    return SPIMACEE_SUCCESS;
}


/*********************************************************************
 * Function:        SPIMACEE_RESULT SPIMACEEReadArray(BYTE address,
 *                                          BYTE *buffer,
 *                                          WORD length)
 *
 * PreCondition:    SPIMACEEInit() is already called.
 *
 * Input:           address     - Address from where array is to be read
 *                  buffer      - Caller supplied buffer to hold the data
 *                  length      - Number of bytes to read.
 *
 * Output:          SPIMACEE_SUCCESS
 *
 * Side Effects:    None
 *
 * Overview:        Reads desired number of bytes in sequential mode.
 *                  This function performs all necessary steps
 *                  and releases the bus when finished.
 *
 * Note:            None
 ********************************************************************/
SPIMACEE_RESULT SPIMACEEReadArray(BYTE address,
                        		  BYTE *buffer,
                        		  WORD length)
{
    volatile BYTE Dummy;
    BYTE vSPIONSave;
    #if defined(__18CXX)
    BYTE SPICON1Save;
    #elif defined(__C30__)
    WORD SPICON1Save;
    #else
    DWORD SPICON1Save;
    #endif

    // Save SPI state (clock speed)
    SPICON1Save = MAC_EEPROM_SPICON1;
    vSPIONSave = SPI_ON_BIT;

    // Configure SPI
    SPI_ON_BIT = 0;
    MAC_EEPROM_SPICON1 = PROPER_SPICON2;
    SPI_ON_BIT = 1;

    MAC_EEPROM_CS_IO = 0;

    // Send READ opcode
    MAC_EEPROM_SSPBUF = OPCODE_READ;
    WaitForDataByte();
    Dummy = MAC_EEPROM_SSPBUF;

    // Send address
    MAC_EEPROM_SSPBUF = address;
    WaitForDataByte();
    Dummy = MAC_EEPROM_SSPBUF;

    while(length--)
    {
        MAC_EEPROM_SSPBUF = 0;
        WaitForDataByte();
        Dummy = MAC_EEPROM_SSPBUF;
        if(buffer != NULL)
            *buffer++ = Dummy;
    };

    MAC_EEPROM_CS_IO = 1;

    // Restore SPI state
    SPI_ON_BIT = 0;
    MAC_EEPROM_SPICON1 = SPICON1Save;
    SPI_ON_BIT = vSPIONSave;


    return SPIMACEE_SUCCESS;
}


/*********************************************************************
 * Function:        SPIMACEE_RESULT SPIMACEEBeginWrite(BYTE address)
 *
 * PreCondition:    None
 *
 * Input:           address     - address to be set for writing
 *
 * Output:          SPIMACEE_SUCCESS
 *
 * Side Effects:    None
 *
 * Overview:        Modifies internal address counter of MAC EEPROM.
 *
 * Note:            Unlike SPIMACEESetAddr() in xeeprom.c for I2C EEPROM
 *                  memories, this function is used only for writing
 *                  to the EEPROM.  Reads must use SPIMACEEBeginRead(),
 *                  SPIMACEERead(), and SPIMACEEEndRead().
 *                  This function does not use the SPI bus.
 ********************************************************************/
SPIMACEE_RESULT SPIMACEEBeginWrite(BYTE address)
{
	vBytesInBuffer = 0;
    MACEEPROMAddress = address;
    return SPIMACEE_SUCCESS;
}


/*********************************************************************
 * Function:        SPIMACEE_RESULT SPIMACEEWrite(BYTE val)
 *
 * PreCondition:    SPIMACEEInit() && SPIMACEEBeginWrite() are already called.
 *
 * Input:           val - Byte to be written
 *
 * Output:          SPIMACEE_SUCCESS
 *
 * Side Effects:    None
 *
 * Overview:        Writes a byte to the write cache, and if full, 
 *					commits the write.  Also, if a write boundary is 
 *					reached the write is committed.  When finished 
 *					writing, SPIMACEEEndWrite() must be called to commit 
 *					any unwritten bytes from the write cache.
 *
 * Note:            None
 ********************************************************************/
SPIMACEE_RESULT SPIMACEEWrite(BYTE val)
{
	MACEEPROMBuffer[vBytesInBuffer++] = val;
	if(vBytesInBuffer >= sizeof(MACEEPROMBuffer))
		DoWrite();
	else if(((MACEEPROMAddress + vBytesInBuffer) & (MAC_EEPROM_PAGE_SIZE-1)) == 0u)
		DoWrite();

    return SPIMACEE_SUCCESS;
}


/*****************************************************************************
  Function:		SPIMACEE_RESULT SPIMACEEWriteArray(BYTE *val, WORD wLen)

  Summary:		Writes an array of bytes to the EEPROM part.

  Description:	This function writes an array of bytes to the EEPROM at the address 
  				specified when SPIMACEEBeginWrite() was called.  Page boundary crossing is 
 				handled internally.
    
  Precondition:	SPIMACEEInit() was called once and SPIMACEEBeginWrite() was called.

  Parameters:	vData - The array to write to the next memory location
  				wLen - The length of the data to be written

  Returns:		None

  Remarks:		The internal write cache is flushed at completion, so it is unnecessary 
  				to call SPIMACEEEndWrite() after calling this function.  However, if you do 
				so, no harm will be done.
  ***************************************************************************/
void SPIMACEEWriteArray(BYTE *val, WORD wLen)
{
	while(wLen--)
		SPIMACEEWrite(*val++);
	
	SPIMACEEEndWrite();
}


/*********************************************************************
 * Function:        SPIMACEE_RESULT SPIMACEEEndWrite(void)
 *
 * PreCondition:    SPIMACEEInit() && SPIMACEEBeginWrite() are already called.
 *
 * Input:           None
 *
 * Output:          SPIMACEE_SUCCESS
 *
 * Side Effects:    None
 *
 * Overview:        Commits any last uncommitted bytes in cache to 
 *					physical storage.
 *
 * Note:            Call this function when you no longer need to 
 *					write any more bytes at the selected address.
 ********************************************************************/
SPIMACEE_RESULT SPIMACEEEndWrite(void)
{
	if(vBytesInBuffer)
		DoWrite();

    return SPIMACEE_SUCCESS;
}

static void DoWrite(void)
{
    BYTE i;
    volatile BYTE vDummy;
    BYTE vSPIONSave;
    #if defined(__18CXX)
    BYTE SPICON1Save;
    #elif defined(__C30__)
    WORD SPICON1Save;
    #else
    DWORD SPICON1Save;
    #endif

    // Save SPI state
    SPICON1Save = MAC_EEPROM_SPICON1;
    vSPIONSave = SPI_ON_BIT;

    // Configure SPI
    SPI_ON_BIT = 0;
    MAC_EEPROM_SPICON1 = PROPER_SPICON2;
    SPI_ON_BIT = 1;

    // Set the Write Enable latch
    MAC_EEPROM_CS_IO = 0;
    MAC_EEPROM_SSPBUF = OPCODE_WREN;
    WaitForDataByte();
    vDummy = MAC_EEPROM_SSPBUF;
    MAC_EEPROM_CS_IO = 1;

    // Send WRITE opcode
    MAC_EEPROM_CS_IO = 0;
    MAC_EEPROM_SSPBUF = OPCODE_WRITE;
    WaitForDataByte();
    vDummy = MAC_EEPROM_SSPBUF;

    // Send address
    MAC_EEPROM_SSPBUF = MACEEPROMAddress;
    WaitForDataByte();
    vDummy = MAC_EEPROM_SSPBUF;

    for(i = 0; i < vBytesInBuffer; i++)
    {
        // Send the byte to write
        MAC_EEPROM_SSPBUF = MACEEPROMBuffer[i];
        WaitForDataByte();
        vDummy = MAC_EEPROM_SSPBUF;
    }

    // Begin the write
    MAC_EEPROM_CS_IO = 1;

	// Update write address and clear write cache
    MACEEPROMAddress += vBytesInBuffer;
    vBytesInBuffer = 0;

    // Restore SPI State
    SPI_ON_BIT = 0;
    MAC_EEPROM_SPICON1 = SPICON1Save;
    SPI_ON_BIT = vSPIONSave;


    // Wait for write to complete
    while( SPIMACEEIsBusy() );
}


/*********************************************************************
 * Function:        BOOL SPIMACEEIsBusy(void)
 *
 * PreCondition:    SPIMACEEInit() is already called.
 *
 * Input:           None
 *
 * Output:          FALSE if MAC EEPROM is not busy
 *                  TRUE if MAC EEPROM is busy
 *
 * Side Effects:    None
 *
 * Overview:        Reads the status register
 *
 * Note:            None
 ********************************************************************/
BOOL SPIMACEEIsBusy(void)
{
    volatile BYTE_VAL result;
    BYTE vSPIONSave;
    #if defined(__18CXX)
    BYTE SPICON1Save;
    #elif defined(__C30__)
    WORD SPICON1Save;
    #else
    DWORD SPICON1Save;
    #endif

    // Save SPI state
    SPICON1Save = MAC_EEPROM_SPICON1;
    vSPIONSave = SPI_ON_BIT;

    // Configure SPI
    SPI_ON_BIT = 0;
    MAC_EEPROM_SPICON1 = PROPER_SPICON2;
    SPI_ON_BIT = 1;

    MAC_EEPROM_CS_IO = 0;
    // Send RDSR - Read Status Register opcode
    MAC_EEPROM_SSPBUF = OPCODE_RDSR;
    WaitForDataByte();
    result.Val = MAC_EEPROM_SSPBUF;

    // Get register contents
    MAC_EEPROM_SSPBUF = 0;
    WaitForDataByte();
    result.Val = MAC_EEPROM_SSPBUF;
    MAC_EEPROM_CS_IO = 1;

    // Restore SPI State
    SPI_ON_BIT = 0;
    MAC_EEPROM_SPICON1 = SPICON1Save;
    SPI_ON_BIT = vSPIONSave;

    return result.bits.b0;
}


#endif //#if defined(MAC_EEPROM_CS_TRIS)
