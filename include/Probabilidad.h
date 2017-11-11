#pragma once
#ifndef PROBABILIDAD_H

#include "Random.h"

class Probabilidad{

    int n;
    float *probabilidades;
    float rango;

    public:

        Probabilidad(float *probabilidades,int n);
        ~Probabilidad();

    public:

        const int Next() const ;

        /*FUNCIONES GETTER USADAS PARA OBTENER LOS DATOS QUE ADMINISTRAN LA CLASE*/
        inline const float GetProbabilidad(int i) const {return probabilidades[i];}
        inline const float GetRango() const {return rango;}

};


#endif
