#pragma once

#ifndef LABERINTO_H
#define LABERINTO_H

#include <string>
#include <cstdio>
#include "Celda.h"

class Laberinto{

    int n,m;
    Celda **celdas;
    int ix,iy;
    int fx,fy;

    public:

    Laberinto();
    Laberinto(std::string archivo);
    ~Laberinto();

    private:


    void CrearMemoria();
    void BorrarMemoria();
    void Actualizar();

    public:

    bool LeerLaberinto(std::string archivo);
    void MostrarLaberinto();
    void MostrarLaberinto(int x,int y,char c);

    public:

        inline const Celda& GetCelda(int x,int y) const {return celdas[y][x];}
        inline const Celda& GetInicio() const {return GetCelda(ix,iy);}
        inline const Celda& GetFinal()  const {return GetCelda(fx,fy);}
        inline const int GetN() const {return n;}
        inline const int GetM() const {return m;}

};



#endif

