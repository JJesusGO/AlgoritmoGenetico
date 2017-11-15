#include "Binario.h"

/*CONSTRUCTOR DE LA CLASE BINARIO QUE PIDE COMO VARIABLES EL TIPO DE CONVERSION Y EL RANGO PARA LOS VALORES REALES*/
Binario::Binario(int tipo,float rmin,float rmax){
    this->tipo = tipo;
    this->rmin = rmin;
    this->rmax = rmax;
}
/*ESTA FUNCION SE ENCARGA DE CONVERTIR LOS VALORES DE BINARIO A TIPO DESCRITO POR LA CLASE*/
const float Binario::GetNumero(const bool *binario,unsigned int bits) const{

    bool signo = tipo & BINARIO_SIGNO;
    bool real  = tipo & BINARIO_REAL;
    const bool *bin = (signo)?binario+1:binario;
    int n = (signo)?bits-1:bits;
    float numero = 0.0f;
    for(unsigned int i=0;i<n;i++)
        numero += bin[i]*pow(2,n-(i+1));
    if(real)
        numero = numero/(pow(2,n)-1)*(rmax-rmin) + rmin;
    if(signo)
        numero *= (binario[0])?-1.0f:1.0f;
    return numero;
}
