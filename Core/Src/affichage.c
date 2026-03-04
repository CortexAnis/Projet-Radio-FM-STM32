#include "affichage.h"
#include "main.h"
#include "radio.h"
#include "presets.h"

// Variables d'état définies dans d'autres modules
extern uint8_t menu_actif;
extern uint8_t menu_selection;
extern uint8_t page_actuelle;
extern uint8_t bass_boost_actif;
extern const char* version_firmware;
extern uint16_t presets[3];
extern uint8_t preset_selection;

void battery(uint8_t percent)
{
    if (percent > 100) percent = 100;

    ssd1306_DrawRectangle(2, 2, 20, 10, White);

    if ((percent * 16) / 100 > 0)
    {
        ssd1306_FillRectangle(3, 3, 3 + (percent * 16) / 100, 9, White);
    }
}

void signal(uint8_t reseau)
{
    uint8_t bars = reseau / 20;
    if (bars > 5) bars = 5;

    ssd1306_FillRectangle(98, 0, 127, 16, Black);

    for (uint8_t i = 0; i < bars; i++)
    {
        ssd1306_FillRectangle(100 + i * 5, 15 - (i * 3), 102 + i * 5, 15, White);
    }
}

void mettre_a_jour_frequence(void)
{
    char buffer[10];

    sprintf(buffer, "%d.%d", RDA_GetRealFrequency(&hi2c1) / 100,
                            (RDA_GetRealFrequency(&hi2c1) / 10) % 10);

    ssd1306_FillRectangle(32, 19, 90, 45, Black);
    ssd1306_SetCursor(22, 22);
    ssd1306_WriteString(buffer, Font_16x26, White);
    ssd1306_SetCursor(105, 31);
    ssd1306_WriteString("Mhz", Font_7x10, White);

    ssd1306_UpdateScreen();
}

void ligne(void)
{
    ssd1306_Line(0, 18, 127, 18, White);
    ssd1306_Line(0, 51, 127, 51, White);
}

void afficher_menu(void)
{
    ssd1306_Fill(Black);

    ssd1306_SetCursor(40, 2);
    ssd1306_WriteString("MENU", Font_16x15, White);

    if (menu_selection == 0) {
        ssd1306_FillRectangle(2, 15, 39, 30, White);
        ssd1306_SetCursor(4, 19);
        ssd1306_WriteString("Radio", Font_7x10, Black);
    } else {
        ssd1306_DrawRectangle(2, 15, 39, 30, White);
        ssd1306_SetCursor(4, 19);
        ssd1306_WriteString("Radio", Font_7x10, White);
    }

    if (menu_selection == 1) {
        ssd1306_FillRectangle(43, 15, 80, 30, White);
        ssd1306_SetCursor(45, 19);
        ssd1306_WriteString("Rech", Font_7x10, Black);
    } else {
        ssd1306_DrawRectangle(43, 15, 80, 30, White);
        ssd1306_SetCursor(45, 19);
        ssd1306_WriteString("Rech", Font_7x10, White);
    }

    if (menu_selection == 2) {
        ssd1306_FillRectangle(84, 15, 125, 30, White);
        ssd1306_SetCursor(86, 19);
        ssd1306_WriteString("Preset", Font_7x10, Black);
    } else {
        ssd1306_DrawRectangle(84, 15, 121, 30, White);
        ssd1306_SetCursor(86, 19);
        ssd1306_WriteString("Preset", Font_7x10, White);
    }

    if (menu_selection == 3) {
        ssd1306_FillRectangle(2, 33, 39, 48, White);
        ssd1306_SetCursor(4, 37);
        ssd1306_WriteString("Audio", Font_7x10, Black);
    } else {
        ssd1306_DrawRectangle(2, 33, 39, 48, White);
        ssd1306_SetCursor(4, 37);
        ssd1306_WriteString("Audio", Font_7x10, White);
    }

    if (menu_selection == 4) {
        ssd1306_FillRectangle(43, 33, 80, 48, White);
        ssd1306_SetCursor(45, 37);
        ssd1306_WriteString("Param", Font_7x10, Black);
    } else {
        ssd1306_DrawRectangle(43, 33, 80, 48, White);
        ssd1306_SetCursor(45, 37);
        ssd1306_WriteString("Param", Font_7x10, White);
    }

    if (menu_selection == 5) {
        ssd1306_FillRectangle(84, 33, 121, 48, White);
        ssd1306_SetCursor(86, 37);
        ssd1306_WriteString("Info", Font_7x10, Black);
    } else {
        ssd1306_DrawRectangle(84, 33, 121, 48, White);
        ssd1306_SetCursor(86, 37);
        ssd1306_WriteString("Info", Font_7x10, White);
    }

    ssd1306_SetCursor(34, 54);
    ssd1306_WriteString("<  OK  >", Font_7x10, White);
    ssd1306_Line(0, 51, 127, 51, White);
    ssd1306_UpdateScreen();
}

void Affiche_Page(uint8_t i)
{
    switch(i)
    {
        case 0:
            afficher_menu();
            break;
        case 1:
            afficher_page_radio();
            break;
        case 2:
            afficher_page_recherche();
            break;
        case 3:
            afficher_page_presets();
            break;
        case 4:
            afficher_page_audio();
            break;
        case 5:
            afficher_page_parametres();
            break;
        case 6:
            afficher_page_info();
            break;
        default:
            afficher_menu();
            break;
    }
}

void afficher_page_radio(void)
{
    ssd1306_Fill(Black);

    ssd1306_SetCursor(50, 2);
    ssd1306_WriteString("FM", Font_16x15, White);

    mettre_a_jour_frequence();
    battery(75);
    signal(RDA_GetQuality(&hi2c1));

    ssd1306_SetCursor(0, 54);
    ssd1306_WriteString("Freq-  Menu  Freq+", Font_7x10, White);

    ligne();
    ssd1306_UpdateScreen();
}

void afficher_page_recherche(void)
{
    ssd1306_Fill(Black);

    ssd1306_SetCursor(13, 2);
    ssd1306_WriteString("RECHERCHE", Font_16x15, White);

    char buffer[15];
    sprintf(buffer, "%d.%d", RDA_GetRealFrequency(&hi2c1) / 100,
                            (RDA_GetRealFrequency(&hi2c1) / 10) % 10);
    ssd1306_SetCursor(22, 25);
    ssd1306_WriteString(buffer, Font_16x26, White);

    ssd1306_SetCursor(26, 54);
    ssd1306_WriteString("S-   OK   S+", Font_7x10, White);
    ssd1306_SetCursor(105, 31);
    ssd1306_WriteString("Mhz", Font_7x10, White);
    ligne();

    ssd1306_UpdateScreen();
}

void afficher_page_presets(void)
{
    ssd1306_Fill(Black);

    ssd1306_SetCursor(26, 2);
    ssd1306_WriteString("PRESETS", Font_16x15, White);

    char p1[20];
    if (presets[0] == 0) {
        sprintf(p1, "P1: Vide");
    } else {
        sprintf(p1, "P1: %d.%d MHz", presets[0] / 100, (presets[0] / 10) % 10);
    }
    if (preset_selection == 0) {
        ssd1306_FillRectangle(0, 20, 127, 27, White);
        ssd1306_SetCursor(5, 21);
        ssd1306_WriteString(">", Font_7x10, Black);
        ssd1306_SetCursor(15, 21);
        ssd1306_WriteString(p1, Font_7x10, Black);
    } else {
        ssd1306_SetCursor(15, 21);
        ssd1306_WriteString(p1, Font_7x10, White);
    }

    char p2[20];
    if (presets[1] == 0) {
        sprintf(p2, "P2: Vide");
    } else {
        sprintf(p2, "P2: %d.%d MHz", presets[1] / 100, (presets[1] / 10) % 10);
    }
    if (preset_selection == 1) {
        ssd1306_FillRectangle(0, 28, 127, 35, White);
        ssd1306_SetCursor(5, 29);
        ssd1306_WriteString(">", Font_7x10, Black);
        ssd1306_SetCursor(15, 29);
        ssd1306_WriteString(p2, Font_7x10, Black);
    } else {
        ssd1306_SetCursor(15, 29);
        ssd1306_WriteString(p2, Font_7x10, White);
    }

    char p3[20];
    if (presets[2] == 0) {
        sprintf(p3, "P3: Vide");
    } else {
        sprintf(p3, "P3: %d.%d MHz", presets[2] / 100, (presets[2] / 10) % 10);
    }
    if (preset_selection == 2) {
        ssd1306_FillRectangle(0, 36, 127, 43, White);
        ssd1306_SetCursor(5, 37);
        ssd1306_WriteString(">", Font_7x10, Black);
        ssd1306_SetCursor(15, 37);
        ssd1306_WriteString(p3, Font_7x10, Black);
    } else {
        ssd1306_SetCursor(15, 37);
        ssd1306_WriteString(p3, Font_7x10, White);
    }

    ssd1306_SetCursor(35, 54);
    ssd1306_WriteString("<  OK  >", Font_7x10, White);
    ligne();

    ssd1306_UpdateScreen();
}

void afficher_page_audio(void)
{
    ssd1306_Fill(Black);

    ssd1306_SetCursor(40, 2);
    ssd1306_WriteString("AUDIO", Font_16x15, White);

    ssd1306_SetCursor(10, 25);
    ssd1306_WriteString("Bass Boost:", Font_7x10, White);
    if (bass_boost_actif) {
        ssd1306_SetCursor(80, 25);
        ssd1306_WriteString("ON", Font_7x10, White);
    } else {
        ssd1306_SetCursor(80, 25);
        ssd1306_WriteString("OFF", Font_7x10, White);
    }

    ssd1306_SetCursor(10, 35);
    ssd1306_WriteString("Volume:", Font_7x10, White);
    ssd1306_SetCursor(80, 35);
    ssd1306_WriteString("75%", Font_7x10, White);

    ssd1306_SetCursor(35, 54);
    ssd1306_WriteString("<  OK  >", Font_7x10, White);
    ligne();

    ssd1306_UpdateScreen();
}

void afficher_page_parametres(void)
{
    ssd1306_Fill(Black);

    ssd1306_SetCursor(7, 2);
    ssd1306_WriteString("PARAMETRES", Font_16x15, White);

    ssd1306_SetCursor(10, 20);
    ssd1306_WriteString("Bande: 87-108MHz", Font_7x10, White);
    ssd1306_SetCursor(10, 30);
    ssd1306_WriteString("Espace: 100kHz", Font_7x10, White);
    ssd1306_SetCursor(10, 40);
    ssd1306_WriteString("Mode: Stereo", Font_7x10, White);

    ssd1306_SetCursor(35, 54);
    ssd1306_WriteString("<  OK  >", Font_7x10, White);
    ligne();

    ssd1306_UpdateScreen();
}

void afficher_page_info(void)
{
    ssd1306_Fill(Black);

    ssd1306_SetCursor(35, 2);
    ssd1306_WriteString("INFO", Font_16x15, White);

    ssd1306_SetCursor(10, 20);
    ssd1306_WriteString("Version:", Font_7x10, White);
    ssd1306_SetCursor(70, 20);
    ssd1306_WriteString(version_firmware, Font_7x10, White);

    ssd1306_SetCursor(10, 30);
    ssd1306_WriteString("Bass Boost:", Font_7x10, White);
    if (bass_boost_actif) {
        ssd1306_SetCursor(80, 30);
        ssd1306_WriteString("ACTIF", Font_7x10, White);
    } else {
        ssd1306_SetCursor(80, 30);
        ssd1306_WriteString("INACTIF", Font_7x10, White);
    }

    char freq_str[15];
    sprintf(freq_str, "Freq: %d.%d MHz", RDA_GetRealFrequency(&hi2c1) / 100,
                                        (RDA_GetRealFrequency(&hi2c1) / 10) % 10);
    ssd1306_SetCursor(10, 40);
    ssd1306_WriteString(freq_str, Font_7x10, White);

    char qual_str[15];
    sprintf(qual_str, "Signal: %d%%", RDA_GetQuality(&hi2c1));
    ssd1306_SetCursor(10, 50);
    ssd1306_WriteString(qual_str, Font_7x10, White);

    ssd1306_Line(0, 18, 127, 18, White);
    ssd1306_Line(0, 51, 127, 51, White);
    ssd1306_UpdateScreen();
}

