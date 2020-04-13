

#ifndef EEPROM_H
#define	EEPROM_H

#include "common.h"

#ifdef	__cplusplus
extern "C" {
#endif

void EEPROM_write(uint8_t uiAddress, unsigned char ucData);
uint8_t EEPROM_read(uint8_t uiAddress);


#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */

