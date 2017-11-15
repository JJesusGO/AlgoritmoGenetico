#include  "Binario.h"
#include "Laberinto.h"
#include "Entidad.h"
#include "Random.h"
#include "AG.h"

#include <cmath>

float Evaluar(Individuo &individuo){
    return individuo.GetValorR(0)+individuo.GetValorR(1);
}
float Fitness(Individuo &individuo){
    return fabs(individuo.GetValorObjetivo());
}

int main(){

    Random::SetRandom();
    Random::SetSeed(Seed(4));

    int bitsgenes []= {8,8};
    int tipogenes []= {BINARIO_REAL,BINARIO_REAL};

    AG ag(10,1);

    ag.SetFunciones(Evaluar,Fitness);
    ag.SetProbabilidades(0.6,0.05);
    ag.SetPrioridad(AG_MENOR);

    ag.IniciarPoblacion(bitsgenes,tipogenes,2);
    ag.EvaluarPoblacion();

    int generacion = 0;
    while(ag.IsNextGeneracion(generacion)){
        ag.NextIteracion();
        generacion++;
    }
    ag.MostrarPoblacion();
    return 0;

}
