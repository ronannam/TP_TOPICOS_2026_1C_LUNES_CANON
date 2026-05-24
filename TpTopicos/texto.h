#ifndef TEXTO_H_INCLUDED
#define TEXTO_H_INCLUDED

#include <stdint.h>
#include "GBT/gbt_graficos.h"

#define FUENTE_8X8 1
#define FUENTE_8X16 2


void EscribirTexto(uint16_t x, uint16_t y, const char* texto, uint8_t colorIndice, uint8_t tamano);

#endif // TEXTO_H_INCLUDED

