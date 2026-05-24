/*
Apellido, nombre: Pezzoni, Roman
DNI: 44513959
Usuario: ronannam
Entrega: Sí

Apellido, nombre: Guzman, Sergio
DNI: 34536390
Usuario: Crysis2741989
Entrega:

Apellido, nombre: Merele, Dylan
DNI: 44793697
Usuario:DyMe16
Entrega:

Apellido, nombre: Brizzolara, Cesar
DNI: 34728140
Usuario:cesarBrizzolara
Entrega:
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "tetrominios.h"
#include "juego.h"
#include "texto.h"
#define ANCHO_CGA 320
#define ALTO_CGA 200
#define ANCHO_VGA 640
#define ALTO_VGA 480
#include "GBT/gbt.h"

int main(int argc, char* argv[])
{

    CargarConfiguracion();

    int ancho, alto, escala = 2;

    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "vga") == 0) {
            configActual.resolucion = 1;
        }
        else if(strcmp(argv[i], "cga") == 0) {
            configActual.resolucion = 0;
        }
        else if(strcmp(argv[i], "escala") == 0 && (i + 1) < argc) {
            escala = atoi(argv[i + 1]);
            i++;
        }
    }


    if(configActual.resolucion == 0) {
        ancho = ANCHO_CGA;
        alto = ALTO_CGA;
    } else {
        ancho = ANCHO_VGA;
        alto = ALTO_VGA;
    }


    if(gbt_iniciar() != 0) {
        printf("Error: Falla al inicializar GBT.\n");
        printf("Diagnostico: %s\n", gbt_obtener_log());
        system("pause");
        return -1;
    }


    if(gbt_crear_ventana("TETRIS", ancho, alto, escala) < 0) {
        printf("Error: No se pudo inicializar el contexto grafico.\n");
        printf("Diagnostico: %s\n", gbt_obtener_log());
        gbt_cerrar();
        system("pause");
        return -1;
    }

    if(configActual.paleta == 0) {
        gbt_aplicar_paleta(paletaCGA, CANT_COLORES, GBT_FORMATO_888);
    } else{
        gbt_aplicar_paleta(paletaAlternativa, CANT_COLORES, GBT_FORMATO_888);
    }



    bool JuegoEmpezado = true;
    Estados estado = PRESENTACION;

    char nombre_jugador[16];
    memset(nombre_jugador, 0, sizeof(nombre_jugador));
    uint8_t indice_nombre = 0;

    // Ciclo de la aplicación
    while(JuegoEmpezado) {

        gbt_procesar_entrada();
        gbt_borrar_backbuffer(NEGRO);

        switch(estado) {
         case PRESENTACION:
                EscribirTexto(100, 50, "TETRIS", CIAN, FUENTE_8X16);
                EscribirTexto(60, 100, "ENTER: JUGAR", AMARILLO, FUENTE_8X8);
                EscribirTexto(60, 120, "O: OPCIONES", MARRON, FUENTE_8X8);
                EscribirTexto(60, 140, "E: ESTADISTICAS", AZUL, FUENTE_8X8); // Línea agregada

                if(gbt_tecla_presionada(GBTK_ENTER)) {
                    estado = INGRESO_NOMBRE;
                }
                else if(gbt_tecla_presionada(GBTK_o)) {
                    estado = MENU_OPCIONES;
                }
                else if(gbt_tecla_presionada(GBTK_e)) {
                    estado = ESTADISTICAS;
                }
                break;

            case MENU_OPCIONES:
                EscribirTexto(80, 20, "OPCIONES", AMARILLO, FUENTE_8X16);

                char buf_res[30];
                sprintf(buf_res, "1. RES: %s", configActual.resolucion == 0 ? "CGA" : "VGA");
                EscribirTexto(40, 60, buf_res, AZUL, FUENTE_8X8);

                char buf_pal[30];
                sprintf(buf_pal, "2. COLOR: %s", configActual.paleta == 0 ? "CLASICO" : "NEON");
                EscribirTexto(40, 90, buf_pal, AMARILLO, FUENTE_8X8);

                char buf_vel[30];
                sprintf(buf_vel, "3. VELOCIDAD: %d MS", configActual.velocidadInicial);
                EscribirTexto(40, 120, buf_vel, CIAN, FUENTE_8X8);

                EscribirTexto(20, 160, "ENTER: GUARDAR Y SALIR", ROJO, FUENTE_8X8);

                if(gbt_tecla_presionada(GBTK_1)) {
                    configActual.resolucion = (configActual.resolucion == 0) ? 1 : 0;
                }
                else if(gbt_tecla_presionada(GBTK_2)) {
                    configActual.paleta = (configActual.paleta == 0) ? 1 : 0;

                    if(configActual.paleta == 0) {
                        gbt_aplicar_paleta(paletaCGA, CANT_COLORES, GBT_FORMATO_888);
                    } else{
                        gbt_aplicar_paleta(paletaAlternativa, CANT_COLORES, GBT_FORMATO_888);
                    }
                }
                else if(gbt_tecla_presionada(GBTK_3)) {
                    if(configActual.velocidadInicial == 1000) {
                        configActual.velocidadInicial = 800;
                    } else if(configActual.velocidadInicial == 800) {
                        configActual.velocidadInicial = 500;
                    } else{
                        configActual.velocidadInicial = 1000;
                    }
                }
                else if(gbt_tecla_presionada(GBTK_ENTER)) {
                    GuardarConfiguracion();
                    estado = PRESENTACION;
                }
                break;

            case JUEGO:
                MoverPiezas();
                if(PiezaCayendo() == true) {
                    GuardarEstadistica(nombre_jugador, puntajeActual);
                    estado = GAME_OVER;
                }
                DibujarJuego();

                if(gbt_tecla_presionada(GBTK_p)){
                    PausarTemporizadores();
                    estado = PAUSA;
                }
                break;

            case GAME_OVER:
                EscribirTexto(100, 80, "GAME OVER", ROJO, FUENTE_8X16);
                EscribirTexto(30, 120, "ENTER PARA REINTENTAR", MARRON, FUENTE_8X8);

                if(gbt_tecla_presionada(GBTK_ENTER)) {
                    InicializarTablero();
                    InicializarJuego();
                    GenerarPieza();
                    estado = JUEGO;
                }
                break;

            case PAUSA:
                DibujarJuego();
                EscribirTexto(100, 80, "PAUSA", ROJO, FUENTE_8X16);
                EscribirTexto(60, 120, "PRESIONE P PARA DESPAUSAR", MARRON, FUENTE_8X8);

                if(gbt_tecla_presionada(GBTK_p)){
                    ReanudarTemporizadores();
                    estado = JUEGO;
                }
                break;

            case INGRESO_NOMBRE:
                EscribirTexto(40, 50, "INGRESE SU NOMBRE:", CIAN, FUENTE_8X8);
                EscribirTexto(40, 80, nombre_jugador, MARRON, FUENTE_8X16);

                eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

                if(tecla != GBTK_DESCONOCIDA) {
                    if (tecla == GBTK_ENTER && indice_nombre > 0) {
                            InicializarTablero();
                        InicializarJuego();
                        GenerarPieza();
                        estado = JUEGO;
                    }
                    else if(tecla == GBTK_RETROCESO && indice_nombre > 0) {
                        indice_nombre--;
                        nombre_jugador[indice_nombre] = '\0';
                    }
                    else if(indice_nombre < 4) {
                        char caracter = (char)tecla;
                        if(caracter >= 'a' && caracter <= 'z') {
                            caracter -= 32;
                        }
                        if((caracter >= 'A' && caracter <= 'Z') || (caracter >= '0' && caracter <= '9')) {
                            nombre_jugador[indice_nombre] = caracter;
                            indice_nombre++;
                            nombre_jugador[indice_nombre] = '\0';
                        }
                    }
                }
                break;
               case ESTADISTICAS:
                EscribirTexto(80, 20, "ESTADISTICAS", CIAN, FUENTE_8X16);
                EscribirTexto(20, 160, "ENTER: VOLVER", ROJO, FUENTE_8X8);

                FILE* archStats = fopen("estadisticas.txt", "r");
                if(archStats != NULL) {
                    char lineas[8][64];
                    uint8_t totalLineas = 0;
                    char bufferTemp[64];

                    while(fgets(bufferTemp, sizeof(bufferTemp), archStats) != NULL) {
                        bufferTemp[strcspn(bufferTemp, "\n")] = 0;

                        if(totalLineas < 8) {
                            strcpy(lineas[totalLineas], bufferTemp);
                            totalLineas++;
                        } else{
                            for (int i = 0; i < 7; i++) {
                                strcpy(lineas[i], lineas[i+1]);
                            }
                            strcpy(lineas[7], bufferTemp);
                        }
                    }
                    fclose(archStats);

                    uint16_t posY = 50;
                    for(int i = 0; i < totalLineas; i++) {
                        EscribirTexto(20, posY, lineas[i], AMARILLO, FUENTE_8X8);
                        posY += 12;
                    }
                } else{
                    EscribirTexto(20, 50, "NO EXISTEN REGISTROS", MARRON, FUENTE_8X8);
                }

                if(gbt_tecla_presionada(GBTK_ENTER)) {
                    estado = PRESENTACION;
                }
                break;
            default:
                break;
        }

        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }

    gbt_destruir_ventana();
    gbt_cerrar();

    return 0;
}
