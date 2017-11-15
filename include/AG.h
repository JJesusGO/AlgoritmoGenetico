#pragma once

#ifndef AG_H
#define AG_H

#include <cstdio>
#include <cstdlib>

#define  AG_MENOR 0
#define  AG_MAYOR 1

#include "Random.h"
#include "Probabilidad.h"
#include "Binario.h"
#include "Individuo.h"



class AG{

    private:

    int     prioridad;
    int     individuos, mejor;
    int     generaciones;
    float   pc, pm;
    int     *parejas,
            parejasn;

    float  (*evaluar)(Individuo &individuo);
    float  (*fitness)(Individuo &individuo);

    Individuo *poblacion;

    public:

    AG(int individuos,int generaciones);
    ~AG();

    public:

    void SetFunciones(float (*evaluar)(Individuo &individuo),
                      float  (*fitness)(Individuo &individuo));
    void SetProbabilidades(float pc,float pm);
    void SetPrioridad(int prioridad);

    inline const int        GetMejorIndex() const {return mejor;}
    inline const Individuo& GetMejor() const {return poblacion[mejor];}
    inline const float      GetProbabilidadCruza() const {return pc;}
    inline const float      GetProbabilidadMutacion() const {return pm;}
    inline const int        GetPrioridad() const {return prioridad;}

    inline Individuo& operator[](int index){return poblacion[index];}

    private:

    void BorrarPoblacion(Individuo *poblacion);

    public:

    void NextIteracion();
    void IniciarPoblacion(int *bitsgenes,int *tipogenes,int genes);
    void MostrarPoblacion();
    void MostrarParejas();
    void EvaluarPoblacion();
    void SeleccionarPoblacion();
    void CruzarPoblacion();
    void MutarPoblacion();

    inline const bool IsNextGeneracion(int generacion) const {return generacion < generaciones;}

};



#endif
