#pragma once
#ifndef ENTIDAD_H
#define ENTIDAD_H

#include "Laberinto.h"
#include "Probabilidad.h"

#define ENTIDAD_PLANTILLAS  9
#define ENTIDAD_CELDAS      4

#define ENTIDAD_ARRIBA      0
#define ENTIDAD_DERECHA     1
#define ENTIDAD_ABAJO       2
#define ENTIDAD_IZQUIERDA   3
#define ENTIDAD_INICIO      4

#include "Individuo.h"
#include "Laberinto.h"

class Entidad{

const static int plantillas[ENTIDAD_PLANTILLAS][ENTIDAD_CELDAS];

Laberinto* laberinto;
Individuo* individuo;

bool **celdas;

bool colision,termino;
int direccion,plantilla,
    pasos,puntuacion;
int x,y;

public:

    Entidad(Laberinto *laberinto,Individuo *individuo);
    ~Entidad();

public:

    void Reiniciar();
    void MostrarLaberinto();
    bool NextMovimiento();

    inline const int GetDireccion() const {return direccion;}
    inline const int GetPlantilla() const {return plantilla;}

    inline const bool IsColision() const {return colision;}
    inline const bool IsTermino() const {return termino;}
    inline const int GetPasos() const {return pasos;}
    inline const int GetPuntuacion() const {return puntuacion;}

    inline const Individuo* GetIndividuo() const {return individuo;}
    inline const Laberinto* GetLaberinto() const {return laberinto;}

};


#endif
