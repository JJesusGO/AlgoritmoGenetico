#include <cmath>

#include  "Binario.h"
#include "Laberinto.h"
#include "Entidad.h"
#include "Random.h"
#include "AG.h"

static Laberinto *laberinto = NULL;


float Evaluar(Individuo *individuo){

    Entidad entidad(laberinto,individuo);

    Seed seed(4);
    Random::SetSeed(seed);

    while(entidad.NextMovimiento());

    individuo->SetSeed(seed);

    if(entidad.IsTermino())
        return 100  - (entidad.GetPasos() - entidad.GetPuntuacion());
    return entidad.GetPuntuacion();

}
float Fitness(Individuo *individuo){
    return individuo->GetValorObjetivo();
}

int main(){

    Random::SetRandom();
    Seed seed(4);
    printf("SEED: %s\n\n",seed.GetSeedString().c_str());
    Random::SetSeed(seed);

    int generacion = 0;
    int bitsgenes [ENTIDAD_PLANTILLAS*ENTIDAD_CELDAS];
    int tipogenes [ENTIDAD_PLANTILLAS*ENTIDAD_CELDAS];

    for (int i=0;i<ENTIDAD_PLANTILLAS*ENTIDAD_CELDAS;i++){
        bitsgenes[i] = 8;
        tipogenes[i] = BINARIO_REAL;
    }

    laberinto = new Laberinto("Laberinto1.txt");
    AG ag(1000,75);

    ag.SetFunciones(Evaluar,Fitness);
    ag.SetProbabilidades(0.60,0.02);
    ag.SetPrioridad(AG_MAYOR);

    ag.IniciarPoblacion(bitsgenes,tipogenes,ENTIDAD_PLANTILLAS*ENTIDAD_CELDAS);
    ag.EvaluarPoblacion();

    laberinto->MostrarLaberinto();

    printf("\n\n---------------------------------------------\nCALCULANDO...");

    float valor = 0.0;
    while(ag.IsNextGeneracion(generacion)){
        ag.NextIteracion();
        if(valor < ag.GetMejor().GetValorObjetivo()){
            printf("\n%0.3d - %0.1f",generacion,ag.GetMejor().GetValorObjetivo());
            valor = ag.GetMejor().GetValorObjetivo();
        }
        generacion++;
    }

    printf("\n\n---------------------------------------------\n\n");

    //ag.MostrarPoblacionSimple();
    printf("PROMEDIO : %0.4f\nMEJOR DE LA GENERACION: %0.1f\n",
           ag.GetPromedioObjetivo(),
           ag.GetMejor().GetValorObjetivo());

    printf("\n\n---------------------------------------------\n\n");

    ag.GetMejor().MostrarIndividuo(ag.GetMejorIndex());

    printf("\n\n---------------------------------------------\n\n");

    Entidad entidad(laberinto,ag.GetIndividuo());

    Random::SetSeed(entidad.GetIndividuo()->GetSeed());

    entidad.MostrarLaberinto();
    while(entidad.NextMovimiento())
        entidad.MostrarLaberinto();
    entidad.MostrarLaberinto();

    printf("\nPASOS: %d\nPUNTUACION: %0.1f",entidad.GetPasos(),entidad.GetPuntuacion());

    delete laberinto;

    return 0;

}
