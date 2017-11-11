#pragma once
#ifndef BINARIO_H

#include <cmath>

/*BANDERAS PARA LA DECOIFICACION DE NUMEROS BINARIOS*/
#define BINARIO_ENTERO  0
#define BINARIO_SIGNO   1
#define BINARIO_REAL    2

class Binario{

    int tipo;
    float rmin;
    float rmax;

    public:
    Binario(int tipo = 0,float rmin = 0.0f,float rmax = 1.0f);

    public:
        const float GetNumero(bool *binario,unsigned int bits) const;

};


#endif
