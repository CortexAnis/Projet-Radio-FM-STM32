#ifndef EEPROM_H
#define EEPROM_H

#include <stdint.h>

#define EEPROM_I2C_ADDR          0xA0
#define EEPROM_PRESET_BASE_ADDR  0x0000

void EEPROM_WriteUint16(uint16_t addr, uint16_t value);
uint16_t EEPROM_ReadUint16(uint16_t addr);
void charger_presets_eeprom(void);

#endif

