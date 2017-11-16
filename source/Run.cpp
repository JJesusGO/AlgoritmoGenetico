#include "Run.h"

Run::Run(){

}
Run::Run(Seed seed,Individuo &individuo){
    this->seed = seed;
    this->individuo.SetIndividuo(individuo);
}
void Run::MostrarRun(Laberinto *laberinto){

    Entidad entidad(laberinto,&individuo);
    Random::SetSeed(seed);
    while(entidad.NextMovimiento())
        entidad.MostrarLaberinto();

}
