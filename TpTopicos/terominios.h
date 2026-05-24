#ifndef TETROMINIOS_H_INCLUDED
#define TETROMINIOS_H_INCLUDED
#define CANT_COLORES 16
#define VACIO 15
#define ROJO 12
#define CIAN 3
#define VERDE 10
#define AZUL 1
#define MAGENTA 13
#define NEGRO 0
#define AMARILLO 14
#define MARRON 6
#define TAMANO_FILAS 10
#define TAMANO_COLUMNAS 24
#include "GBT/gbt.h"



extern tGBT_ColorRGB paletaCGA[CANT_COLORES];
extern tGBT_ColorRGB paletaAlternativa[CANT_COLORES];
extern const uint8_t FIGURAS[7][4][4][4];
#endif // TETROMIIOS_H_INCLUDED
