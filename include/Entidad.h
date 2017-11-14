#pragma once
#ifndef ENTIDAD_H
#define ENTIDAD_H

#include "Laberinto.h"
#include "Probabilidad.h"

#define ENTIDAD_PLANTILLAS  9

#define ENTIDAD_ARRIBA      0
#define ENTIDAD_DERECHA     1
#define ENTIDAD_ABAJO       2
#define ENTIDAD_IZQUIERDA   3
#define ENTIDAD_INICIO      4

class Entidad{

const static int plantillas[ENTIDAD_PLANTILLAS][4];

Laberinto* laberinto;
bool colision;
int direccion,plantilla;
int x,y;

public:

    Entidad(Laberinto *laberinto);

public:

    void Reiniciar();
    void MostrarLaberinto();
    bool NextMovimiento();

    inline const int GetDireccion() const {return direccion;}
    inline const int GetPlantilla() const {return plantilla;}

    inline const int IsColision() const {return colision;}

};


#endif
