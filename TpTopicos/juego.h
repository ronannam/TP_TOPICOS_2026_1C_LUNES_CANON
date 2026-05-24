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

    bool apoyada;

}PiezaEnJuego;
typedef enum {
    PRESENTACION,
    INGRESO_NOMBRE,
    JUEGO,
    PAUSA,
    GAME_OVER,
    MENU_OPCIONES,
    ESTADISTICAS
}Estados;

typedef struct {
    uint8_t resolucion;
    uint8_t paleta;
    uint16_t velocidadInicial;
} Configuracion;


extern Configuracion configActual;
extern uint32_t puntajeActual;

void CargarConfiguracion();
void GuardarConfiguracion();
void GuardarEstadistica(const char* nombre, uint32_t puntos);

void InicializarJuego();
void InicializarTablero();
void ReanudarTemporizadores();
void PausarTemporizadores();
void GenerarPieza();
bool HayColision();
bool PiezaCayendo();
void FijarPieza();
uint8_t LimpiarLineas();
void MoverPiezas();
void DibujarJuego();
#endif // JUEGO_H_INCLUDED
