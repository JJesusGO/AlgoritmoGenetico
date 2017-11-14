#pragma once
#ifndef ENTIDAD_H
#define ENTIDAD_H

#include "Laberinto.h"
#include "Probabilidad.h"

class Entidad{

Laberinto* laberinto;
int x,y;

public:
    Entidad(Laberinto *laberinto);

public:
    void Reiniciar();
    void MostrarLaberinto();
    void NextMovimiento();

};


#endif
