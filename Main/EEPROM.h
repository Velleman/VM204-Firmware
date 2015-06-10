/* 
 * File:   SD.h
 * Author: bn
 *
 * Created on 11 juni 2014, 16:31
 */

#ifndef SD_H
#define	SD_H

#ifdef	__cplusplus
extern "C" {
#endif
// 25AA02E48 I/O pins (for MAC address)
#define MAC_EEPROM_CS_TRIS		(TRISGbits.TRISG2)
#define MAC_EEPROM_CS_IO		(LATGbits.LATG2)
#define MAC_EEPROM_SCK_TRIS		(TRISGbits.TRISG6)
#define MAC_EEPROM_SDI_TRIS		(TRISGbits.TRISG7)
#define MAC_EEPROM_SDO_TRIS		(TRISGbits.TRISG8)
#define MAC_EEPROM_SPI_IF		(PIR1bits.SSP2IF)
#define MAC_EEPROM_SSPBUF		(SPI2BUF)
#define MAC_EEPROM_SPIBRG               (SPI2BRG)
#define MAC_EEPROM_SPICON1		(SPI2CON)
#define MAC_EEPROM_SPICON1bits	(SPI2CONbits)
#define MAC_EEPROM_SPICON2		(SPI2ACON)
#define MAC_EEPROM_SPISTAT		(SP2STAT)
#define MAC_EEPROM_SPISTATbits	(SPI2STATbits)
#define MAC_EEPROM_ADDR_LOC		(0xFA)



#ifdef	__cplusplus
}
#endif

#endif	/* SD_H */

