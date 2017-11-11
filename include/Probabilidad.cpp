#include "Probabilidad.h"

/*CONTRUCTOR DE LA CLASE PROBABILIDAD, SOLICITA LAS PROBABILIDADES CON LA QUE GENERARA EL INDE RESPECTIVO*/
Probabilidad::Probabilidad(float *probabilidades,int n){

    this->n              = n;
    this->probabilidades = new float[n];

    this->rango = 0.0f;
    for(unsigned int i=0;i<n;i++){
        this->probabilidades[i] = probabilidades[i];
        this->rango += probabilidades[i];
    }

}
/*DESTRUCTOR ENCARGAO DE ELIMINAR TODA LA MEMORIA SOLICITADA PARA EL ALMACENAMIENTO DE VARIABES DINAMICAS*/
Probabilidad::~Probabilidad(){
    delete [] probabilidades;
}

/*FUNCION ENCARGADA DE GENERAR UN INDEX ALEATORIO CON RESPECTO A LA PROBABILIDAD*/
const int Probabilidad::Next() const {

    float posicion = Random::NextDouble(rango);
    float suma = 0.0f;
    for(unsigned int i=0;i<n;i++){
        if(posicion >= suma && posicion < (suma+probabilidades[i]))
            return i;
        suma += probabilidades[i];
    }
    return n-1;

}
