#include "tetrominios.h"
#include "juego.h"


PiezaEnJuego pieza;
uint8_t Tablero[24][10] = { VACIO };
tGBT_Temporizador* timer = NULL;

void InicializarTablero(){

    for( int i = 0; i < 24; i++){
        for( int j = 0; j < 10; j++){
            Tablero[i][j] = VACIO;
        }
    }
}

void GenerarPieza(){
    uint8_t min = 0, maxp = 6, maxr = 3;

    pieza.corX = 3;
    pieza.corY = 0;
    pieza.tipo_pieza = min + rand() % (maxp - min + 1);
    pieza.rotacion = min + rand() % (maxr - min + 1);
}

bool HayColision(){
        for( int y = 0; y < 4; y++){
            for( int x = 0; x < 4; x++){
                int posTableroX = pieza.corX + x;
                int posTableroY = pieza.corY + y;
                if(FIGURAS[pieza.tipo_pieza][pieza.rotacion][y][x] != VACIO ){
                    if (posTableroX < 0 || posTableroX >= 10 || posTableroY >= 24 || Tablero[posTableroY][posTableroX] != VACIO) {
                        return true;
                    }

                }
            }
        }
    return false;
}

void PiezaCayendo(){
    if(timer == NULL){
        printf("ERROR: Timer vacio\n");
        getchar();
        exit(1);
    }
    if(gbt_temporizador_consumir(timer)){
          pieza.corY++;
          if(HayColision()){
            pieza.corY--;
            FijarPieza();
          }
    }

}

void FijarPieza(){
     for( int y = 0; y < 4; y++){
            for( int x = 0; x < 4; x++){
                int posTableroX = pieza.corX + x;
                int posTableroY = pieza.corY + y;
                if(FIGURAS[pieza.tipo_pieza][pieza.rotacion][y][x] != VACIO ){
                    Tablero[posTableroY][posTableroX] = FIGURAS[pieza.tipo_pieza][pieza.rotacion][y][x];
                }
        }
    }
}

void LimpiarLineas(){

    for(int8_t y = 23; y >= 0; y--){
        uint8_t cont = 0;
        for(int8_t x = 0; x < 10; x++){
            if(Tablero[y][x] != VACIO){
                cont++;
            }
            }//Salimos del for en x y hay que aplicar gravedad
            if(cont == TAMANO_FILAS){
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
}
