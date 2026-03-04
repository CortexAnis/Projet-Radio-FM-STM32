#include "radio.h"
#include "RDA_5807.h"
#include "main.h"

uint8_t bass_boost_actif = 0;

void appliquer_bass_boost(void)
{
    if (bass_boost_actif) {
        RDA_SetBass(&hi2c1, TRUE);
    } else {
        RDA_SetBass(&hi2c1, FALSE);
    }
}

