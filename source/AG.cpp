#include "AG.h"

/*CONTRUCTOR DE LA CLASE ENCARGADA DE INICIAR AS VARIABLES NECESARIAS PARA SU IMPLEMENTACION*/
AG::AG(int individuos,int generaciones){

    this->generaciones  = generaciones;
    this->individuos    = individuos;
    this->prioridad     = AG_MAYOR;
    this->mejor         = 0;
    this->pm            = 0.01;
    this->pc            = 0.6;

    this->parejasn = (individuos%2==0)?individuos:individuos+1;
    this->parejas    = new int[parejasn];

    this->poblacion     = NULL;
    this->evaluar       = NULL;
    this->fitness       = NULL;

}
/*DESTRUCTOR UTILIZADO PARA ELIMINAR LA MEMORIA DINAMICA SOLICITADA PARA EL ALMACENAMIENTO DE TODOS LOS DATOS*/
AG::~AG(){

    if(parejas != NULL)
        delete [] parejas;

    BorrarPoblacion(poblacion);

}

/*FUNCION UTILIZADA PARA INICIAR LOS PUNTEROS A FUNCIONES*/
void AG::SetFunciones(float (*evaluar)(Individuo *individuo),
                      float  (*fitness)(Individuo *individuo)){

    if(evaluar!=NULL)
        this->evaluar     = evaluar;
    if(fitness!=NULL)
        this->fitness     = fitness;

}

/*CAMBIAR EL VALOR DE LAS PROBABILIDADDES DE CRUZA Y MUTACION*/
void AG::SetProbabilidades(float pc,float pm){
    this->pc = pc;
    this->pm = pm;
}

/*PRIORIDAD DE FUNCIONAMIENTO ES DECIR IMPORTA MAS EL QUE TIENE MAS O MENOS*/
void AG::SetPrioridad(int prioridad){
    this->prioridad = prioridad;
}

/*CALCULAR EL PROMEDIO DEL OBJETIVO DE TODA LA POBLACION*/
const float AG::GetPromedioObjetivo() const{
    float promedio = 0.0f;
    for(unsigned int i=0;i<individuos;i++)
        promedio += poblacion[i].GetValorObjetivo();
    return promedio/individuos;
}

/*INICIALIZACION DE LA POBLACION*/
void AG::IniciarPoblacion(int *bitsgenes,int *tipogenes,int genes){

    poblacion = new Individuo[individuos];
    individuo.SetIndividuo(bitsgenes,tipogenes,genes);

    for(unsigned int i=0;i<individuos;i++){

        //INICIALIZACION DE CADA UNO DE LOS INDIVIDUOS EN LA POBLACION
        poblacion[i].SetIndividuo(bitsgenes,tipogenes,genes);
        //GENERACION ALEATORIA DE LOS GENES
        poblacion[i].SetCromosoma();

    }

}

/*BORRAR UN TIPO DE POBLACION DE INDIVIDUOS*/
void AG::BorrarPoblacion(Individuo* poblacion){

    if(poblacion != NULL){
        delete [] poblacion;
        poblacion = NULL;
    }

}


/*FUNCION QUE MUESTRA LA INFORMACION DE LA POBLACION EN CONSOLA*/
void AG::MostrarPoblacion(){
    for(unsigned int i=0;i<individuos;i++){
        poblacion[i].MostrarIndividuo(i);
        printf("\n\n");
    }
}
/*FUNCION QUE MUESTRA DE MANERA SENCILLA EL VALOR OBJETIVO Y FITNESS DE LA POBLACION*/
void AG::MostrarPoblacionSimple(){
    for(unsigned int i=0;i<individuos;i++)
        printf("INDIVIDUO[%0.3d]-> OBJETIVO: %0.1f - FITNESS: %0.1f \n",i,poblacion[i].GetValorObjetivo(),poblacion[i].GetFitness());


}
/*MOSTRAR LA TABLA DE PAREJAS PARA LA CRUZA*/
void AG::MostrarParejas(){
    for(unsigned int i=0;i<parejasn/2;i++)
        printf("%d - %d\n",parejas[i*2],parejas[i*2+1]);
}

/*EJECUTAR TODAS LAS FUNCIONES DE UNA ITERACION*/
void AG::NextIteracion(){
    SeleccionarPoblacion();
    CruzarPoblacion();
    MutarPoblacion();
    EvaluarPoblacion();
}

/*FUNCION PARA LA EVALUACION DE LA POBLACION*/
void AG::EvaluarPoblacion(){

    //EJECUCION DE LA EVALUACION DE CADA INDIVIDUO
    if(evaluar!=NULL)
        for(unsigned int i=0;i<individuos;i++)
            poblacion[i].SetValorObjetivo(evaluar(&poblacion[i]));

    //EJECUCION DE LA DETERMINACION DEL FITNESS DE CADA INDIVIDUO
    if(fitness!=NULL)
        for(unsigned int i=0;i<individuos;i++)
            poblacion[i].SetFitness(fitness(&poblacion[i]));

    //NORMALIZACION Y DETERMINACION DEL MEJOR INDIVIDUO
    float minimo = poblacion[0].GetFitness();
        for(unsigned int i=0;i<individuos;i++)
            if(poblacion[i].GetFitness() < minimo)
                minimo = poblacion[i].GetFitness();
    minimo = (minimo<0)?-minimo:minimo;
    for(unsigned int i=0;i<individuos;i++)
        poblacion[i].SetFitness(poblacion[i].GetFitness() + minimo);

     //DETERMINACION DE LAS PROBABILIDADES DE CADA INDIVIDUO
    if(prioridad == AG_MAYOR){

        float total = 0.0f;
        for(unsigned int i=0;i<individuos;i++)
            total += poblacion[i].GetFitness();
        for(unsigned int i=0;i<individuos;i++)
            poblacion[i].SetPorcentaje(poblacion[i].GetFitness()/total);

    }
    else {
        float total = 1.0f;
        float mayor = poblacion[0].GetFitness();
        for(unsigned int i=1;i<individuos;i++)
            if(poblacion[i].GetFitness()>mayor)
                mayor = poblacion[i].GetFitness();
        for(unsigned int i=0;i<individuos;i++)
            total += fabs(poblacion[i].GetFitness()-mayor);
        for(unsigned int i=0;i<individuos;i++)
            poblacion[i].SetPorcentaje(fabs(poblacion[i].GetFitness()-mayor)/total);
    }

    for(unsigned int i=0;i<individuos;i++)
        if(poblacion[i].GetPorcentaje() > poblacion[mejor].GetPorcentaje())
            mejor = i;

    if(prioridad == AG_MAYOR)
        if(poblacion[mejor].GetValorObjetivo() >= individuo.GetValorObjetivo())
            individuo.SetIndividuo(poblacion[mejor]);

    if(prioridad == AG_MENOR)
        if(poblacion[mejor].GetValorObjetivo() <= individuo.GetValorObjetivo())
            individuo.SetIndividuo(poblacion[mejor]);


}

/*FUNCION SELECCION Y EJECCUCION DE LA RULETA PARA LA DETERMINACION DE LAS PAREJAS*/
void AG::SeleccionarPoblacion(){


    float *probabilidades = new float[individuos];


    //DETERMINACION DE LAS PROBABILIDADES DE CADA INDIVIDUO
     //DETERMINACION DE LAS PROBABILIDADES DE CADA INDIVIDUO
    for(unsigned int i=0;i<individuos;i++)
        probabilidades[i] = poblacion[i].GetPorcentaje();

    //RULETA DE SELECCION
    Probabilidad probabilidad(probabilidades,individuos);
    for(unsigned int i=0;i<parejasn;i++)
        parejas[i] = probabilidad.Next();


    delete[] probabilidades;

}
/*FUNCION PARA LA CRUZA DE LOS INDIVIDUOS EN PAREJAS*/
void AG::CruzarPoblacion(){

    float probabilidades[] = {pc,1.0f-pc};
    Probabilidad probabilidad(probabilidades,2);

    Individuo *npoblacion = new Individuo[individuos];
    for(unsigned int i=0;i<individuos;i++)
        npoblacion[i].SetIndividuo(poblacion[i]);

    for(unsigned int i=0;i < parejasn/2;i++){

        if(probabilidad.Next()==0){
            int posicion = Random::Next(1,npoblacion[i*2].GetBits()-1);
            npoblacion[i*2].SetIndividuo();
            if( !(i == (parejasn/2-1) && individuos%2!=0) )
                npoblacion[i*2 + 1].SetIndividuo();

            for(unsigned int j=0;j<posicion;j++){
                npoblacion[i*2].SetCromosoma(j,poblacion[parejas[i*2]].GetCromosoma(j));
                if( !(i == (parejasn/2-1) && individuos%2!=0) )
                    npoblacion[i*2+1].SetCromosoma(j,poblacion[parejas[i*2+1]].GetCromosoma(j));
            }
            for(unsigned int j = posicion;j<npoblacion[i*2].GetBits();j++){
                npoblacion[i*2].SetCromosoma(j,poblacion[parejas[i*2+1]].GetCromosoma(j));
                if( !(i == (parejasn/2-1) && individuos%2!=0) )
                    npoblacion[i*2+1].SetCromosoma(j,poblacion[parejas[i*2]].GetCromosoma(j));
            }

        }
        else{
            npoblacion[i*2].SetIndividuo(poblacion[parejas[i]]);
            if( !(i == (parejasn/2-1) && individuos%2!=0) )
                npoblacion[i*2+1].SetIndividuo(poblacion[parejas[i+1]]);
        }
    }

    for(int i=0;i<individuos;i++){
        poblacion[i].SetIndividuo(npoblacion[i]);
        poblacion[i].Actualizar();
    }

    BorrarPoblacion(npoblacion);

}

/*PROCESO DE MUTACION DE BITS DE UN CROMOSOMA*/
void AG::MutarPoblacion(){

    float probabilidades[] = {pm,1-pm};
    Probabilidad probabilidad(probabilidades,sizeof(probabilidades)/sizeof(probabilidades[0]));

    for(unsigned int i=0;i<individuos;i++){
        for(unsigned int j = 0;j<poblacion[i].GetBits();j++)
            if(probabilidad.Next() == 0)
                poblacion[i].InvertirCromosoma(j);
        poblacion[i].Actualizar();
    }



}
