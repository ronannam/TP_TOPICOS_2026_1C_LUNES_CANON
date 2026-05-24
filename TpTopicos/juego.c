#include "tetrominios.h"
#include "juego.h"
#include "texto.h"
#include <time.h>
#include <stdio.h>
#define CAIDA_EN_MS 1000.0

PiezaEnJuego pieza;
uint8_t Tablero[24][10];
tGBT_Temporizador* timerCaida = NULL;
tGBT_Temporizador* timerFijacion = NULL;
double velocidadCaida = CAIDA_EN_MS;
uint32_t puntajeActual = 0;
uint32_t piezasCaidas = 0;
bool GameOver = false;


Configuracion configActual;

void CargarConfiguracion() {
    FILE* archivo = fopen("config.bin", "rb");

    if(archivo == NULL) {
        configActual.resolucion = 0;
        configActual.paleta = 0;
        configActual.velocidadInicial = 1000;
    } else{
        fread(&configActual, sizeof(Configuracion), 1, archivo);
        fclose(archivo);


        if(configActual.velocidadInicial == 0) {
            configActual.velocidadInicial = 1000;
        }
    }
}

void GuardarConfiguracion() {

    FILE* archivo = fopen("config.bin", "wb");

    if(archivo != NULL) {
        fwrite(&configActual, sizeof(Configuracion), 1, archivo);
        fclose(archivo);
    } else{
        printf("ERROR: No se pudo escribir en el disco.\n");
    }
}
void GuardarEstadistica(const char* nombre, uint32_t puntos) {
    FILE* archivo = fopen("estadisticas.txt", "a");
    if(archivo != NULL) {
        fprintf(archivo, "JUGADOR: %s - PUNTOS: %u\n", nombre, puntos);
        fclose(archivo);
    }
}


void InicializarJuego(){
    velocidadCaida = (double)configActual.velocidadInicial;
    piezasCaidas = 0;
    puntajeActual = 0;

    if(timerCaida != NULL) gbt_temporizador_destruir(timerCaida);
    if(timerFijacion != NULL) gbt_temporizador_destruir(timerFijacion);

    timerCaida = gbt_temporizador_crear(velocidadCaida / CAIDA_EN_MS);
    timerFijacion = gbt_temporizador_crear((velocidadCaida * 0.5) / CAIDA_EN_MS);
    srand(time(NULL));
}
void InicializarTablero(){

    for(int i = 0; i < 24; i++){
        for( int j = 0; j < 10; j++){
            Tablero[i][j] = VACIO;
        }
    }
}

void PausarTemporizadores() {
    if(timerCaida != NULL){
        gbt_temporizador_pausar(timerCaida);
    }
    if(timerFijacion != NULL){
        gbt_temporizador_pausar(timerFijacion);
    }
}

void ReanudarTemporizadores() {
    if(timerCaida != NULL){
        gbt_temporizador_reanudar(timerCaida);
    }
    if(timerFijacion != NULL){
        gbt_temporizador_reanudar(timerFijacion);
    }
}

void GenerarPieza(){
    uint8_t min = 0, maxp = 6, maxr = 3;

    pieza.corX = 3;
    pieza.corY = 0;
    pieza.tipo_pieza = min + rand() % (maxp - min + 1);
    pieza.rotacion = min + rand() % (maxr - min + 1);
    pieza.apoyada = false;
}

bool HayColision(){
    for(int y = 0; y < 4; y++){
        for(int x = 0; x < 4; x++){
            int posTableroX = pieza.corX + x;
            int posTableroY = pieza.corY + y;
            if(FIGURAS[pieza.tipo_pieza][pieza.rotacion][y][x] != VACIO ){
                if(posTableroX < 0 || posTableroX >= 10 || posTableroY >= 24 || posTableroY < 0 || Tablero[posTableroY][posTableroX] != VACIO) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool PiezaCayendo(){
    if(timerCaida == NULL){
        printf("ERROR: Timer vacio\n");
        getchar();
        exit(1);
    }

    if(pieza.apoyada == false){
        if(gbt_temporizador_consumir(timerCaida)){
            pieza.corY++;
            if(HayColision()){
                pieza.apoyada = true;
                pieza.corY--;
                gbt_temporizador_pausar(timerCaida);
                gbt_temporizador_destruir(timerFijacion);
                timerFijacion = gbt_temporizador_crear((velocidadCaida * 0.5) / CAIDA_EN_MS);
            }
        }
    }
    else {
       if(gbt_temporizador_consumir(timerFijacion)){
            FijarPieza();

            piezasCaidas++;
            if(piezasCaidas % 10 == 0) {
                velocidadCaida = velocidadCaida * 0.97;

                gbt_temporizador_destruir(timerCaida);
                timerCaida = gbt_temporizador_crear(velocidadCaida / CAIDA_EN_MS);
            }


            uint8_t lineas = LimpiarLineas();
            if(lineas > 0) {
                double velocidad = CAIDA_EN_MS / velocidadCaida;
                uint32_t puntosCombo;

                if(lineas == 1) {
                    puntosCombo = 100;
                }
                else if(lineas == 2) {
                    puntosCombo = 300;
                }
                else if(lineas == 3) {
                    puntosCombo = 500;
                }
                else{

                    puntosCombo = 800;
                }

                puntajeActual += (uint32_t)(puntosCombo * velocidad);
            }
            GenerarPieza();

            if(HayColision()){
                return true; // GAME OVER
            }

            pieza.apoyada = false;
            gbt_temporizador_pausar(timerFijacion);
            gbt_temporizador_reanudar(timerCaida);
        }
    }

    return false;
}
void FijarPieza(){
     for(int y = 0; y < 4; y++){
            for(int x = 0; x < 4; x++){
                int posTableroX = pieza.corX + x;
                int posTableroY = pieza.corY + y;
                if(FIGURAS[pieza.tipo_pieza][pieza.rotacion][y][x] != VACIO ){
                    Tablero[posTableroY][posTableroX] = FIGURAS[pieza.tipo_pieza][pieza.rotacion][y][x];
                }
        }
    }
}


uint8_t LimpiarLineas(){
    uint8_t lineasBorradas = 0;

    for(int8_t y = 23; y >= 0; y--){
        uint8_t cont = 0;
        for(int8_t x = 0; x < 10; x++){
            if(Tablero[y][x] != VACIO){
                cont++;
            }
        }


        if(cont == TAMANO_FILAS){
            lineasBorradas++;

            for(int j = y; j > 0; j--){
                for(uint8_t i = 0; i < 10; i++){
                    Tablero[j][i] = Tablero[j - 1][i];
                }
            }
            for(int h = 0; h < 10; h++){
                Tablero[0][h] = VACIO;
            }
            y++;
        }
    }

    return lineasBorradas;
}

void MoverPiezas() {
    bool movimientoExitoso = false;

    if (gbt_tecla_presionada(GBTK_DERECHA) || gbt_tecla_presionada(GBTK_d)) {
        pieza.corX++;
        if (HayColision()) {
            pieza.corX--;
        } else{
            movimientoExitoso = true;
        }
    }
    else if(gbt_tecla_presionada(GBTK_IZQUIERDA) || gbt_tecla_presionada(GBTK_a)) {
        pieza.corX--;
        if(HayColision()) {
            pieza.corX++;
        } else{
            movimientoExitoso = true;
        }
    }

    else if(gbt_tecla_presionada(GBTK_e)) {
        pieza.rotacion = (pieza.rotacion + 1) % 4;
        if(HayColision()) {
            pieza.rotacion = (pieza.rotacion + 3) % 4;
        } else{
            movimientoExitoso = true;
        }
    }
    else if(gbt_tecla_presionada(GBTK_q)) {
        pieza.rotacion = (pieza.rotacion + 3) % 4;
        if(HayColision()) {
            pieza.rotacion = (pieza.rotacion + 1) % 4;
        } else{
            movimientoExitoso = true;
        }
    }

    else if(gbt_tecla_presionada(GBTK_ABAJO) || gbt_tecla_presionada(GBTK_s)) {
        pieza.corY++;
        if(HayColision()) {
            pieza.corY--;

        } else{
            puntajeActual += 1;

            gbt_temporizador_destruir(timerCaida);
            timerCaida = gbt_temporizador_crear(velocidadCaida / CAIDA_EN_MS);
        }
    }


    if(movimientoExitoso) {
        pieza.corY++;
        if(!HayColision()) {
            pieza.apoyada = false;
            gbt_temporizador_reanudar(timerCaida);
            if (timerFijacion != NULL) gbt_temporizador_pausar(timerFijacion);
        } else{
            if(pieza.apoyada && timerFijacion != NULL) {
                gbt_temporizador_destruir(timerFijacion);
                timerFijacion = gbt_temporizador_crear((velocidadCaida * 0.5) / CAIDA_EN_MS);
            }
        }
        pieza.corY--;
    }
}
void DibujarJuego(){

    for(int y = 4; y < 24; y++){
        for(int x = 0; x < 10; x++){
            if(Tablero[y][x] != VACIO){
                for(uint16_t i = 0; i < 10; i++){
                    for(uint16_t j = 0; j < 10; j++){
                        gbt_dibujar_pixel((x * 10) + i, ((y - 4) * 10) + j, Tablero[y][x]);
                    }
                }
            }
        }
    }

    for(int y = 0; y < 4; y++){
        for(int x = 0; x < 4; x++){
            if(FIGURAS[pieza.tipo_pieza][pieza.rotacion][y][x] != VACIO){
                int posTableroX = pieza.corX + x;
                int posTableroY = pieza.corY + y;

                if(posTableroY >= 4){
                    for(uint16_t i = 0; i < 10; i++){
                        for(uint16_t j = 0; j < 10; j++){
                            gbt_dibujar_pixel((posTableroX * 10) + i, ((posTableroY - 4) * 10) + j, FIGURAS[pieza.tipo_pieza][pieza.rotacion][y][x]);
                        }
                    }
                }
            }
        }
    }

    char buf[30];

    sprintf(buf, "PTS: %u", puntajeActual);
    EscribirTexto(120, 20, buf, AMARILLO, FUENTE_8X8);

    sprintf(buf, "MS: %d", (int)velocidadCaida);
    EscribirTexto(120, 40, buf, CIAN, FUENTE_8X8);

    sprintf(buf, "PIEZAS: %u", piezasCaidas);
    EscribirTexto(120, 60, buf, MARRON, FUENTE_8X8);

}
