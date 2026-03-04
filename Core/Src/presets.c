#include "presets.h"
#include "eeprom.h"
#include "RDA_5807.h"
#include "main.h"

uint16_t presets[3] = {0, 0, 0};
uint8_t preset_selection = 0;

void sauvegarder_preset(uint8_t num_preset)
{
    if (num_preset < 3) {
        presets[num_preset] = RDA_GetRealFrequency(&hi2c1);
        EEPROM_WriteUint16(EEPROM_PRESET_BASE_ADDR + (uint16_t)(num_preset * 2),
                           presets[num_preset]);
    }
}

void charger_preset(uint8_t num_preset)
{
    if (num_preset < 3 && presets[num_preset] != 0) {
        RDA_Tune(&hi2c1, presets[num_preset]);
        HAL_Delay(200);
    }
}

