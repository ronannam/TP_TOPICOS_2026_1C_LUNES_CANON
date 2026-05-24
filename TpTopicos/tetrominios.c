#include "tetrominios.h"
#include <stdint.h>

//---------Colores----------//
tGBT_ColorRGB paletaCGA[CANT_COLORES] = {

    {0x00, 0x00, 0x00}, // 0:   Negro
    {0x00, 0x00, 0xAA}, // 1:   Azul
    {0x00, 0xAA, 0x00}, // 2:   Verde
    {0x00, 0xAA, 0xAA}, // 3:   Cian
    {0xAA, 0x00, 0x00}, // 4:   Rojo
    {0xAA, 0x00, 0xAA}, // 5:   Magenta
    {0xAA, 0x55, 0x00}, // 6:   Marron
    {0xAA, 0xAA, 0xAA}, // 7:   Gris claro
    {0x55, 0x55, 0x55}, // 8:   Gris oscuro
    {0x55, 0x55, 0xFF}, // 9:   Azul brillante
    {0x55, 0xFF, 0x55}, // 10:  Verde brillante
    {0x55, 0xFF, 0xFF}, // 11:  Cian brillante
    {0xFF, 0x55, 0x55}, // 12:  Rojo brillante
    {0xFF, 0x55, 0xFF}, // 13:  Magenta brillante
    {0xFF, 0xFF, 0x55}, // 14:  Amarillo
    {0xFF, 0xFF, 0xFF}  // 15:  Usado como transparente por GBT
};
//---------Paleta Alternativa (Neón)----------//
tGBT_ColorRGB paletaAlternativa[CANT_COLORES] = {
    {0x00, 0x00, 0x00}, // 0:  Negro
    {0xFF, 0x00, 0x7F}, // 1:  Rosa Neón
    {0x00, 0xFF, 0x7F}, // 2:  Verde Primavera
    {0x00, 0xFF, 0xFF}, // 3:  Cian Neón
    {0xFF, 0x45, 0x00}, // 4:  Naranja Rojizo
    {0x8A, 0x2B, 0xE2}, // 5:  Violeta Azulado
    {0xD2, 0x69, 0x1E}, // 6:  Chocolate
    {0xD3, 0xD3, 0xD3}, // 7:  Gris claro
    {0xA9, 0xA9, 0xA9}, // 8:  Gris oscuro
    {0x1E, 0x90, 0xFF}, // 9:  Azul Dodger
    {0x32, 0xCD, 0x32}, // 10: Verde Lima
    {0x40, 0xE0, 0xD0}, // 11: Turquesa
    {0xDC, 0x14, 0x3C}, // 12: Carmesí
    {0xFF, 0x14, 0x93}, // 13: Rosa Profundo
    {0xFF, 0xD7, 0x00}, // 14: Oro
    {0xFF, 0xFF, 0xFF}  // 15: Transparente
};

//---------Figuras-------------//
const uint8_t FIGURAS[7][4][4][4] = {


//O:

{
    {   //Esta pieza no rota
        {VACIO, VACIO, VACIO, VACIO},
        {VACIO, ROJO, ROJO, VACIO},
        {VACIO, ROJO, ROJO, VACIO},
        {VACIO, VACIO, VACIO, VACIO}
    },

    {   {VACIO, VACIO, VACIO, VACIO},
        {VACIO, ROJO, ROJO, VACIO},
        {VACIO, ROJO, ROJO, VACIO},
        {VACIO, VACIO, VACIO, VACIO}
    },

    {
        {VACIO, VACIO, VACIO, VACIO},
        {VACIO, ROJO, ROJO, VACIO},
        {VACIO, ROJO, ROJO, VACIO},
        {VACIO, VACIO, VACIO, VACIO}
    },

    {
        {VACIO, VACIO, VACIO, VACIO},
        {VACIO, ROJO, ROJO, VACIO},
        {VACIO, ROJO, ROJO, VACIO},
        {VACIO, VACIO, VACIO, VACIO}
    }
},

//I:
{
    {   //Rotacion 0(acostada)
        {VACIO, VACIO, VACIO, VACIO},
        {CIAN, CIAN, CIAN, CIAN},
        {VACIO, VACIO, VACIO, VACIO},
        {VACIO, VACIO, VACIO, VACIO}
    },

    {   //Rotaci�n 1(parada)
        {VACIO, VACIO, CIAN, VACIO},
        {VACIO, VACIO, CIAN, VACIO},
        {VACIO, VACIO, CIAN, VACIO},
        {VACIO, VACIO, CIAN, VACIO}
    },

    {   //Rotaci�n 2(acostada para el otro lado)
        {VACIO, VACIO, VACIO, VACIO},
        {VACIO, VACIO, VACIO, VACIO},
        {CIAN, CIAN, CIAN, CIAN},
        {VACIO, VACIO, VACIO, VACIO}
    },

    {   //Rotaci�n 3(parada para el otro lado)
        {VACIO, CIAN, VACIO, VACIO},
        {VACIO, CIAN, VACIO, VACIO},
        {VACIO, CIAN, VACIO, VACIO},
        {VACIO, CIAN, VACIO, VACIO}
    },
},

//J:
{
    {   //Rotacion 0
        {VACIO,VACIO,VACIO,VACIO},
        {VACIO,VERDE,VACIO,VACIO},
        {VACIO,VERDE,VERDE,VERDE},
        {VACIO,VACIO,VACIO,VACIO}
    },

    {   //Rotaci�n 1
        {VACIO, VACIO, VACIO, VACIO},
        {VACIO, VERDE, VERDE, VACIO},
        {VACIO, VERDE, VACIO, VACIO},
        {VACIO, VERDE, VACIO, VACIO}
    },

    {   //Rotaci�n 2
        {VACIO, VACIO, VACIO, VACIO},
        {VERDE, VERDE, VERDE, VACIO},
        {VACIO, VACIO, VERDE, VACIO},
        {VACIO, VACIO, VACIO, VACIO}
    },

    {   //Rotaci�n 3
        {VACIO, VACIO, VERDE, VACIO},
        {VACIO, VACIO, VERDE, VACIO},
        {VACIO, VERDE, VERDE, VACIO},
        {VACIO, VACIO, VACIO, VACIO}
    }
},

//L:
{
    {   //Rotacion 0
        {VACIO, VACIO, VACIO, VACIO},
        {VACIO, VACIO, AZUL, VACIO},
        {AZUL, AZUL, AZUL, VACIO},
        {VACIO, VACIO, VACIO, VACIO}
    },

    {   //Rotaci�n 1
        {VACIO, AZUL, VACIO, VACIO},
        {VACIO, AZUL, VACIO, VACIO},
        {VACIO, AZUL, AZUL, VACIO},
        {VACIO, VACIO, VACIO, VACIO}
    },

    {   //Rotaci�n 2
        {VACIO, VACIO, VACIO, VACIO},
        {VACIO, AZUL, AZUL, AZUL},
        {VACIO, AZUL, VACIO, VACIO},
        {VACIO, VACIO, VACIO, VACIO}
    },

    {   //Rotaci�n 3
        {VACIO, VACIO, VACIO, VACIO},
        {VACIO, AZUL, AZUL, VACIO},
        {VACIO, VACIO, AZUL, VACIO},
        {VACIO, VACIO, AZUL, VACIO}
    }
},

//S:
{
    {   //Rotacion 0
        {VACIO, VACIO, VACIO, VACIO},
        {VACIO, MAGENTA, MAGENTA, VACIO},
        {MAGENTA, MAGENTA, VACIO, VACIO},
        {VACIO, VACIO, VACIO, VACIO}
    },

    {   //Rotaci�n 1
        {VACIO, MAGENTA, VACIO, VACIO},
        {VACIO, MAGENTA, MAGENTA, VACIO},
        {VACIO, VACIO, MAGENTA, VACIO},
        {VACIO, VACIO, VACIO, VACIO}
    },

    {   //Rotaci�n 2
        {VACIO, VACIO, VACIO, VACIO},
        {VACIO, VACIO, MAGENTA, MAGENTA},
        {VACIO, MAGENTA, MAGENTA, VACIO},
        {VACIO, VACIO, VACIO, VACIO}
    },

    {   //Rotaci�n 3
        {VACIO, VACIO, VACIO, VACIO},
        {VACIO, MAGENTA, VACIO, VACIO},
        {VACIO, MAGENTA, MAGENTA, VACIO},
        {VACIO, VACIO, MAGENTA, VACIO}
    }
},

//T:
{
    { // Rotaci�n 0 (Apuntando arriba)
        {VACIO, VACIO,    VACIO,    VACIO},
        {VACIO, AMARILLO, VACIO,    VACIO},
        {VACIO, AMARILLO, AMARILLO, VACIO},
        {VACIO, AMARILLO, VACIO,    VACIO}
    },
    { // Rotaci�n 1 (Apuntando derecha)
        {VACIO, VACIO,    VACIO,    VACIO},
        {VACIO, VACIO,    VACIO,    VACIO},
        {AMARILLO, AMARILLO, AMARILLO, VACIO},
        {VACIO, AMARILLO, VACIO,    VACIO}
    },
    { // Rotaci�n 2 (Apuntando abajo)
        {VACIO, VACIO,    VACIO,    VACIO},
        {VACIO, AMARILLO, VACIO,    VACIO},
        {AMARILLO, AMARILLO, VACIO,    VACIO},
        {VACIO, AMARILLO, VACIO,    VACIO}
    },
    { // Rotaci�n 3 (Apuntando izquierda)
        {VACIO, VACIO,    VACIO,    VACIO},
        {VACIO, AMARILLO, VACIO,    VACIO},
        {AMARILLO, AMARILLO, AMARILLO, VACIO},
        {VACIO, VACIO,    VACIO,    VACIO}
    }
},
//Z:
{
    {   //Rotacion 0
        {VACIO, VACIO, VACIO, VACIO},
        {VACIO, MARRON, MARRON, VACIO},
        {VACIO, VACIO, MARRON, MARRON},
        {VACIO, VACIO, VACIO, VACIO}
    },

    {   //Rotaci�n 1
        {VACIO, VACIO, VACIO, VACIO},
        {VACIO, VACIO, MARRON, VACIO},
        {VACIO, MARRON, MARRON, VACIO},
        {VACIO, MARRON, VACIO, VACIO}
    },

    {   //Rotaci�n 2
        {VACIO, VACIO, VACIO, VACIO},
        {MARRON, MARRON, VACIO, VACIO},
        {VACIO, MARRON, MARRON, VACIO},
        {VACIO, VACIO, VACIO, VACIO}
    },

    {   //Rotaci�n 3
        {VACIO, VACIO, MARRON, VACIO},
        {VACIO, MARRON, MARRON, VACIO},
        {VACIO, MARRON, VACIO, VACIO},
        {VACIO, VACIO, VACIO, VACIO}
    }
}
};

