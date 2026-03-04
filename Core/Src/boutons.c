#include "boutons.h"
#include "main.h"

// Définition des pins des boutons (mêmes valeurs qu'avant dans main.c)
#define BUTTON_G_PIN    GPIO_PIN_3  // Bouton Gauche (Left_Button) - PC3
#define BUTTON_G_PORT   GPIOC
#define BUTTON_D_PIN    GPIO_PIN_1  // Bouton Droite (Right_Button) - PA1
#define BUTTON_D_PORT   GPIOA
#define BUTTON_M_PIN    GPIO_PIN_0  // Bouton Centre (Center_Button) - PA0
#define BUTTON_M_PORT   GPIOA

static uint8_t prev_gauche = 0, prev_droite = 0, prev_centre = 0;

// Retourne: 0 = aucun bouton, 1 = gauche, 2 = droite, 3 = centre
uint8_t gerer_bouton(void)
{
    uint8_t etat = 0;

    uint8_t g = (HAL_GPIO_ReadPin(BUTTON_G_PORT, BUTTON_G_PIN) == GPIO_PIN_RESET);
    uint8_t d = (HAL_GPIO_ReadPin(BUTTON_D_PORT, BUTTON_D_PIN) == GPIO_PIN_RESET);
    uint8_t m = (HAL_GPIO_ReadPin(BUTTON_M_PORT, BUTTON_M_PIN) == GPIO_PIN_RESET);

    if (g && !prev_gauche) etat = 1;
    else if (d && !prev_droite) etat = 2;
    else if (m && !prev_centre) etat = 3;

    prev_gauche  = g;
    prev_droite  = d;
    prev_centre  = m;

    return etat;
}

