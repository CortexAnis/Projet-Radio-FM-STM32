#include "eeprom.h"
#include "main.h"

// Les presets sont définis dans main.c
extern uint16_t presets[3];

void EEPROM_WriteUint16(uint16_t addr, uint16_t value)
{
    HAL_I2C_Mem_Write(&hi2c1,
                      EEPROM_I2C_ADDR,
                      addr,
                      I2C_MEMADD_SIZE_16BIT,
                      (uint8_t*)&value,
                      2,
                      100);
    HAL_Delay(5);
}

uint16_t EEPROM_ReadUint16(uint16_t addr)
{
    uint16_t value = 0;

    HAL_I2C_Mem_Read(&hi2c1,
                     EEPROM_I2C_ADDR,
                     addr,
                     I2C_MEMADD_SIZE_16BIT,
                     (uint8_t*)&value,
                     2,
                     100);

    return value;
}

void charger_presets_eeprom(void)
{
    for (uint8_t i = 0; i < 3; i++)
    {
        uint16_t val = EEPROM_ReadUint16(EEPROM_PRESET_BASE_ADDR + (uint16_t)(i * 2));
        presets[i] = val;
    }
}

