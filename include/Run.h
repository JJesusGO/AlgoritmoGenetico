#pragma once
#ifndef RUN_H
#define RUN_H

#include "Random.h"
#include "Laberinto.h"
#include "Individuo.h"

class Run{

    Seed seed;
    Individuo individuo;

    public:
        Run();
        Run(Seed seed,Individuo &individuo);

    void MostrarRun(Laberinto *laberinto);

};


#endif
