#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <conio.h>


typedef struct{

    int32_t corX;

    int32_t corY;

    uint8_t tipo_pieza;

    uint8_t rotacion;

}PiezaEnJuego;

void InicializarTablero();
void GenerarPieza();
bool HayColision();
void PiezaCayendo();
void FijarPieza();
void LimpiarLineas();
#endif // JUEGO_H_INCLUDED
