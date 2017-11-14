#include  "Binario.h"
#include "Laberinto.h"
#include "Entidad.h"
#include "Random.h"

int main(){

    Random::SetRandom();
    Random::SetSeed(Seed(4));

    Laberinto lab("Laberinto.txt");
    lab.MostrarLaberinto();

    printf("\n");

    Entidad entidad(&lab);
    entidad.MostrarLaberinto();
    printf("\n");
    while(!entidad.NextMovimiento()){
        entidad.MostrarLaberinto();
        printf("\n");
    }
    entidad.MostrarLaberinto();

    return 0;

}
